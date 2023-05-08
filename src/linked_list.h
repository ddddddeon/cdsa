#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList LinkedList;

LinkedList *linked_list_new();
int linked_list_size(LinkedList *ll);
int linked_list_first(LinkedList *ll);
int linked_list_last(LinkedList *ll);
void linked_list_insert_beginning(LinkedList *ll, int n);
void linked_list_insert_at(LinkedList *ll, int n, int idx);
void linked_list_update_at(LinkedList *ll, int n, int idx);
void linked_list_insert_end(LinkedList *ll, int n);
void linked_list_delete(LinkedList *ll, int n);
void linked_list_reverse(LinkedList *ll);
void linked_list_print(LinkedList *ll);
void linked_list_free(LinkedList **ll);

#endif /* LINKED_LIST_H  */
