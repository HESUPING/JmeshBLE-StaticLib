
set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/mesh_user_main.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)


add_subdirectory(simple_generic_onoff_server)


