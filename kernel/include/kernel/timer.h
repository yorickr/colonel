#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#include <kernel/regs.h>
#include <stdint.h>
#include <kernel/mmio.h>

enum {
    TIMER_BASE = BCM_PERIPHERAL_BASE + 0x3000,

    TIMER_CS = TIMER_BASE,
    TIMER_CLO = (TIMER_BASE + 0x4),
    TIMER_CHI = (TIMER_BASE + 0x8),
};

void sleep(uint64_t sleep);

uint64_t micros();

#endif
