#include "test_nanosleep.h"

#include "../print.h"

// Fills screen with PIT counter
void test_pit_map() {
    for (ui32 i = 0; i < 2000; ++i) {
        ui16 counter = port_byte_in(0x40);
        ui8 column = i % 80;
        ui8 row = i / 80;
        print_char(47 + counter);
        asm volatile("pause");
    }
}

// Fills screen with PIT counter divided by 26
void test_pit_map26() {
    for (ui32 i = 0; i < 2000; ++i) {
        ui16 counter = port_byte_in(0x40) / 26;
        ui8 column = i % 80;
        ui8 row = i / 80;
        print_char(48 + counter);
        for (ui32 w = 0; w < 10; ++w) {
            asm volatile("pause");
        }
    }
}

// Shows red when more than 25 PIT ticks were missed and green when repeatedly read same value
void test_pit_map2() {
    ui16 pos = 0;
    ui16 old_counter = port_byte_in(0x40);
    ui32 repeats = 0;
    while (pos < 2000) {
        ui16 counter = port_byte_in(0x40) / 26;
        for (ui32 w = 0; w < 1; ++w) {
            asm volatile("pause");
        }
        if (counter == old_counter) {
            ++repeats;
            continue;
        }
        ui8 column = pos % 80;
        ui8 row = pos / 80;
        ui8 color = PRINT_COLOR_WHITE;
        if (old_counter - counter > 1 || (old_counter == 0 && counter != 9)) {
            color = PRINT_COLOR_RED;
        } else if (repeats) {
            color = PRINT_COLOR_GREEN;
        }
        print_char(48 + counter);
        pos++;
        repeats = 0;
        old_counter = counter;
    }
}

void test_nanosleep() {
    nanosleep_init();
    for (ui32 i = 0; i < 2000; ++i) {
        nanosleep(1000000);
        ui8 column = i % 80;
        ui8 row = i / 80;
        print_char("W");
    }
}

void test_nanosleep_exact() {
    // Initialize initial counter value
    ui8 hint = nanosleep_exact_init();
    ui32 divider = 1;
    for (ui32 i = 0; i < 2000; ++i) {
        hint = nanosleep_exact(1000000 / divider, hint);
        ui8 column = i % 80;
        ui8 row = i / 80;
        print_char(48 + (i % divider));
    }
}
