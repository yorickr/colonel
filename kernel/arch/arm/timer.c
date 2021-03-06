#include <kernel/timer.h>
#include <kernel/mmio.h>
#include <stdio.h>

// This will only work on the real hardware :(
// Never returns in the emulator
void sleep(uint64_t sleep) {
    uint64_t start = micros();
    while ( (micros() - start) <= sleep) {
    }
}

void sleep_inaccurate(uint64_t sleep) {
    delay(sleep * 300000);
}

uint64_t micros() {
    uint64_t bottom = mmio_read(TIMER_CLO);
    uint64_t top = mmio_read(TIMER_CHI);
    top <<= 32;
    return top | bottom;
}
