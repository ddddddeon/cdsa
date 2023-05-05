#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"

struct LinkedListNode {
    int value;
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

LinkedListNode *linked_list_node_new(int n) {
    LinkedListNode *p = malloc(sizeof(LinkedListNode));
    p->value = n;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void linked_list_print(LinkedList *ll) {
    ABORT_IF_NULL(ll);
    LinkedListNode *curr = ll->first;
    if (curr == NULL) {
        return;
    }

    printf("[ ");
    while (curr != NULL) {
        printf("%d ", curr->value);
        curr = curr->next;
    }

    printf("]\n");
}

void linked_list_insert_beginning(LinkedList *ll, int n) {
    ABORT_IF_NULL(ll);
    LinkedListNode *new = linked_list_node_new(n);
    new->prev = NULL;
    ll->first->prev = new;
    new->next = ll->first;
    ll->first = new;
    ll->size++;
}

void linked_list_insert_end(LinkedList *ll, int n) {
    ABORT_IF_NULL(ll);
    LinkedListNode *new = linked_list_node_new(n);

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

void linked_list_insert_at(LinkedList *ll, int n, int idx) {
    ABORT_IF_NULL(ll);
    if (idx < 0 || idx > ll->size) {
        return;
    }

    if (idx == 0) {
        linked_list_insert_beginning(ll, n);
        return;
    }

    if (idx == ll->size) {
        linked_list_insert_end(ll, n);
        return;
    }

    LinkedListNode *curr = ll->first;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }

    LinkedListNode *prev = curr->prev;
    LinkedListNode *new = linked_list_node_new(n);
    new->prev = prev;
    new->next = curr;
    prev->next = new;
    curr->prev = new;
    ll->size++;
}

void linked_list_update_at(LinkedList *ll, int n, int idx) {
    ABORT_IF_NULL(ll);
    if (idx < 0 || idx >= ll->size) {
        return;
    }

    LinkedListNode *curr = ll->first;
    for (int i = 0; i < idx; i++) {
        curr = curr->next;
    }

    LinkedListNode *next = curr->next;
    LinkedListNode *prev = curr->prev;
    LinkedListNode *new = linked_list_node_new(n);
    new->prev = prev;
    new->next = next;
    prev->next = new;
    next->prev = new;
    free(curr);
}

void linked_list_delete(LinkedList *ll, int n) {
    ABORT_IF_NULL(ll);
    if (ll->first->value == n) {
        LinkedListNode *new = ll->first->next;
        LinkedListNode *old_first = ll->first;
        free(old_first);
        ll->first = new;
        ll->first->prev = NULL;
        ll->size--;
        return;
    }

    LinkedListNode *curr = ll->first;
    while (curr->next != NULL) {
        if (curr->next->value == n) {
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
