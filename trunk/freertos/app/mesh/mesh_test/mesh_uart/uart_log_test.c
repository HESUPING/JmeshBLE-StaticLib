/*
 * uart_log_test.c
 *
 *  Created on: 2018年4月10日
 *      Author: huichen
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#ifdef OSAPP_UART_LOG_TEST
/******include******/
#include "uart_log_test.h"
#include "app_uart.h"
//#include "uart.h"       // uart definition
//#include "reg_uart.h"   // uart register
//#include "dw_apb_uart_typedef.h"
//#include "field_manipulate.h"
#include "bx_ring_queue.h"


// -----------  define
#define SLAVE_REC_DATA_LEN  (255+2)
#define SLAVE_TX_DATA_LEN  (255+5)
#define UART_STATE_MASK_RX_FINSH  (0x01)
#define UART_STATE_MASK_TX_FINSH  (0x02)

#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK != 1)
//msg len
#define UART_MSG_QUEUE_LENGTH  20
#endif

//send data idx
#define UART_TX_CMD_IDX  1
#define UART_TX_LEN_IDX  2
#define UART_TX_DATA_IDX  3
#define UART_TX_CRC_BASE_IDX  3

#define UART_TX_STATE_CMD_CLR  0x00
// -----------  extern value
TaskHandle_t handler_uart_log_task;

// -----------  static value
static app_uart_inst_t m_uart_log = UART_INSTANCE(0);  /**< UART1 instance. */
static uint8_t m_uart_rec_buf[SLAVE_REC_DATA_LEN];// cmd+len+data  1+1+255
static uint8_t m_uart_tx_buf[SLAVE_TX_DATA_LEN]={0xA5,0x10,0x01,0x31,0x22,0x11};// head+cmd+len+data+crc  1+1++1+255+2

static volatile uint8_t m_uart_state_mask=0;
static uart_log_rx_env_t m_uart_log_rx_env=SERIAL_ST_HEAD;
static uart_log_packet_t m_uart_log_packet=
{
 0
};
static uart_log_tx_env_t m_uart_log_tx_env=
{
	.cmd = 0,
	.pdata = m_uart_tx_buf,
	.tx_len = 0
};
#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK != 1)
//uart msg tx queue
static uart_log_tx_env_t m_msg_queue_buffer[UART_MSG_QUEUE_LENGTH];
static volatile uart_log_msg_queue_t m_msg_queue;
#endif


//uart msg rx  callback  handle
static uartlog_msg_handler_table_t m_rx_cb;

//add rx ring queue
static DEF_RING_QUEUE(log_rxbuf_q,SLAVE_REC_DATA_LEN,uint8_t);
static uint8_t m_log_rx_ring=0;
// -----------  static function
static crc_func_t crc_func = (crc_func_t)0x18d;//调用rom中固化函数

static void uart_log_read_finish(void *parma,uint8_t i);
static void uart_log_write_finish(void *parma,uint8_t i);
static uart_log_rx_fifo_st_t uart_log_read_state(void);
static void uart_log_read(void *parma,uint8_t len);
static void uart_log_write(void *parma,uint16_t len);
static void uart_log_packet_rx_ok(void);
static void uart_log_rx_parser(void);
static void app_uart_log_module_init(void);
#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK == 1)
static void uart_log_send_state_set(uint8_t state);
static uint8_t uart_log_send_state_get(void);
#endif
static void uart_log_tx_parser(void);

#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK == 0)
//uart msg queue
static void uart_log_msg_init(void);
static void uart_log_msg_send(uint8_t cmd,const void *parma,uint16_t len);
static void uart_log_msg_receive(void);
static void tools_queue_check_full(void);
static uint8_t tools_queue_is_full(void);
static uint8_t tools_circular_add(uint8_t x, uint8_t idx);
static uint8_t tools_circular_diff(uint8_t rear, uint8_t front);
static void tools_receive_data(void);
#endif
/******USER FUNCTION******/
static void uart_log_read_finish(void *parma,uint8_t i)
{
//	m_uart_state_mask |= UART_STATE_MASK_RX_FINSH;
	bx_enqueue(&log_rxbuf_q,&m_log_rx_ring);
	app_uart_read(&m_uart_log.inst,(uint8_t*)(&m_log_rx_ring),1,uart_log_read_finish,NULL);
}

static void uart_log_write_finish(void *parma,uint8_t i)
{
	m_uart_state_mask |= UART_STATE_MASK_TX_FINSH;
}

static uart_log_rx_fifo_st_t uart_log_read_state(void)
{
	uint8_t rx_st = (uint8_t)Receiver_Empty;

	//rx_st = FIELD_RD(m_uart_log.reg, LSR, UART_DR);

	if(bx_ring_queue_empty(&log_rxbuf_q))	rx_st = Receiver_Empty;
	else									rx_st = Receiver_Ready;

	return (uart_log_rx_fifo_st_t)(rx_st);
}

static void uart_log_read(void *parma,uint8_t len)
{
	// clear rx flag
//	m_uart_state_mask &= ~UART_STATE_MASK_RX_FINSH;
	// rx
//	app_uart_read(&m_uart_log.inst,parma,len,uart_log_read_finish,NULL);
	// wait finsh
//	while(!(m_uart_state_mask&UART_STATE_MASK_RX_FINSH));
	uint8_t maxsize = bx_ring_queue_amount(&log_rxbuf_q);

	while(maxsize < len) maxsize = bx_ring_queue_amount(&log_rxbuf_q);//wait queue

	for(uint8_t i=0;i<len;i++)
	{
		taskENTER_CRITICAL();
		uint8_t *data = bx_dequeue(&log_rxbuf_q);
		taskEXIT_CRITICAL();
		((uint8_t *)parma)[i] = *data;
	}
}

static void uart_log_write(void *parma,uint16_t len)
{
	// clear tx flag
	m_uart_state_mask &= ~UART_STATE_MASK_TX_FINSH;
	// tx
	app_uart_write(&m_uart_log.inst,parma,len,uart_log_write_finish,NULL);
	// wait finsh
	while(!(m_uart_state_mask&UART_STATE_MASK_TX_FINSH));
}

void uart_log_rx_callback_register(uint8_t id,uartlog_msg_handler_t callback)
{
	switch(id)
	{
	case UART_PKTCMD_CLIENT_RX :  //0x91 //Config client set message
		{
			m_rx_cb.cfg_client_cb = callback;
		}
		break;
	case UART_PKTCMD_PROVISIONER_RX :  //0x92 //Provisioner Set
		{
			m_rx_cb.provisoner_cb = callback;
		}
		break;
	case UART_PKTCMD_UNPROV_DEV_RX :  //0x93 //Unprov device Set
		{
			m_rx_cb.unprov_dev_cb = callback;
		}
		break;
	case UART_PKTCMD_DEBUG_RX      :  //0xf2 //debug set message
		{
			m_rx_cb.debug_cb = callback;
		}
		break;
	default:
		break;
	}
}

// 串口 数据帧 解析正确后 执行
static void uart_log_packet_rx_ok(void)
{
	switch(m_uart_log_packet.cmd)
	{
	case UART_PKTCMD_CLIENT_RX :  //0x91 //Config client set message
		{
			if(m_rx_cb.cfg_client_cb != NULL)
			{
				m_rx_cb.cfg_client_cb(m_uart_log_packet.pdata,m_uart_log_packet.data_len);
			}
		}
		break;
	case UART_PKTCMD_PROVISIONER_RX :  //0x92 //Provisioner Set
		{
			if(m_rx_cb.provisoner_cb != NULL)
			{
				m_rx_cb.provisoner_cb(m_uart_log_packet.pdata,m_uart_log_packet.data_len);
			}
		}
		break;
	case UART_PKTCMD_UNPROV_DEV_RX :  //0x93 //Unprov device Set
		{
			if(m_rx_cb.unprov_dev_cb != NULL)
			{
				m_rx_cb.unprov_dev_cb(m_uart_log_packet.pdata,m_uart_log_packet.data_len);
			}
		}
		break;
	case UART_PKTCMD_DEBUG_RX      :  //0xf2 //debug set message
		{
			if(m_rx_cb.debug_cb != NULL)
			{
				m_rx_cb.debug_cb(m_uart_log_packet.pdata,m_uart_log_packet.data_len);
			}
		}
		break;
	default:
		break;
	}

	//uart_log_send_cmd((m_uart_log_packet.cmd-0x80),m_uart_log_packet.pdata,m_uart_log_packet.data_len);
	//UART_TEST_LOG(3,"uart_log_packet_rx_ok cmd: %x\n",m_uart_log_packet.cmd);
}


//crc_func()
// 串口 数据帧 解析
static void uart_log_rx_parser(void)
{
    while (uart_log_read_state()==Receiver_Ready)
    {
		switch (m_uart_log_rx_env)
		 {
		 case SERIAL_ST_HEAD :
		   {
			 m_uart_log_packet.rx_len = 1;
			 uart_log_read(m_uart_rec_buf,m_uart_log_packet.rx_len);

			 if( m_uart_rec_buf[0] == UART_LOG_PACKET_HEAD)
			 {
				 // next state
				 m_uart_log_rx_env = SERIAL_ST_CMD;
			 }

//			 LOG(3,"SERIAL_ST_HEAD : %d\n",m_uart_log_packet.rx_len);
		   }
		   break;
		 case SERIAL_ST_CMD :
		   {
			 m_uart_log_packet.rx_len = 1;
			 uart_log_read(m_uart_rec_buf,m_uart_log_packet.rx_len);

			 m_uart_log_packet.cmd = m_uart_rec_buf[0];
			 // next state
			 m_uart_log_rx_env = SERIAL_ST_LEN;

//			 LOG(3,"SERIAL_ST_CMD : %d\n",m_uart_log_packet.rx_len);
		   }
		   break;
		 case SERIAL_ST_LEN :
		   {
			 m_uart_log_packet.rx_len = 1;
			 uart_log_read((m_uart_rec_buf+1),m_uart_log_packet.rx_len);

			 m_uart_log_packet.data_len = m_uart_rec_buf[1];
			 m_uart_log_packet.rx_len = m_uart_rec_buf[1];
			 // next state
			 m_uart_log_rx_env = SERIAL_ST_DATA;

//			 LOG(3,"SERIAL_ST_LEN : %d\n",m_uart_log_packet.rx_len);
		   }
		   break;
		 case SERIAL_ST_DATA :
		   {
			 uart_log_read((m_uart_rec_buf+2),m_uart_log_packet.rx_len);
			 m_uart_log_packet.pdata = m_uart_rec_buf+2;
			 // next state
			 m_uart_log_rx_env = SERIAL_ST_CHECK;

//			 LOG(3,"SERIAL_ST_DATA : %d\n",m_uart_log_packet.rx_len);
		   }
		   break;
		 case SERIAL_ST_CHECK :
		   {
			 m_uart_log_packet.rx_len = 2;
			 uart_log_read((uint8_t *)&m_uart_log_packet.crc,m_uart_log_packet.rx_len);

#if (defined UART_LOG_PKT_CRC_SET) && (UART_LOG_PKT_CRC_SET == 1)
			 uint16_t crc_check=0;
			 //crc check  crc16ccitt
			 crc_check = crc_func(0,m_uart_rec_buf,(m_uart_log_packet.data_len+2));
			 if(crc_check == m_uart_log_packet.crc)
			 {
				 uart_log_packet_rx_ok();
			 }
#else
			 uart_log_packet_rx_ok();
#endif
			 // next state
			 m_uart_log_rx_env = SERIAL_ST_HEAD;

//			 LOG(3,"SERIAL_ST_CHECK : %d\n",m_uart_log_packet.rx_len);
		   }
		   break;
		 default:
		   {
			 m_uart_log_rx_env = SERIAL_ST_HEAD;
		   }
		   break;
		 }
    };
}

//uart1 log init
static void app_uart_log_module_init(void)
{
	m_uart_log.param.baud_rate = UART_BAUDRATE_2000000;
	m_uart_log.param.rx_pin_no = 13;
	m_uart_log.param.tx_pin_no = 12;
	m_uart_log.param.tx_dma = 1;
	m_uart_log.param.rx_dma = 1;

    app_uart_init(&m_uart_log.inst);

	m_uart_log_tx_env.pdata = m_uart_tx_buf;

	app_uart_read(&m_uart_log.inst,(uint8_t*)(&m_log_rx_ring),1,uart_log_read_finish,NULL);
//	LOG(3,"app_uart_log_module_init()");
}

void uart_log_task(void *params)
{
	//static uint32_t uart_log_task_tick_test=0;
//	LOG(3,"uart_log_task start!\n");
    while(1)
    {
#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK != 1)
    	uart_log_msg_init();
#endif
    	app_uart_log_module_init();//uart1 log init
        vTaskDelay(5);//delay 100ms
        while(1)
        {
        	vTaskDelay(1);//delay 20ms
        	uart_log_tx_parser();
   		    //LOG(3,"uart_log_task running:  %d \n",uart_log_task_tick_test++);
   		    //stk_chk_dbg();
        	uart_log_rx_parser();
        }
    }
}



//
static void uart_log_tx_parser(void)
{
#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK == 1)
	if(uart_log_send_state_get() != UART_TX_STATE_CMD_CLR)
	{
		uint16_t crc_idx = 0;
		uint16_t crc_check = 0;

		//1. update crc len
		m_uart_log_tx_env.tx_len =(uint16_t)m_uart_log_tx_env.pdata[UART_TX_LEN_IDX] + 2;//cmd(1)+len(1)+data
		//2. crc check  crc16ccitt
		crc_check = crc_func(0,(m_uart_log_tx_env.pdata+UART_TX_CMD_IDX),m_uart_log_tx_env.tx_len);
		//3. updata  crc to  tx data
		crc_idx = (uint16_t)m_uart_log_tx_env.pdata[UART_TX_LEN_IDX] + UART_TX_CRC_BASE_IDX;
		memcpy((m_uart_log_tx_env.pdata+crc_idx),(uint8_t *)&crc_check,2);
		//4. update send len
		m_uart_log_tx_env.tx_len += 3;//crc (2) + head(1)
		//5. send
    	uart_log_write(m_uart_log_tx_env.pdata,m_uart_log_tx_env.tx_len);

    	uart_log_send_state_set(UART_TX_STATE_CMD_CLR);
	}
#else
		uart_log_msg_receive();
#endif/* UART_LOG_CFG_SEND_BLOCK */
}

#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK == 1)
static void uart_log_send_state_set(uint8_t state)
{
	m_uart_log_tx_env.cmd = state;
}

static uint8_t uart_log_send_state_get()
{
	return m_uart_log_tx_env.cmd;
}
#endif/* UART_LOG_CFG_SEND_BLOCK */

void uart_log_send_cmd(uint8_t cmd,const void *parma,uint16_t len)
{
#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK != 1)
	uart_log_msg_init();//预防 queue还没有初始化就进行了操作
#endif

	switch(cmd)
	{
	case UART_PKTCMD_LOG_OUT_TX      :// 0x10 //LOG out
	case UART_PKTCMD_CLIENT_TX 	     :// 0x11 //Config client out message
	case UART_PKTCMD_PROVISIONER_TX  :// 0x12 //Provisioner out message
	case UART_PKTCMD_UNPROV_DEV_TX   :// 0x13 //Unprov device out message
	case UART_PKTCMD_DEBUG_TX   	 :// 0xf1  //debug out message
		{
#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK == 1)
			// set flag
			uart_log_send_state_set(cmd);
			// upadta cmd
			m_uart_log_tx_env.pdata[UART_TX_CMD_IDX] = cmd;
			// update len
			m_uart_log_tx_env.pdata[UART_TX_LEN_IDX] = len;
			// update data
			memcpy((m_uart_log_tx_env.pdata+UART_TX_DATA_IDX),(uint8_t *)parma,m_uart_log_tx_env.pdata[UART_TX_LEN_IDX]);
#else
			uart_log_msg_send(cmd,(uint8_t *)parma,len);
#endif/* UART_LOG_CFG_SEND_BLOCK*/
		}
		break;
	default:break;
	}
}

void uart_log_printf(int8_t level, const char * format, ...)
{
#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK != 1)
	uart_log_msg_init();//预防 queue还没有初始化就进行了操作
#endif

	char *sprintf_buffer = (char *)pvPortMalloc(100);
	uint16_t len=1;

	BX_ASSERT(sprintf_buffer!=NULL);

    va_list args;
    va_start(args,format);

    len += vsprintf((sprintf_buffer+1),format,args);
	sprintf_buffer[0]=level;
	uart_log_send_cmd(UART_PKTCMD_LOG_OUT_TX,(uint8_t *)sprintf_buffer,len);

	if(sprintf_buffer) vPortFree(sprintf_buffer);

    va_end(args);
}

#if (defined UART_LOG_CFG_SEND_BLOCK) && (UART_LOG_CFG_SEND_BLOCK != 1)
static void uart_log_msg_init(void)
{
	if(m_msg_queue.is_init == task_noinit)
	{
		m_msg_queue.front = 0;
		m_msg_queue.rear = 0;
		m_msg_queue.maxlen = UART_MSG_QUEUE_LENGTH;
		m_msg_queue.buffer = m_msg_queue_buffer;
		m_msg_queue.block = isunblock;
		m_msg_queue.is_init = task_init;

		LOG(3,"uart_log_msg_init !\n");
	}
}
static void uart_log_msg_send(uint8_t cmd,const void *parma,uint16_t len)
{
taskENTER_CRITICAL();
	if (tools_queue_is_full())// queue is full
	{
		if(m_msg_queue.block == isunblock)
		{
			m_msg_queue.block = isblock;
			//1. msg  data
			volatile uart_log_tx_env_t *pmsg = (m_msg_queue.buffer+m_msg_queue.rear);

			pmsg->cmd = cmd;
			pmsg->tx_len = len;

			if(len)
			{
				pmsg->pdata = (uint8_t *)pvPortMalloc(len*sizeof(uint8_t));
				BX_ASSERT(pmsg->pdata!=NULL);
				memcpy(pmsg->pdata,(uint8_t *)parma,len);
			}
			//2. check full
			tools_queue_check_full();
			//3。 update rear
			m_msg_queue.rear = tools_circular_add(m_msg_queue.rear,1);
			m_msg_queue.block = isunblock;
		}
	}
	else//queue is not full
	{
		//1. msg  data
		volatile uart_log_tx_env_t *pmsg = (m_msg_queue.buffer+m_msg_queue.rear);

		pmsg->cmd = cmd;
		pmsg->tx_len = len;

		if(len)
		{
			pmsg->pdata = (uint8_t *)pvPortMalloc(len*sizeof(uint8_t));
			BX_ASSERT(pmsg->pdata!=NULL);
			memcpy(pmsg->pdata,(uint8_t *)parma,len);
		}
		//2. check full
		tools_queue_check_full();
		//3。 update rear
		m_msg_queue.rear = tools_circular_add(m_msg_queue.rear,1);
	}
taskEXIT_CRITICAL();
}

static void uart_log_msg_receive(void)
{
	taskENTER_CRITICAL();
	if((m_msg_queue.block == isunblock)&&(m_msg_queue.rear != m_msg_queue.front))
	{
		m_msg_queue.block = isblock;
        //calculate how many bytes can be sent
        uint8_t diff = tools_circular_diff(m_msg_queue.rear,m_msg_queue.front);
        taskEXIT_CRITICAL();

        while(diff)
        {
        	//receive data
        	tools_receive_data();
        	diff--;
        }

        taskENTER_CRITICAL();
        m_msg_queue.block = isunblock;
        taskEXIT_CRITICAL();
	}
	else
	{
		taskEXIT_CRITICAL();
	}
}
static void tools_queue_check_full(void)
{
    if( (m_msg_queue.maxlen-1) == tools_circular_diff(m_msg_queue.rear,m_msg_queue.front))
    {
        //updata front
    	if(m_msg_queue.buffer[m_msg_queue.front].pdata) vPortFree(m_msg_queue.buffer[m_msg_queue.front].pdata);
    	m_msg_queue.front = tools_circular_add(m_msg_queue.front,1);
    }
}
static uint8_t tools_queue_is_full(void)
{
	uint8_t st = 0;
    if((m_msg_queue.maxlen-1) == tools_circular_diff(m_msg_queue.rear,m_msg_queue.front))
    {
    	st = 1;
    }
    return st;
}
static uint8_t tools_circular_add(uint8_t x, uint8_t idx)
{
  uint8_t sum = x + idx;

  sum = sum % m_msg_queue.maxlen;

  return sum;
}
static uint8_t tools_circular_diff(uint8_t rear, uint8_t front)
{
  if (rear >= front)
  {
    return (rear - front);
  }
  else
  {
    return ((m_msg_queue.maxlen - front) + rear);
  }
}

static void tools_receive_data(void)
{
/// <0>msg queue dequeue

	volatile uart_log_tx_env_t *pmsg = (m_msg_queue.buffer+m_msg_queue.front);
	uint16_t crc_idx = 0;
	uint16_t crc_check = 0;

	//msg send
/// <1>  updata data
	// upadta cmd
	m_uart_log_tx_env.pdata[UART_TX_CMD_IDX] = pmsg->cmd;
	// update len
	m_uart_log_tx_env.pdata[UART_TX_LEN_IDX] = pmsg->tx_len;
	// update data
	memcpy((m_uart_log_tx_env.pdata+UART_TX_DATA_IDX),(uint8_t *)pmsg->pdata,m_uart_log_tx_env.pdata[UART_TX_LEN_IDX]);
/// <2> crc data
	//1. update crc len
	m_uart_log_tx_env.tx_len =(uint16_t)m_uart_log_tx_env.pdata[UART_TX_LEN_IDX] + 2;//cmd(1)+len(1)+data
	//2. crc check  crc16ccitt
	crc_check = crc_func(0,(m_uart_log_tx_env.pdata+UART_TX_CMD_IDX),m_uart_log_tx_env.tx_len);
	//3. updata  crc to  tx data
	crc_idx = (uint16_t)m_uart_log_tx_env.pdata[UART_TX_LEN_IDX] + UART_TX_CRC_BASE_IDX;
	memcpy((m_uart_log_tx_env.pdata+crc_idx),(uint8_t *)&crc_check,2);
	//4. update send len
	m_uart_log_tx_env.tx_len += 3;//crc (2) + head(1)
	//5. send
	uart_log_write(m_uart_log_tx_env.pdata,m_uart_log_tx_env.tx_len);

/// <3>msg queue     //updata front

	if(pmsg->pdata) vPortFree(pmsg->pdata);
	m_msg_queue.front = tools_circular_add(m_msg_queue.front,1);
}
#endif/* UART_LOG_CFG_SEND_BLOCK  false*/
#endif/* OSAPP_UART_LOG_TEST */
#endif/* OSAPP_MESH */
