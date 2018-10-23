set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/src/display.c
${CMAKE_CURRENT_SOURCE_DIR}/src/display_task.c
)
add_sources(ROM_2400_SRCS ${SRC})

target_include_directories(fw_inc 
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/api
)