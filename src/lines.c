#include "drawing.h"
#include "math.h"

void draw_line(point_t start, point_t end, color_t color){
    int x0 = get_x(start);
    int y0 = get_y(start);
    int x1 = get_x(end);
    int y1 = get_y(end);

    if (x0 == x1)
        draw_vertical_line(start, end, color);
    else if (y0 == y1)
        draw_horizontal_line(start, end, color);
    else {
        int deltax = abs(x1 - x0);
        int deltay = -abs(y1 - y0);
        int dirx = x0 < x1 ? 1 : -1;
        int diry = y0 < y1 ? 1 : -1;
        int error = deltax + deltay;
        while(1){
            draw_pixel(point(x0, y0), color);
            int double_error = error * 2;
            if(double_error >= deltay){
                if(x0 == x1) break;
                error += deltay;
                x0 += dirx;
            }
            if(double_error <= deltax){
                if(y0 == y1) break;
                error += deltax;
                y0 += diry;
            }
        }
    }
}