#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ili9341_driver.h"

#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define TOUCH_CS 20
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_D_C  22 // data selection, command: 0, display data: 1
#define PIN_RST  21

void write_command(uint8_t cmd) 
{
    gpio_put(PIN_D_C, 0);  // Command mode
    gpio_put(PIN_CS, 0);
    spi_write_blocking(SPI_PORT, &cmd, 1);
    gpio_put(PIN_CS, 1);
    sleep_ms(1);
}

void write_data(uint8_t data) 
{
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


void lcd_init() 
{
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

// touch control
// control byte: S A2 A1 A0 MODE SER/DFR PD1 PD0
// TODO:
// 1. define a new chip select for the touch control chip
// 2. define control byte
// 3. define write mode
// 4. define read mode