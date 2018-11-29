set(SRC
#${CMAKE_CURRENT_SOURCE_DIR}/aes_ccm_test.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(multi_node)
