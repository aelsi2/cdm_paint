#include "app/editor.h"
#include "drawing/core.h"
#include "drawing/shape.h"
#include "io/display.h"
#include "io/menu.h"
#include "io/input.h"

inline static void update_screen() {
    display_write_range(dr_context->frame_buffer, dr_context->dirty_start, dr_context->dirty_end);
    dr_reset_dirty();
}

inline static void update_ui() {
    if (editor_state->mode == MODE_MENU) {
        menu_set_cursor(editor_state->menu_cursor_pos);
        display_set_primary_cursor(DISPLAY_CURSOR_HIDDEN);
    } else {
        menu_set_cursor(MENU_CURSOR_HIDDEN);
        display_set_primary_cursor(editor_state->primary_cursor_pos);
    }
    menu_data_t data = (menu_data_t)editor_state->tool;
    if (editor_state->fill) {
        data |= MENU_FILL_ON;
    }
    if (editor_state->color) {
        data |= MENU_COLOR_WHITE;
    }
    menu_set_data(data);
    display_set_secondary_cursor(editor_state->secondary_cursor_pos);
}

#pragma clang diagnostic ignored "-Wmain-return-type"
void main() {
    static dr_context_t ctx;
    static editor_state_t state;
    dr_context = &ctx;
    editor_state = &state;

    dr_reset_dirty();
    editor_init();

    update_ui();

    shape_t shape;
    while (1) {
        if (editor_dequeue(&shape)) {
            dr_draw_shape(&shape);
            update_screen();
        }
    }
}

void on_user_input(buttons_t buttons) {
    editor_move_cursor(get_x_dir(buttons), get_y_dir(buttons));

    if (buttons & BTN_LR) {
        editor_toggle_mode();
    } 
    if (buttons & BTN_A) {
        if (editor_state->mode == MODE_NORMAL) {
            if (editor_needs_secondary_cursor()) {
                editor_set_secondary_cursor();
            } else {
                editor_enqueue();
            }
        } else {
            editor_toggle_mode();
        }
    } else if (buttons & BTN_B) {
        if (editor_state->mode == MODE_NORMAL) {
            editor_reset_secondary_cursor();
        } else {
            editor_toggle_mode();
        }
    }
    update_ui();
}
