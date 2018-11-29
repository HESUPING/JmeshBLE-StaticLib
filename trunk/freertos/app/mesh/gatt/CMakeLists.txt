set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/mesh_gatt_cfg.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_gatt.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_gatt_filter.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_gatt_proxy.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(api)
add_subdirectory(proxy)
add_subdirectory(provisioning)

