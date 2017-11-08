#include <kernel/idt.h>

extern void load_idt(struct idt_ptr *idt_ptr);

extern void keyboard_handler();

void idt_init() {
	uint32_t keyboard_address;
	uint32_t idt_address;

	/* populate IDT entry of keyboard's interrupt */
	keyboard_address = (uint32_t)keyboard_handler;
	IDT[0x21].offset_1 = keyboard_address & 0xffff;
	IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = INTERRUPT_GATE; /* INTERRUPT_GATE */
	IDT[0x21].offset_2 = (keyboard_address & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	outb(0x20 , 0x11);
	outb(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	outb(0x21 , 0x20);
	outb(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	outb(0x21 , 0x00);
	outb(0xA1 , 0x00);

	/* ICW4 - environment info */
	outb(0x21 , 0x01);
	outb(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	outb(0x21 , 0xff);
	outb(0xA1 , 0xff);

	/* fill the IDT descriptor */
	// The IDT descriptor consists of a limit and a base.
	struct idt_ptr idt_ptr;
	idt_address = (uint32_t)IDT ;
	idt_ptr.limit = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr.base = idt_address >> 16 ;

    load_idt(&idt_ptr);
	// asm volatile ( "lidt %0" : : "m"(idt_ptr));
	// asm volatile ( "sti" );
}
