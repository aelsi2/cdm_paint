#include "drawing/internal.h"
#include "drawing/ellipse.h"
#include "drawing/core.h"
#include "math.h"

#define draw_outline_pixels(xc, yc, x, y, color, x_even, y_even) \
    do { \
        int pt_plus_x = (xc) + (x) + x_even; \
        int pt_minus_x = (xc) - (x); \
        int pt_plus_y = (yc) + (y) + y_even; \
        int pt_minus_y = (yc) - (y); \
        color_t pt_col = (color); \
        if (pt_plus_x < SCREEN_WIDTH && pt_plus_y < SCREEN_HEIGHT) { \
            dri_draw_pixel(pt(pt_plus_x, pt_plus_y), pt_col); \
        } \
        if (pt_minus_x >= 0 && pt_plus_y < SCREEN_HEIGHT) { \
            dri_draw_pixel(pt(pt_minus_x, pt_plus_y), pt_col); \
        } \
        if (pt_plus_x < SCREEN_WIDTH && pt_minus_y >= 0) { \
            dri_draw_pixel(pt(pt_plus_x, pt_minus_y), pt_col); \
        } \
        if (pt_minus_x >= 0 && pt_minus_y >= 0) { \
            dri_draw_pixel(pt(pt_minus_x, pt_minus_y), pt_col); \
        } \
    } while (0)

#define draw_fill_pixels(xc, yc, x, y, color, x_even, y_even) \
    do { \
        int pt_plus_x = (xc) + (x) + x_even; \
        int pt_minus_x = (xc) - (x); \
        int pt_plus_y = (yc) + (y) + y_even; \
        int pt_minus_y = (yc) - (y); \
        pt_plus_x = min(pt_plus_x, SCREEN_WIDTH - 1); \
        pt_minus_x = max(pt_minus_x, 0); \
        color_t pt_col = (color); \
        if (pt_plus_y < SCREEN_HEIGHT) { \
            dri_draw_horizontal_line(pt(pt_minus_x, pt_plus_y), pt(pt_plus_x, pt_plus_y), pt_col); \
        } \
        if (pt_minus_y >= 0) { \
            dri_draw_horizontal_line(pt(pt_minus_x, pt_minus_y), pt(pt_plus_x, pt_minus_y), pt_col); \
        } \
    } while (0)

void dr_draw_outline_ellipse(point_t pt1, point_t pt2, color_t color) {
    int x1 = pt_x(pt1);
    int y1 = pt_y(pt1);
    int x2 = pt_x(pt2);
    int y2 = pt_y(pt2);
    sort(x1, x2);
    sort(y1, y2);

    int xc = (x1 + x2) / 2;
    int yc = (y1 + y2) / 2;
    int rx = (x2 - x1) / 2;
    int ry = (y2 - y1) / 2;
    int x_even = (x1 ^ x2) & 1;
    int y_even = (y1 ^ y2) & 1;

    if (rx == 0 || ry == 0) {
        dr_draw_filled_rect(pt1, pt2, color);
        return;
    }
    dri_mark_dirty_range(y1, y2);

    int x = 0;
    int y = ry;
    int ryry = multiply(ry, ry);
    int rxrx = multiply(rx, rx);
    
    int dx = 0;
    int dy = multiply(rxrx, y) * 2;
    
    int d1 = ryry - multiply(rxrx, ry) + (rxrx / 4);

    while(dx < dy){
        draw_outline_pixels(xc, yc, x, y, color, x_even, y_even);

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
        draw_outline_pixels(xc, yc, x, y, color, x_even, y_even);
 
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

void dr_draw_filled_ellipse(point_t pt1, point_t pt2, color_t color) {
    int x1 = pt_x(pt1);
    int y1 = pt_y(pt1);
    int x2 = pt_x(pt2);
    int y2 = pt_y(pt2);
    sort(x1, x2);
    sort(y1, y2);

    int xc = (x1 + x2) / 2;
    int yc = (y1 + y2) / 2;
    int rx = (x2 - x1) / 2;
    int ry = (y2 - y1) / 2;
    int x_even = (x1 ^ x2) & 1;
    int y_even = (y1 ^ y2) & 1;

    if (rx == 0 || ry == 0) {
        dr_draw_filled_rect(pt1, pt2, color);
        return;
    }
    dri_mark_dirty_range(y1, y2);

    int x = 0;
    int y = ry;
    int ryry = multiply(ry, ry);
    int rxrx = multiply(rx, rx);
    
    int dx = 0;
    int dy = multiply(rxrx, y) * 2;
    
    int d1 = ryry - multiply(rxrx, ry) + (rxrx / 4);

    while(dx < dy){
        draw_fill_pixels(xc, yc, x, y, color, x_even, y_even);

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
        draw_fill_pixels(xc, yc, x, y, color, x_even, y_even);
 
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

