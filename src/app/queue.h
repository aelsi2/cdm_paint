// Drawing queue.

#pragma once

#include "graphics.h"

#define QUEUE_SIZE 16

// Represents a shape drawing queue.
typedef struct { 
    shape_t array[QUEUE_SIZE];
    int start_index;
    int end_index;
} drawing_queue_t;

// Initializes the queue.
void queue_init(drawing_queue_t* queue);

// Tries to enqueue a shape. Returns 0 on failure.
char enqueue(drawing_queue_t* queue, const shape_t *shape);

// Tries to dequeue a shape. Returns 0 on failure.
char dequeue(drawing_queue_t* queue, shape_t *shape);
