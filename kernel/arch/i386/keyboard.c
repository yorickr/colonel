#include <kernel/keyboard.h>

void kb_init() {
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	outb(0x21 , 0xFD);
}

void keyboard_handler_main() {
	outb(0x20, 0x20);
	terminal_writestring("Hi\n");
}
