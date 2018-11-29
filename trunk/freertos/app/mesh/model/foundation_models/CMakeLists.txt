set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/config_relay.c
${CMAKE_CURRENT_SOURCE_DIR}/config_composition_data.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

