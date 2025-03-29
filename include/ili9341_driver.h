#ifndef ILI9341_DRIVER
#define ILI9341_DRIVER

void write_command(uint8_t cmd);
void write_data(uint8_t data);
void write_data_buffer(uint8_t *data, size_t length);
void lcd_reset();
void lcd_init();
void landscape_mode();

#endif // ILI9341_DRIVER