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
        int error = delta_x + delta_y;
        while (1) {
            dri_draw_pixel(pt(x0, y0), color);
            int double_error = 2 * error;
            if (double_error >= delta_y) {
                if (x0 == x1) { 
                    break;
                }
                error += delta_y;
                x0 += dir_x;
            }
            if (double_error <= delta_x){
                if (y0 == y1) { 
                    break;
                }
                error += delta_x;
                y0 += dir_y;
            }
        }
    }
}
