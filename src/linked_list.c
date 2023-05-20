#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

struct LinkedListNode {
    void *value;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
};

typedef struct LinkedListNode LinkedListNode;

typedef struct {
    int size;
    LinkedListNode *first;
    LinkedListNode *last;
} LinkedList;

LinkedList *linked_list_new() {
    LinkedList *p = malloc(sizeof(LinkedList));
    p->size = 0;
    p->first = NULL;
    p->last = NULL;
    return p;
}

LinkedListNode *linked_list_node_new(void *value) {
    LinkedListNode *p = malloc(sizeof(LinkedListNode));
    p->value = value;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

int linked_list_size(LinkedList *ll) { return ll->size; }
void *linked_list_first(LinkedList *ll) { return ll->first->value; }
void *linked_list_last(LinkedList *ll) { return ll->last->value; }

void *linked_list_get(LinkedList *ll, int idx) {
    ABORT_IF_NULL(ll);
    if (idx < 0 || idx >= ll->size) {
        return NULL;
    }

    LinkedListNode *curr = ll->first;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }

    return curr->value;
}

void linked_list_print(LinkedList *ll) {
    ABORT_IF_NULL(ll);
    LinkedListNode *curr = ll->first;
    if (curr == NULL) {
        return;
    }

    // will only work for strings
    printf("[ ");
    while (curr != NULL) {
        printf("%s ", (const char *)curr->value);
        curr = curr->next;
    }

    printf("]\n");
}

void linked_list_insert_beginning(LinkedList *ll, void *value) {
    ABORT_IF_NULL(ll);
    LinkedListNode *new = linked_list_node_new(value);

    if (ll->size == 0) {
        ll->last = new;
        ll->first = new;
        ll->size++;
        return;
    }

    new->prev = NULL;
    ll->first->prev = new;
    new->next = ll->first;
    ll->first = new;
    ll->size++;
}

void linked_list_insert_end(LinkedList *ll, void *value) {
    ABORT_IF_NULL(ll);
    LinkedListNode *new = linked_list_node_new(value);

    if (ll->size == 0) {
        ll->last = new;
        ll->first = new;
        ll->size++;
        return;
    }

    new->prev = ll->last;
    ll->last->next = new;
    ll->last = ll->last->next;
    ll->size++;
}

void linked_list_insert_at(LinkedList *ll, void *value, int idx) {
    ABORT_IF_NULL(ll);
    if (idx < 0 || idx > ll->size) {
        return;
    }

    if (idx == 0) {
        linked_list_insert_beginning(ll, value);
        return;
    }

    if (idx == ll->size) {
        linked_list_insert_end(ll, value);
        return;
    }

    LinkedListNode *curr = ll->first;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }

    LinkedListNode *prev = curr->prev;
    LinkedListNode *new = linked_list_node_new(value);
    new->prev = prev;
    new->next = curr;
    prev->next = new;
    curr->prev = new;
    ll->size++;
}

void linked_list_update_at(LinkedList *ll, void *value, int idx) {
    ABORT_IF_NULL(ll);
    if (idx < 0 || idx >= ll->size) {
        return;
    }

    LinkedListNode *curr = ll->first;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }
    curr->value = value;
}

void linked_list_delete(LinkedList *ll, void *value) {
    ABORT_IF_NULL(ll);
    if (ll->first->value == value) {
        LinkedListNode *new = ll->first->next;
        LinkedListNode *old_first = ll->first;
        free(old_first);
        ll->first = new;
        ll->first->prev = NULL;
        ll->size--;
        return;
    }

    if (ll->last->value == value) {
        LinkedListNode *tmp = ll->last;
        ll->last->prev->next = NULL;
        ll->last = ll->last->prev;
        ll->size--;
        free(tmp);
        return;
    }

    LinkedListNode *curr = ll->first;
    while (curr->next != NULL) {
        if (curr->next->value == value) {
            LinkedListNode *tmp = curr->next;
            curr->next = curr->next->next;
            curr->next->prev = curr;
            free(tmp);
            ll->size--;
            return;
        }
        curr = curr->next;
    }
}

void linked_list_reverse(LinkedList *ll) {
    ABORT_IF_NULL(ll);
    LinkedListNode *prev = NULL;
    LinkedListNode *curr = ll->first;
    LinkedListNode *next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    ll->last = ll->first;
    ll->first = prev;
}

void linked_list_free(LinkedList **ll) {
    ABORT_IF_NULL(*ll);
    LinkedListNode *curr = (*ll)->first;
    while (curr != NULL) {
        LinkedListNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(*ll);
    *ll = NULL;
}
