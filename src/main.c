#include "drawing.h"

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
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

extern char joy;
void handle_input() {
    draw_pixel(joy, COLOR_WHITE);
    update_screen();
}
