#include "drawing.h"

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    draw_pattern(0b1010111010010011, 0, COLOR_WHITE);
    draw_pattern(0b1010100010010010, 2, COLOR_WHITE);
    draw_pattern(0b1110111010010010, 4, COLOR_WHITE);
    draw_pattern(0b1010100010010010, 6, COLOR_WHITE);
    draw_pattern(0b1010111011011011, 8, COLOR_WHITE);
    draw_pattern(0b1000000000000000, 1, COLOR_WHITE);
    draw_pattern(0b1000000000000000, 3, COLOR_WHITE);
    draw_pattern(0b1000000000000000, 5, COLOR_WHITE);
    draw_pattern(0b1001000000000000, 7, COLOR_WHITE);
    draw_pattern(0b1010000000000000, 9, COLOR_WHITE);
    
    draw_pattern(0b1010101110111010, 12, COLOR_WHITE);
    draw_pattern(0b1010101010101010, 14, COLOR_WHITE);
    draw_pattern(0b1010101010110010, 16, COLOR_WHITE);
    draw_pattern(0b1010101010101010, 18, COLOR_WHITE);
    draw_pattern(0b0101001110101011, 20, COLOR_WHITE);
    draw_pattern(0b0110010000000000, 13, COLOR_WHITE);
    draw_pattern(0b0101010000000000, 15, COLOR_WHITE);
    draw_pattern(0b0101010000000000, 17, COLOR_WHITE);
    draw_pattern(0b0101000000000000, 19, COLOR_WHITE);
    draw_pattern(0b0110010000000000, 21, COLOR_WHITE);

    update_screen();

    clear(COLOR_WHITE);
    update_screen();
}

