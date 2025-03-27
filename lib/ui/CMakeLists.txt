add_library(ui ui.c images.c screens.c styles.c 
               ui_image_plant_icon.c ui_image_plant_icon2.c 
               ui_image_water_icon.c  )

# Ensure LVGL is properly linked
target_link_libraries(ui PUBLIC lvgl)

# Ensure the UI library can find LVGL headers
target_include_directories(ui PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/lib/lvgl"
)