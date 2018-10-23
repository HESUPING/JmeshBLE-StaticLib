add_sources(PLF_2400_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/rst_gen.c
)

target_include_directories(inc_2400
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)  