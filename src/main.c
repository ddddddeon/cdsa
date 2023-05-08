#include <stdio.h>

#include "array.h"
#include "cdsa.h"

int main(int argc, char* argv[]) {
    printf("array:\n");
    Array* a = array_new(10);
    array_insert(a, 1);
    array_insert(a, 2);
    printf("%s\n", array_has_duplicate(a) ? "true" : "false");
    array_insert_at(a, 3, 1);
    array_insert_at(a, 5, 0);
    array_update_at(a, 8, 1);
    array_print(a);
    array_reverse(a);
    array_insert(a, 12);
    array_insert(a, 0);
    array_insert(a, 100);
    array_insert(a, 2);
    array_insert(a, 35);
    array_print(a);
    Array* b = array_copy(a);
    array_print(b);
    array_bubble_sort(a);
    array_selection_sort(b);
    array_print(a);
    array_print(b);
    printf("%d\n", array_max_value(a));
    printf("%s\n", array_has_duplicate(a) ? "true" : "false");
    printf("%d\n", array_get(a, 2));
    printf("%d\n", array_index_of(a, 8));
    array_delete_at(a, 1);
    array_delete_at(a, 2);
    array_delete_at(a, 2);
    array_delete_at(a, 2);
    array_print(a);
    printf("%zu\n", array_size(a));
    array_fill(a, 0);
    array_print(a);
    array_update_at(a, 100, 5);
    array_print(a);
    array_free(&a);
    // array_print(a);

    printf("linked list:\n");
    LinkedList* l = linked_list_new();
    linked_list_insert_end(l, 0);
    linked_list_insert_end(l, 1);
    linked_list_print(l);
    linked_list_insert_end(l, 2);
    linked_list_print(l);
    linked_list_insert_beginning(l, 3);
    linked_list_insert_at(l, 4, 1);
    linked_list_insert_at(l, 10, 4);
    linked_list_print(l);
    linked_list_update_at(l, 11, 4);
    linked_list_print(l);
    linked_list_delete(l, 3);
    linked_list_print(l);
    linked_list_delete(l, 1);
    linked_list_print(l);
    linked_list_reverse(l);
    linked_list_print(l);
    linked_list_free(&l);
    // linked_list_print(l);

    printf("ordered set:\n");
    OrderedSet* o = ordered_set_new(10);
    ordered_set_insert(o, 12);
    ordered_set_print(o);
    ordered_set_insert(o, 4);
    ordered_set_print(o);
    ordered_set_insert(o, 24);
    ordered_set_print(o);
    ordered_set_insert(o, 0);
    ordered_set_print(o);
    ordered_set_insert(o, 24);
    ordered_set_print(o);
    ordered_set_insert(o, 4);
    ordered_set_print(o);
    ordered_set_insert(o, 0);
    ordered_set_print(o);
    ordered_set_insert(o, 35);
    ordered_set_print(o);
    ordered_set_insert(o, 1);
    ordered_set_print(o);
    ordered_set_insert(o, 1);
    ordered_set_print(o);
    ordered_set_insert(o, -1);
    ordered_set_print(o);
    ordered_set_insert(o, 25);
    ordered_set_print(o);
    ordered_set_insert(o, -1);
    ordered_set_print(o);
    ordered_set_insert(o, 35);
    ordered_set_print(o);
    ordered_set_insert(o, 12);
    ordered_set_print(o);
    ordered_set_insert(o, 24);
    ordered_set_print(o);
    OrderedSet* o2 = ordered_set_copy(o);
    ordered_set_print(o2);
    int i = ordered_set_index_of(o, 24);
    printf("%d\n", i);
    int j = ordered_set_index_of(o, 4);
    printf("%d\n", j);
    ordered_set_free(&o);

    printf("stack:\n");
    Stack* s = stack_new();
    stack_print(s);
    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    stack_print(s);

    StackItem r = stack_pop(s);
    if (r.exists) {
        printf("%d\n", r.value);
    } else {
        printf("Stack is empty!\n");
    }
    stack_print(s);

    StackItem r2 = stack_peek(s);
    if (r.exists) {
        printf("%d\n", r2.value);
    } else {
        printf("Stack is empty!\n");
    }
    stack_print(s);

    stack_pop(s);
    stack_pop(s);
    StackItem r3 = stack_pop(s);
    if (r3.exists) {
        printf("%d\n", r3.value);
    } else {
        printf("Stack is empty!\n");
    }

    stack_free(&s);

    printf("queue:\n");
    Queue* q = queue_new();
    queue_enqueue(q, 1);
    queue_enqueue(q, 2);
    queue_enqueue(q, 3);
    queue_enqueue(q, 4);
    queue_print(q);

    for (int i = 0; i < 6; i++) {
        QueueItem d = queue_dequeue(q);
        if (d.exists) {
            printf("%d\n", d.value);
        } else {
            printf("Queue is empty!\n");
        }
    }

    queue_print(q);
    queue_free(&q);
}
