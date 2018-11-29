set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/mesh_tools.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(static_mem_manage)
