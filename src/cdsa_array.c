#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    size_t size;
    size_t cap;
    bool freed;
    int data[];
} cdsa_array;

#define ABORT_IF_FREED                                                              \
    do {                                                                            \
        if (c->freed) {                                                             \
            printf("[%s:%d] cdsa_array has been freed!\n", __FUNCTION__, __LINE__); \
            abort();                                                                \
        }                                                                           \
} while (0)

cdsa_array *cdsa_array_new(size_t len) {
    cdsa_array *p = malloc(sizeof(cdsa_array) + len * sizeof(int));
    p->cap = len;
    p->size = 0;
    p->freed = false;
    return p;
}

void cdsa_array_free(cdsa_array *c) {
    free(c);
    c->freed = true;
}

size_t cdsa_array_size(cdsa_array *c) { return c->size; }
size_t cdsa_array_cap(cdsa_array *c) { return c->cap; }

void cdsa_array_display(cdsa_array *c) {
    ABORT_IF_FREED;
    printf("[ ");
    for (int i = 0; i < c->size; i++) {
        printf("%d ", c->data[i]);
    }
    printf("]\n");
}

int cdsa_array_avail(cdsa_array *c) {
    ABORT_IF_FREED;
    return c->cap - c->size;
}

int cdsa_array_insert(cdsa_array *c, int n) {
    ABORT_IF_FREED;
    if (cdsa_array_avail(c) <= 0) {
        return -1;
    }

    int idx = c->size;
    *(c->data + idx) = n;
    c->size++;
    return idx;
}

int cdsa_array_insert_at(cdsa_array *c, int n, int i) {
    ABORT_IF_FREED;
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

int cdsa_array_update_at(cdsa_array *c, int n, int i) {
    ABORT_IF_FREED;
    if (i >= c->cap) {
        return -1;
    }

    *(c->data + i) = n;
    return i;
}

int cdsa_array_delete_at(cdsa_array *c, int i) {
  ABORT_IF_FREED;
  if (i >= c->size) {
    return -1;
  }

  for (int idx = i; i < c->size; i++) {
    *(c->data + i) = c->data[i + 1];
  }

  c->size--;
}

void cdsa_array_fill(cdsa_array *c, int n) {
    ABORT_IF_FREED;
    c->size = 0;
    for (int i = 0; i < c->cap; i++) {
        *(c->data + i) = n;
        c->size++;
    }
}
