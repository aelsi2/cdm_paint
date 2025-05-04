// Input device API.

#pragma once

// Represents the buttons pressed on the input device.
typedef enum : unsigned char {
    BTN_A = 1,
    BTN_B = 2,
    BTN_DOWN = 4,
    BTN_UP = 8,
    BTN_RIGHT = 16,
    BTN_LEFT = 32,
    BTN_R = 64,
    BTN_L = 128,

    BTN_DIRECTION = BTN_DOWN | BTN_UP | BTN_LEFT | BTN_RIGHT,
    BTN_ACTION = BTN_A | BTN_B | BTN_L | BTN_R,
} buttons_t;

// Gets the horizontal direction (-1, 0 or 1) of the joystick.
inline static int get_x_dir(buttons_t buttons) {
    if (buttons & BTN_LEFT) {
        return -1;
    } else if (buttons & BTN_RIGHT) {
        return 1;
    } else {
        return 0;
    }
}

// Gets the vertical direction (-1, 0 or 1) of the joystick.
inline static int get_y_dir(buttons_t buttons) {
    if (buttons & BTN_UP) {
        return -1;
    } else if (buttons & BTN_DOWN) {
        return 1;
    } else {
        return 0;
    }
}

// The buttons currently pressed on the input device.
extern volatile const buttons_t input_state;

/*
 * Called by the input module when an input event happens (initial or repeating).
 * This function is not defined in this module and must be defined elsewhere.
 */
void on_user_input(buttons_t buttons);
