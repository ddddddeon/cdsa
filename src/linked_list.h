#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList LinkedList;

LinkedList *linked_list_new();
void linked_list_insert_beginning(LinkedList *ll, int n);
void linked_list_insert_end(LinkedList *ll, int n);
void linked_list_delete(LinkedList *ll, int n);
void linked_list_reverse(LinkedList *ll);
void linked_list_print(LinkedList *ll);
void linked_list_free(LinkedList *ll);

#endif /* LINKED_LIST_H  */
