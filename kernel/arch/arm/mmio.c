#include <kernel/mmio.h>
// Memory-Mapped I/O output
void mmio_write(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t*)reg = data;
}

// Memory-Mapped I/O input
uint32_t mmio_read(uint32_t reg)
{
	return *(volatile uint32_t*)reg;
}

long long mmio_read_len(uint32_t reg) {
	return *(volatile long long*)reg;
}

// Loop <delay> times in a way that the compiler won't optimize away
void delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}
