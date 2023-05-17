#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "common.h"
#include "queue.h"

struct BinaryTree {
    int value;
    struct BinaryTree *left;
    struct BinaryTree *right;
};

typedef struct BinaryTree BinaryTree;

BinaryTree *binary_tree_new(int value) {
    BinaryTree *p = malloc(sizeof(BinaryTree));
    p->value = value;
    p->left = NULL;
    p->right = NULL;

    return p;
}

int binary_tree_value(BinaryTree *t) {
    ABORT_IF_NULL(t);
    return t->value;
}

BinaryTree *binary_tree_left(BinaryTree *t) {
    if (t == NULL) {
        return NULL;
    }

    return t->left;
}

BinaryTree *binary_tree_right(BinaryTree *t) {
    if (t == NULL) {
        return NULL;
    }

    return t->right;
}

void binary_tree_insert(BinaryTree *t, int value) {
    if (value == t->value) {
        return;
    }

    if (value < t->value) {
        if (t->left == NULL) {
            BinaryTree *new = binary_tree_new(value);
            t->left = new;
        } else {
            binary_tree_insert(t->left, value);
        }
    } else {
        if (t->right == NULL) {
            BinaryTree *new = binary_tree_new(value);
            t->right = new;
        } else {
            binary_tree_insert(t->right, value);
        }
    }
}

BinaryTree *binary_tree_min(BinaryTree *t) {
    if (t == NULL) {
        return NULL;
    }

    while (t->left != NULL) {
        t = t->left;
    }

    return t;
}

void binary_tree_delete(BinaryTree **t, int value) {
    if (*t == NULL) {
        return;
    }

    if (value < (*t)->value) {
        binary_tree_delete(&(*t)->left, value);
    } else if (value > (*t)->value) {
        binary_tree_delete(&(*t)->right, value);
    } else {
        if ((*t)->left == NULL) {
            BinaryTree *temp = (*t)->right;
            free(*t);
            *t = temp;
        } else if ((*t)->right == NULL) {
            BinaryTree *temp = (*t)->left;
            free(*t);
            *t = temp;
        } else {
            BinaryTree *temp = binary_tree_min((*t)->right);
            (*t)->value = temp->value;
            binary_tree_delete(&(*t)->right, temp->value);
        }
    }
}

bool binary_tree_search(BinaryTree *t, int value) {
    if (t == NULL) {
        return false;
    }
    if (value == t->value) {
        return true;
    }

    if (value < t->value) {
        return binary_tree_search(t->left, value);
    } else if (value > t->value) {
        return binary_tree_search(t->right, value);
    }

    return false;
}

void binary_tree_df_print_pre_order(BinaryTree *t) {
    if (t == NULL) {
        return;
    }

    printf("%d ", t->value);
    binary_tree_df_print_pre_order(t->left);
    binary_tree_df_print_pre_order(t->right);
}

void binary_tree_df_print(BinaryTree *t) {
    binary_tree_df_print_pre_order(t);
    printf("\n");
}

void binary_tree_bf_print(BinaryTree *t) {
    Queue *q = queue_new();

    if (t == NULL) {
        return;
    }

    queue_enqueue(q, t);
    while (queue_size(q) != 0) {
        BinaryTree *node = (BinaryTree *)queue_dequeue(q);

        printf("%d ", node->value);

        if (node->left != NULL) {
            queue_enqueue(q, node->left);
        }

        if (node->right != NULL) {
            queue_enqueue(q, node->right);
        }
    }
    printf("\n");
}

void binary_tree_free(BinaryTree **t) {
    if (*t == NULL) {
        return;
    }

    if ((*t)->left != NULL) {
        binary_tree_free(&(*t)->left);
    }

    if ((*t)->right != NULL) {
        binary_tree_free(&(*t)->right);
    }

    free(*t);
    *t = NULL;
}
