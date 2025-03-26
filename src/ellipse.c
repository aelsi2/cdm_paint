#include "drawing.h"
#include "math.h"
#include "ellipse.h"

#define draw_outline_pixels(xc, yc, x, y, color) \
    do { \
        int pt_plus_x = (xc) + (x); \
        int pt_minus_x = (xc) - (x); \
        int pt_plus_y = (yc) + (y); \
        int pt_minus_y = (yc) - (y); \
        color_t pt_col = (color); \
        if (pt_plus_x < SCREEN_WIDTH && pt_plus_y < SCREEN_HEIGHT) { \
            draw_pixel(point(pt_plus_x, pt_plus_y), pt_col); \
        } \
        if (pt_minus_x >= 0 && pt_plus_y < SCREEN_HEIGHT) { \
            draw_pixel(point(pt_minus_x, pt_plus_y), pt_col); \
        } \
        if (pt_plus_x < SCREEN_WIDTH && pt_minus_y >= 0) { \
            draw_pixel(point(pt_plus_x, pt_minus_y), pt_col); \
        } \
        if (pt_minus_x >= 0 && pt_minus_y >= 0) { \
            draw_pixel(point(pt_minus_x, pt_minus_y), pt_col); \
        } \
    } while (0)

#define draw_fill_pixels(xc, yc, x, y, color) \
    do { \
        int pt_plus_x = (xc) + (x); \
        int pt_minus_x = (xc) - (x); \
        int pt_plus_y = (yc) + (y); \
        int pt_minus_y = (yc) - (y); \
        pt_plus_x = min(pt_plus_x, SCREEN_WIDTH - 1); \
        pt_minus_x = max(pt_minus_x, 0); \
        color_t pt_col = (color); \
        if (pt_plus_y < SCREEN_HEIGHT) { \
            draw_horizontal_line(point(pt_minus_x, pt_plus_y), point(pt_plus_x, pt_plus_y), pt_col); \
        } \
        if (pt_minus_y >= 0) { \
            draw_horizontal_line(point(pt_minus_x, pt_minus_y), point(pt_plus_x, pt_minus_y), pt_col); \
        } \
    } while (0)

void draw_outline_ellipse(point_t center, int rx, int ry, color_t color) {
    int xc = get_x(center);
    int yc = get_y(center);

    int x = 0;
    int y = ry;
    int ryry = multiply(ry, ry);
    int rxrx = multiply(rx, rx);
    
    int dx = 0;
    int dy = multiply(rxrx, y) * 2;
    
    int d1 = ryry - multiply(rxrx, ry) + (rxrx / 4);

    while(dx < dy){
        draw_outline_pixels(xc, yc, x, y, color);

        if (d1 < 0){
            x++;
            dx += ryry * 2;
            d1 += dx + ryry;
        }
        else {
            x++;
            y--;
            dx += ryry * 2;
            dy -= rxrx * 2;
            d1 += dx - dy + ryry;
        }
    }

    int d2 = multiply(ryry, multiply(x * 2 + 1, x * 2 + 1) / 4) + 
             multiply(rxrx, multiply(y - 1, y - 1) - ryry);

    while (y >= 0) {
        draw_outline_pixels(xc, yc, x, y, color);
 
        if (d2 > 0) {
            y--;
            dy -= rxrx * 2;
            d2 += rxrx - dy;
        }
        else {
            y--;
            x++;
            dx += ryry * 2;
            dy -= rxrx * 2;
            d2 += dx - dy + rxrx;
        }
    }
}

void draw_filled_ellipse(point_t center, int rx, int ry, color_t color) {
    int xc = get_x(center);
    int yc = get_y(center);

    int x = 0;
    int y = ry;
    int ryry = multiply(ry, ry);
    int rxrx = multiply(rx, rx);
    
    int dx = 0;
    int dy = multiply(rxrx, y) * 2;
    
    int d1 = ryry - multiply(rxrx, ry) + (rxrx / 4);

    while(dx < dy){
        draw_fill_pixels(xc, yc, x, y, color);

        if (d1 < 0){
            x++;
            dx += ryry * 2;
            d1 += dx + ryry;
        }
        else {
            x++;
            y--;
            dx += ryry * 2;
            dy -= rxrx * 2;
            d1 += dx - dy + ryry;
        }
    }

    int d2 = multiply(ryry, multiply(x * 2 + 1, x * 2 + 1) / 4) + 
             multiply(rxrx, multiply(y - 1, y - 1) - ryry);

    while (y >= 0) {
        draw_fill_pixels(xc, yc, x, y, color);
 
        if (d2 > 0) {
            y--;
            dy -= rxrx * 2;
            d2 += rxrx - dy;
        }
        else {
            y--;
            x++;
            dx += ryry * 2;
            dy -= rxrx * 2;
            d2 += dx - dy + rxrx;
        }
    }
}

