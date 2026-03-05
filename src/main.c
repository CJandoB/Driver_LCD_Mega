#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "lcd_pcf8574.h"

#define LCD_ADDR 0x4E  // 0x4E (0x27 << 1) para la pantalla QAPASS

int main(void) {
    i2c_init();
    lcd_init();

    lcd_print_string("Mira mi huevo");

    while(1) {}

    return 0;
}