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

ui8 inb(ui16 port) {
  ui8 ret;
  asm volatile("inb %1, %0"
               : "=a"(ret)
               : "d"(port));
  return ret;
}

void outb(ui16 port, ui8 val) {
  asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
  /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
    * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
    * The  outb  %al, %dx  encoding is the only option for all other cases.
    * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
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
