#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>

typedef struct heap {
    void *arr;
    size_t elem_size;
    size_t capacity;
    size_t size;
    int (*comp)(const void *, const void *);
} heap;

heap init_heap(size_t capacity, int (*comp)(const void *, const void *), size_t elem_size);
void destroy_heap(heap *ptr);
void insert_into_heap(heap *ptr, void * element);
void remove_highest_priority(heap *ptr);
void * get_highest_priority(const heap *ptr);
size_t percolate_down(heap * ptr, size_t index, void * value);
size_t percolate_up(heap * ptr, size_t index, void * value);


#endif