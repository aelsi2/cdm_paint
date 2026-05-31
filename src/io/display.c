#include "display.h"

__attribute__((naked)) void display_set_primary_cursor(point_t position) {
    __asm__("ldi r1, cursor1_position\n"
            "stw r1, r0\n"
            "rts\n");
}

__attribute__((naked)) void display_set_secondary_cursor(point_t position) {
    __asm__("ldi r1, cursor2_position\n"
            "stw r1, r0\n"
            "rts\n");
}

__attribute__((naked)) void display_write_range(block_t *buffer, int start_row,
                                                int end_row) {
    __asm__("push r4\n"
            "push r5\n"
            "add r1, r0\n"
            "add r1, r0\n"
            "add r1, r0\n"
            "add r1, r0\n"
            "ldi r3, display_row_index\n"
            "ldi r4, display_row\n"
            "br 1f\n"
            "0:\n"
            "stb r3, r1\n"
            "ldw r0, r5\n"
            "stw r4, r5\n"
            "add r4, 2\n"
            "add r0, 2\n"
            "ldw r0, r5\n"
            "stw r4, r5\n"
            "sub r4, 2\n"
            "add r0, 2\n"
            "inc r1\n"
            "1:\n"
            "cmp r1, r2\n"
            "ble 0b\n"
            "pop r5\n"
            "pop r4\n"
            "rts\n");
}
