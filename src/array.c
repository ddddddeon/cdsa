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
} Array;

Array *array_new(size_t len) {
    Array *p = malloc(sizeof(Array) + len * sizeof(int));
    p->cap = len;
    p->size = 0;
    return p;
}

void array_free(Array **c) {
    ABORT_IF_NULL(c);
    free(*c);
    *c = NULL;
}

size_t array_size(Array *c) { return c->size; }
size_t array_cap(Array *c) { return c->cap; }

void array_print(Array *c) {
    ABORT_IF_NULL(c);
    printf("[ ");
    for (int i = 0; i < c->size; i++) {
        printf("%d ", c->data[i]);
    }
    printf("]\n");
}

int array_avail(Array *c) {
    ABORT_IF_NULL(c);
    return c->cap - c->size;
}

int array_insert(Array *c, int n) {
    ABORT_IF_NULL(c);
    if (array_avail(c) <= 0) {
        return -1;
    }

    int idx = c->size;
    *(c->data + idx) = n;
    c->size++;
    return idx;
}

int array_insert_at(Array *c, int n, int i) {
    ABORT_IF_NULL(c);
    if (c->cap - c->size < 1 || i >= c->cap || i < 0) {
        return -1;
    }

    c->size++;
    for (int idx = c->size - 1; idx >= i; idx--) {
        *(c->data + idx + 1) = c->data[idx];
    }

    *(c->data + i) = n;
    return i;
}

int array_update_at(Array *c, int n, int i) {
    ABORT_IF_NULL(c);
    if (i >= c->cap) {
        return -1;
    }

    *(c->data + i) = n;
    return i;
}

void array_delete_at(Array *c, int i) {
    ABORT_IF_NULL(c);
    if (i >= c->size) {
        return;
    }

    for (int idx = i; idx < c->size; idx++) {
        *(c->data + idx) = c->data[idx + 1];
    }

    c->size--;
}

int array_get(Array *c, int i) { return c->data[i]; }

int array_index_of(Array *c, int n) {
    for (int i = 0; i < c->size; i++) {
        if (c->data[i] == n) {
            return i;
        }
    }

    return -1;
}

void array_fill(Array *c, int n) {
    ABORT_IF_NULL(c);
    c->size = 0;
    for (int i = 0; i < c->cap; i++) {
        *(c->data + i) = n;
        c->size++;
    }
}

void array_reverse(Array *c) {
    ABORT_IF_NULL(c);
    for (int i = 0; i < c->size / 2; i++) {
        int tmp = c->data[i];
        *(c->data + i) = c->data[c->size - i - 1];
        *(c->data + c->size - i - 1) = tmp;
    }
}
