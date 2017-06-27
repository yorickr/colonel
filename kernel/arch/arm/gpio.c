
#include <kernel/mmio.h>
#include <kernel/gpio.h>

void gpio_write_pud(uint32_t data) {
    mmio_write(GPPUD, data);
}

void gpio_write_pudclk(uint8_t clock_register, uint32_t data) {
    if (clock_register == 0) {
        mmio_write(GPPUDCLK0, data);
    } else  if (clock_register == 1) {
        mmio_write(GPPUDCLK1, data);
    }
}

// Write 001 to GPFSEL for output, 000 for input.
// if output, write to GPSET or GPCLR
// if input, configure PUD, read from GPLEV

void gpio_set_pin(uint8_t pin, uint8_t value) {
    // GPFSEL0 = pin 0 to 9
    // GPFSEL1 = pin 10 to 19
    // GPFSEL2 = pin 20 to 29
    // GPFSEL3 = pin 30 to 39
    // GPFSEL4 = pin 40 to 49
    // GPFSEL5 = pin 50 to 53
    if (0 >= pin && pin <= 9) {
        mmio_write(GPFSEL0, value << pin);
        mmio_write(GPSET0, 1 << pin);
    } else if (10 >= pin && pin <= 19) {
        mmio_write(GPFSEL1, value << pin);
        mmio_write(GPSET0, 1 << pin);
    } else if (20 >= pin && pin <= 29) {
        mmio_write(GPFSEL2, value << pin);
        mmio_write(GPSET0, 1 << pin);
    } else if (30 >= pin && pin <= 39) {
        mmio_write(GPFSEL3, value << pin);
        // TODO: test
        if (30 >= pin && pin <= 31) {
            mmio_write(GPSET0, 1 << pin);
        } else {
            mmio_write(GPSET1, 1 << pin);
        }
    } else if (40 >= pin && pin <= 49) {
        mmio_write(GPFSEL4, value << pin);
        mmio_write(GPSET1, 1 << pin);
    } else if (50 >= pin && pin <= 53) {
        mmio_write(GPFSEL5, value << pin);
        mmio_write(GPSET1, 1 << pin);
    }
}
