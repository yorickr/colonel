#ifndef _KERNEL_UART_H
#define _KERNEL_UART_H

#include <kernel/uart_regs.h>

void uart_init();

void uart_putc(unsigned char c);
unsigned char uart_getc();
void uart_puts(const char* str);

#endif
