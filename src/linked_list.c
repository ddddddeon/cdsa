#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#define ABORT_IF_LL_FREED(l)                                            \
    do {                                                                \
        if (l->freed) {                                                 \
            printf("[%s] linked list has been freed!\n", __FUNCTION__); \
            abort();                                                    \
        }                                                               \
    } while (0)

struct LinkedListNode {
    int value;
    struct LinkedListNode *next;
};

typedef struct LinkedListNode LinkedListNode;

typedef struct {
    int size;
    bool freed;
    LinkedListNode *first;
    LinkedListNode *last;
} LinkedList;

LinkedList *linked_list_new() {
    LinkedList *p = malloc(sizeof(LinkedList));
    p->size = 0;
    p->freed = false;
    p->first = NULL;
    p->last = NULL;

    return p;
}

LinkedListNode *linked_list_node_new(int n) {
    LinkedListNode *p = malloc(sizeof(LinkedListNode));
    p->value = n;
    p->next = NULL;
    return p;
}

void linked_list_print(LinkedList *ll) {
    ABORT_IF_LL_FREED(ll);

    LinkedListNode *curr = ll->first;
    if (curr == NULL) {
        return;
    }

    printf("[ ");

    do {
        printf("%d ", curr->value);
        curr = curr->next;
    } while (curr != NULL);

    printf("]\n");
}

void linked_list_insert_beginning(LinkedList *ll, int n) {
    ABORT_IF_LL_FREED(ll);
    LinkedListNode *new = linked_list_node_new(n);
    new->next = ll->first;
    ll->first = new;
}

void linked_list_insert_end(LinkedList *ll, int n) {
    ABORT_IF_LL_FREED(ll);
    LinkedListNode *new = linked_list_node_new(n);

    if (ll->size == 0) {
        ll->last = new;
        ll->first = new;
        ll->size++;
        return;
    }

    ll->last->next = new;
    ll->last = ll->last->next;
    ll->size++;
}

void linked_list_delete(LinkedList *ll, int n) {
    ABORT_IF_LL_FREED(ll);
    if (ll->first->value == n) {
        LinkedListNode *new = ll->first->next;
        if (new != NULL) {
            *ll->first = *new;
        }

        return;
    }

    LinkedListNode *curr = ll->first;
    while (curr->next != NULL) {
        if (curr->next->value == n) {
            free(curr->next);
            curr->next = curr->next->next;
            return;
        }
    }
}

void linked_list_reverse(LinkedList *ll) {
    ABORT_IF_LL_FREED(ll);
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

void linked_list_free(LinkedList *ll) {
    ABORT_IF_LL_FREED(ll);

    LinkedListNode *curr = ll->first;
    while (curr != NULL) {
        LinkedListNode *next = curr->next;
        free(curr);
        curr = next;
    }

    free(ll);
    ll->freed = true;
}