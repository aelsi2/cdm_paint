#include "queue.h"
#include "ellipse.h"
#include "lines.h"
#include "core.h"
#include "screen.h"

void init_queue(draw_queue* q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int is_full(draw_queue* q){
    return q->size == QUEUE_SIZE;
}

void enqueue(draw_queue* q, shape* s) {
    if(is_full(q)){
        return;
    }
    //q->data[q->rear] = *s;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->size++;
}

shape* peek(draw_queue* q) {
    return &q->data[q->front];
}

void dequeue(draw_queue* q) {
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->size--;
}

void dr_draw_shape(shape* s){
    switch (s->type) {
        case SHAPE_LINE:
            dr_draw_line(s->pt1, s->pt2, COLOR_WHITE);
            break;
        case SHAPE_RECTANGLE:
            if(s->filled){
                dr_draw_filled_rect(s->pt1, s->pt2, s->color);
            } else {
                dr_draw_outline_rect(s->pt1, s->pt2, s->color);
            }
            break;
        case SHAPE_ELLIPSE:
            if(s->filled){
                dr_draw_filled_ellipse(s->pt1, s->pt2, s->pt3, s->color);
            } else {
                dr_draw_outline_ellipse(s->pt1, s->pt2, s->pt3, s->color);
            }
            break;
    }
}
