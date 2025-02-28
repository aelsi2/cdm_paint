#include "drawing.h"
#include "math.h"

#define FRAME_BUFFER_SIZE 64
#define BLOCK_SIZE 16
#define BLOCKS_PER_ROW 2

static block_t frame_buffer[FRAME_BUFFER_SIZE];
static const block_t masks_left[BLOCK_SIZE] = {
    0b1111111111111111, 0b0111111111111111, 0b0011111111111111, 0b0001111111111111,
    0b0000111111111111, 0b0000011111111111, 0b0000001111111111, 0b0000000111111111,
    0b0000000011111111, 0b0000000001111111, 0b0000000000111111, 0b0000000000011111,
    0b0000000000001111, 0b0000000000000111, 0b0000000000000011, 0b0000000000000001,
};
static const block_t masks_right[BLOCK_SIZE] = {
    0b1000000000000000, 0b1100000000000000, 0b1110000000000000, 0b1111000000000000,
    0b1111100000000000, 0b1111110000000000, 0b1111111000000000, 0b1111111100000000,
    0b1111111110000000, 0b1111111111000000, 0b1111111111100000, 0b1111111111110000,
    0b1111111111111000, 0b1111111111111100, 0b1111111111111110, 0b1111111111111111,
};
static const block_t masks_pixel[BLOCK_SIZE] = {
    0b1000000000000000, 0b0100000000000000, 0b0010000000000000, 0b0001000000000000,
    0b0000100000000000, 0b0000010000000000, 0b0000001000000000, 0b0000000100000000,
    0b0000000010000000, 0b0000000001000000, 0b0000000000100000, 0b0000000000010000,
    0b0000000000001000, 0b0000000000000100, 0b0000000000000010, 0b0000000000000001,
};

extern void write_row(char index, block_t block1, block_t block2);
extern void write_buffer(block_t *buffer);

void draw_pattern(block_t pattern, int index, color_t color) {
    switch (color) {
        case COLOR_WHITE:
            frame_buffer[index] |= pattern;
            return;
        case COLOR_BLACK:
            frame_buffer[index] &= ~pattern;
            return;
    }
}

void clear(color_t color) {
    block_t block;
    switch (color) {
        case COLOR_BLACK:
            block = 0x0000;
            break;
        case COLOR_WHITE:
            block = 0xFFFF;
            break;
    }
    for (int i = 0; i < FRAME_BUFFER_SIZE; i++) {
        frame_buffer[i] = block;
    }
}

void draw_pixel(point_t point, color_t color) {
    int block_index = point / BLOCK_SIZE;
    int pixel_index = point % BLOCK_SIZE;
    block_t block = masks_pixel[pixel_index];
    draw_pattern(block, block_index, color);
}

void draw_vertical_line(point_t start, point_t end, color_t color) {
    int start_block_index = start / BLOCK_SIZE;
    int end_block_index = end / BLOCK_SIZE;
    int pixel_index = start % BLOCK_SIZE;
    block_t block = masks_pixel[pixel_index];
    for (int block_index = start_block_index; block_index <= end_block_index; block_index += BLOCKS_PER_ROW) {
        draw_pattern(block, block_index, color);
    }
}

void draw_horizontal_line(point_t start, point_t end, color_t color) {
    int start_block_index = start / BLOCK_SIZE;
    int end_block_index = end / BLOCK_SIZE;
    int start_pixel_index = start % BLOCK_SIZE;
    int end_pixel_index = end % BLOCK_SIZE;
    if (start_block_index == end_block_index) {
        block_t block = masks_left[start_pixel_index] & masks_right[end_pixel_index];
        draw_pattern(block, start_block_index, color);
    } else {
        block_t block_start = masks_left[start_pixel_index];
        block_t block_end = masks_right[end_pixel_index];
        draw_pattern(block_start, start_block_index, color);
        draw_pattern(block_end, end_block_index, color);
    }
}

void draw_filled_rect(point_t p1, point_t p2, color_t color) {
    int min_row = min(p1 / SCREEN_WIDTH, p2 / SCREEN_WIDTH);
    int max_row = max(p1 / SCREEN_WIDTH, p2 / SCREEN_WIDTH);
    int min_col = min(p1 % SCREEN_WIDTH, p2 % SCREEN_WIDTH);
    int max_col = max(p1 % SCREEN_WIDTH, p2 % SCREEN_WIDTH);

    if ((min_col < BLOCK_SIZE) == (max_col < BLOCK_SIZE)) {
        int block_index = min_col / BLOCK_SIZE;
        min_col %= BLOCK_SIZE;
        max_col %= BLOCK_SIZE;
        block_t block = masks_left[min_col] & masks_right[max_col];
        for (int row = min_row; row <= max_row; row++) {
            draw_pattern(block, row * BLOCKS_PER_ROW + block_index, color);
        }
    } else {
        min_col %= BLOCK_SIZE;
        max_col %= BLOCK_SIZE;
        block_t block_start = masks_left[min_col];
        block_t block_end = masks_right[max_col];
        for (int row = min_row; row <= max_row; row++) {
            draw_pattern(block_start, row * BLOCKS_PER_ROW, color);
            draw_pattern(block_end, row * BLOCKS_PER_ROW + 1, color);
        }
    }
}

void draw_outline_rect(point_t p1, point_t p2, color_t color) {
    int min_row = min(p1 / SCREEN_WIDTH, p2 / SCREEN_WIDTH);
    int max_row = max(p1 / SCREEN_WIDTH, p2 / SCREEN_WIDTH);
    int min_col = min(p1 % SCREEN_WIDTH, p2 % SCREEN_WIDTH);
    int max_col = max(p1 % SCREEN_WIDTH, p2 % SCREEN_WIDTH);
    draw_horizontal_line(point(min_row, min_col), point(min_row, max_col), color);
    draw_horizontal_line(point(max_row, min_col), point(max_row, max_col), color);
    draw_vertical_line(point(min_row, min_col), point(max_row, min_col), color);
    draw_vertical_line(point(min_row, max_col), point(max_row, max_col), color);
}

void update_screen() {
    write_buffer(frame_buffer);
    return;
}

