#include "print.h"

#include "utils.h"

#include "chars.h"

struct ColorChar * color_text_video_buffer = (struct ColorChar * ) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;
char * char_mem;
size_t input_pos = 0;

void clear_row(size_t row) {
    struct ColorChar empty = (struct ColorChar) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        color_text_video_buffer[col + NUM_COLS * row] = empty;
    }
}

void clear_col() {
    col--;
    struct ColorChar empty = (struct ColorChar) {
        character: ' ',
        color: color,
    };
    color_text_video_buffer[col + NUM_COLS * row] = empty;
    input_pos--;
    move_cursor(col, row);
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void print_newline() {
    col = 0;

    if (row < NUM_ROWS) {
        row++;
        return;
    }

    for (size_t row = 0; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct ColorChar character = color_text_video_buffer[col + NUM_COLS * row];
            color_text_video_buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_COLS - 1);
}

void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (col > NUM_COLS) {
        print_newline();
    }

    color_text_video_buffer[col + NUM_COLS * row] = (struct ColorChar) {
        character: (uint8_t) character,
        color: color,
    };
    input_pos = col + NUM_COLS * row;
    col++;
    move_cursor(col, row);
}

struct ColorChar get_screen_color_char(ui8 column, ui8 row) {
    return color_text_video_buffer[column + NUM_COLS * row];
}

void print_str(char * str) {
    for (size_t i = 0; 1; i++) {
        *(char_mem + 1) = str;
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }
        print_char(character);
    }
}

void print_int(int num) {
    char str_num[digit_count(num) + 1];
    itoa(num, str_num, false);
    print_str(str_num);
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

void pprint_char(ui8 column, ui8 row, ui8 character, ui8 color, ui8 bg_color) {
    ui8 packed_color = color | bg_color << 4;
    color_text_video_buffer[column + NUM_COLS * row] = (struct ColorChar) {
        character: character,
        color: color,
    };
}

void pprint_str(ui8 column, ui8 row, char* str, ui8 color, ui8 bg_color) {
    for (size_t i = 0; 1; i++) {
        if (str[i] == '\0') {
            break;
        }
        pprint_char(column + i, row, str[i], color, bg_color);
    }
}

void pprint_int(ui8 column, ui8 row, i32 num, ui8 color, ui8 bg_color) {
    char str[digit_count(num) + 1];
    itoa(num, str, true);
    pprint_str(column, row, str, color, bg_color);
}

void pprint_int_pad(ui8 column, ui8 row, i32 num, ui8 pad, ui8 color, ui8 bg_color) {
    char str[pad + 1];
    for (size_t i = 1; i < pad; ++i) {
        str[i] = ' ';
    }
    str[pad] = '\0';
    itoa(num, str, false);
    pprint_str(column, row, str, color, bg_color);
}

void pprint_int_pad0(ui8 column, ui8 row, i32 num, ui8 pad, ui8 color, ui8 bg_color) {
    char str[pad + 1];
    for (size_t i = 0; i < pad; ++i) {
        str[i] = '0';
    }
    itoa(num, &(str[pad - digit_count(num)]), true);
    pprint_str(column, row, str, color, bg_color);
}

void print_set_x_y(size_t Lcol , size_t Lrow){
    col = Lcol;
    row = Lrow;
}