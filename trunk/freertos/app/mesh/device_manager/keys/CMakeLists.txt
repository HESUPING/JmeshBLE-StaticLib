set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/app_keys_dm.c
${CMAKE_CURRENT_SOURCE_DIR}/device_keys_dm.c
${CMAKE_CURRENT_SOURCE_DIR}/network_keys_dm.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

