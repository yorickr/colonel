.global load_idt

load_idt:
    mov 0x4(%esp), %edx
    lidtl (%edx)
    sti
    ret
