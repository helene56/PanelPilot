#ifndef ILI9341_DRIVER
#define ILI9341_DRIVER

void write_command(uint8_t cmd);
void write_data(uint8_t data);
void write_data_buffer(uint8_t *data, size_t length);
void lcd_reset();
void lcd_init();
void landscape_mode();

// should move to its own driver file at some point
uint8_t touch_control_x_pos();
uint8_t touch_control_y_pos();
uint8_t touch_control_z_pos();
void touch_read_write(uint8_t control_byte);
void initialize_touch();
#endif // ILI9341_DRIVER