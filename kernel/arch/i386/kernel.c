#include <stddef.h>
#include <stdint.h>

#include <kernel/tty.h>

#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/keyboard.h>
#include <kernel/pic.h>

#include <kernel/asm.h>

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main(void) {

	terminal_initialize();

	terminal_writestring("Hello, kernel World!\n");


	gdt_init();
	pic_init();
	idt_init();

	kb_init();

	// TODO: Find out why we can't enable interrupts before this point.
	as_sti();

	while(1) {
	}
}
