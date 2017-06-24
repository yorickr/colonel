#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <kernel/tty.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
	// Declare as unused
	(void) r0;
	(void) r1;
	(void) atags;

	uart_init();
	uart_puts("Hello, kernel World!\r\n");

	while (1)
		uart_putc(uart_getc());

	// terminal_initialize();
	//
	// terminal_writestring("Hello, kernel World!\n");
	//
	// terminal_writestring("Hello line two\n");
	// for (size_t i = 0; i < 100; i++) {
	// 	terminal_writestring("Hello multiple lines\n");
	// }
	// terminal_writestring("Here is another final string\n");
	// terminal_writestring("Here is the actual final string\n");
}
