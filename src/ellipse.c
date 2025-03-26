#include "drawing.h"
#include "math.h"

void draw_ellipse(point_t center, point_t point_x, point_t point_y, color_t color){
    

    int rx = abs(get_x(center) - get_x(point_x));
    int ry = abs(get_y(center) - get_y(point_y));
    int xc = get_x(center);
    int yc = get_y(center);

    int x = 0;
    int y = ry;
    int ryry = multiply(ry, ry);
    int rxrx = multiply(rx, rx);
    int d1 = ryry - multiply(rxrx, ry) + (rxrx / 4);
    int dx = 0;
    int dy = multiply(rxrx, y) * 2;

    while(dx < dy){
        if(xc + x <= SCREEN_WIDTH && yc + y <= SCREEN_HEIGHT){
            draw_pixel(point(xc + x, yc + y), color);
        }
        if(xc - x >= 0 && yc + y <= SCREEN_HEIGHT){
            draw_pixel(point(xc - x, yc + y), color);
        }
        if(xc + x <= SCREEN_WIDTH && yc - y >= 0){
            draw_pixel(point(xc + x, yc - y), color);
        }
        if(xc - x >= 0 && yc - y >= 0){
            draw_pixel(point(xc - x, yc - y), color);
        }

        if(d1 < 0){
            x++;
            dx = dx + ryry * 2;
            d1 = d1 + dx + ryry;
        }
        else {
            x++;
            y--;
            dx = dx + ryry * 2;
            dy = dy - rxrx * 2;
            d1 = d1 + dx - dy + ryry;
        }
    }

    int d2 = (multiply(ryry, (multiply(x * 2 + 1,x * 2 + 1) / 4))) + multiply(rxrx, multiply(y - 1, y - 1)) - multiply(rxrx, ryry);

    while (y >= 0) {
 
        if(xc + x <= SCREEN_WIDTH && yc + y <= SCREEN_HEIGHT){
            draw_pixel(point(xc + x, yc + y), color);
        }
        if(xc - x >= 0 && yc + y <= SCREEN_HEIGHT){
            draw_pixel(point(xc - x, yc + y), color);
        }
        if(xc + x <= SCREEN_WIDTH && yc - y >= 0){
            draw_pixel(point(xc + x, yc - y), color);
        }
        if(xc - x >= 0 && yc - y >= 0){
            draw_pixel(point(xc - x, yc - y), color);
        }
 
        if (d2 > 0) {
            y--;
            dy = dy - rxrx * 2;
            d2 = d2 + rxrx - dy;
        }
        else {
            y--;
            x++;
            dx = dx + ryry * 2;
            dy = dy - rxrx * 2;
            d2 = d2 + dx - dy + rxrx;
        }
    }

}