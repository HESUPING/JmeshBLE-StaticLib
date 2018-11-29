/*
 * node_save.h
 *
 *  Created on: 2018-8-20
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_H_
#define FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_H_
#include "node_save_keys.h"
#include "node_save_misc.h"
#include "node_save_model.h"

#define NODE_SAVE_LOG_ENABLE    1
#define NODE_SAVE_DIR_LIST_NUM  128





void node_save_process_next_stage(void);
void node_save_recover(void);
void node_save_mesh_reset(void);


#endif /* FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_H_ */
