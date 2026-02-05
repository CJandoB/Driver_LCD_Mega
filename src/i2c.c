#include <avr/io.h>
#include "i2c.h"

#include <stdint.h>


void i2c_init(void) {
    TWBR = 12;
    TWSR = 0x00;
    TWCR = 1 << TWEN;
}

void i2c_start(void) {
    TWCR = (1 << TWINT | 1 << TWSTA | 1 << TWEN);
    while(!(TWCR & (1 << TWINT)));
}

void i2c_stop(void) {
    TWCR = (1 << TWINT | 1 << TWSTO | 1 << TWEN);
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN | 1<< TWINT);
    while(!(TWCR & (1 << TWINT)));
}