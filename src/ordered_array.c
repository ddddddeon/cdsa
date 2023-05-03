#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

typedef struct {
    size_t size;
    size_t cap;
    int data[];
} OrderedArray;

OrderedArray *ordered_array_new(size_t len) {
    OrderedArray *p = malloc(sizeof(OrderedArray) + len * sizeof(int));
    p->cap = len;
    p->size = 0;
    return p;
}

void ordered_array_free(OrderedArray **c) {
    ABORT_IF_NULL(c);
    free(*c);
    *c = NULL;
}

size_t ordered_array_size(OrderedArray *c) { return c->size; }
size_t ordered_array_cap(OrderedArray *c) { return c->cap; }

void ordered_array_print(OrderedArray *c) {
    ABORT_IF_NULL(c);
    printf("[ ");
    for (int i = 0; i < c->size; i++) {
        printf("%d ", c->data[i]);
    }
    printf("]\n");
}

int ordered_array_avail(OrderedArray *c) {
    ABORT_IF_NULL(c);
    return c->cap - c->size;
}

int ordered_array_insert(OrderedArray *c, int n) {
    ABORT_IF_NULL(c);
    if (ordered_array_avail(c) <= 0) {
        return -1;
    }

    if (c->size == 0) {
        *(c->data + 0) = n;
        c->size++;
        return 0;
    }

    if (n >= c->data[c->size - 1]) {
        *(c->data + c->size) = n;
        c->size++;
        return c->size - 1;
    }

    for (int i = 0; i < c->size; i++) {
        if (c->data[i] > n) {
            for (int idx = c->size - 1; idx >= i; idx--) {
                *(c->data + idx + 1) = c->data[idx];
            }
            *(c->data + i) = n;
            c->size++;
            return i;
        }
    }

    return -1;
}

void ordered_array_delete_at(OrderedArray *c, int i) {
    ABORT_IF_NULL(c);
    if (i >= c->size) {
        return;
    }

    for (int idx = i; idx < c->size; idx++) {
        *(c->data + idx) = c->data[idx + 1];
    }

    c->size--;
}

int ordered_array_get(OrderedArray *c, int i) { return c->data[i]; }

/*
 * TODO use binary search
 */
int ordered_array_index_of(OrderedArray *c, int n) {
    if (n > c->data[c->size - 1]) {
        return -1;
    }

    for (int i = 0; i < c->size; i++) {
        if (c->data[i] == n) {
            return i;
        }
    }

    return -1;
}
