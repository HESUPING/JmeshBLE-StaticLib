add_sources(PLF_2401_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/modem.c
)

target_include_directories(inc_2401
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)  