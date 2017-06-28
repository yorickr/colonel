#ifndef _KERNEL_GPIO_REGS_H
#define _KERNEL_GPIO_REGS_H

#include <kernel/regs.h>

enum {
    GPIO_BASE = BCM_PERIPHERAL_BASE + 0x200000, // for raspi2 & 3, 0x20200000 for raspi1

    // The offsets for reach register.

    // Controls actuation of pull up/down to ALL GPIO pins.
    GPPUD = (GPIO_BASE + 0x94), // GPIO Pin Pull Up/Down Enable

    // Controls actuation of pull up/down for specific GPIO pin.
    GPPUDCLK0 = (GPIO_BASE + 0x98),
    GPPUDCLK1 = (GPIO_BASE + 0x9C),

    GPFSEL0 = (GPIO_BASE + 0x0),
    GPFSEL1 = (GPIO_BASE + 0x4),
    GPFSEL2 = (GPIO_BASE + 0x8),
    GPFSEL3 = (GPIO_BASE + 0xC),
    GPFSEL4 = (GPIO_BASE + 0x10),
    GPFSEL5 = (GPIO_BASE + 0x14),

    GPSET0 = (GPIO_BASE + 0x1C),
    GPSET1 = (GPIO_BASE + 0x20),

    GPCLR0 = (GPIO_BASE + 0x28),
    GPCLR1 = (GPIO_BASE + 0x2C),

};

#endif
