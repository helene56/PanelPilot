#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pins.h"
#include "actions.h"
#include "ui.h"
#include "xpt2046_driver.h"
constexpr uint TOUCH_CS   {20};
constexpr uint TOUCH_PEN  {26};

uint8_t TOUCH_OUTPUT[4]; 


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
    spi_set_baudrate(SPI_PORT, 63 * 1000 * 1000);  
}

// get x and y values
void get_coordinates()
{
    // note x and y coordinates starts in the right bottom corner
    // the first two values should hold the x coor, the next two the y coor
    // first get x coor
    // assume landscape mode, so essentially we are using y coor now

    if ((gpio_get(TOUCH_PEN) == 0)) 
    {
        touch_read_write(0b10010000, TOUCH_OUTPUT);
        // now move the pointer to store the y coor
        touch_read_write(0b11010000, &TOUCH_OUTPUT[2]);
        // Touch detected
        // Combine the two 8-bit values into a 12-bit integer
        uint16_t x_coor = ((TOUCH_OUTPUT[0] << 8) | (TOUCH_OUTPUT[1] & 0xFF)) >> 4; // Shift to get 12 bits
        uint16_t y_coor = ((TOUCH_OUTPUT[2] << 8) | (TOUCH_OUTPUT[3] & 0xFF)) >> 4; // Shift to get 12 bits
        // Print the decimal value of the 12-bit integer
        printf("x coordinate: %d, ", x_coor);
        printf("y coordinate: %d\n", y_coor);
    }  
}





void my_input_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    touch_read_write(0b10010100, TOUCH_OUTPUT);
        // now move the pointer to store the y coor
    touch_read_write(0b11010100, &TOUCH_OUTPUT[2]);

    if (gpio_get(TOUCH_PEN) == 0)
    {

        uint16_t x_coor = ((TOUCH_OUTPUT[0] << 8) | (TOUCH_OUTPUT[1] & 0xFF)) >> 4; // Shift to get 12 bits
        uint16_t y_coor = ((TOUCH_OUTPUT[2] << 8) | (TOUCH_OUTPUT[3] & 0xFF)) >> 4; // Shift to get 12 bits

        data->point.x = x_coor;
        data->point.y = y_coor;
        data->state = LV_INDEV_STATE_PRESSED;

        // Check if the touch is within the button area
        uint16_t x1 = 574, x2 = 1701, y1 = 552, y2 = 789;
        if ((x_coor < x2) && (x_coor > x1) && (y_coor > y1) && (y_coor < y2)) 
        {
            // Simulate a button press by calling action_back_page
            action_back_page(NULL);
        }
        else
        if ((x_coor > 0) && (x_coor < 300) && (y_coor > 513) && (y_coor < 814))
        {
            action_next_page(NULL);
        }

    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void action_back_page(lv_event_t *e) 
{
    // go to plant_status_1
    loadScreen(SCREEN_ID_PLANT_STATUS_1);

}

void action_next_page(lv_event_t *e) 
{
    // go to plant_status_1
    loadScreen(SCREEN_ID_PLANT_STATUS);

}


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
