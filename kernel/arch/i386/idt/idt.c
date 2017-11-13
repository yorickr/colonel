#include <kernel/idt.h>

#include <kernel/port.h>
#include <kernel/asm.h>
#include <kernel/tty.h>
#include <kernel/pic.h>

#include <stdio.h>

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
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

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

struct IDT_entry{
	uint16_t offset_1; // offset bits 0..15
	uint16_t selector; // a code segment selector in GDT or LDT
	uint8_t zero;      // unused, set to 0
	uint8_t type_attr; // type and attributes
	uint16_t offset_2; // offset bits 16..31
} __attribute__((packed));

struct idt_ptr {
	uint32_t limit;
	uint32_t base;
} __attribute__((packed));

extern void load_idt(struct idt_ptr *idt_ptr);

struct IDT_entry IDT[IDT_SIZE];
isr_cb_t interrupt_cbs[IDT_SIZE];

void register_cb(uint8_t interrupt, isr_cb_t callback) {
	printf("Registering cb %d\n", interrupt);
    interrupt_cbs[interrupt] = callback;
}

void isr_cb(registers_t regs) {
	printf("Received isr%d\n", regs.int_no);
    // TODO: a lot.
	printf("Error code %d\n", regs.err_code);

	as_hlt();
}

void irq_cb(registers_t regs) {
    // printf("Received irq%d\n", regs.int_no);
    if (regs.int_no >= 40) {
        outb(SLAVE_CMD, EOI);
    }
    outb(MASTER_CMD, EOI); // send EOI

    // Handle callback.
    if (interrupt_cbs[regs.int_no]) {
        interrupt_cbs[regs.int_no](regs);
    }

}

void idt_create_entry(uint8_t id, uint32_t base, uint16_t sel, uint8_t flags) {
	IDT[id].offset_1 = base & 0xFFFF;
	IDT[id].selector = sel;
	IDT[id].zero = 0;
	IDT[id].type_attr = flags;
	IDT[id].offset_2 = (base >> 16) & 0xFFFF;
}

void idt_init() {
	printf("Initializing idt\n");
	uint32_t idt_address;

	// populate IDT
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

    idt_create_entry(32, (uint32_t)irq0, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(33, (uint32_t)irq1, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(34, (uint32_t)irq2, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(35, (uint32_t)irq3, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(36, (uint32_t)irq4, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(37, (uint32_t)irq5, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(38, (uint32_t)irq6, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(39, (uint32_t)irq7, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(40, (uint32_t)irq8, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(41, (uint32_t)irq9, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(42, (uint32_t)irq10, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(43, (uint32_t)irq11, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(44, (uint32_t)irq12, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(45, (uint32_t)irq13, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(46, (uint32_t)irq14, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);
    idt_create_entry(47, (uint32_t)irq15, KERNEL_CODE_SEGMENT_OFFSET, INTERRUPT_GATE);

	struct idt_ptr idt_ptr;
	idt_address = (uint32_t)IDT ;
	idt_ptr.limit = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr.base = idt_address >> 16 ;

	printf("Loading idt\n");
    load_idt(&idt_ptr);
	printf("Enabling interrupts\n");
	as_sti(); // enable interrupts after setting up the idt.
}
