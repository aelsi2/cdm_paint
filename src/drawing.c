#include "drawing.h"

#define ROW_COUNT 32
#define FRAME_BUFFER_SIZE 64

static block_t frame_buffer[FRAME_BUFFER_SIZE];
static const block_t masks_left[16] = {
    0b1111111111111111, 0b0111111111111111, 0b0011111111111111, 0b0001111111111111,
    0b0000111111111111, 0b0000011111111111, 0b0000001111111111, 0b0000000111111111,
    0b0000000011111111, 0b0000000001111111, 0b0000000000111111, 0b0000000000011111,
    0b0000000000001111, 0b0000000000000111, 0b0000000000000011, 0b0000000000000001,
};
static const block_t masks_right[16] = {
    0b1000000000000000, 0b1100000000000000, 0b1110000000000000, 0b1111000000000000,
    0b1111100000000000, 0b1111110000000000, 0b1111111000000000, 0b1111111100000000,
    0b1111111110000000, 0b1111111111000000, 0b1111111111100000, 0b1111111111110000,
    0b1111111111111000, 0b1111111111111100, 0b1111111111111110, 0b1111111111111111,
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

void draw_horizontal_line(int start, int end, color_t color) {
    int start_block_index = start / 16;
    int end_block_index = end / 16;
    int start_pixel_index = start % 16;
    int end_pixel_index = end % 16;
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

void update_screen() {
    write_buffer(frame_buffer);
    return;
}

