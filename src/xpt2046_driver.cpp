#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pins.h"
#include "actions.h"
#include "ui.h"
#include "xpt2046_driver.h"
#include "animations.h"

// Define your touch controller's raw value ranges
#define TOUCH_X_MIN     0
#define TOUCH_X_MAX     4095    // 12-bit resolution
#define TOUCH_Y_MIN     0
#define TOUCH_Y_MAX     4095    // 12-bit resolution

// Display dimensions
#define DISPLAY_WIDTH   320
#define DISPLAY_HEIGHT  240



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
        uint16_t raw_x = ((TOUCH_OUTPUT[0] << 8) | (TOUCH_OUTPUT[1] & 0xFF)) >> 4; // Shift to get 12 bits
        uint16_t raw_y = ((TOUCH_OUTPUT[2] << 8) | (TOUCH_OUTPUT[3] & 0xFF)) >> 4; // Shift to get 12 bits
        // // Map raw values to screen coordinates
        // uint16_t mapped_x = (raw_x - 0) * 320 / (1811 - 0); // Map X to 320px width
        // uint16_t mapped_y = (raw_y - 0) * 240 / (1867 - 0); // Map Y to 240px height
        // Print the decimal value of the 12-bit integer
        printf("x coordinate: %d, ", raw_x);
        printf("y coordinate: %d\n", raw_y);
    }  
}

// Simple map function
static inline int map_value(int val, int in_min, int in_max, int out_min, int out_max) 
{
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void my_input_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    touch_read_write(0b10010100, TOUCH_OUTPUT);
        // now move the pointer to store the y coor
    touch_read_write(0b11010100, &TOUCH_OUTPUT[2]);

    if (gpio_get(TOUCH_PEN) == 0)
    {

        uint16_t raw_x = ((TOUCH_OUTPUT[0] << 8) | (TOUCH_OUTPUT[1] & 0xFF)) >> 4; // Shift to get 12 bits
        uint16_t raw_y = ((TOUCH_OUTPUT[2] << 8) | (TOUCH_OUTPUT[3] & 0xFF)) >> 4; // Shift to get 12 bits

        // Map raw values to screen coordinates
        // Calibrated bounds from your measurements
        const int x_raw_min = 118;
        const int x_raw_max = 1868;

        const int y_raw_min = 179;
        const int y_raw_max = 1885;

        // Display resolution
        const int screen_width = 320;
        const int screen_height = 240;

        // Map raw to screen coordinates, flipping X and Y
        int mapped_x = map_value(raw_x, x_raw_max, x_raw_min, 0, screen_width - 1);
        int mapped_y = map_value(raw_y, y_raw_min, y_raw_max, screen_height - 1, 0);

        // Clamp values to screen bounds just in case
        if (mapped_x < 0) mapped_x = 0;
        if (mapped_x >= screen_width) mapped_x = screen_width - 1;

        if (mapped_y < 0) mapped_y = 0;
        if (mapped_y >= screen_height) mapped_y = screen_height - 1;

        data->point.x = mapped_x;
        data->point.y = mapped_y;
        data->state = LV_INDEV_STATE_PRESSED;
        
        
        printf("Mapped X: %d, Mapped Y: %d, State: %s\n", 
            mapped_x, 
            mapped_y, 
            data->state == LV_INDEV_STATE_PRESSED ? "PRESSED" : "RELEASED");
        // // Check if the touch is within the button area
        // if ((x_coor < 1800) && (x_coor > 574) && (y_coor > 552) && (y_coor < 830)) 
        // {
        //     // Simulate a button press by calling action_back_page
        //     action_back_page(NULL);
        // }
        // else
        // // TODO: maybe for both clicks allow a bigger area to be clicked for more responseviness
        // if ((x_coor > 0) && (x_coor < 300) && (y_coor > 513) && (y_coor < 814))
        // {
        //     action_next_page(NULL);
        // }

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

void button_event_handler(lv_event_t *e) 
{
    printf("Button pressed!\n");
    // Call gradual_bar_anim to animate obj4 and obj5
    gradual_bar_anim(0); // Start the animation with a value of 10
}


void action_next_page(lv_event_t *e) 
{
    // go to plant_status
    loadScreen(SCREEN_ID_PLANT_STATUS);
    // TODO: this was just to test the animations.
    // in the future maybe this would be nice when user updates display 
    // to check for updated values?
    bar_anim();

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
