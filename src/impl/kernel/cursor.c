#include "types.h"
#include "print.h"
#include "utils.h"

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

void enable_cursor(ui8 cursor_start, ui8 cursor_end) {
	outb(FB_COMMAND_PORT, 0x0A);
	outb(FB_DATA_PORT, (inb(FB_DATA_PORT) & 0xC0) | cursor_start);
 
	outb(FB_COMMAND_PORT, 0x0B);
	outb(FB_DATA_PORT, (inb(FB_DATA_PORT) & 0xE0) | cursor_end);
}

void move_cursor(ui16 column, ui16 row) {
    ui16 pos = column + row * NUM_COLS;
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0xFF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0xFF);
}
