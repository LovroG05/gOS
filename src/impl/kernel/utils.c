#include "utils.h"

ui32 strlen(const char* str) {
  ui32 length = 0;
  while (str[length])
    length++;
  return length;
}

ui32 digit_count(int num) {
  if (num < 0) {
    return digit_count(-num) + 1;
  }
  if (num == 0) {
    return 1;
  }
  ui32 count = 0;
  while (num > 0) {
    count++;
    num = num / 10;
  }
  return count;
}

void itoa(int num, char *str, bool set_trailing_zero) {
  int dgcount = digit_count(num);
  if (num < 0) {
    str[0] = '-';
    itoa(-num, &(str[1]), set_trailing_zero);
  } else if (num == 0 && dgcount == 1) {
    str[0] = '0';
    if (set_trailing_zero) {
      str[dgcount] = '\0';
    }
  } else {
    int index = dgcount - 1;
    char x;
    while (num != 0) {
      x = num % 10;
      str[index] = x + '0';
      index--;
      num = num / 10;
    }
    if (set_trailing_zero) {
      str[dgcount] = '\0';
    }
  }
}

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

void set_char_at_video_memory(char character, int offset) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = BROWN_ON_BLACK;
}
/*
keep the cpu busy for doing nothing
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void sleep(ui32 cycles_count) {
    while (cycles_count-- > 0) {
        asm volatile("pause");
    }
}

int memcmp(const void *v1, const void *v2, uint n) {
  const uchar *s1, *s2;

  s1 = v1;
  s2 = v2;
  while (n-- > 0){
    if (*s1 != *s2)
      return *s1 - *s2;
    s1++, s2++;
  }

  return 0;
}

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}
