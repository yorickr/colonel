#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <kernel/tty.h>
#include <kernel/gpio.h>
#include <kernel/mmio.h>
#include <kernel/timer.h>

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
	// Declare as unused
	(void) r0;
	(void) r1;
	(void) atags;

	gpio_set_pin_mode(16, PIN_OUTPUT);
	gpio_set_pin(16, POWER_LOW);

	terminal_initialize();

	terminal_writestring("Hello, kernel World!\n");

	terminal_writestring("Hello line two\n");
	for (size_t i = 0; i < 100; i++) {
		terminal_writestring("Hello multiple lines\n");
	}
	terminal_writestring("Here is another final string\n");
	terminal_writestring("Here is the actual final string\n");
	#ifdef _RPI_1
	terminal_writestring("This is a raspberry pi 1 or pi zero\n");
	#elif _RPI_2
	terminal_writestring("This is a raspberry pi 2 or 3\n");
	#endif
	char x = 'x';
	printf("Char is %c\n", x);
	int bot = 0b001;
	int top = 0b100;
	int result = 0b100001; // should be this.
	printf("Int is %d\n", bot);
	printf("Int is %d\n", top);
	printf("Int is %d\n", (top << 3) + bot);
	printf("Int is %d\n", result);
	uint64_t time = micros();
	printf("Time is %d\n", time);
	while(1) {
		// gpio_set_pin(1, POWER_HIGH);
		delay(10000);
		// uint64_t time = micros();
		// printf("Time is %d\n", time);
		// terminal_writestring("Hello world\n");
	}
}
