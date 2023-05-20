#include <malloc.h>
#include <string.h>

#include "common.h"

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
    Entry *data[];
} HashMap;

HashMap *hash_map_new() {
    HashMap *p = malloc(sizeof(HashMap) + sizeof(Entry *) * INITIAL_CAP);
    p->cap = INITIAL_CAP;
    p->size = 0;
    memset(p->data, 0, sizeof(Entry *) * INITIAL_CAP);
    return p;
}

int hash_map_size(HashMap *h) { return h->size; }
int hash_map_cap(HashMap *h) { return h->cap; }

void hash_map_resize_data(HashMap **h) {
    ABORT_IF_NULL(*h);
    HashMap *new = malloc(sizeof(HashMap) + sizeof(Entry *) * (*h)->cap * 2);
    new->cap = (*h)->cap * 2;
    new->size = (*h)->size;
    memset(new->data, 0, sizeof(void *) * INITIAL_CAP);
    memcpy(new->data, (*h)->data, new->cap * sizeof(Entry *));
    free(*h);
    *h = new;
}

int compute_hash(const char *key) {
    int hash = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        if (i >= MAX_KEY_SIZE) {
            return -1;
        }
        hash += (key[i] - 'a') * (i + 1);
    }
    return hash;
}

void hash_map_set(HashMap *h, const char *key, void *value) {
    ABORT_IF_NULL(h);

    if (h->size >= h->cap) {
        hash_map_resize_data(&h);
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
