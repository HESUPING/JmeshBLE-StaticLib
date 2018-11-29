/*
 * uart_debug_test.c
 *
 *  Created on: 2018Äê7ÔÂ14ÈÕ
 *      Author: huichen
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#include "mesh_uart_config.h"
#ifdef OSAPP_UART_LOG_TEST
#include "mesh_uart_ctrl.h"
#ifdef MESH_UART_DEBUG_TEST_CMD
#include "uart_debug_test.h"
#include "config_client.h"
#include "config_server.h"
#include "mesh_definitions.h"
#include "upper_transport.h"
#include "generic_onoff_client.h"
#include "generic_onoff_server.h"
#include "generic_onoff_common.h"
#include "mesh_app_action.h"
#include "client_server_uart_test.h"
#include "plf.h"
#include "stdint.h"
#include "mesh_app.h"
#include "string.h"
#include "mesh_iv_operation.h"
#include "mesh_iv_operation_ex.h"
#include "mesh_iv_update_test.h"
#include "mesh_kr_test.h"


//----------------------------------------------------------------------------------------------------------------
// -----------  define

// -----------  extern function

// -----------  static function

// -----------  static value

//----------------------------------------------------------------------------------------------------------------
/******USER FUNCTION******/

/*********CALLBACKS************/
void config_relay_get_tx_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_relay_get_tx_cb\n");
}
void config_relay_set_tx_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_relay_set_tx_cb\n");
}

void config_composition_data_get_tx_cb(access_pdu_tx_t * param_a,uint8_t param_b)
{
    LOG(3,"config_composition_data_get_tx_cb\n");
}






void mesh_debug_uart_test_rx_callback(uint8_t const *param,uint8_t len)
{
	uint8_t i=0;
	//parse  msg
	LOG(LOG_LVL_INFO,"mesh_debug_uart_test_rx_callback !\n");
	for(i=0;i<len;i++)
	{
		LOG(LOG_LVL_INFO,"0x%02X-",param[i]);
	}

//    //uint16_t uni_addr = param[1] << 8 | param[2];
      uint32_t signal = param[1] ;
//
//    //switch opcode
       switch(param[0])
       {
//       /* case RX_OP_CLIENT_CONFIG_RELAY_Get :
//        {
//            config_relay_get_tx(&config_client.model.base,uni_addr,config_relay_get_tx_cb);
//        }
//            break;
//        case RX_OP_CLIENT_CONFIG_RELAY_Set:
//        {
//            config_relay_param_t relay_para;
//            memcpy(&relay_para , &param[3] , 2);
//            config_relay_set_tx(&config_client.model.base,&relay_para,uni_addr,config_relay_set_tx_cb);
//        }
//        break;*/
       case  RX_OP_IV_UPDATE_TRANSACTION:
       {
          mesh_test_mode_transition_run((mesh_iv_update_signals_t)signal);
        //mesh_debug_uart_test_tx(param,len);
        }
      break;
      case 0xc1 :
       {
           mesh_iv_update_scene_cmd cmd = (mesh_iv_update_scene_cmd)signal;
           iv_update_ivrefresh_scene(cmd);
       }
       break;
       case 0xc2 :
       {
           mesh_kr_update_scene_cmd cmd = (mesh_iv_update_scene_cmd)signal;
           mesh_kr_update_scene_test(cmd);
       }
       break;
    }
	//mesh_debug_uart_test_tx(param,len);
}


void mesh_debug_uart_test_tx(const void *param,uint16_t len)
{
	uart_log_tx_env_t debug;

	if(param)
	{
		debug.cmd = UART_PKTCMD_DEBUG_TX;
		debug.tx_len = len;
		if(debug.tx_len)
		{
			debug.pdata = (uint8_t *)pvPortMalloc(debug.tx_len);
			BX_ASSERT(debug.pdata!=NULL);
			memcpy(debug.pdata,(uint8_t *)(param),debug.tx_len);
		}

		uart_log_send_cmd(debug.cmd,debug.pdata,debug.tx_len);
		if(debug.tx_len) vPortFree(debug.pdata);
	}

	LOG(LOG_LVL_INFO,"mesh_debug_uart_test_tx !\n");
}
//----------------------------------------------------------------------------------------------------------------
#endif /* MESH_UART_DEBUG_TEST_CMD */
#endif /* OSAPP_UART_LOG_TEST */
#endif /* OSAPP_MESH */

