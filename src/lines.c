#include "drawing.h"
#include "math.h"

void draw_line(point_t start, point_t end, color_t color){
    int x0 = get_x(start);
    int y0 = get_y(start);
    int x1 = get_x(end);
    int y1 = get_y(end);

    if (x0 == x1) {
        draw_vertical_line(start, end, color);
    } else if (y0 == y1) {
        draw_horizontal_line(start, end, color);
    } else {
        int delta_x = abs(x1 - x0);
        int delta_y = -abs(y1 - y0);
        int dir_x = sign(x1 - x0);
        int dir_y = sign(y1 - y0);
        int double_dx = delta_x * 2;
        int double_dy = delta_y * 2;
        int error = double_dx + double_dy;
        while (1) {
            draw_pixel(point(x0, y0), color);
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
