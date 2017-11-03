#ifndef _KERNEL_PORT_H
#define _KERNEL_PORT_H

#include <stdint.h>

#include <kernel/tty.h>

static inline void outb(uint16_t port, uint8_t val);

static inline uint8_t inb(uint16_t port);

void idt_init();

#endif
