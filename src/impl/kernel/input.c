#include <stdbool.h>
#include "keyboard.h"
#include "print.h"
#include "types.h"
#include "chars.h"
#include "utils.h"
#include "color_spin.h"

static ui8 get_input_keycode() {
    ui8 code = 0;
    while (!code) {
        nanosleep(10000);

        show_date_time();
        //show_color_spin();
        //show_random_ship();

        code = inb(KEYBOARD_PORT);
    }
    
    // This outputs key code at the bottom of the screen for debug
    pprint_str(66, 23, "Keycode:", PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    pprint_int_pad(75, 23, code, 4, PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);

    return code;
}

// Returns true if pressed Enter, or false if pressed Esc
bool input_str(char* str, int max_len) {
    bool capslock = false;
    bool shift = false;
    bool alt = false;
    bool ctrl = false;
    bool numlock = true;
    bool scrolllock = false;
    ui32 repeats = 0;

    ui8 last_keycode = 0;
    int pos = 0;
    while (true) {
        ui8 c = get_input_keycode();
        // Skip repeating keys
        if (c == last_keycode) {
            ++repeats;
            if (repeats < 40 || repeats % 8 != 0) {
                continue;
            }
        } else {
            repeats = 0;
        }
        last_keycode = c;
        if (c == KEY_LEFT_SHIFT_RELEASE) {
            shift = false;
        }
        if (c == KEY_RIGHT_SHIFT_RELEASE) {
            shift = false;
        }
        // Skip depressing other keys
        if (c > 127) {
            continue;
        }
        if (c == KEY_ENTER) {
            str[pos] = '\0';
            return true;
        } else if (c == KEY_ESC) {
            str[pos] = '\0';
            return false;
        } else if (c == KEY_BACKSPACE) {
            if (pos) {
                pos--;
                clear_col();
            }
        } else if (c == KEY_LEFT_SHIFT_PRESS) {
            shift = true;
        } else if (c == KEY_CAPS_LOCK_PRESS) {
            capslock = !capslock;
        } else if ((c >=2 && c <= 13) || (c >= 16 && c <= 27) || (c >= 30 && c <= 41) || (c >= 43 && c <= 53) || c == 57) {
            if (pos + 1 < max_len) {
                char ch;
                if (capslock || shift) {
                    ch = get_ascii_char(c);
                } else {
                    ch = get_ascii_char_lower(c);
                }
                str[pos] = ch;
                print_char(ch);
                pos++;
            }
        }
    }
}

