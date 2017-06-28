#include <kernel/timer.h>
#include <stdio.h>

void sleep(uint64_t sleep) {

}

uint64_t micros() {
    uint64_t bottom = mmio_read(TIMER_CLO);
    printf("Value is %b\n", bottom);
    uint64_t top = mmio_read(TIMER_CHI);
    top <<= 32;
    printf("Value is %b\n", top);
    printf("Combined they are %b\n", (top | bottom));
    return 0;
}
