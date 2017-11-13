#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <stdint.h>

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8e
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

struct registers
{
    uint32_t ds;                             // Data segment
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by isr_common_stub
    uint32_t int_no, err_code;               // Interrupt number and error code
    uint32_t eip, cs, eflags, useresp, ss;   // Pushed by the processor
} __attribute__((packed));
typedef struct registers registers_t;

typedef void (*isr_cb_t)(registers_t);

void idt_init();

void register_cb(uint8_t interrupt, isr_cb_t callback);

#define IRQ0 32
#define IRQ1 33

#define DIVISION_BY_ZERO            0
#define DEBUG_EXCEPTION             1
#define NON_MASKABLE_INTERRUPT      2
#define BREAKPOINT_EXCEPTION        3
#define INTO_DETECTED_OVERFLOW      4
#define OUT_OF_BOUNDS_EXCEPTION     5
#define INVALID_OPCODE_EXCEPTION    6
#define NO_COPROCESSOR_EXCEPTION    7
#define DOUBLE_FAULT                8
#define COPROCESSOR_SEGMENT_OVERRUN 9
#define BAD_TSS                     10
#define SEGMENT_NOT_PRESENT         11
#define STACK_FAULT                 12
#define GENERAL_PROTECTION_FAULT    13
#define PAGE_FAULT                  14
#define UNKNOWN_INTERRUPT_EXCEPTION 15
#define COPROCESSOR_FAULT           16
#define ALIGNMENT_CHECK_EXCEPTION   17
#define MACHINE_CHECK_EXCEPTION     18

#endif
