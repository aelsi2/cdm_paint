#include "drawing/core.h"
#include "drawing/ellipse.h"
#include "drawing/queue.h"
#include "io/display.h"
#include "io/input.h"
#include "screen.h"

int cursor_x = 15;
int cursor_y = 15;
draw_queue shape_queue;

void update_screen() {
    display_write_range(dr_context->frame_buffer, dr_context->dirty_start, dr_context->dirty_end);
    dr_reset_dirty();
}

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    display_set_primary_cursor(pt(cursor_x, cursor_y));
    static dr_context_t ctx;
    dr_context = &ctx;
    dr_reset_dirty();
    init_queue(&shape_queue);
    dr_draw_outline_ellipse(pt(15,15), 7, 4, COLOR_WHITE);
    update_screen();
    while (1);
}

shape new_shape;
void on_user_input(buttons_t buttons) {
    cursor_x += get_x_dir(buttons);
    cursor_y += get_y_dir(buttons);
    if (cursor_x >= SCREEN_WIDTH) {
        cursor_x -= SCREEN_WIDTH;
    }
    if (cursor_x < 0) {
        cursor_x += SCREEN_WIDTH;
    }
    if (cursor_y >= SCREEN_HEIGHT) {
        cursor_y -= SCREEN_HEIGHT;
    }
    if (cursor_y < 0) {
        cursor_y += SCREEN_HEIGHT;
    }
    display_set_primary_cursor(pt(cursor_x, cursor_y));
    
    if(buttons & BTN_A){
        new_shape = (shape){SHAPE_ELLIPSE,0,COLOR_WHITE,pt(cursor_x,cursor_y), pt(cursor_x + 5, cursor_y + 5)};
        enqueue(&shape_queue, &new_shape);
        update_screen();
    }
    
    if(buttons & BTN_B){
        new_shape = *peek(&shape_queue);
        dr_draw_shape(&new_shape);
        dequeue(&shape_queue);
        update_screen();
    }
}
