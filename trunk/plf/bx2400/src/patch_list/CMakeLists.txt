set(SRC

#${CMAKE_CURRENT_SOURCE_DIR}/patch_test.c
#${CMAKE_CURRENT_SOURCE_DIR}/rf_calib_sw_patch.c
${CMAKE_CURRENT_SOURCE_DIR}/tx_test_end.c
${CMAKE_CURRENT_SOURCE_DIR}/adv_int.c
${CMAKE_CURRENT_SOURCE_DIR}/h4tl_patch.c
${CMAKE_CURRENT_SOURCE_DIR}/set_adv_payload_31Byte_patch.c
${CMAKE_CURRENT_SOURCE_DIR}/prog_latency_patch.c
#${CMAKE_CURRENT_SOURCE_DIR}/patch_list.s
${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_C_COMPILER_ID}/h4tl_patch_asm.s
)

add_sources(PLF_2400_SRCS ${SRC})

target_include_directories(inc_2400
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)