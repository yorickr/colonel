.global load_idt

load_idt:
    mov 0x4(%esp), %edx
    lidtl (%edx)
    ret

.macro isr_no_err id
.global isr\id
isr\id:
    cli
    push $0
    push $\id
    jmp isr_common_stub
.endm

.macro isr_err id
.global isr\id
isr\id:
    cli
    push $\id
    jmp isr_common_stub
.endm

isr_no_err 0
isr_no_err 1
isr_no_err 2
isr_no_err 3
isr_no_err 4
isr_no_err 5
isr_no_err 6
isr_no_err 7
isr_err 8
isr_no_err 9
isr_err 10
isr_err 11
isr_err 12
isr_err 13
isr_err 14
isr_no_err 15
isr_no_err 16
isr_no_err 17
isr_no_err 18
isr_no_err 19
isr_no_err 20
isr_no_err 21
isr_no_err 22
isr_no_err 23
isr_no_err 24
isr_no_err 25
isr_no_err 26
isr_no_err 27
isr_no_err 28
isr_no_err 29
isr_no_err 30
isr_no_err 31

.extern isr_cb

isr_common_stub:
    pusha

    mov %ds, %ax
    pushl %eax
    movl %eax, %esi

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call isr_cb

    pop	%eax
    movl %esi, %eax

    mov	%ax, %ds
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    popa
    add	$8, %esp # Clean up the pushed error code and ISR id
    sti
    iret
