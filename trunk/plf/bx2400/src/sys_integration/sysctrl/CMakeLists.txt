add_sources(PLF_2400_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/sysctrl.c
${CMAKE_CURRENT_SOURCE_DIR}/rf_reg_settings_2400.c
${CMAKE_CURRENT_SOURCE_DIR}/io_ctrl.c
)

target_include_directories(inc_2400
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)  