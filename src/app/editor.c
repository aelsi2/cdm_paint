#include "app/editor.h"
#include "app/queue.h"
#include "graphics.h"
#include "math.h"

editor_state_t *editor_state;

void editor_init() {
    editor_state->mode = MODE_NORMAL;
    editor_state->tool = TOOL_LINE;
    editor_state->color = COLOR_WHITE;
    editor_state->fill = 1;
    editor_state->primary_cursor_pos = pt(15, 15);
    editor_state->secondary_cursor_pos = EDITOR_CURSOR_UNSET;
    editor_state->menu_cursor_pos = MENU_TOOL;
    queue_init(&editor_state->drawing_queue);
}

void editor_move_cursor(int dir_x, int dir_y) {
    if (editor_state->mode == MODE_NORMAL) {
        int cursor_x = pt_x(editor_state->primary_cursor_pos) + dir_x;
        int cursor_y = pt_y(editor_state->primary_cursor_pos) + dir_y;
        cursor_x &= SCREEN_WIDTH_MASK;
        cursor_y &= SCREEN_HEIGHT_MASK;
        editor_state->primary_cursor_pos = pt(cursor_x, cursor_y);
    } else {
        menu_row_t cursor_y = wrap_max(editor_state->menu_cursor_pos + dir_y, MENU_ROW_COUNT);
        editor_state->menu_cursor_pos = cursor_y;
        switch (cursor_y) {
            case MENU_TOOL:
                editor_state->tool = wrap_max(editor_state->tool + dir_x, TOOL_COUNT);
                break;
            case MENU_COLOR:
                if (dir_x) { 
                    editor_state->color ^= 1;
                }
                break;
            case MENU_FILL:
                if (dir_x) {
                    editor_state->fill ^= 1;
                }
                break;
        }
        
    }
}

void editor_toggle_mode() {
    editor_state->secondary_cursor_pos = EDITOR_CURSOR_UNSET;
    editor_state->mode ^= 1;
}

char editor_needs_secondary_cursor() {
    tool_t tool = editor_state->tool;
    if (tool >= TOOL_FLOOD_FILL) {
        return 0;
    }
    if (tool == TOOL_PIXEL) {
        return 0;
    }
    return editor_state->secondary_cursor_pos == EDITOR_CURSOR_UNSET;
}

void editor_set_secondary_cursor() {
    editor_state->secondary_cursor_pos = editor_state->primary_cursor_pos;
}

void editor_reset_secondary_cursor() {
    editor_state->secondary_cursor_pos = EDITOR_CURSOR_UNSET;
}

void editor_enqueue() {
    shape_t shape = {
        .tool = editor_state->tool,
        .color = editor_state->color,
        .fill = editor_state->fill,
        .pt1 = editor_state->primary_cursor_pos,
        .pt2 = editor_state->secondary_cursor_pos
    };
    enqueue(&editor_state->drawing_queue, &shape);
    editor_state->secondary_cursor_pos = EDITOR_CURSOR_UNSET;
}

char editor_dequeue(shape_t *shape) {
    return dequeue(&editor_state->drawing_queue, shape);
}
