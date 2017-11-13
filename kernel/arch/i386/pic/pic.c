#include <kernel/pic.h>
#include <kernel/port.h>
#include <stdio.h>


void pic_init() {
	printf("Initializing pic\n");
    // Initialize PIC
	outb(MASTER_CMD , 0x11);
	outb(SLAVE_CMD , 0x11);

    // Remap PIC so we do not conflict with intel's 32 interrupts.
	outb(MASTER_DATA , 0x20); // remap to 0x20
	outb(SLAVE_DATA , 0x28); // remap to 0x28

    // ICW3
	outb(MASTER_DATA , 0x00); // indicate direct interrupts.
	outb(SLAVE_DATA , 0x00);

    // ICW4
	outb(MASTER_DATA , 0x01); // set pic to 8086 mode
	outb(SLAVE_DATA , 0x01);

    // Mask all interrupts. OCW1
	outb(MASTER_DATA , 0xFF);
	outb(SLAVE_DATA , 0xFF);
}
