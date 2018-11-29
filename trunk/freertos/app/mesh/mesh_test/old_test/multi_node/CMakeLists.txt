set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/mesh_nvds_operation.c
${CMAKE_CURRENT_SOURCE_DIR}/multi_basic_test_client.c
${CMAKE_CURRENT_SOURCE_DIR}/multi_basic_test_server.c
${CMAKE_CURRENT_SOURCE_DIR}/multi_basic_test_common.c

)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

