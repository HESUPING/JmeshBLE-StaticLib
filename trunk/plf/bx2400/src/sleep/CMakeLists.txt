set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/sys_sleep.c
${CMAKE_CURRENT_SOURCE_DIR}/sys_sleep_ram.c
)

add_sources(PLF_2400_SRCS ${SRC})

target_include_directories(inc_2400
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)