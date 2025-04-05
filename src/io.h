// IO-related types and functions.

#pragma once

#include "screen.h"

#define BTN_A 1
#define BTN_B 2
#define BTN_DOWN 4
#define BTN_UP 8
#define BTN_RIGHT 16
#define BTN_LEFT 32
#define BTN_R 64
#define BTN_L 128

// Represents the buttons pressed on a controller.
typedef unsigned char buttons_t;

// The currently pressed controller buttons.
extern volatile const buttons_t joy;

/*
 * Sends the contents of range of rows of a screen buffer to the actual screen.
 * Both bounds are inclusive.
 */
void screen_write_range(block_t *buffer, int start_row, int end_row);

void screen_write_row(block_t left, block_t right, int row_index);
