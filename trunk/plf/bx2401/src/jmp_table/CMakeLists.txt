set(SRC

${CMAKE_CURRENT_SOURCE_DIR}/jump_table.c
)

add_sources(PLF_2401_SRCS ${SRC})
target_include_directories(inc_2401
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)