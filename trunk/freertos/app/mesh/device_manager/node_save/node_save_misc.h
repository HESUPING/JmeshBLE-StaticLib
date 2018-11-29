/*
 * node_save_misc.h
 *
 *  Created on: 2018-8-22
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MISC_H_
#define FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MISC_H_


void node_save_misc_provision_now_status(void);
void node_save_misc_mesh_app_have_initialized(void);
void node_save_misc_sequence_number(void);
void node_save_misc_iv_index(void);
void node_recover_misc(void);


void node_save_element_uni_adddr(void);
void node_recover_element_uni_adddr(void);


#endif /* FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MISC_H_ */
