# Automatically include all .c files in the current directory
file(GLOB UI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# Add the library with all .c files
add_library(ui ${UI_SOURCES})

# Ensure LVGL is properly linked
target_link_libraries(ui PUBLIC lvgl)

# Ensure the UI library can find LVGL headers
target_include_directories(ui PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/lib"
)