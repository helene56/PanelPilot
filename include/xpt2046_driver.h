#ifndef XPT2046_DRIVER
#define XPT2046_DRIVER

void initialize_touch();
uint8_t touch_control_x_pos();
uint8_t touch_control_y_pos();
uint8_t touch_control_z_pos();
void touch_read_write(uint8_t control_byte, uint8_t *read_buffer);
void get_coordinates();
void my_input_read(lv_indev_t * indev, lv_indev_data_t * data);


#endif // XPT2046_DRIVER