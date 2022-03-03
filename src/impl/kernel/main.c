#import "print.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_BROWN, PRINT_COLOR_BLACK);
    print_str("Welcome to gOS - the duck OS!");
}