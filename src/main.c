#include "drawing.h"

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    draw_horizontal_line(point(0, 4), point(7, 4), COLOR_WHITE);
    draw_vertical_line(point(8, 0), point(8, 4), COLOR_WHITE);
    update_screen();

    while(1);
    clear(COLOR_WHITE);
    update_screen();
    draw_filled_rect(point(3, 3), point(28, 28), COLOR_BLACK);
    update_screen();
    draw_horizontal_line(point(5, 5), point(10, 5), COLOR_WHITE);
    update_screen();
    draw_horizontal_line(point(21, 26), point(26, 26), COLOR_WHITE);
    update_screen();
    draw_filled_rect(point(15, 15), point(16, 16), COLOR_WHITE);
    update_screen();
    draw_outline_rect(point(13, 13), point(18, 18), COLOR_WHITE);
    update_screen();
}

extern volatile const unsigned char joy;
void handle_input() {
    unsigned char joy_new = joy;
    draw_pixel(point(5, 1), (joy_new & 1) != 0);
    draw_pixel(point(4, 1), (joy_new & 2) != 0);
    draw_pixel(point(1, 2), (joy_new & 4) != 0);
    draw_pixel(point(1, 0), (joy_new & 8) != 0);
    draw_pixel(point(2, 1), (joy_new & 16) != 0);
    draw_pixel(point(0, 1), (joy_new & 32) != 0);
    draw_pixel(point(6, 0), (joy_new & 64) != 0);
    draw_pixel(point(0, 0), (joy_new & 128) != 0);
    update_screen();
}
