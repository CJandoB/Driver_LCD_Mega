#ifndef LCD_PCF8574_H
#define LCD_PCF8574_H

#include <stdint.h>

#define RS_CMD 0x00
#define RS_DATA 0x01

void lcd_send_byte(uint8_t data, uint8_t rs_mode);
void lcd_init(void);
void lcd_print_string(const char *str);

#endif