/*
 * access_api.h
 *
 *  Created on: 2018��9��11��
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_CORE_API_ACCESS_API_H_
#define FREERTOS_APP_MESH_CORE_API_ACCESS_API_H_


/**
 ****************************************************************************************
 * @addtogroup MESH_CORE_ACCESS_API
 * @ingroup  MESH_CORE_API
 * @brief defines for BLE MESH CORE API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_model.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** The access message structure. */
typedef struct
{
    /** The opcode of the message. */
    uint16_t opcode;
    /** The message pointer you want to send. */
    const uint8_t * p_buffer;
    /** The callback when message sent. */
    void (*cb)(access_pdu_tx_t *,uint8_t);
    /** The length of the message you want to send. */
    uint16_t length;
} access_message_tx_t;

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 * @brief     Send an access message with a random delay.
 * @param[in] elmt      the pointer of the element which contains the model.
 * @param[in] model     client model pointer.
 * @param[in] p_tx      the message you want send.
 * @param[in] dst_addr  the address of the element you want to set.
 */
void access_model_reply(mesh_elmt_t *elmt,model_base_t *model,access_message_tx_t *p_tx,uint16_t dst_addr);


/**
 * @brief     Send an access message without a random delay.
 * @param[in] elmt      the pointer of the element which contains the model.
 * @param[in] model     client model pointer.
 * @param[in] p_tx      the message you want send.
 * @param[in] dst_addr  the address of the element you want to set.
 */
void access_model_send(mesh_elmt_t *elmt,model_base_t *model,access_message_tx_t *p_tx,uint16_t dst_addr);

/// @} MESH_CORE_ACCESS_API

#endif /* FREERTOS_APP_MESH_CORE_API_ACCESS_API_H_ */
