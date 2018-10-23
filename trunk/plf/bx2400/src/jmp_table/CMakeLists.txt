set(SRC
#${CMAKE_CURRENT_SOURCE_DIR}/Hbeacon.c
${CMAKE_CURRENT_SOURCE_DIR}/jump_table.c
)

add_sources(PLF_2400_SRCS ${SRC})
target_include_directories(inc_2400
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)