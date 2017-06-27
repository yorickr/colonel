#ifndef _KERNEL_GPIO_H
#define _KERNEL_GPIO_H

#include <kernel/gpio_regs.h>

enum {
    POWER_LOW = 0x000,
    POWER_HIGH = 0x001,
};

void gpio_write_pudclk(uint8_t clock_register, uint32_t data);
void gpio_write_pud(uint32_t data);
void gpio_set_pin(uint8_t pin, uint8_t value);

#endif
