#include <kernel/keyboard.h>
#include <kernel/pic.h>
#include <kernel/port.h>
#include <kernel/tty.h>
#include <kernel/idt.h>

#include <stdint.h>
#include <stdio.h>

unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void keyboard_handler() {
    uint8_t status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        char keycode = inb(KEYBOARD_DATA_PORT); // do not forget to read the key.
        if (keycode < 0) {
            return;
        }
        uint8_t key = keyboard_map[keycode];
        // printf("Received keycode %d which is %d %c\n", keycode, key, key);
        terminal_putchar(key);
    }
}

void kb_init() {
    printf("Initializing keyboard\n");
    // Enables irq1 which is the keyboard.
    // 11111101
	outb(MASTER_DATA , 0xFD);

    register_cb(IRQ1, keyboard_handler);
}
