#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"
typedef struct {
    int bottom_idx;
    int cap;
    int heap[];
} MaxHeap;

MaxHeap *max_heap_new(int size) {
    MaxHeap *p = malloc(sizeof(MaxHeap) + sizeof(int) * size);
    p->cap = size;
    p->bottom_idx = -1;
    return p;
}

int max_heap_top_idx(MaxHeap *h) {
    ABORT_IF_NULL(h);
    return 0;
}

int max_heap_top(MaxHeap *h) {
    ABORT_IF_NULL(h);
    if (h->bottom_idx == -1) {
        return -1;
    }

    return h->heap[0];
}

int max_heap_bottom_idx(MaxHeap *h) {
    ABORT_IF_NULL(h);
    return h->bottom_idx;
}

int max_heap_bottom(MaxHeap *h) {
    ABORT_IF_NULL(h);
    if (h->bottom_idx == -1) {
        return -1;
    }

    return h->heap[h->bottom_idx];
}

int max_heap_parent(int i) { return (i - 1) / 2; }
int max_heap_left_child(int i) { return (i * 2) + 1; }
int max_heap_right_child(int i) { return (i * 2) + 2; }

void max_heap_print(MaxHeap *h) {
    printf("[ ");
    for (int i = 0; i <= h->bottom_idx; i++) {
        printf("%d ", h->heap[i]);
    }
    printf("]\n");
}

bool max_heap_insert(MaxHeap *h, int value) {
    ABORT_IF_NULL(h);

    if (h->bottom_idx >= h->cap) {
        return false;
    }

    h->bottom_idx++;
    int i = h->bottom_idx;
    int parent = max_heap_parent(i);
    *(h->heap + i) = value;

    // heapify up
    while (i > 0 && h->heap[i] > h->heap[parent]) {
        int tmp = h->heap[i];
        *(h->heap + i) = h->heap[parent];
        *(h->heap + parent) = tmp;
        i = parent;
        parent = max_heap_parent(i);
    }

    return true;
}

int max_heap_greater_child(MaxHeap *h, int i) {
    int left_idx = max_heap_left_child(i);
    int right_idx = max_heap_right_child(i);

    if (right_idx > h->bottom_idx) {
        return left_idx;
    }

    int left_value = h->heap[left_idx];
    int right_value = h->heap[right_idx];
    return (left_value > right_value) ? left_idx : right_idx;
}

bool max_heap_has_greater_child(MaxHeap *h, int i) {
    int left_child = max_heap_left_child(i);
    int right_child = max_heap_right_child(i);

    return (
        (left_child <= h->bottom_idx && h->heap[left_child] > h->heap[i]) ||
        (right_child <= h->bottom_idx && h->heap[right_child] > h->heap[i]));
}

int max_heap_delete(MaxHeap *h) {
    ABORT_IF_NULL(h);
    if (h->bottom_idx < 0) {
        return -1;
    }

    int last_value = max_heap_bottom(h);
    h->bottom_idx--;
    *(h->heap + 0) = last_value;

    int trickle_idx = 0;

    // heapify down
    while (max_heap_has_greater_child(h, trickle_idx)) {
        int greater_child_idx = max_heap_greater_child(h, trickle_idx);
        int tmp = h->heap[trickle_idx];
        printf("swapping %d and %d\n", h->heap[trickle_idx],
               h->heap[greater_child_idx]);

        *(h->heap + trickle_idx) = h->heap[greater_child_idx];
        *(h->heap + greater_child_idx) = tmp;

        trickle_idx = greater_child_idx;

        max_heap_print(h);
    }
}
