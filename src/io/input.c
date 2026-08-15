#include <cdm/ivt.h>
#include "io/input.h"

#define REPEAT_TRANSITION_MAX 3

int repeat_transition_counter;
char is_repeating = 0;

extern volatile char timer_state;

ISR void on_input_interrupt(context_t *ctx) {
    static buttons_t joy_old = 0;
    buttons_t joy_new = input_state;

    buttons_t joy_pressed = joy_new & ~joy_old;
    buttons_t joy_dirs = joy_pressed & BTN_DIRECTION;
    buttons_t joy_actions = joy_pressed & BTN_ACTION;

    if (joy_dirs) {
        if (!is_repeating) {
            on_user_input(joy_dirs);
            repeat_transition_counter = REPEAT_TRANSITION_MAX;
        }
        timer_state = 1;
    }
    if (joy_actions) {
        on_user_input(joy_actions);
    }
    joy_old = joy_new;
}

ISR void on_timer_interrupt(context_t *ctx) {
    buttons_t joy_dirs = input_state & BTN_DIRECTION;

    if (is_repeating && joy_dirs) {
        on_user_input(joy_dirs);
        repeat_transition_counter = REPEAT_TRANSITION_MAX;
    }

    if (repeat_transition_counter > 0) {
        repeat_transition_counter--;
    } else if (is_repeating) {
        is_repeating = 0;
        timer_state = 0;
    } else {
        is_repeating = 1;
    }
}
