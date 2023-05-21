#include <stdbool.h>

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct BinaryTree BinaryTree;

BinaryTree *binary_tree_new(int value);
int binary_tree_value(BinaryTree *t);
BinaryTree *binary_tree_left(BinaryTree *t);
BinaryTree *binary_tree_right(BinaryTree *t);
void binary_tree_insert(BinaryTree *t, int value);
void binary_tree_delete(BinaryTree **t, int value);
bool binary_tree_search(BinaryTree *t, int value);
void binary_tree_df_print(BinaryTree *t);
void binary_tree_bf_print(BinaryTree *t);
int binary_tree_shortest_path(BinaryTree *t, int end);
void binary_tree_free(BinaryTree **t);

#endif /* BINARY_TREE_H  */
