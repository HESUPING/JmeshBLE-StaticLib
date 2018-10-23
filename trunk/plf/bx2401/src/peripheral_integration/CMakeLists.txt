add_sources(PLF_2401_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/uart/uart_integration.c
${CMAKE_CURRENT_SOURCE_DIR}/dmac/dmac_integration.c
${CMAKE_CURRENT_SOURCE_DIR}/qspi/qspi_integration.c
)

set(INC
${CMAKE_CURRENT_SOURCE_DIR}/uart
${CMAKE_CURRENT_SOURCE_DIR}/dmac
${CMAKE_CURRENT_SOURCE_DIR}/qspi
)

target_include_directories(inc_2401
INTERFACE ${INC}
)