#include <kernel/idt.h>

#include <kernel/port.h>
#include <kernel/asm.h>
#include <kernel/tty.h>

extern void load_idt(struct idt_ptr *idt_ptr);

extern void keyboard_handler();

struct registers
{
    uint32_t ds;                             // Data segment
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by isr_common_stub
    uint32_t int_no, err_code;               // Interrupt number and error code
    uint32_t eip, cs, eflags, useresp, ss;   // Pushed by the processor
} __attribute__((packed));
typedef struct registers registers_t;

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isr_cb(registers_t regs) {
	terminal_writestring("Received isr\n");
}

void idt_create_entry(uint8_t id, uint32_t base, uint16_t sel, uint8_t flags) {
	IDT[id].offset_1 = base & 0xFFFF;
	IDT[id].selector = sel;
	IDT[id].zero = 0;
	IDT[id].type_attr = flags;
	IDT[id].offset_2 = (base >> 16) & 0xFFFF;
}

void idt_init() {

	uint32_t idt_address;

	// populate IDT.
	// isr0();
	idt_create_entry( 0, (uint32_t)isr0, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
	idt_create_entry( 1, (uint32_t)isr1 , KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 2, (uint32_t)isr2, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 3, (uint32_t)isr3, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 4, (uint32_t)isr4, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 5, (uint32_t)isr5, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 6, (uint32_t)isr6, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 7, (uint32_t)isr7, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 8, (uint32_t)isr8, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry( 9, (uint32_t)isr9, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(10, (uint32_t)isr10, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(11, (uint32_t)isr11, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(12, (uint32_t)isr12, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(13, (uint32_t)isr13, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(14, (uint32_t)isr14, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(15, (uint32_t)isr15, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(16, (uint32_t)isr16, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(17, (uint32_t)isr17, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(18, (uint32_t)isr18, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(19, (uint32_t)isr19, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(20, (uint32_t)isr20, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(21, (uint32_t)isr21, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(22, (uint32_t)isr22, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(23, (uint32_t)isr23, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(24, (uint32_t)isr24, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(25, (uint32_t)isr25, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(26, (uint32_t)isr26, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(27, (uint32_t)isr27, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(28, (uint32_t)isr28, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(29, (uint32_t)isr29, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(30, (uint32_t)isr30, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(31, (uint32_t)isr31, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);

	idt_create_entry(0x21, (uint32_t)keyboard_handler, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);

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
	as_sti();
}
