#ifndef OS_CALLBACK_H
#define OS_CALLBACK_H
#include"os_time.h"
#include"../driver/jmesh_system.h"
#include"../bearer/adv/jmesh_adv.h"
#include"../jmesh/jmesh_pdu.h"
#include"../jmesh/jmesh_print.h"
#include"../jmesh/jmesh_addr.h"
#include"../jmesh/jmesh_device.h"
#include"../jmesh/jmesh_task.h"
#include"../jmesh/jmesh_features.h"
#include"../jmesh/jmesh_device.h"
#include"../driver/jmesh_ble.h"
#include"../bearer/beacon/jmesh_beacon.h"
#include"../bearer/gatt/jmesh_gatt.h"
#include"../network/jmesh_interface.h"
#include"../network/jmesh_network.h"
#include"../network/jmesh_netkey.h"
#include"../lower/jmesh_segment.h"
#include"../access/jmesh_access.h"
#include"../foundation/state/jmesh_appkey.h"
#include"../foundation/state/jmesh_TTL.h"
#include"../foundation/config/config_client.h"
#include"../foundation/config/config_client_app.h"
#include"../app/app_include.h"
#include"../upper/routing/jmesh_routing.h"
#include"../upper/routing/jmesh_routing_neighbor_table.h"
#include"../upper/routing/jmesh_routing_table.h"
#include"../driver/jmesh_uart.h"
#include"../driver/jmesh_gpio.h"
#include"stdio.h"
#include"../foundation/state/jmesh_state.h"
#include"../driver/jmesh_driver_config.h"
#include"../bearer/provisioning/jmesh_provisioning_server.h"
void os_start_callback(void);
void os_inited_callback(void);
void os_cycle_callback(void);




#endif // OS_CALLBACK_H
