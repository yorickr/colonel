#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(void) {

	terminal_initialize();

	terminal_writestring("Hello, kernel World!\n");

	terminal_writestring("Hello line two\n");
	for (size_t i = 0; i < 100; i++) {
		terminal_writestring("Hello multiple lines\n");
	}
	terminal_writestring("Here is another final string\n");
	terminal_writestring("Here is the actual final string\n");
	while(1) {
	}
}