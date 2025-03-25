#include "drawing/core.h"
#include "drawing/internal.h"
#include "math.h"

dr_context_t *dr_context;

void dr_reset_dirty() {
    dr_context->dirty_end = -1;
    dr_context->dirty_start = SCREEN_HEIGHT;
}

void dr_clear(color_t color) {
    block_t block;
    switch (color) {
        case COLOR_BLACK:
            block = 0x0000;
            break;
        case COLOR_WHITE:
            block = 0xFFFF;
            break;
    }
    dri_mark_dirty_range(0, 31);
    for (int i = 0; i < DR_FRAME_BUFFER_SIZE; i++) {
        dr_context->frame_buffer[i] = block;
    }
}

void dr_draw_pixel(point_t point, color_t color) {
    dri_mark_dirty(point / SCREEN_WIDTH);
    dri_draw_pixel(point, color);
}

void dr_draw_filled_rect(point_t p1, point_t p2, color_t color) {
    int min_row = min(pt_y(p1), pt_y(p2));
    int max_row = max(pt_y(p1), pt_y(p2));
    int min_col = min(pt_x(p1), pt_x(p2));
    int max_col = max(pt_x(p1), pt_x(p2));
    dri_mark_dirty_range(min_row, max_row);
    
    if ((min_col < PIXELS_PER_BLOCK) == (max_col < PIXELS_PER_BLOCK)) {
        int block_index = min_col / PIXELS_PER_BLOCK;
        min_col %= PIXELS_PER_BLOCK;
        max_col %= PIXELS_PER_BLOCK;
        block_t block = dri_mask_left[min_col] & dri_mask_right[max_col];
        for (int row = min_row; row <= max_row; row++) {
            dri_draw_pattern(block, row * DR_BLOCKS_PER_ROW + block_index, color);
        }
    } else {
        min_col %= PIXELS_PER_BLOCK;
        max_col %= PIXELS_PER_BLOCK;
        block_t block_start = dri_mask_left[min_col];
        block_t block_end = dri_mask_right[max_col];
        for (int row = min_row; row <= max_row; row++) {
            dri_draw_pattern(block_start, row * DR_BLOCKS_PER_ROW, color);
            dri_draw_pattern(block_end, row * DR_BLOCKS_PER_ROW + 1, color);
        }
    }
}

void dr_draw_outline_rect(point_t p1, point_t p2, color_t color) {
    int min_row = min(pt_y(p1), pt_y(p2));
    int max_row = max(pt_y(p1), pt_y(p2));
    int min_col = min(pt_x(p1), pt_x(p2));
    int max_col = max(pt_x(p1), pt_x(p2));
    dri_mark_dirty_range(min_row, max_row);
    
    dri_draw_horizontal_line(pt(min_col, min_row), pt(max_col, min_row), color);
    dri_draw_horizontal_line(pt(min_col, max_row), pt(max_col, max_row), color);
    dri_draw_vertical_line(pt(min_col, min_row), pt(min_col, max_row), color);
    dri_draw_vertical_line(pt(max_col, min_row), pt(max_col, max_row), color);
}

