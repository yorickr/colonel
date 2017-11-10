.global keyboard_handler

.extern keyboard_handler_main

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

.global as_sti
as_sti:
	sti
