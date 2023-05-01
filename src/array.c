#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    size_t size;
    size_t cap;
    bool freed;
    int data[];
} Array;

#define ABORT_IF_FREED(c)                                         \
    do {                                                          \
        if (c->freed) {                                           \
            printf("[%s] array has been freed!\n", __FUNCTION__); \
            abort();                                              \
        }                                                         \
    } while (0)

Array *array_new(size_t len) {
    Array *p = malloc(sizeof(Array) + len * sizeof(int));
    p->cap = len;
    p->size = 0;
    p->freed = false;
    return p;
}

void array_free(Array *c) {
    c->freed = true;
    free(c);
}

size_t array_size(Array *c) { return c->size; }
size_t array_cap(Array *c) { return c->cap; }

void array_display(Array *c) {
    ABORT_IF_FREED(c);
    printf("[ ");
    for (int i = 0; i < c->size; i++) {
        printf("%d ", c->data[i]);
    }
    printf("]\n");
}

int array_avail(Array *c) {
    ABORT_IF_FREED(c);
    return c->cap - c->size;
}

int array_insert(Array *c, int n) {
    ABORT_IF_FREED(c);
    if (array_avail(c) <= 0) {
        return -1;
    }

    int idx = c->size;
    *(c->data + idx) = n;
    c->size++;
    return idx;
}

int array_insert_at(Array *c, int n, int i) {
    ABORT_IF_FREED(c);
    if (c->cap - c->size < 1 || i >= c->cap) {
        return -1;
    }

    c->size++;
    for (int idx = c->size - 1; idx >= i; idx--) {
        printf("* %d\n", c->data[idx]);
        *(c->data + idx + 1) = c->data[idx];
    }

    *(c->data + i) = n;
    return i;
}

int array_update_at(Array *c, int n, int i) {
    ABORT_IF_FREED(c);
    if (i >= c->cap) {
        return -1;
    }

    *(c->data + i) = n;
    return i;
}

int array_delete_at(Array *c, int i) {
    ABORT_IF_FREED(c);
    if (i >= c->size) {
        return -1;
    }

    for (int idx = i; i < c->size; i++) {
        *(c->data + i) = c->data[i + 1];
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
    ABORT_IF_FREED(c);
    c->size = 0;
    for (int i = 0; i < c->cap; i++) {
        *(c->data + i) = n;
        c->size++;
    }
}
