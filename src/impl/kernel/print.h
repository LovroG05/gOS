#pragma once

#include <stdint.h>
#include <stddef.h>
#include "types.h"

#define NUM_COLS 80
#define NUM_ROWS 25

struct ColorChar {
    ui8 character;
    ui8 color;
};

enum {
    PRINT_COLOR_BLACK = 0,
    PRINT_COLOR_BLUE = 1,
    PRINT_COLOR_GREEN = 2,
    PRINT_COLOR_CYAN = 3,
    PRINT_COLOR_RED = 4,
    PRINT_COLOR_MAGENTA = 5,
    PRINT_COLOR_BROWN = 6,
    PRINT_COLOR_LIGHT_GRAY = 7,
    PRINT_COLOR_DARK_GRAY = 8,
    PRINT_COLOR_LIGHT_BLUE = 9,
    PRINT_COLOR_LIGHT_GREEN = 10,
    PRINT_COLOR_LIGHT_CYAN = 11,
    PRINT_COLOR_LIGHT_RED = 12,
    PRINT_COLOR_PINK = 13,
    PRINT_COLOR_YELLOW = 14,
    PRINT_COLOR_WHITE = 15,
};

void print_clear();
void print_char(char character);
void print_str(char* string);
void print_set_color(uint8_t foreground, uint8_t background);
struct ColorChar get_screen_color_char(ui8 column, ui8 row);
size_t input_pos;

void pprint_char(ui8 column, ui8 row, ui8 character, ui8 color, ui8 bg_color);
void pprint_str(ui8 column, ui8 row, char* str, ui8 color, ui8 bg_color);
void pprint_int(ui8 column, ui8 row, i32 num, ui8 color, ui8 bg_color);
void pprint_int_pad(ui8 column, ui8 row, i32 num, ui8 pad, ui8 color, ui8 bg_color);
void pprint_int_pad0(ui8 column, ui8 row, i32 num, ui8 pad, ui8 color, ui8 bg_color);
void print_set_x_y(size_t Lcol , size_t Lrow);
