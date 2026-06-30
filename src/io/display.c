#include "display.h"

void display_write_range(block_t *buffer, int start_row, int end_row) {
    extern volatile char display_row_index;
    extern volatile block_t display_row[2];
    for (int i = start_row; i <= end_row; i++) {
        display_row_index = i;
        display_row[0] = buffer[i * 2];
        display_row[1] = buffer[i * 2 + 1];
    }
}
