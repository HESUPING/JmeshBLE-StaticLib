/*
 * node_save_macro.h
 *
 *  Created on: 2018-8-20
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MACRO_H_
#define FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MACRO_H_

#include "node_save_import.h"


#define MESH_SAVE_ERROR  0xFF


//FILESIZE
#define MESH_SIZE_PROVISION_NOW_STATUS          sizeof(provision_now_status)
#define MESH_SIZE_SEQUENCE_NUMBER               sizeof(sequence_number)
#define MESH_SIZE_IV_INDEX                      sizeof(uint32_t)
#define MESH_SIZE_UNI_ADDR                      sizeof(uint16_t)
#define MESH_SIZE_NETKEYLIST                    sizeof(net_key_nodesave_t)
#define MESH_SIZE_APPKEYLIST                    sizeof(app_key_nodesave_t)
#define MESH_SIZE_DEVKEYLIST                    sizeof(dev_key_nodesave_t)
#define MESH_SIZE_PUBLISH_STATE                 sizeof(model_publish_state_t)
#define MESH_SIZE_SUBSCRIPTION_LIST             sizeof(mesh_addr_t)
#define MESH_SIZE_BOUND_KEY                     sizeof(uint16_t)


//FOLDER
//MESHDIR1_dir1name
//MESHDIR2_dir1name_dir2name
//MESHDIR3_dir1name_dir2name_dir3name
#define MESHDIR1_MISC                               0x01
#define MESHDIR1_KEYS                               0x02
#define MESHDIR1_ELMT_MIN                           0x03
#define MESHDIR1_ELMT_MAX                           (MESHDIR1_ELMT_MIN + SERVER_ELEMENT_NUM)
#define MESHDIR2_KEYS_NETKEYLIST                    0x01
#define MESHDIR2_KEYS_APPKEYLIST                    0x02
#define MESHDIR2_KEYS_DEVKEYLIST                    0x03
#define MESHDIR3_ELMTX_MODELX_SUBSCRIPTION_LIST     0x01
#define MESHDIR3_ELMTX_MODELX_BOUNDKEY_LIST         0x02


//FILE
//MESHFILE1_dir1name_filename
//MESHFILE2_dir1name_dir2name_filename
#define MESHFILE1_MISC_PROVISION_NOW_STATUS         0x00
#define MESHFILE1_MISC_SEQUENCE_NUMBER              0x01
#define MESHFILE1_MISC_IV_INDEX                     0x02
#define MESHFILE1_ELMT_UNI_ADDR                     0x00
#define MESHFILE2_ELMT_MODEL_PUBLISH_STATE          0x00












#endif /* FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_MACRO_H_ */
