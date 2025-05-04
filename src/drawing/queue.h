#pragma once
#include "screen.h"

#define QUEUE_SIZE 16

typedef enum : unsigned char {
    SHAPE_LINE = 0,
    SHAPE_RECTANGLE = 1,
    SHAPE_ELLIPSE = 2
} shape_type_t;

typedef struct {
    shape_type_t type;
    unsigned char filled;
    color_t color;
    point_t pt1;
    point_t pt2;
} shape;

typedef struct { 
    shape data[QUEUE_SIZE];
    int front;
    int rear;
    int size;
} draw_queue;

void init_queue(draw_queue* q);

int is_full(draw_queue* q);

void enqueue(draw_queue* q, shape* s);

shape* peek(draw_queue* q);

void dequeue(draw_queue* q);

void dr_draw_shape(shape* s);
