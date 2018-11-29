/*
 * node_save_keys.h
 *
 *  Created on: 2018-8-22
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_KEYS_H_
#define FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_KEYS_H_
#include "mesh_model.h"


void node_save_app_key_add(app_key_t *buf,uint8_t save_index);
void node_save_net_key_add(net_key_t *buf,uint8_t save_index);
void node_save_dev_key_add(dev_key_t *buf,uint8_t save_index);

void node_save_app_key_recover(void);
void node_save_net_key_recover(void);
void node_save_dev_key_recover(void);

void node_save_app_key_delete(uint8_t save_index);
void node_save_net_key_delete(uint8_t save_index);
void node_save_dev_key_delete(uint8_t save_index);


#endif /* FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_KEYS_H_ */
