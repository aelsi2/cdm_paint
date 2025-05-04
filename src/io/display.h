// Primary display API.

#pragma once

#include "graphics.h"

#define DISPLAY_CURSOR_HIDDEN (-1)

/*
 * Sends the contents of range of rows of a screen buffer to the primary display.
 * Both bounds are inclusive.
 */
void display_write_range(block_t *buffer, int start_row, int end_row);

/* 
 * Sets the position of the primary cursor of the primary display.
 */
void display_set_primary_cursor(point_t position);

/* 
 * Sets the position of the secondary cursor of the primary display.
 */
void display_set_secondary_cursor(point_t position);
