// Editor functionality.

#pragma once

#include "graphics.h"
#include "app/queue.h"

#define EDITOR_CURSOR_UNSET (-1)
#define MENU_ROW_COUNT 3

// Represents the current editor mode.
typedef enum {
    MODE_NORMAL = 0,
    MODE_MENU = 1
} editor_mode_t;

// Represents the selected row of the menu.
typedef enum : char {
    MENU_TOOL = 0,
    MENU_COLOR = 1,
    MENU_FILL = 2,
} menu_row_t;

// Represents the state of the editor.
typedef struct {
    editor_mode_t mode;
    tool_t tool;
    color_t color;
    char fill;
    int primary_cursor_pos;
    point_t secondary_cursor_pos;
    menu_row_t menu_cursor_pos;
    drawing_queue_t drawing_queue;
} editor_state_t;

/*
 * The current editor state.
 * Should be set before using any of the editor_* functions.
 */
extern editor_state_t *editor_state;

// Initializes the current editor state.
void editor_init();

// Toggles the mode of the current editor (between menu and normal).
void editor_toggle_mode();

// Moves the cursor by the specified amount.
// Behavior depends on the current mode.
void editor_move_cursor(int dir_x, int dir_y);

// Checks if the secondary cursor needs to be positioned before enqueuing a drawing
// operation with the current tool.
char editor_needs_secondary_cursor();

// Puts the secondary cursor at the primary cursor.
void editor_set_secondary_cursor();

// Removes the secondary cursor.
void editor_reset_secondary_cursor();

// Enqueues a new drawing operation based on the selected parameters.
void editor_enqueue();

// Tries to dequeue a drawing operation. Returns 0 on failure.
char editor_dequeue(shape_t *shape);
