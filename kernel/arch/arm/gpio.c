
#include <kernel/mmio.h>
#include <kernel/gpio.h>

#include <math.h>

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

void gpio_set_pin(uint8_t pin, uint8_t value) {
    // If pin = 16, value is POWER_LOW (0)
    // We need to write 0b 10 000 000 000 000 000 to GPCLR0
    // If pin = 35, value is POWER_LOW
    // We need to write  0b 1 000 to GPCLR1
    switch (value) {
        case POWER_LOW:
            mmio_write(GPCLR0 + (floor(pin / 32) * 0x4), 1 << (pin % 32));
            break;
        case POWER_HIGH:
            mmio_write(GPSET0 + (floor(pin / 32) * 0x4), 1 << (pin % 32));
            break;
    }
}

// set to output or input, value being either PIN_INPUT or PIN_OUTPUT
void gpio_set_pin_mode(uint8_t pin, uint8_t value) {
    // Lets say pin = 16, value = PIN_OUTPUT (so 0b001),
    // We have to select the pin by shifting VALUE left, every 3 bits (hence the *3)
    // So if pin = 16, value = PIN_OUTPUT, this will return 0b 001 000 000 000 000 000 000
    // If pin = 2, value = PIN_OUTPUT, this returns 0b 001 000 000
    // To select the proper register,
    // 10/10 = 1, so register 1 instead of 0.
    mmio_write(GPFSEL0 + (floor(pin / 10) * 0x4), value << ((pin % 10) * 3)); // select the pin in our register
}
