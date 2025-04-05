#include "drawing/core.h"
#include "drawing/lines.h"
#include "drawing/ellipse.h"
#include "io.h"
#include "screen.h"
#include "drawing/internal.h"

int cursor_x = 0;
int cursor_y = 0;

void update_screen() {
    screen_write_range(dr_context->frame_buffer, dr_context->dirty_start, dr_context->dirty_end);
    dr_reset_dirty();
}

void show_cursor(int x, int y){
    block_t left = dr_context->frame_buffer[y * SCREEN_WIDTH / PIXELS_PER_BLOCK];
    block_t right = dr_context->frame_buffer[y * SCREEN_WIDTH / PIXELS_PER_BLOCK + 1];
    int mask = dri_mask_pixel[x % PIXELS_PER_BLOCK];
    if(x < PIXELS_PER_BLOCK){
        left ^= mask;
    } else {
        right ^= mask;
    }
    screen_write_row(left, right, y);
}

void restore_row(int y){
    block_t left = dr_context->frame_buffer[y * SCREEN_WIDTH / PIXELS_PER_BLOCK];
    block_t right = dr_context->frame_buffer[y * SCREEN_WIDTH / PIXELS_PER_BLOCK + 1];
    screen_write_row(left, right, y);
}

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    static dr_context_t ctx;
    dr_context = &ctx;
    dr_reset_dirty();
    dr_clear(COLOR_WHITE);

    update_screen();
    dr_draw_filled_rect(pt(3, 3), pt(28, 28), COLOR_BLACK);
    update_screen();
    /*dr_draw_line(pt(5, 7), pt(11, 5), COLOR_WHITE);
    update_screen();
    dr_draw_line(pt(20, 26), pt(26, 24), COLOR_WHITE);
    update_screen();
    dr_draw_filled_rect(pt(15, 15), pt(16, 16), COLOR_WHITE);
    update_screen();
    dr_draw_outline_rect(pt(13, 13), pt(18, 18), COLOR_WHITE);
    update_screen();
    dr_draw_outline_ellipse(pt(15, 15), 7, 7, COLOR_WHITE);
    update_screen();*/
    while(1);
}

void handle_input() {
    buttons_t joy_new = joy;
    if(joy_new & BTN_RIGHT){
        cursor_x++;
    }
    if(joy_new & BTN_LEFT){
        cursor_x--;
    }
    if(joy_new & BTN_DOWN){
        restore_row(cursor_y);
        cursor_y++;
    }
    if(joy_new & BTN_UP){
        restore_row(cursor_y);
        cursor_y--;
    }
    if(cursor_x >= SCREEN_WIDTH){
        cursor_x -= SCREEN_WIDTH;
    }
    if(cursor_x < 0){
        cursor_x += SCREEN_WIDTH;
    }
    if(cursor_y >= SCREEN_HEIGHT){
        cursor_y -= SCREEN_HEIGHT;
    }
    if(cursor_y < 0){
        cursor_y += SCREEN_HEIGHT;
    }
    show_cursor(cursor_x, cursor_y);
}
