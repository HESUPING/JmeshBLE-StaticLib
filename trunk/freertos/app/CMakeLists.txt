set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/task_init.c
${CMAKE_CURRENT_SOURCE_DIR}/os_bridge.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_task.c
${CMAKE_CURRENT_SOURCE_DIR}/ble_task.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_utils.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_connparam_change.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_dis_server.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_template.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_adv.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_scan.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_dis_client.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_advdata_change.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_advintv_change.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_bond_master.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_bond_slave.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_selfie.c
#${CMAKE_CURRENT_SOURCE_DIR}/osapp_mi_scale.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_uart_server.c
#${CMAKE_CURRENT_SOURCE_DIR}/osapp_demo.c
#${CMAKE_CURRENT_SOURCE_DIR}/osapp_mesh.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_1M2M_master.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_1M2M_slave.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_throughput_server.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_throughput_client.c)
add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(mesh)
add_subdirectory(ble_profiles)
add_subdirectory(ble_peripheral)
add_subdirectory(ble_central)
add_subdirectory(ble_broadcaster)
add_subdirectory(ble_observer)
add_subdirectory(ble_main)

