#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"

#define LCD_ADDR 0x4E  // 0x4E (0x27 << 1) para la pantalla QAPASS

int main(void) {
    i2c_init();
    _delay_ms(100);

    while (1) {
        // ENCENDER BACKLIGHT 
        i2c_start();
        i2c_write(LCD_ADDR);
        i2c_write(0x08); // El bit 3 es el Backlight (0000 1000 en binario)
        i2c_stop();

        _delay_ms(1000);

        // APAGAR BACKLIGHT 
        i2c_start();
        i2c_write(LCD_ADDR);
        i2c_write(0x00); 
        i2c_stop();

        _delay_ms(1000);
    }
    return 0;
}