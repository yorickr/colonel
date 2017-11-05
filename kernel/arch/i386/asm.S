.global load_idt
.global load_gdt

.global keyboard_handler

.extern keyboard_handler_main


load_idt:
    mov 0x4(%esp), %edx
    lidtl (%edx)
    sti
    ret

load_gdt:
    mov 0x4(%esp), %edx
    lgdtl (%edx)
    ret

keyboard_handler:
	push %ds
	push %es
	push %fs
	push %gs
	pusha

	call keyboard_handler_main

	popa
	pop %ds
	pop %es
	pop %fs
	pop %gs
	iret
