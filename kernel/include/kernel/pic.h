#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

#define MASTER_CMD 0x20
#define MASTER_DATA 0x21

#define SLAVE_CMD 0xA0
#define SLAVE_DATA 0xA1

#define EOI 0x20

void pic_init();

#endif
