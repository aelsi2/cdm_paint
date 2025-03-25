#include "drawing/core.h"
#include "io.h"

static dr_context_t ctx;

void update_screen() {
    screen_write_range(dr_context->frame_buffer, dr_context->dirty_start, dr_context->dirty_end);
    dr_reset_dirty();
}

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    dr_context = &ctx;
    dr_reset_dirty();
    dr_clear(COLOR_WHITE);

    update_screen();
    dr_draw_filled_rect(pt(3, 3), pt(28, 28), COLOR_BLACK);
    update_screen();
    dr_draw_filled_rect(pt(5, 5), pt(10, 5), COLOR_WHITE);
    update_screen();
    dr_draw_filled_rect(pt(21, 26), pt(26, 26), COLOR_WHITE);
    update_screen();
    dr_draw_filled_rect(pt(15, 15), pt(16, 16), COLOR_WHITE);
    update_screen();
    dr_draw_outline_rect(pt(13, 13), pt(18, 18), COLOR_WHITE);
    update_screen();
    while(1);
}

void handle_input() {
    buttons_t joy_new = joy;
    dr_draw_pixel(pt(5, 1), (joy_new & BTN_A) == 0);
    dr_draw_pixel(pt(4, 1), (joy_new & BTN_B) == 0);
    dr_draw_pixel(pt(1, 2), (joy_new & BTN_DOWN) == 0);
    dr_draw_pixel(pt(1, 0), (joy_new & BTN_UP) == 0);
    dr_draw_pixel(pt(2, 1), (joy_new & BTN_RIGHT) == 0);
    dr_draw_pixel(pt(0, 1), (joy_new & BTN_LEFT) == 0);
    dr_draw_pixel(pt(6, 0), (joy_new & BTN_R) == 0);
    dr_draw_pixel(pt(0, 0), (joy_new & BTN_L) == 0);
    update_screen();
}
