#include "drawing/internal.h"
#include "math.h"

void dr_draw_line(point_t start, point_t end, color_t color){
    int x0 = pt_x(start);
    int y0 = pt_y(start);
    int x1 = pt_x(end);
    int y1 = pt_y(end);
    dri_mark_dirty_range(min(y0, y1), max(y0, y1));

    if (x0 == x1) {
        dri_draw_vertical_line(start, end, color);
    } else if (y0 == y1) {
        dri_draw_horizontal_line(start, end, color);
    } else {
        int delta_x = abs(x1 - x0);
        int delta_y = -abs(y1 - y0);
        int dir_x = sign(x1 - x0);
        int dir_y = sign(y1 - y0);
        int double_dx = delta_x * 2;
        int double_dy = delta_y * 2;
        int error = double_dx + double_dy;
        while (1) {
            dri_draw_pixel(pt(x0, y0), color);
            if (error >= delta_y) {
                if (x0 == x1) { 
                    break;
                }
                error += double_dy;
                x0 += dir_x;
            }
            if (error <= delta_x){
                if (y0 == y1) { 
                    break;
                }
                error += double_dx;
                y0 += dir_y;
            }
        }
    }
}
