#include <stdio.h>

#include "cdsa.h"
#include "linked_list.h"

int main(int argc, char* argv[]) {
    printf("array:\n");
    Array* a = array_new(10);
    array_insert(a, 1);
    array_insert(a, 2);
    array_insert_at(a, 3, 1);
    array_insert_at(a, 5, 0);
    array_update_at(a, 8, 1);
    array_print(a);
    array_reverse(a);
    array_print(a);
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
    printf("%d\n", stack_pop(s));
    stack_print(s);
    printf("%d\n", stack_peek(s));
    stack_print(s);
    stack_free(&s);

    printf("queue:\n");
    Queue* q = queue_new();
    queue_enqueue(q, 1);
    queue_enqueue(q, 2);
    queue_enqueue(q, 3);
    queue_enqueue(q, 4);
    queue_print(q);
    int d = queue_dequeue(q);
    printf("%d\n", d);
    queue_print(q);
    queue_free(&q);
}
