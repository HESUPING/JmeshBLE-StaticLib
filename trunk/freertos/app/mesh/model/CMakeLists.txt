set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/config_client.c
${CMAKE_CURRENT_SOURCE_DIR}/config_server.c
${CMAKE_CURRENT_SOURCE_DIR}/sig_msg.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(api)
add_subdirectory(generics)
add_subdirectory(foundation_models)