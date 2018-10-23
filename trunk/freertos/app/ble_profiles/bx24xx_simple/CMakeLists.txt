set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/ble_bx2400_simple_s.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

