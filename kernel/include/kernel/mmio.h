#ifndef _KERNEL_MMIO_H
#define _KERNEL_MMIO_H

#include <stdint.h>
#include <stddef.h>


// Memory-Mapped I/O output
void mmio_write(uint32_t reg, uint32_t data);

// Memory-Mapped I/O input
uint32_t mmio_read(uint32_t reg);
long long mmio_read_len(uint32_t reg);

// Loop <delay> times in a way that the compiler won't optimize away
void delay(int32_t count);

#endif
