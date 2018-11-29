set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/generic_common.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(generic_default_transition_time)
add_subdirectory(generic_onoff)
add_subdirectory(generic_level)