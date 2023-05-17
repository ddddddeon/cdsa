#include <stdbool.h>

#ifndef MAX_HEAP_H
#define MAX_HEAP_H

typedef struct MaxHeap MaxHeap;

MaxHeap *max_heap_new(int size);
int max_heap_top(MaxHeap *h);
int max_heap_bottom(MaxHeap *h);
void max_heap_insert(MaxHeap *h, int value);
int max_heap_delete(MaxHeap *h, int value);
void max_heap_free(MaxHeap **h);
void max_heap_print(MaxHeap *h);

#endif /* MAX_HEAP_H  */
