// Ellipse drawing functions

#pragma once

#include "screen.h"

// Draws the outline of an ellipse with the specified center point and x/y radii.
void dr_draw_outline_ellipse(point_t center, int rx, int ry, color_t color);

// Draws a filled ellipse with the specified center point and x/y radii.
void dr_draw_filled_ellipse(point_t center, int rx, int ry, color_t color);

