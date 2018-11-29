/*
 * unprov_device.h
 *
 *  Created on: 2018-1-22
 *      Author: jiachuang
 */
#ifndef FREERTOS_APP_MESH_PROVISION_UNPROV_DEVICE_H_
#define FREERTOS_APP_MESH_PROVISION_UNPROV_DEVICE_H_
#include "provision_api.h"




void unprovisioned_dev_init(void);
void unprovisioned_dev_reset(void);

extern void unprov_device_init(mesh_prov_evt_cb_t cb);
extern void unprov_device_action_send (mesh_prov_action_type_t type , mesh_prov_evt_param_t param);
extern void unprov_device_config (mesh_prov_config_type_t opcode , mesh_prov_evt_param_t param);


#endif /* FREERTOS_APP_MESH_PROVISION_UNPROV_DEVICE_H_ */

