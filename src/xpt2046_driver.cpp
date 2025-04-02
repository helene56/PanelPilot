#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pins.h"

constexpr uint TOUCH_CS   {20};
constexpr uint TOUCH_PEN  {26};

uint8_t TOUCH_OUTPUT[4]; 

// touch control
void initialize_touch()
{   
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(TOUCH_CS, GPIO_FUNC_SIO);
    gpio_put(TOUCH_CS, 1);

    gpio_init(TOUCH_PEN);
    gpio_set_dir(TOUCH_PEN, GPIO_IN);
    gpio_pull_up(TOUCH_PEN);  // Enable internal pull-up

}
// control byte: S A2 A1 A0 MODE SER/DFR PD1 PD0
uint8_t touch_control_x_pos()
{
    // note this is actually y position in landscape mode
    // PD0 = 0, PD1 = 0
    return 0b11010000;
}

uint8_t touch_control_y_pos()
{
    // uint8_t control_byte {0b10010011}; // start bit: first high bit
    return 0b10010000;
}

uint8_t touch_control_z_pos()
{
    // uint8_t control_byte {0b10110011}; // start bit: first high bit
    return 0b10110000;
}


// 3. define write mode
void touch_read_write(uint8_t control_byte, uint8_t *read_buffer)
{
    spi_set_baudrate(SPI_PORT, 2 * 1000 * 1000);
    gpio_put(PIN_CS, 1); // just in case it was left low
    gpio_put(TOUCH_CS, 0);
    spi_write_blocking(SPI_PORT, &control_byte, 1);
    spi_read_blocking(SPI_PORT, 0x00, read_buffer, 2);
    gpio_put(TOUCH_CS, 1);
    sleep_ms(1); // do i need this?
    spi_set_baudrate(SPI_PORT, 63 * 1000 * 1000);  
}

// get x and y values
void get_coordinates()
{
    // note x and y coordinates starts in the right bottom corner
    // the first two values should hold the x coor, the next two the y coor
    // first get x coor
    // assume landscape mode, so essentially we are using y coor now
    touch_read_write(0b10010000, TOUCH_OUTPUT);
    // now move the pointer to store the y coor
    touch_read_write(0b11010000, &TOUCH_OUTPUT[2]);
    if (gpio_get(TOUCH_PEN) == 0) 
    {
        // Touch detected
        // Combine the two 8-bit values into a 12-bit integer
        uint16_t x_coor = ((TOUCH_OUTPUT[0] << 8) | (TOUCH_OUTPUT[1] & 0xFF)) >> 4; // Shift to get 12 bits
        uint16_t y_coor = ((TOUCH_OUTPUT[2] << 8) | (TOUCH_OUTPUT[3] & 0xFF)) >> 4; // Shift to get 12 bits
        // Print the decimal value of the 12-bit integer
        printf("x coordinate: %d, ", x_coor);
        printf("y coordinate: %d\n", y_coor);
    }  
}