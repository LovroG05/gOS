void test_input_str() {
    int max_len = 50;
    char str[max_len];
    if (input_str(str, max_len)) {
        print_str(str);
    }
}

void test_ascii() {
    for (char c = 0; c < 256; ++c) {
        print_char(c);
    }
}