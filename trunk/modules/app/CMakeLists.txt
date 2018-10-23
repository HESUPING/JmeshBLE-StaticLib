set(SRC
${CMAKE_CURRENT_SOURCE_DIR}/src/app.c
${CMAKE_CURRENT_SOURCE_DIR}/src/app_task.c
${CMAKE_CURRENT_SOURCE_DIR}/src/app_display.c
${CMAKE_CURRENT_SOURCE_DIR}/src/app_sec.c
${CMAKE_CURRENT_SOURCE_DIR}/src/app_ht.c
${CMAKE_CURRENT_SOURCE_DIR}/src/app_dis.c
${CMAKE_CURRENT_SOURCE_DIR}/src/app_batt.c
${CMAKE_CURRENT_SOURCE_DIR}/src/app_hid.c
)

add_sources(USR_SRCS ${SRC})

target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/api
)
