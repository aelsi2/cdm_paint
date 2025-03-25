// Common screen-related types and constants.

#pragma once

// A block of pixels shown on the screen.
typedef unsigned int block_t;

#define PIXELS_PER_BLOCK (sizeof(block_t) * 8)
#define SCREEN_WIDTH 32
#define SCREEN_HEIGHT 32

// Represents the position of a pixel on the screen.
// The top left pixel is (0, 0). Positive x = right. Positive y = down.
typedef int point_t;

#define pt(x, y) ((x) + (y) * SCREEN_WIDTH)
#define pt_x(point) ((point) % SCREEN_WIDTH)
#define pt_y(point) ((point) / SCREEN_WIDTH)

// Represents the color or a pixel on the screen.
typedef enum : unsigned char {
    // Value 0 (black).
    COLOR_BLACK = 0 ,
    // Value 1 (white).
    COLOR_WHITE = 1
} color_t;

