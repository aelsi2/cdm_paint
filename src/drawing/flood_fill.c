#include "drawing/flood_fill.h"
#include "drawing/core.h"
#include "drawing/internal.h"
#include "graphics.h"

#define POINT_STACK_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT) 

struct {
    point_t array[POINT_STACK_SIZE];
    int top;
} point_stack;

void stack_push(point_t point) {
    point_stack.array[point_stack.top++] = point;
}

point_t stack_pop() {
    return point_stack.array[--point_stack.top];
}

color_t get_pixel(point_t point) {
    int block_index = point / PIXELS_PER_BLOCK;
    int pixel_index = point % PIXELS_PER_BLOCK;
    block_t block = dri_mask_pixel[pixel_index];
    return (dr_context->frame_buffer[block_index] & block) != 0;
}

inline static void push_adjacent(point_t start, point_t end, color_t color) {
    char added = 0;
    for (point_t point = start; point <= end; point++) {
        if (get_pixel(point) == color) {
            added = 0;
        } else if (!added) {
            stack_push(point);
            added = 1;
        }
    }
}

void dr_flood_fill(point_t point, color_t color) {
    point_stack.top = 0;
    stack_push(point);
    while (point_stack.top != 0) {
        point_t point = stack_pop();
        point_t row_start = point - pt_x(point);
        point_t row_end = row_start + SCREEN_WIDTH;
        
        point_t start = point - 1;
        while (start >= row_start && get_pixel(start) != color) {
            start--;
        }
        point_t end = point;
        while (end < row_end && get_pixel(end) != color) {
            end++;
        }
        start++;
        end--;
        int y = pt_y(point);

        dri_mark_dirty(y);
        dri_draw_horizontal_line(start, end, color);
        if (y < SCREEN_HEIGHT - 1) {
            push_adjacent(start + pt(0, 1), end + pt(0, 1), color);
        }
        if (y > 0) {
            push_adjacent(start - pt(0, 1), end - pt(0, 1), color);
        }
    }
}

