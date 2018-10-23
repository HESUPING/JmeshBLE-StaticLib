add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(peripheral)
target_include_directories(usr_inc
INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)