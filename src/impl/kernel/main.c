#include "types.h"
#include "print.h"
#include "nanosleep/nanosleep.h"
#include "cmostime.h"
#include <stdbool.h>

void seed_rand() {
    struct rtcdate r;
    cmostime(&r);
    srand(
        r.second + 
        r.minute * 60 +
        r.hour * 60 * 60 +
        r.day * 60 * 60 * 24 +
        r.month * 60 * 60 * 24 * 31 +
        r.year * 60 * 60 * 24 * 31 * 12
    );
}

void show_date_time() {
    struct rtcdate r;
    cmostime(&r);
    pprint_int(0, 23, r.year, PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_char(4, 23, '-', PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_int_pad0(5, 23, r.month, 2, PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_char(7, 23, '-', PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_int_pad0(8, 23, r.day, 2, PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);

    pprint_int_pad0(11, 23, r.hour, 2, PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_char(13, 23, ':', PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_int_pad0(14, 23, r.minute, 2, PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_char(16, 23, ':', PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    pprint_int_pad0(17, 23, r.second, 2, PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
}

void kernel_main() {
    // Enables display of cursor on screen
    enable_cursor(13, 15);


    print_clear();
    print_set_x_y(1, 0);
    print_set_color(PRINT_COLOR_BROWN, PRINT_COLOR_BLACK);
    printf("Welcome to gOS - the duck OS!\n\n");

    seed_rand();
    // Try to beep with PC speaker
    // beep();

    // Get and display CPU verndor string
    char vendor_str[13];
    CPUID_vendor_string(vendor_str);
    printf("Detected CPU vendor string: ");
    printf(vendor_str);

    nanosleep_init();


    // Input some string
    printf("\n\nPlease enter your name: ");
    int max_len = 50;
    char usrname[max_len];
    if (input_str(usrname, max_len)) {
        printf("\nHello, ");
        printf(usrname);
    }

    printf("\n%s@gOS$ ", usrname);
    int max_query_len = 255;
    char input[max_query_len];
    while (input_str(input, max_query_len)) {
        printf("\n%s", input);
        show_date_time();
    }

    printf("\n\nGood bye!");

    // In the end, continue updating date/time
    while (true) {
        nanosleep(10000);
        show_date_time();
    }
}