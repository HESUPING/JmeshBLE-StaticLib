/*
 * node_save_export.h
 *
 *  Created on: 2018-8-20
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_IMPORT_H_
#define FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_IMPORT_H_
#include "provision_base.h"
#include "mesh_app.h"


/******** MESH_DIR_MISC ********/
//provision_base.c
extern prov_unprov_status_t provision_now_status;
//mesh_env.c
extern uint32_t sequence_number;

extern mesh_elmt_t server_elmts[ELEMENT_NUM];





#endif /* FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_IMPORT_H_ */
