#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *get_pointer_at_index(heap *ptr, size_t index)
{
    return ptr->arr + ptr->elem_size * index;
}

heap init_heap(size_t capacity, int (*comp)(const void *, const void *), size_t elem_size)
{
    heap h;
    h.elem_size = elem_size;
    h.capacity = capacity;
    h.size = 0;
    h.comp = comp;
    h.arr = malloc(capacity * elem_size);
    return h;
}
void destroy_heap(heap *ptr)
{
    free(ptr->arr);
    ptr->arr = NULL;
};
void insert_into_heap(heap *ptr, void *element)
{
    if (ptr->size == ptr->capacity)
    {
        printf("Overflow Error");
        return;
    }
    int index = percolate_up(ptr, ptr->size++, element);
    memcpy(get_pointer_at_index(ptr, index), element, ptr->elem_size);
}
void remove_highest_priority(heap *ptr)
{

    size_t index = percolate_down(ptr, 0, get_pointer_at_index(ptr, --ptr->size));
    memcpy(get_pointer_at_index(ptr, index), get_pointer_at_index(ptr, ptr->size), ptr->elem_size);
}
void *get_highest_priority(const heap *ptr)
{
    return ptr->arr;
}
size_t percolate_down(heap *ptr, size_t index, void *value)
{

    while (1)
    {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        if (left >= ptr->size)
        {
            break;
        }

        size_t child;

        if (left == ptr->size - 1)
        {
            child = left;
        }
        else if (ptr->comp(get_pointer_at_index(ptr, left), get_pointer_at_index(ptr, right)) <= 0)
        {
            child = left;
        }
        else
        {
            child = right;
        }

        if (ptr->comp(value, get_pointer_at_index(ptr, child)) <= 0)
        {
            break;
        }
        else
        {
            memcpy(get_pointer_at_index(ptr, index), get_pointer_at_index(ptr, child), ptr->elem_size);
            index = child;
        }
    }
    return index;
}
size_t percolate_up(heap *ptr, size_t index, void *value)
{
    while (index != 0 && ptr->comp(get_pointer_at_index(ptr, (index - 1) / 2), value) > 0)
    {
        memcpy(get_pointer_at_index(ptr, index), get_pointer_at_index(ptr,  (index - 1)/2), ptr->elem_size);
        index = (index - 1) / 2;
    }
    return index;
}