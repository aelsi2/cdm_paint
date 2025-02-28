#pragma once

typedef unsigned char block_index_t;
typedef unsigned int block_t;
typedef enum : unsigned char {
    COLOR_BLACK,
    COLOR_WHITE
} color_t;
typedef int point_t;

#define SCREEN_WIDTH 32
#define SCREEN_HEIGHT 32
#define point(row, col) ((row) * SCREEN_WIDTH + (col))

void draw_pattern(block_t pattern, int index, color_t color);
void clear(color_t color);

void draw_pixel(point_t point, color_t color);
void draw_horizontal_line(point_t start, point_t end, color_t color);
void draw_vertical_line(point_t start, point_t end, color_t color);
void draw_filled_rect(point_t p1, point_t p2, color_t color);
void draw_outline_rect(point_t p1, point_t p2, color_t color);

void update_screen();

