#include "queue.h"

void queue_init(drawing_queue_t* queue) {
    queue->start_index = 0;
    queue->end_index = 0;
}

char enqueue(drawing_queue_t* queue, const shape_t *shape) {
    int start_index = queue->start_index;
    int end_index = queue->end_index;
    int next_index = (end_index + 1) % QUEUE_SIZE;

    if (next_index == start_index) {
        return 0;
    }
    queue->array[end_index] = *shape;
    queue->end_index = next_index;
    return 1;
}

char dequeue(drawing_queue_t* queue, shape_t *shape) {
    int start_index = queue->start_index;
    int end_index = queue->end_index;
    int next_index = (start_index + 1) % QUEUE_SIZE;

    if (start_index == end_index) {
        return 0;
    }
    *shape = queue->array[start_index];
    queue->start_index = next_index;
    return 1;
}

