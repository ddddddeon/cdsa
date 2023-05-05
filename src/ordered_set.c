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
} OrderedSet;

OrderedSet *ordered_set_new(size_t len) {
    OrderedSet *p = malloc(sizeof(OrderedSet) + len * sizeof(int));
    p->cap = len;
    p->size = 0;
    return p;
}

void ordered_set_free(OrderedSet **c) {
    ABORT_IF_NULL(c);
    free(*c);
    *c = NULL;
}

size_t ordered_set_size(OrderedSet *c) {
    ABORT_IF_NULL(c);
    return c->size;
}
size_t ordered_set_cap(OrderedSet *c) {
    ABORT_IF_NULL(c);
    return c->cap;
}

void ordered_set_print(OrderedSet *c) {
    ABORT_IF_NULL(c);
    printf("[ ");
    for (int i = 0; i < c->size; i++) {
        printf("%d ", c->data[i]);
    }
    printf("]\n");
}

int ordered_set_avail(OrderedSet *c) {
    ABORT_IF_NULL(c);
    return c->cap - c->size;
}

int ordered_set_insert(OrderedSet *c, int n) {
    ABORT_IF_NULL(c);
    if (ordered_set_avail(c) <= 0) {
        return -1;
    }

    if (c->size == 0) {
        *(c->data + 0) = n;
        c->size++;
        return 0;
    }

    if (n > c->data[c->size - 1]) {
        *(c->data + c->size) = n;
        c->size++;
        return c->size - 1;
    }

    // binary search O(log n)
    int lower = 0;
    int upper = c->size - 1;
    int mid;

    while (lower <= upper) {
        mid = (upper + lower) / 2;
        int mid_value = c->data[mid];

        if (n == mid_value) {
            return mid;
        }

        if (n < mid_value) {
            upper = mid - 1;
        } else if (n > mid_value) {
            lower = mid + 1;
        }
    }

    int i = lower % c->size;

    // linear shift O(n - i), worst case i = 0: O(n)
    for (int idx = c->size - 1; idx >= i; idx--) {
        *(c->data + idx + 1) = c->data[idx];
    }

    *(c->data + i) = n;
    c->size++;
    return i;
}

void ordered_set_delete_at(OrderedSet *c, int i) {
    ABORT_IF_NULL(c);
    if (i >= c->size) {
        return;
    }

    for (int idx = i; idx < c->size; idx++) {
        *(c->data + idx) = c->data[idx + 1];
    }

    c->size--;
}

int ordered_set_get(OrderedSet *c, int i) { return c->data[i]; }

// binary search O(log n)
int ordered_set_index_of(OrderedSet *c, int n) {
    ABORT_IF_NULL(c);
    if (n > c->data[c->size - 1]) {
        return -1;
    }

    int lower = 0;
    int upper = c->size - 1;
    int mid;

    while (lower <= upper) {
        mid = (upper + lower) / 2;
        int mid_value = c->data[mid];

        if (n == mid_value) {
            return mid;
        }

        if (n < mid_value) {
            upper = mid - 1;
        } else if (n > mid_value) {
            lower = mid + 1;
        }
    }
    return -1;
}
