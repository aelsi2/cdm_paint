#include "drawing.h"

#define ROW_COUNT 32
#define FRAME_BUFFER_SIZE 64

static block_t frame_buffer[FRAME_BUFFER_SIZE];

extern void write_row(char index, block_t block1, block_t block2);

void draw_pattern(block_t pattern, int index, color_t color) {
    if (color == COLOR_WHITE) {
        frame_buffer[index] |= pattern;
    } else {
        frame_buffer[index] &= ~pattern;
    }
}

void clear(color_t color) {
    block_t block;
    if (color == COLOR_WHITE) {
        block = 0xFFFF;
    } else {
        block = 0x0000;
    }
    for (int i = 0; i < FRAME_BUFFER_SIZE; i++) {
        frame_buffer[i] = block;
    }
}

void update_screen() {
    int row_index = 0;
    int block_index = 0;
    while (row_index < ROW_COUNT) {
        block_t block1 = frame_buffer[block_index++];
        block_t block2 = frame_buffer[block_index++];
        write_row(row_index++, block1, block2);
    }
}

