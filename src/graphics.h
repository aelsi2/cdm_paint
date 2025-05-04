// Common graphics-related types and constants.

#pragma once

// A block of pixels shown on the screen.
typedef unsigned int block_t;

#define PIXELS_PER_BLOCK (sizeof(block_t) * 8)
#define SCREEN_WIDTH 32
#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH_MASK 0b11111
#define SCREEN_HEIGHT_MASK 0b11111

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

// Represents a tool used in the editor.
typedef enum : unsigned char {
    // Draws a single pixel.
    TOOL_PIXEL = 0,

    // Draws a line using Bresenham's algorithm.
    TOOL_LINE = 1,

    // Draws a rectangle.
    TOOL_RECT = 2,

    // Draws an ellipse using the midpoint circle algorithm.
    TOOL_ELLIPSE = 3,

    // Fills a connected area of the same color.
    TOOL_FLOOD_FILL = 4,
    
    // Fills the entire screen with a color.
    TOOL_CLEAR = 5,
} tool_t;

#define TOOL_COUNT 6

// Represents a drawable shape.
typedef struct {
    tool_t tool;
    char fill;
    color_t color;
    point_t pt1;
    point_t pt2;
} shape_t;

