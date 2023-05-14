#include <malloc.h>
#include <stdlib.h>

#include "common.h"
#include "queue.h"

struct BinaryTreeNode {
    int value;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

typedef struct BinaryTreeNode BinaryTreeNode;

typedef struct {
    BinaryTreeNode *root;
    int height;
} BinaryTree;

BinaryTreeNode *binary_tree_node_new(int value) {
    BinaryTreeNode *p = malloc(sizeof(BinaryTreeNode));
    p->value = value;
    p->left = NULL;
    p->right = NULL;

    return p;
}

BinaryTree *binary_tree_new() {
    BinaryTree *p = malloc(sizeof(BinaryTree));
    p->root = NULL;
    p->height = 0;

    return p;
}

int binary_tree_height(BinaryTree *t) { return t->height; }
BinaryTreeNode *binary_tree_root(BinaryTree *t) { return t->root; }

void binary_tree_node_insert(BinaryTreeNode *n, int value) {
    if (value == n->value) {
        return;
    }

    if (value < n->value) {
        if (n->left == NULL) {
            BinaryTreeNode *new = binary_tree_node_new(value);
            n->left = new;
        } else {
            binary_tree_node_insert(n->left, value);
        }
    } else {
        if (n->right == NULL) {
            BinaryTreeNode *new = binary_tree_node_new(value);
            n->right = new;
        } else {
            binary_tree_node_insert(n->right, value);
        }
    }
}

void binary_tree_insert(BinaryTree *t, int value) {
    ABORT_IF_NULL(t);
    if (t->root == NULL) {
        BinaryTreeNode *new = binary_tree_node_new(value);
        t->root = new;
        return;
    }

    binary_tree_node_insert(t->root, value);
}

void binary_tree_node_df_print_pre_order(BinaryTreeNode *n) {
    if (n == NULL) {
        return;
    }

    printf("%d ", n->value);
    binary_tree_node_df_print_pre_order(n->left);
    binary_tree_node_df_print_pre_order(n->right);
}

void binary_tree_df_print(BinaryTree *t) {
    ABORT_IF_NULL(t);

    binary_tree_node_df_print_pre_order(t->root);
    printf("\n");
}

void binary_tree_node_bf_print(BinaryTreeNode *n) {
    Queue *q = queue_new();

    if (n == NULL) {
        return;
    }

    queue_enqueue(q, n);
    while (queue_size(q) != 0) {
        BinaryTreeNode *node = (BinaryTreeNode *)queue_dequeue(q);

        printf("%d ", node->value);

        if (node->left != NULL) {
            queue_enqueue(q, node->left);
        }

        if (node->right != NULL) {
            queue_enqueue(q, node->right);
        }
    }
}

void binary_tree_bf_print(BinaryTree *t) {
    ABORT_IF_NULL(t);

    binary_tree_node_bf_print(t->root);
    printf("\n");
}

void binary_tree_free(BinaryTree **t) {}
