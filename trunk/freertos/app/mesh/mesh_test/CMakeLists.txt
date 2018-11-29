set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/mesh_app_action.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_iv_update_test.c
${CMAKE_CURRENT_SOURCE_DIR}/mesh_kr_test.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(mesh_uart)
#add_subdirectory(old_test)
