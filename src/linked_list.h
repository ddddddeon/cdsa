#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct LinkedList LinkedList;

LinkedList *linked_list_new();
int linked_list_size(LinkedList *ll);
void *linked_list_first(LinkedList *ll);
void *linked_list_last(LinkedList *ll);
void *linked_list_get(LinkedList *ll, int idx);
void linked_list_insert_beginning(LinkedList *ll, void *value);
void linked_list_insert_at(LinkedList *ll, void *value, int idx);
void linked_list_update_at(LinkedList *ll, void *, int idx);
void linked_list_insert_end(LinkedList *ll, void *value);
void linked_list_delete(LinkedList *ll, void *value);
void linked_list_reverse(LinkedList *ll);
void linked_list_print(LinkedList *ll);
void linked_list_free(LinkedList **ll);

#endif /* LINKED_LIST_H  */
