set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/node_save.c
${CMAKE_CURRENT_SOURCE_DIR}/node_save_common.c
${CMAKE_CURRENT_SOURCE_DIR}/node_save_keys.c
${CMAKE_CURRENT_SOURCE_DIR}/node_save_misc.c
${CMAKE_CURRENT_SOURCE_DIR}/node_save_model.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)


