set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/simple_generic_onoff_s.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_app.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_app_hal.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

