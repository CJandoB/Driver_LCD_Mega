#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <avr/io.h>
#include "i2c.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd_pcf8574.h"

#define LCD_ADDR 0x4E
#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE 0x04  

#define RS_CMD 0x00
#define RS_DATA 0x01

static void lcd_send_nibble(uint8_t nibble_data, uint8_t rs_mode) {
    uint8_t byte_to_send = (nibble_data | rs_mode | LCD_BACKLIGHT);
    
    i2c_start();
    i2c_write(LCD_ADDR);
    i2c_write(byte_to_send | LCD_ENABLE); 
    i2c_stop();

    _delay_us(1);

    i2c_start();
    i2c_write(LCD_ADDR);
    i2c_write(byte_to_send); 
    i2c_stop();

    _delay_us(50);
}

void lcd_send_byte(uint8_t data, uint8_t rs_mode) {
    uint8_t high_nibble = (data & 0xF0);
    uint8_t low_nibble = ((data << 4) & 0xF0);

    lcd_send_nibble(high_nibble, rs_mode);
    lcd_send_nibble(low_nibble, rs_mode);
}

void lcd_init(void) {
    _delay_ms(50);

    lcd_send_nibble(0x30, RS_CMD);
    _delay_ms(5);

    lcd_send_nibble(0x30, RS_CMD);
    _delay_us(150);

    lcd_send_nibble(0x30, RS_CMD); // Secuencia para inicializar
    lcd_send_nibble(0x20, RS_CMD); // Pasar al modo de 4 bits
    
    lcd_send_byte(0x28, RS_CMD); // Configuración para 4 bits, 2 líneas
    lcd_send_byte(0x08, RS_CMD); // Apagar pantalla
    lcd_send_byte(0x01, RS_CMD); // Limpiar RAM
    _delay_ms(2);

    lcd_send_byte(0x06, RS_CMD); // El 0x06 es para configurar el cursor y así se mueva de manera automática al escribir
    lcd_send_byte(0x0C, RS_CMD); // Esto enciende la pantalla
}

void lcd_print_string(const char *str) {
    while(*str != '\0') {
        lcd_send_byte(*str++, RS_DATA);
    }   
}