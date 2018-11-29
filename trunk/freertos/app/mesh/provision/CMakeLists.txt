set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/provision_base.c
${CMAKE_CURRENT_SOURCE_DIR}/provisioner.c
${CMAKE_CURRENT_SOURCE_DIR}/unprov_device.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(api)
