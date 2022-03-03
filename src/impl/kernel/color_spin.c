#include "types.h"
#include "print.h"
#include "rand.h"

static ui32 spin = 0;
static char spin_char[] = "|/-\\";

static char block_char[] = "\xB0\xB1\xB2";

void show_color_spin() {
    spin++;
    for (ui32 i = 0; i < NUM_COLS; i += 2) {
        pprint_char(i, 24, spin_char[(spin / ((i*i) % 11 + 4)) % 4], (spin / 15 + i) % 15 + 1, PRINT_COLOR_BLACK);
        pprint_char(i+1, 24, spin_char[3 - (spin / ((i*i) % 11 + 4)) % 4], (spin / 15 + i + 1) % 15 + 1, PRINT_COLOR_BLACK);
    }

    ui32 column = rand() % NUM_COLS;
    ui32 color = rand() % 15 + 1;
    pprint_char(column, 22, block_char[rand() % 3], color, PRINT_COLOR_BLACK);
}
