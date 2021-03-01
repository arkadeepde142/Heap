#include <stdio.h>
#include "heap.h"

int comp(const void *a, const void *b)
{
    return  - *(int *)a + *(int *)b; 
}

int main()
{
    heap h = init_heap(16, comp, sizeof(int));
    int arr[] = {1,4,2,3};
    insert_into_heap(&h, arr);
    insert_into_heap(&h, arr + 1);
    insert_into_heap(&h, arr + 2);
    insert_into_heap(&h, arr + 3);
    while(h.size > 0)
    {
        printf("%d \n", *(int *)get_highest_priority(&h));
        remove_highest_priority(&h);
    }
}