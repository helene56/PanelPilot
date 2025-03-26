#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/timer.h"
#include "lib/lvgl/lvgl.h"
#include "lib/ui/ui.h"
// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_D_C  22 // data selection, command: 0, display data: 1
#define PIN_RST  21
// todo:
// 1. include lvgl and eez studio ui
// 2. initialize ui from eez studio an initialize lvgl, in main loop periodically call lv_timer_handler and ui_tick.


void write_command(uint8_t cmd) {
    gpio_put(PIN_D_C, 0);  // Command mode
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(PIN_CS, 1);
    sleep_ms(1);
}

void write_data(uint8_t data) {
    gpio_put(PIN_D_C, 1);  // Data mode
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &data, 1);
    gpio_put(PIN_CS, 1);
    sleep_ms(1);
}

void write_data_buffer(uint8_t *data, size_t length) 
{
    gpio_put(PIN_D_C, 1);  // Data mode
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, data, length);
    gpio_put(PIN_CS, 1);
}


void lcd_reset() 
{
    gpio_put(PIN_RST, 0);
    sleep_ms(10);
    gpio_put(PIN_RST, 1);
    sleep_ms(120);
}

void fill_screen(uint16_t color) 
{
    uint8_t data[320 * 2];  // Buffer for 320 pixels (each pixel = 2 bytes in 16-bit RGB565 format)
    
    for (int i = 0; i < 320; i++) 
    {
        data[2 * i] = (color >> 8) & 0xFF;  // High byte
        data[2 * i + 1] = color & 0xFF;     // Low byte
    }

    write_command(0x2A);  // Column Address Set
    write_data(0x00); write_data(0x00);  // Start column (0)
    write_data(0x00); write_data(0xEF);  // End column (239)

    write_command(0x2B);  // Row Address Set
    write_data(0x00); write_data(0x00);  // Start row (0)
    write_data(0x01); write_data(0x3F);  // End row (319)

    write_command(0x2C);  // Memory Write

    // Send pixel data in chunks
    for (int y = 0; y < 240; y++) 
    {
        write_data_buffer(data, sizeof(data));  // Write 320 pixels at once
    }
}


void lcd_init() {
    // Configure SPI and GPIOs
    spi_init(SPI_PORT, 63 * 1000 * 1000);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS, GPIO_FUNC_SIO);  // CS pin is typically controlled manually
    // gpio_init(PIN_CS);
    gpio_init(PIN_D_C);
    gpio_init(PIN_RST);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_set_dir(PIN_D_C, GPIO_OUT);
    gpio_set_dir(PIN_RST, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    
    lcd_reset();

    // Initialize ILI9341
    write_command(0xEF);
    write_data(0x03);
    write_data(0x80);
    write_data(0x02);

    write_command(0xCF);
    write_data(0x00);
    write_data(0xC1);
    write_data(0x30);

    write_command(0xED);
    write_data(0x64);
    write_data(0x03);
    write_data(0x12);
    write_data(0x81);

    write_command(0xE8);
    write_data(0x85);
    write_data(0x00);
    write_data(0x78);

    write_command(0xCB);
    write_data(0x39);
    write_data(0x2C);
    write_data(0x00);
    write_data(0x34);
    write_data(0x02);

    write_command(0xF7);
    write_data(0x20);

    write_command(0xEA);
    write_data(0x00);
    write_data(0x00);

    write_command(0xC0);    // Power control
    write_data(0x23);

    write_command(0xC1);    // Power control
    write_data(0x10);

    write_command(0xC5);    // VCM control
    write_data(0x3e);
    write_data(0x28);

    write_command(0xC7);    // VCM control2
    write_data(0x86);

    write_command(0x36);    // Memory Access Control
    write_data(0x40 | 0x08);  // Rotation 0 (portrait mode)

    write_command(0x3A);
    write_data(0x55);

    write_command(0xB1);
    write_data(0x00);
    write_data(0x13); // 0x18 79Hz, 0x1B default 70Hz, 0x13 100Hz

    write_command(0xB6);    // Display Function Control
    write_data(0x08);
    write_data(0x82);
    write_data(0x27);

    write_command(0xF2);    // 3Gamma Function Disable
    write_data(0x00);

    write_command(0x26);    // Gamma curve selected
    write_data(0x01);

    write_command(0xE0);    // Set Gamma
    write_data(0x0F);
    write_data(0x31);
    write_data(0x2B);
    write_data(0x0C);
    write_data(0x0E);
    write_data(0x08);
    write_data(0x4E);
    write_data(0xF1);
    write_data(0x37);
    write_data(0x07);
    write_data(0x10);
    write_data(0x03);
    write_data(0x0E);
    write_data(0x09);
    write_data(0x00);

    write_command(0xE1);    // Set Gamma
    write_data(0x00);
    write_data(0x0E);
    write_data(0x14);
    write_data(0x03);
    write_data(0x11);
    write_data(0x07);
    write_data(0x31);
    write_data(0xC1);
    write_data(0x48);
    write_data(0x08);
    write_data(0x0F);
    write_data(0x0C);
    write_data(0x31);
    write_data(0x36);
    write_data(0x0F);

    write_command(0x11);    // Exit Sleep
    gpio_put(PIN_CS, 1);    // end write, set cs high
    sleep_ms(120);
    gpio_put(PIN_CS, 0);    // begin write, set cs low
    
    write_command(0x29);    // Display on
}

void landscape_mode()
{
    write_command(0x36); // memory access
    // writedata(TFT_MAD_MX | TFT_MAD_MY | TFT_MAD_MV | TFT_MAD_COLOR_ORDER);
    write_data(0x40 | 0x80 | 0x20 | 0x08); // set to landscape
}

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
