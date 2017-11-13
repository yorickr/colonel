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

.macro irq id, val
.global irq\id
irq\id:
    cli
    push $0
    push $\val
    jmp irq_stub
.endm

irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47

.extern irq_cb
irq_stub:
    pusha

    mov %ds, %ax
    pushl %eax
    movl %eax, %esi

    movw $0x10, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call irq_cb

    pop %ebx
    movl %esi, %ebx

    movw %bx, %ds
    movw %bx, %es
    movw %bx, %fs
    movw %bx, %gs

    popa
    add	$8, %esp # Clean up the pushed error code and IRQ id
    sti
    iret
