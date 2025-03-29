#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/timer.h"
#include "lib/lvgl/lvgl.h"
#include "lib/ui/ui.h"
#include "include/ili9341_driver.h"


void my_flush(lv_display_t * display, const lv_area_t * area, uint8_t * px_map)
{
    uint16_t * pixel_buffer {(uint16_t *)px_map};
    int32_t row_width = area->x2 - area->x1 + 1;  // Width of the area
    uint8_t data[row_width * 2];                 // 8-bit buffer for SPI

    write_command(0x2A);  // Column Address Set
    // start column
    write_data((area->x1 >> 8) & 0xFF);  // MSB
    write_data(area->x1 & 0xFF);         // LSB
    // end column
    write_data((area->x2 >> 8) & 0xFF);  // MSB
    write_data(area->x2 & 0xFF);         // LSB

    write_command(0x2B);  // Row Address Set
    // start row
    write_data((area->y1 >> 8) & 0xFF);  // MSB
    write_data(area->y1 & 0xFF);         // LSB
    // end row
    write_data((area->y2 >> 8) & 0xFF);  // MSB
    write_data(area->y2 & 0xFF);         // LSB

    write_command(0x2C);  // Memory Write
    
    for (int32_t y = area->y1; y <= area->y2; ++y) 
    {
        // Prepare one row of pixel data
        for (int32_t x = 0; x < row_width; ++x) 
        {
            data[2 * x]     = (pixel_buffer[x] >> 8) & 0xFF;  // High byte (MSB)
            data[2 * x + 1] = pixel_buffer[x] & 0xFF;         // Low byte (LSB)
        }

        // Send the row data
        write_data_buffer(data, sizeof(data));

        // Move to the next row in the pixel buffer
        pixel_buffer += row_width;
    }

    lv_display_flush_ready(display);
}

void setup_screen()
{
    
    lv_init(); // initialize lvgl
    lcd_init(); // initialize lcd screen
    landscape_mode();
    
    constexpr int32_t hor_res {320};
    constexpr int32_t ver_res {240};
    lv_display_t * disp = lv_display_create(hor_res, ver_res); 
    lv_display_set_flush_cb(disp, my_flush);
    static lv_color_t buf[hor_res * ver_res / 10]; // 1/10 size to render 10% of the screen
    lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    // Test screen
    // lv_obj_t *test_screen = lv_obj_create(NULL);
    // lv_obj_t *label = lv_label_create(test_screen);
    // lv_label_set_text(label, "really long test label");
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_style_bg_color(test_screen, lv_color_hex(0xffc9d858), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_scr_load(test_screen);


    ui_init();

}



// need a timer to trigger the ui elements correctly
void init_lvgl_tick() 
{
    hardware_alarm_claim(0);  // Claim alarm 0 for LVGL
    hardware_alarm_set_callback(0, [](uint alarm_num) {
        lv_tick_inc(1);  // Update LVGL tick every 1ms
        hardware_alarm_set_target(alarm_num, make_timeout_time_ms(1));  // Reschedule
    });
    hardware_alarm_set_target(0, make_timeout_time_ms(1));  // First trigger
}


int main()
{
    stdio_init_all();
    // lcd_init();
    setup_screen();

    init_lvgl_tick();

    while (true) 
    {        
        lv_timer_handler();  // Handle LVGL timers

        ui_tick();
    }
}
