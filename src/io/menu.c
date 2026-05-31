#include "menu.h"

__attribute__((naked))
void menu_set_data(menu_data_t data) {
    __asm__("ldi r1, menu_data\n"
            "stb r1, r0\n"
            "rts\n");
}

__attribute__((naked))
void menu_set_cursor(char position) {
    __asm__("ldi r1, menu_cursor_position\n"
            "stb r1, r0\n"
            "rts\n");
}
