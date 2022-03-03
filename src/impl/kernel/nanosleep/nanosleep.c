#include "nanosleep.h"

#include "../utils.h"

// Initialize PIT channel 0 to single low byte with maximum 255 count value
void nanosleep_init() {
    outb(0x43, 0x14); // Config: channel 0, low byte, rate generator
    outb(0x40, 255); // Low byte initial count
}

// Sleep for specified amount of nanoseconds using PIT counter
void nanosleep(ui32 nanoseconds) {
    // Multiply by 1.1931816666 MHz (approximately)
    ui32 ticks = nanoseconds + nanoseconds / 5;
    ui32 ticks_passed = 0;
    ui8 old_counter = inb(0x40);
    while (ticks_passed < ticks) {
        asm volatile("pause");
        ui8 counter = inb(0x40);
        ui8 delta = old_counter - counter;
        ticks_passed += delta;
        old_counter = counter;
    }
}

