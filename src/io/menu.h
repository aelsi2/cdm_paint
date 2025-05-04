// Tool menu display API.

#pragma once

#define MENU_CURSOR_HIDDEN (-1)

// Represents the contents of the tool menu display.
typedef enum : unsigned char {
    MENU_TOOL_PIXEL = 0b000,
    MENU_TOOL_LINE = 0b001,
    MENU_TOOL_RECT = 0b010,
    MENU_TOOL_ELLIPSE = 0b011,
    MENU_TOOL_CLEAR = 0b100,

    MENU_COLOR_WHITE = 0b1000,
    MENU_COLOR_BLACK = 0b0000,
    
    MENU_FILL_ON = 0b10000,
    MENU_FILL_OFF = 0b00000,
} menu_data_t;

/*
 * Sets the contents of the tool menu display.
 */
void menu_set_data(menu_data_t data);

/*
 * Sets the position of the tool menu display's cursor.
 */
void menu_set_cursor(char position);
