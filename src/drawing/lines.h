// Functions for drawing lines.

#pragma once

#include "screen.h"

// Draws a line between two points using Bresenham's algorithm.
void dr_draw_line(point_t start, point_t end, color_t color);
