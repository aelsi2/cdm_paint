#include "drawing.h"

static const block_t hello_world_patterns[] = {
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

static void draw_hello_world() {
    for (int i = 0; i < sizeof(hello_world_patterns) / sizeof(hello_world_patterns[0]); i++) {
        draw_pattern(hello_world_patterns[i], i, COLOR_WHITE);
    }
}

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    draw_hello_world();
    update_screen();

    clear(COLOR_WHITE);
    draw_filled_rect(point(3, 3), point(28, 28), COLOR_BLACK);
    draw_horizontal_line(point(5, 5), point(5, 10), COLOR_WHITE);
    draw_horizontal_line(point(26, 21), point(26, 26), COLOR_WHITE);
    draw_filled_rect(point(15, 15), point(16, 16), COLOR_WHITE);
    update_screen();
}

void handle_input() {

}