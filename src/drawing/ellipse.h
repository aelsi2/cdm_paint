// Ellipse drawing functions.

#pragma once

#include "graphics.h"

// Draws the outline of an ellipse between the specified corner points.
void dr_draw_outline_ellipse(point_t pt1, point_t pt2, color_t color);

// Draws a filled ellipse between the specified corner points.
void dr_draw_filled_ellipse(point_t pt1, point_t pt2, color_t color);
