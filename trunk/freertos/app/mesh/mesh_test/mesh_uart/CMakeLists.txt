set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/uart_log_test.c
${CMAKE_CURRENT_SOURCE_DIR}/provisioner_uart_test.c
${CMAKE_CURRENT_SOURCE_DIR}/client_server_uart_test.c
${CMAKE_CURRENT_SOURCE_DIR}/cb_mesh_uart_test_all.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_uart_ctrl.c
${CMAKE_CURRENT_SOURCE_DIR}/unprov_dev_uart_test.c
${CMAKE_CURRENT_SOURCE_DIR}/uart_debug_test.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

