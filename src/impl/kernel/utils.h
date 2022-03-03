#ifndef UTILS_H
#define UTILS_H

#include "types.h"

extern ui32 strlen(const char*);
extern ui32 digit_count(int);
extern void itoa(int, char *, bool);
int memcmp(const void *v1, const void *v2, uint n);

void sleep(ui32 cycles_count);

ui8 inb(ui16 port);
void outb(ui16 port, ui8 val);

#endif
