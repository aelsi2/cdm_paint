// Basic drawing functionality.

#pragma once

#include "graphics.h"

#define DR_BLOCKS_PER_ROW (SCREEN_WIDTH / PIXELS_PER_BLOCK)
#define DR_FRAME_BUFFER_SIZE ((SCREEN_WIDTH * SCREEN_HEIGHT) / PIXELS_PER_BLOCK)

// The drawing context which stores the frame buffer and the dirty range.
typedef struct {
    block_t frame_buffer[DR_FRAME_BUFFER_SIZE];
    int dirty_start;
    int dirty_end;
} dr_context_t;

/* 
 * The current drawing context.
 * Should be set before using any of the dr_* functions.
 */
extern dr_context_t *dr_context;

// Resets the dirty range stored in the current drawing context.
void dr_reset_dirty();

// Fills the frame with the specified color.
void dr_clear(color_t color);

// Draws a single pixel at the specified point with the specified color.
void dr_draw_pixel(point_t point, color_t color);

// Draws a filled rectangle with the specified corner points and color. 
void dr_draw_filled_rect(point_t p1, point_t p2, color_t color);

// Draws the outline of a rectangle with the specified corner points and color. 
void dr_draw_outline_rect(point_t p1, point_t p2, color_t color);

