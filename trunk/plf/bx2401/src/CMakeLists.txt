add_subdirectory(arch)
add_subdirectory(jmp_table)
add_subdirectory(peripheral_integration)
add_subdirectory(sleep)
add_subdirectory(sys_integration)
target_include_directories(inc_2401
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/build/ble-full/reg/fw
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc
)