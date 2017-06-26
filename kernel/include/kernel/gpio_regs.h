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
};

#endif
