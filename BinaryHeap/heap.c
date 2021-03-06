#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    function to get pointer at an index.
    -------------------
    return type : void *
    -------------------
    parameters : heap type pointer, integer (index)

    returns ptr->arr + ptr->elem_size * index
*/
void *get_pointer_at_index(heap *ptr, size_t index)
{
    return ptr->arr + ptr->elem_size * index;
}
/*
    function to initialise a heap.
    -------------------
    return type : heap
    -------------------
    parameters : capacity, size of each element, function pointer of a comparator function
    -------------------
    declare a heap,
    assigns the heap variables,
    allocates space for the elements,
    initialises size =0,

    returns the heap
*/
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
/*
    function to delete a heap.
    -------------------
    return type : void 
    -------------------
    parameters : heap type pointer
    -------------------
    free the array pointer,
    assign null 
*/
void destroy_heap(heap *ptr)
{
    free(ptr->arr);
    ptr->arr = NULL;
};
/*
    function to insert an element into heap.
    -------------------
    return type : void 
    -------------------
    parameters : heap type pointer, void * (pointer to the element)
    check if size <= capacity, if no, exit,
    else
    call : percolate_up(ptr, ptr->size++, element),
    copy the element at the index where it belongs(satisfying heap property)
*/
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
/*
    function to delete highest priority element from heap.
    -------------------
    return type : void 
    -------------------
    parameters : heap type pointer
    -------------------
    call : percolate_down(ptr, --ptr->size, get_pointer_at_index(ptr, --ptr->size)),
    copy the element at the index where it belongs(satisfying heap property)
*/
void remove_highest_priority(heap *ptr)
{

    size_t index = percolate_down(ptr, 0, get_pointer_at_index(ptr, --ptr->size));
    memcpy(get_pointer_at_index(ptr, index), get_pointer_at_index(ptr, ptr->size), ptr->elem_size);
}
/*
    function to return highest priority element from heap.
    -------------------
    return type : void *
    -------------------
    parameters : heap type pointer
    -------------------
    return first array element reference
*/
void *get_highest_priority(const heap *ptr)
{
    return ptr->arr;
}
/*
    function to percolate down the heap.
    -------------------
    return type : size_t (integer)
    -------------------
    parameters : heap type pointer, index, void * value
    -------------------
    removes the highest priority element which generates a hole.
    returns the index of the array where the hole stops after percolating down
    (considering that the last array element will replace the hole)
*/
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
/*
    function to percolate up the heap.
    -------------------
    return type : size_t (integer)
    -------------------
    parameters : heap type pointer, index, void * value
    -------------------
    adds the new element to the array.
    returns the index of the array where the new element stops after percolating up
    (satisfying the heap property).
*/
size_t percolate_up(heap *ptr, size_t index, void *value)
{
    while (index != 0 && ptr->comp(get_pointer_at_index(ptr, (index - 1) / 2), value) > 0)
    {
        memcpy(get_pointer_at_index(ptr, index), get_pointer_at_index(ptr,  (index - 1)/2), ptr->elem_size);
        index = (index - 1) / 2;
    }
    return index;
}