#ifndef UTILS_H
#define UTILS_H

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e


#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define BROWN_ON_BLACK 0x5f

#include "types.h"

extern ui32 strlen(const char*);
extern ui32 digit_count(int);
extern void itoa(int, char *, bool);
int memcmp(const void *v1, const void *v2, uint n);

void sleep(ui32 cycles_count);

ui8 inb(ui16 port);
void outb(ui16 port, ui8 val);

#endif
