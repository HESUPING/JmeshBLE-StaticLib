set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/generic_onoff_client.c
${CMAKE_CURRENT_SOURCE_DIR}/generic_onoff_server.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)


