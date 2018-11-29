/*
 * node_save_model.h
 *
 *  Created on: 2018��8��22��
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MODEL_H_
#define FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MODEL_H_
#include "mesh_model.h"

void node_save_bind_appkey(model_base_t *model , uint16_t appkey_idx , uint8_t save_keybuf_index);
void node_save_subscription_list(model_base_t *model , uint8_t save_index);
void node_recover_bind_appkey(void);
void node_recover_subscription_list(void);


#endif /* FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MODEL_H_ */
