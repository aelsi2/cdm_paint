#include "drawing/internal.h"
#include "drawing/line.h"
#include "math.h"

void dr_draw_line(point_t p1, point_t p2, color_t color) {
    sort(p1, p2);

    int x0 = pt_x(p1);
    int y0 = pt_y(p1);
    int x1 = pt_x(p2);
    int y1 = pt_y(p2);
    dri_mark_dirty_range(min(y0, y1), max(y0, y1));

    if (x0 == x1) {
        dri_draw_vertical_line(p1, p2, color);
    } else if (y0 == y1) {
        dri_draw_horizontal_line(p1, p2, color);
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
