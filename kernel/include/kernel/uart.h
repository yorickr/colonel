enum
{
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
    GPIO_BASE = BCM_PERIPHERAL_BASE + 0x200000, // for raspi2 & 3, 0x20200000 for raspi1

    // The offsets for reach register.

    // Controls actuation of pull up/down to ALL GPIO pins.
    GPPUD = (GPIO_BASE + 0x94),

    // Controls actuation of pull up/down for specific GPIO pin.
    GPPUDCLK0 = (GPIO_BASE + 0x98),

    // The base address for UART.
    UART0_BASE = BCM_PERIPHERAL_BASE + 0x201000, // for raspi2 & 3, 0x20201000 for raspi1

    // The offsets for reach register for the UART.
    // According to BCM2835 peripherals doc
    UART0_DR     = (UART0_BASE + 0x00), // Data register, size 32
    UART0_RSRECR = (UART0_BASE + 0x04), // size 32
    UART0_FR     = (UART0_BASE + 0x18), // Flag register, size 32
    UART0_ILPR   = (UART0_BASE + 0x20), // Not in use, size 32
    UART0_IBRD   = (UART0_BASE + 0x24), // Integer Baud rate divisor, size 32
    UART0_FBRD   = (UART0_BASE + 0x28), // Fractional Baud rate divisor, size 32
    UART0_LCRH   = (UART0_BASE + 0x2C), // Line Control Register, size 32
    UART0_CR     = (UART0_BASE + 0x30), // Control register, size 32
    UART0_IFLS   = (UART0_BASE + 0x34), // Interrupt FIFO Level Select Register, size 32
    UART0_IMSC   = (UART0_BASE + 0x38), // Interrupt Mask Set Clear Register, size 32
    UART0_RIS    = (UART0_BASE + 0x3C), // Raw Interrupt Status Register, size 32
    UART0_MIS    = (UART0_BASE + 0x40), // Masked Interrupt Status Register, size 32
    UART0_ICR    = (UART0_BASE + 0x44), // Interrupt Clear Register, size 32
    UART0_DMACR  = (UART0_BASE + 0x48), // DMA Control Register, size 32
    UART0_ITCR   = (UART0_BASE + 0x80), // Test Control Register, size 32
    UART0_ITIP   = (UART0_BASE + 0x84), // Integration test input register, size 32
    UART0_ITOP   = (UART0_BASE + 0x88), // Integration test output register, size 32
    UART0_TDR    = (UART0_BASE + 0x8C), // Test Data register, size 32
};

void uart_init();

void uart_putc(unsigned char c);
unsigned char uart_getc();
void uart_puts(const char* str);
