#include <malloc.h>
#include <string.h>

#include "common.h"
#include "queue.h"

#define INITIAL_CAP 1024
#define MAX_KEY_SIZE 1024
#define COLLISION_RETRIES 64

typedef struct {
    const char *key;
    void *value;
} Entry;

typedef struct {
    int cap;
    int size;
    Entry **data;
} HashMap;

HashMap *hash_map_new() {
    HashMap *p = malloc(sizeof(HashMap));
    p->cap = INITIAL_CAP;
    p->size = 0;
    p->data = malloc(sizeof(Entry *) * INITIAL_CAP);
    memset(p->data, 0, sizeof(Entry *) * INITIAL_CAP);
    return p;
}

int hash_map_size(HashMap *h) { return h->size; }
int hash_map_cap(HashMap *h) { return h->cap; }

void hash_map_resize_data(HashMap *h) {
    ABORT_IF_NULL(h);
    Entry **data = realloc(h->data, sizeof(Entry *) * (h->cap * 2));
    h->data = data;
    h->cap *= 2;
}

int compute_hash(const char *key) {
    int hash = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        if (i >= MAX_KEY_SIZE) {
            return -1;
        }
        hash += (key[i] - '0') * (i + 1);
    }
    return hash;
}

void hash_map_set(HashMap *h, const char *key, void *value) {
    ABORT_IF_NULL(h);

    if (h->size >= h->cap) {
        hash_map_resize_data(h);
    }

    int hash = compute_hash(key);
    if (hash < 0) {
        printf("Key too large! Max size is %d\n", MAX_KEY_SIZE);
        return;
    }

    int idx = hash % h->cap;
    int new_idx = ((h->cap - idx) * (h->cap - idx)) % h->cap;
    int i = h->cap / 2;
    int tries = 0;

    do {
        if (h->data[idx] == NULL) {
            Entry *entry = malloc(sizeof(Entry));
            entry->key = key;
            entry->value = value;
            *(h->data + idx) = entry;
            h->size++;
            return;
        } else {
            if (strcmp(h->data[idx]->key, key) == 0) {
                h->data[idx]->value = (void *)value;
                return;
            }

            idx = new_idx + i;
            i++;
            tries++;
        }
    } while (h->data[idx] != NULL && tries <= COLLISION_RETRIES);
}

void *hash_map_get(HashMap *h, const char *key) {
    ABORT_IF_NULL(h);
    int hash = compute_hash(key);

    if (h->data[hash] != NULL) {
        return h->data[hash]->value;
    }
    return NULL;
}

void hash_map_delete(HashMap **h, const char *key) {
    ABORT_IF_NULL(*h);
    int hash = compute_hash(key);
    int idx = hash % (*h)->cap;

    if ((*h)->data[idx] != NULL) {
        free((*h)->data[idx]);
        (*h)->data[idx] = NULL;
    }
}

void hash_map_free(HashMap **h) {
    for (int i = 0; i < (*h)->size; i++) {
        if ((*h)->data[i] != NULL) {
            free(&(*h)->data[i]);
            (*h)->data[i] = NULL;
        }
    }
    free(*h);
    *h = NULL;
}

Queue *hash_map_to_queue(HashMap *h) {
    Queue *q = queue_new();
    for (int i = 0; i < h->cap; i++) {
        if (h->data[i] != NULL) {
            queue_enqueue(q, h->data[i]->value);
        }
    }
    return q;
}

void hash_map_print_string(HashMap *h) {
    for (int i = 0; i < h->cap; i++) {
        if (h->data[i] != NULL) {
            // only works for strings
            printf("%s: %s\n", h->data[i]->key,
                   (const char *)h->data[i]->value);
        }
    }
}

void hash_map_print_int(HashMap *h) {
    for (int i = 0; i < h->cap; i++) {
        if (h->data[i] != NULL) {
            // only works for ints
            printf("%s: %d\n", h->data[i]->key, *(int *)h->data[i]->value);
        }
    }
}

void hash_map_print_ptr(HashMap *h) {
    for (int i = 0; i < h->cap; i++) {
        if (h->data[i] != NULL) {
            // only works for pointers
            printf("%s: %p\n", h->data[i]->key, h->data[i]->value);
        }
    }
}
