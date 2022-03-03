#include "nanosleep_exact.h"

#include "../utils.h"

// Specify PIT channel 0 or 2
static ui8 pit_channel = 0;

static ui16 get_pit_count() {
    outb(0x43, pit_channel << 6); // Latch count before reading
    return inb(0x40 + pit_channel) | inb(0x40 + pit_channel) << 8;
}

// Get initial hint
ui16 nanosleep_exact_init() {
    outb(0x43, 0x34 | (pit_channel << 6)); // Config: low/high byte, rate generator
    outb(0x40 + pit_channel, 0xFF); // Low byte initial count
    outb(0x40 + pit_channel, 0xFF); // High byte initial count
    
    return get_pit_count();
}

// This function allows to sleep for specified amount of nanoseconds, while cancelling short user delays
ui16 nanosleep_exact_continue(ui32 nanoseconds, ui32 hint) {
    // Multiply by 1.1931816666 MHz (approximately)
    ui32 ticks = 
        nanoseconds
        + nanoseconds / 5
        - nanoseconds / 146
        + nanoseconds / 32277;
    ui32 ticks_passed = 0;
    ui16 old_counter = hint;
    ui16 counter = old_counter;
    while (ticks_passed < ticks) {
        asm volatile("pause");
        counter = get_pit_count();
        ui16 delta = old_counter - counter;
        // When counter reaches 0, it is immediately reset to maximum value 0xFFFF
        // We need to compensate for this reset here
        if (old_counter < counter) {
            delta -= 1;
        }
        old_counter = counter;
        ticks_passed += delta;
    }
    // Return latest counter if user wants to cancel short delays
    return counter;
}

// Sleep for specified number of nanoseconds
ui16 nanosleep_exact(ui32 nanoseconds) {
    return nanosleep_exact_continue(nanoseconds, get_pit_count());
}
