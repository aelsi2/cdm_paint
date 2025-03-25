// Internal drawing functionality used to implement the public API.

#pragma once

#include "drawing/core.h"
#include "math.h"

/*
 * Contains bit masks with (index) most significant bits set to 0,
 * and others set to 1.
 */
extern const block_t dri_mask_left[PIXELS_PER_BLOCK];

/*
 * Contains bit masks with (index + 1) most significant bits set to 1,
 * and others set to 0.
 */
extern const block_t dri_mask_right[PIXELS_PER_BLOCK];

/*
 * Contains bit masks with the (index)-th pixel set to 1, and others set to 0.
 */
extern const block_t dri_mask_pixel[PIXELS_PER_BLOCK];

// Marks the specified line range as dirty. Both bounds are inclusive.
inline static void dri_mark_dirty_range(int start, int end) {
    dr_context->dirty_start = min(start, dr_context->dirty_start);
    dr_context->dirty_end = max(end, dr_context->dirty_end);
}

// Marks the specified line as dirty.
inline static void dri_mark_dirty(int line) {
    dr_context->dirty_start = min(line, dr_context->dirty_start);
    dr_context->dirty_end = max(line, dr_context->dirty_end);
}

/* 
 * Draws the specified bit pattern at the specified block index with the specified color.
 * When the color is DR_WHITE, the frame buffer bits corresponding to the bits in the pattern set to 1, are set to 1.
 * When the color is DR_BLACK, the same bits are set to 0.
 * 
 * Does not modify the dirty range.
 */ 
inline static void dri_draw_pattern(block_t pattern, int index, color_t color) {
    switch (color) {
        case COLOR_WHITE:
            dr_context->frame_buffer[index] |= pattern;
            return;
        case COLOR_BLACK:
            dr_context->frame_buffer[index] &= ~pattern;
            return;
    }
}

/*
 * Draws a single pixel at the specified point with the specified color.
 *
 * Does not modify the dirty range.
 */
inline static void dri_draw_pixel(point_t point, color_t color) {
    int block_index = point / PIXELS_PER_BLOCK;
    int pixel_index = point % PIXELS_PER_BLOCK;
    block_t block = dri_mask_pixel[pixel_index];
    dri_draw_pattern(block, block_index, color);
}


/*
 * Draws a vertical line between the specified points with the specified color.
 * The y value of start must be less than or equal to the y value of end
 * and the x values must be equal.
 */
inline static void dri_draw_vertical_line(point_t start, point_t end, color_t color) {
    int start_block_index = start / PIXELS_PER_BLOCK;
    int end_block_index = end / PIXELS_PER_BLOCK;
    int pixel_index = start % PIXELS_PER_BLOCK;
    block_t block = dri_mask_pixel[pixel_index];
    
    for (int block_index = start_block_index; block_index <= end_block_index; block_index += DR_BLOCKS_PER_ROW) {
        dri_draw_pattern(block, block_index, color);
    }
}

/*
 * Draws a horizontal line between the specified points with the specified color.
 * The x value of start must be less than or equal to the x value of end
 * and the y values must be equal.
 */
inline static void dri_draw_horizontal_line(point_t start, point_t end, color_t color) {
    int start_block_index = start / PIXELS_PER_BLOCK;
    int end_block_index = end / PIXELS_PER_BLOCK;
    int start_pixel_index = start % PIXELS_PER_BLOCK;
    int end_pixel_index = end % PIXELS_PER_BLOCK;
    
    if (start_block_index == end_block_index) {
        block_t block = dri_mask_left[start_pixel_index] & dri_mask_right[end_pixel_index];
        dri_draw_pattern(block, start_block_index, color);
    } else {
        block_t block_start = dri_mask_left[start_pixel_index];
        block_t block_end = dri_mask_right[end_pixel_index];
        dri_draw_pattern(block_start, start_block_index, color);
        dri_draw_pattern(block_end, end_block_index, color);
    }
}
