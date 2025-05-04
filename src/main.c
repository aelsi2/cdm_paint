#include "drawing/core.h"
#include "drawing/ellipse.h"
#include "internal.h"
#include "io.h"
#include "screen.h"
#include "drawing/queue.h"
#include "cdm.h"

int cursor_x = 15;
int cursor_y = 15;
draw_queue shape_queue;

void update_screen() {
    screen_write_range(dr_context->frame_buffer, dr_context->dirty_start, dr_context->dirty_end);
    dr_reset_dirty();
}

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    screen_write_cursor(pt(cursor_x, cursor_y));
    static dr_context_t ctx;
    dr_context = &ctx;
    dr_reset_dirty();
    init_queue(&shape_queue);
    dr_draw_outline_ellipse(pt(15,15), 7, 4, COLOR_WHITE);
    update_screen();
    while (1);
}

inline static int get_dir(buttons_t buttons, buttons_t negative, buttons_t positive) {
    if (buttons & negative) { 
        return -1;
    }
    if (buttons & positive) {
        return 1;
    }
    return 0;
}

static void move_cursor(buttons_t buttons) {
    cursor_x += get_dir(buttons, BTN_LEFT, BTN_RIGHT);
    cursor_y += get_dir(buttons, BTN_UP, BTN_DOWN);
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
    screen_write_cursor(pt(cursor_x, cursor_y));
}

#define REPEAT_TRANSITION_MAX 3
int repeat_transition_counter;
char is_repeating = 0;

shape new_shape;
void handle_input() {
    static buttons_t joy_old = 0;
    buttons_t joy_new = joy;
    if (!is_repeating) {
        move_cursor(joy_new & ~joy_old);
        repeat_transition_counter = REPEAT_TRANSITION_MAX;
    }
    joy_old = joy_new;

    if(joy_new & BTN_A){
        new_shape = (shape){SHAPE_ELLIPSE,0,COLOR_WHITE,pt(cursor_x,cursor_y),5,5};
        enqueue(&shape_queue, &new_shape);
        update_screen();
    }
    
    if(joy_new & BTN_B){
        new_shape = *peek(&shape_queue);
        dr_draw_shape(&new_shape);
        dequeue(&shape_queue);
        update_screen();
    }
}

void handle_input_repeating() {
    buttons_t joy_new = joy;
    if (is_repeating) {
        move_cursor(joy_new);
    } else if (!joy_new) {
        return;
    } else if (repeat_transition_counter > 0) {
        repeat_transition_counter--;
        return;
    } else {
        is_repeating = 1;
    }

    if (joy_new) {
        repeat_transition_counter = REPEAT_TRANSITION_MAX;
    } else if (repeat_transition_counter > 0) {
        repeat_transition_counter--;
    } else {
        is_repeating = 0;
    }
}

//clear screen function needed