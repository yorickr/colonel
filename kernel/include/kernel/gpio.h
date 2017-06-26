#ifndef _KERNEL_GPIO_H
#define _KERNEL_GPIO_H

#include <kernel/gpio_regs.h>

void gpio_write_pudclk(uint8_t clock_register, uint32_t data);
void gpio_write_pud(uint32_t data);

#endif
