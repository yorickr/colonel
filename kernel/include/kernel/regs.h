#ifndef _KERNEL_REGS_H
#define _KERNEL_REGS_H

enum {
    // From the docs:
    //      Physical addresses range from 0x20000000 to 0x20FFFFFF for peripherals. The bus
    //      addresses for peripherals are set up to map onto the peripheral bus address range starting at
    //      0x7E000000. Thus a peripheral advertised here at bus address 0x7Ennnnnn is available at
    //      physical address 0x20nnnnnn.

    // The GPIO registers base address.
    #ifdef _RPI_1
    BCM_PERIPHERAL_BASE = 0x20000000, // raspberry 1
    #elif _RPI_2
    BCM_PERIPHERAL_BASE = 0x3F000000, // raspberry 2 or 3
    #endif
};

#endif
