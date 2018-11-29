set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/access.c
${CMAKE_CURRENT_SOURCE_DIR}/beacon.c
${CMAKE_CURRENT_SOURCE_DIR}/bearer.c
${CMAKE_CURRENT_SOURCE_DIR}/lower_transport.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_env.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_iv_operation.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_kr_comm.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_kr_client.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_kr_server.c
${CMAKE_CURRENT_SOURCE_DIR}/network.c
${CMAKE_CURRENT_SOURCE_DIR}/osapp_mesh.c
${CMAKE_CURRENT_SOURCE_DIR}/security.c
${CMAKE_CURRENT_SOURCE_DIR}/upper_transport.c
${CMAKE_CURRENT_SOURCE_DIR}/virt_addr_mngt.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_stack_init.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_node_base.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(api)
