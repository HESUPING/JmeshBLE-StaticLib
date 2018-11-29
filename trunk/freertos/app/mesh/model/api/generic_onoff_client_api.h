#ifndef GENERIC_ONOFF_CLIENT__H
#define GENERIC_ONOFF_CLIENT__H

/**
 ****************************************************************************************
 * @addtogroup MESH_MODEL_ONOFF_CLIENT
 * @ingroup  MESH_MODEL_API
 * @brief defines for BLE MESH MODEL API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include <stdint.h>
#include "mesh_model.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** model inst. */
typedef struct
{
    /** The model base of the model. */
    model_client_base_t model;
}generic_onoff_client_t;


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 * @brief     Send a onoff get message to server.
 * @param[in] client        client model pointer.
 * @param[in] msg           message content , should be a pointer of generic_onoff_msg_set_t or generic_onoff_msg_default_set_t.
 * @param[in] msg_length    the length of message size. is sizeof(generic_onoff_msg_set_t) or sizeof(generic_onoff_msg_default_set_t)
 * @param[in] dst_addr      the address of the element you want to set.
 */
void generic_onoff_get_tx(generic_onoff_client_t *client,void *msg , uint8_t msg_length,uint16_t dst_addr);


/**
 * @brief     Send a onoff set message to server.
 * @param[in] client        client model pointer.
 * @param[in] msg           message content , should be a pointer of generic_onoff_msg_set_t or generic_onoff_msg_default_set_t.
 * @param[in] msg_length    the length of message size. is sizeof(generic_onoff_msg_set_t) or sizeof(generic_onoff_msg_default_set_t)
 * @param[in] dst_addr      the address of the element you want to set.
 */
void generic_onoff_set_tx(generic_onoff_client_t *client,void *msg , uint8_t msg_length,uint16_t dst_addr);


/**
 * @brief     Send a onoff set message without acknowledge to server.
 * @param[in] client        client model pointer.
 * @param[in] msg           message content , should be a pointer of generic_onoff_msg_set_t or generic_onoff_msg_default_set_t.
 * @param[in] msg_length    the length of message size. is sizeof(generic_onoff_msg_set_t) or sizeof(generic_onoff_msg_default_set_t)
 * @param[in] dst_addr      the address of the element you want to set.
 */
void generic_onoff_set_unacknowledged_tx(generic_onoff_client_t *client,void *msg , uint8_t msg_length,uint16_t dst_addr);



/// @} MESH_MODEL_ONOFF_CLIENT
#endif


