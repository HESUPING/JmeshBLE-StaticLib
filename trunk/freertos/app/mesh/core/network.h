#ifndef NETWORK_H_
#define NETWORK_H_
#include <stdint.h>
//#include "sdk_mesh_config.h"
//#include "sdk_mesh_definitions.h"

#include "bearer.h"
#include "security.h"
#include "mesh_env.h"
#include "lower_transport.h"


/*
 * DEFINES
 ****************************************************************************************
 */
#define IVI_OFFSET 7
#define IVI_MASK 0x80
#define NID_OFFSET 0
#define NID_MASK 0x7f
#define CTL_OFFSET 31
#define CTL_MASK 0x80000000
#define TTL_OFFSET 24
#define TTL_MASK 0x7f000000
#define SEQ_NUM_OFFSET 0
#define SEQ_NUM_MASK 0xffffff
#define SRC_DATA_OFFSET 5
#define ENCRYPTED_DATA_OFFSET 7
#define ACCESS_MSG_NETMIC_SIZE 4
#define CONTROL_MSG_NETMIC_SIZE 8
#define DST_ADDR_SIZE 2
#define SRC_ADDR_SIZE 2
#define NETWORK_PDU_MAX_SIZE 	29 //1+1+3+2+2+16+4 = 29 //1+1+3+2+2+12+8 = 29
#define NETWORK_PAYLOAD_MAX_SIZE (BEARER_BUF_SIZE - ENCRYPTED_DATA_OFFSET - ACCESS_MSG_NETMIC_SIZE -DST_ADDR_SIZE)

/*An unassigned address is an address in which the element of a node has not been configured yet or no
address has been allocated. The unassigned address shall have the value 0x0000 .  <mesh core profile 1.0 /3.4.2.1> */
#define NETWORK_UNASSIGNED_ADDR 0x0000
/*
 * MACROS
 ****************************************************************************************
 */
#define IS_UNICAST_ADDR(addr) (!((addr)&0x8000)&&(addr))
#define IS_UNASSIGNED_ADDR(addr) (!(addr))
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
    uint32_t seq_num:24,
         ttl:7 ,
         ctl:1 ;
}ctl_ttl_seq_num_t;
typedef struct
{
    network_pdu_base_t base;
    TimerHandle_t relay_timer;
    void (*cb)();
}network_tx_pdu_t;




network_pdu_base_t *alloc_network_tx_env(mesh_adv_type_t type);


void network_raw_data_fill(network_pdu_base_t *base,uint8_t *pdu,uint8_t length,uint8_t offset);
void network_pdu_tx(network_pdu_base_t *base,void (*cb)());
void free_lower_rx_buf(network_pdu_base_t *ptr);

//============================
/**
 ****************************************************************************************
 * @brief The network handler receive pdu message.
 *
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 * @param[in] p_param     Pointer to the pdu param.
 *
 ****************************************************************************************
 */
extern void network_pdu_rx(const uint8_t *p_data,uint8_t length,const mesh_rx_params_t * p_param );

/**
 ****************************************************************************************
 * @brief The network receive pdu from gatt,and handler the message.
 *
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 * @param[in] p_param     Pointer to the pdu param.
 *
 ****************************************************************************************
 */
extern void network_pdu_gatt_rx(const uint8_t *p_data,uint8_t length,const mesh_rx_params_t * p_param);
/**
 ****************************************************************************************
 * @brief The network receive pdu from gatt,and handler the message.
 *
 * @param[in] p_data      Pointer to the write data.
 * @param[in] length      The length of write data.
 * @param[in] p_param     Pointer to the pdu param.@ref  struct mesh_rx_params_t
 *
 ****************************************************************************************
 */
extern void network_pdu_gatt_decrypt(const uint8_t *p_data,uint8_t length,const mesh_rx_params_t *p_param);

#endif

