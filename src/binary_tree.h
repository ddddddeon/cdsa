#ifndef BINARY_TREE_H
#define BINARY_TREE_H

typedef struct BinaryTree BinaryTree;

BinaryTree *binary_tree_new();
int binary_tree_height(BinaryTree *t);
int binary_tree_root(BinaryTree *t);
void binary_tree_insert(BinaryTree *t, int value);
void binary_tree_print(BinaryTree *t);
void binary_tree_free(BinaryTree **t);

#endif /* BINARY_TREE_H  */
