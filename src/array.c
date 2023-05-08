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

Array *array_copy(Array *c) {
    Array *new = malloc(sizeof(Array) + c->cap * sizeof(int));
    new->cap = c->cap;
    new->size = c->size;
    memcpy(new->data, c->data, c->cap * sizeof(int));
    return new;
}

void array_free(Array **c) {
    ABORT_IF_NULL(c);
    free(*c);
    *c = NULL;
}

size_t array_size(Array *c) {
    ABORT_IF_NULL(c);
    return c->size;
}
size_t array_cap(Array *c) {
    ABORT_IF_NULL(c);
    return c->cap;
}

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

int array_get(Array *c, int i) {
    ABORT_IF_NULL(c);
    return c->data[i];
}

int array_index_of(Array *c, int n) {
    ABORT_IF_NULL(c);
    for (int i = 0; i < c->size; i++) {
        if (c->data[i] == n) {
            return i;
        }
    }

    return -1;
}

// O(n)
int array_max_value(Array *c) {
    ABORT_IF_NULL(c);
    int max = c->data[0];
    for (int i = 1; i < c->size; i++) {
        if (c->data[i] > max) {
            max = c->data[i];
        }
    }
    return max;
}

// O(n * 2) -> O(n)
bool array_has_duplicate(Array *c) {
    ABORT_IF_NULL(c);

    // might allocate a massive array
    bool existing_nums[array_max_value(c) + 1];

    for (int i = 0; i <= c->size; i++) {
        if (existing_nums[c->data[i]] == true) {
            return true;
        }
        existing_nums[c->data[i]] = true;
    }
    return false;
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

// O(n^2)
void array_bubble_sort(Array *c) {
    ABORT_IF_NULL(c);
    bool sorted = false;
    int top = c->size - 1;

    // we could just run while top > 0,
    // but if we pass through while top is still > 0 and
    // it's already sorted, we want to finish early
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < top; i++) {
            if (c->data[i] > c->data[i + 1]) {
                sorted = false;
                int tmp = c->data[i];
                *(c->data + i) = c->data[i + 1];
                *(c->data + i + 1) = tmp;
            }
        }
        top--;
    }
}

// O(n^2) but faster than bubble sort
void array_selection_sort(Array *c) {
    ABORT_IF_NULL(c);
    for (int i = 0; i < c->size; i++) {
        int lowest_number_idx = i;

        for (int j = i + 1; j < c->size; j++) {
            if (c->data[j] < c->data[lowest_number_idx]) {
                lowest_number_idx = j;
            }
        }

        if (i != lowest_number_idx) {
            int tmp = c->data[i];
            *(c->data + i) = c->data[lowest_number_idx];
            *(c->data + lowest_number_idx) = tmp;
        }
    }
}
