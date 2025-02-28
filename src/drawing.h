#pragma once

typedef unsigned char block_index_t;
typedef unsigned int block_t;
typedef enum : unsigned char {
    COLOR_INVERT,
    COLOR_BLACK,
    COLOR_WHITE
} color_t;

void draw_pattern(block_t pattern, int index, color_t color);
void draw_horizontal_line(int start, int end, color_t color);
void clear(color_t color);
void update_screen();
