#include "drawing.h"

#define ROW_COUNT 32
#define FRAME_BUFFER_SIZE 64

static block_t frame_buffer[FRAME_BUFFER_SIZE];

extern void write_row(char index, block_t block1, block_t block2);
extern void write_buffer(block_t *buffer);

void draw_pattern(block_t pattern, int index, color_t color) {
    switch (color) {
        case COLOR_INVERT:
            frame_buffer[index] ^= pattern;
            return;
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
        case COLOR_INVERT:
            for (int i = 0; i < FRAME_BUFFER_SIZE; i++) {
                frame_buffer[i] = ~frame_buffer[i];
            }
            return;
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

