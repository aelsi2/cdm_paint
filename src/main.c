#include "drawing.h"

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    clear(COLOR_WHITE);
    update_screen();
    draw_filled_rect(point(3, 3), point(28, 28), COLOR_BLACK);
    update_screen();
    draw_horizontal_line(point(5, 5), point(5, 10), COLOR_WHITE);
    update_screen();
    draw_horizontal_line(point(26, 21), point(26, 26), COLOR_WHITE);
    update_screen();
    draw_filled_rect(point(15, 15), point(16, 16), COLOR_WHITE);
    update_screen();
}

void handle_input() {

}
