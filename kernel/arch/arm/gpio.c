
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
