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

#define FRAME_BUFFER_SIZE ((SCREEN_WIDTH * SCREEN_HEIGHT) / BLOCK_SIZE)
#define BLOCK_SIZE (sizeof(block_t) * 8)
#define BLOCKS_PER_ROW (SCREEN_WIDTH / BLOCK_SIZE)

#define point(row, col) ((row) * SCREEN_WIDTH + (col))
#define get_row(point) ((point) / SCREEN_WIDTH)
#define get_col(point) ((point) % SCREEN_WIDTH)

extern block_t frame_buffer[FRAME_BUFFER_SIZE];

void clear(color_t color);
void draw_pixel(point_t point, color_t color);
void draw_horizontal_line(point_t start, point_t end, color_t color);
void draw_vertical_line(point_t start, point_t end, color_t color);
void draw_filled_rect(point_t p1, point_t p2, color_t color);
void draw_outline_rect(point_t p1, point_t p2, color_t color);

void update_screen();

