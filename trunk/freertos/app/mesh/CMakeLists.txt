set(SRC
#${CMAKE_CURRENT_SOURCE_DIR}/test.c
)

add_sources(USR_SRCS ${SRC})
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)


#add_subdirectory(mesh_test)
add_subdirectory(provision)
add_subdirectory(model)
add_subdirectory(gatt)
add_subdirectory(core)
add_subdirectory(tools)
add_subdirectory(examples)
add_subdirectory(device_manager)

if(CMAKE_C_COMPILER_ID STREQUAL ARMCC)
aux_source_directory(./core/ LIBSRC)
aux_source_directory(./provision/ LIBSRC)
 
add_library(mesh_static STATIC ${LIBSRC})

set_target_properties(mesh_static PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/libmesh/
)

target_link_libraries(mesh_static 
PUBLIC  fw_inc usr_inc inc_2400)

add_custom_command(TARGET mesh_static POST_BUILD 
COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/output/libmesh/libmesh_static.a ${PROJECT_SOURCE_DIR}/freertos/app/mesh/lib/libmesh_static.lib)

endif()