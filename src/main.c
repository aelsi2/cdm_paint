#include "drawing.h"

block_t patterns[] = {
    0b1010111010010011, 0b1000000000000000,
    0b1010100010010010, 0b1000000000000000,
    0b1110111010010010, 0b1000000000000000,
    0b1010100010010010, 0b1000000000000000,
    0b1010111011011011, 0b1000000000000000,
    0b0000000000000000, 0b0000000000000000,
    0b1010101110111010, 0b0110010000000000,
    0b1010101010101010, 0b0101010000000000,
    0b1010101010110010, 0b0101010000000000,
    0b1010101010101010, 0b0101000000000000,
    0b0101001110101011, 0b0110010000000000
};

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    for (int i = 0; i < sizeof(patterns) / sizeof(patterns[0]); i++) {
        draw_pattern(patterns[i], i, COLOR_WHITE);
    }
    update_screen();
    clear(COLOR_WHITE);
    update_screen();
    for (int i = 0; i < 64; i++) {
        draw_pattern(i + 1, i, COLOR_BLACK);
    }
    update_screen();
}

