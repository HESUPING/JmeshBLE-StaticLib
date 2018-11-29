set(SRC
#${CMAKE_CURRENT_SOURCE_DIR}/XXXXXX.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(api)
add_subdirectory(keys)
add_subdirectory(node_save)