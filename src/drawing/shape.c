#include "drawing/shape.h"
#include "drawing/core.h"
#include "drawing/ellipse.h"
#include "drawing/lines.h"
#include "drawing/flood_fill.h"

void dr_draw_shape(shape_t* s){
    switch (s->tool) {
        case TOOL_PIXEL:
            dr_draw_pixel(s->pt1, s->color);
            break;
        case TOOL_LINE:
            dr_draw_line(s->pt1, s->pt2, s->color);
            break;
        case TOOL_RECT:
            if(s->fill){
                dr_draw_filled_rect(s->pt1, s->pt2, s->color);
            } else {
                dr_draw_outline_rect(s->pt1, s->pt2, s->color);
            }
            break;
        case TOOL_ELLIPSE:
            if(s->fill){
                dr_draw_filled_ellipse(s->pt1, s->pt2, s->color);
            } else {
                dr_draw_outline_ellipse(s->pt1, s->pt2, s->color);
            }
            break;
        case TOOL_FLOOD_FILL:
            dr_flood_fill(s->pt1, s->color);
            break;
        case TOOL_CLEAR:
            dr_clear(s->color);
            break;
    }
}

