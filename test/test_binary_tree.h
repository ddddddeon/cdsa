#ifndef TEST_BINARY_TREE_H
#define TEST_BINARY_TREE_H

#include <check.h>

#include "../src/binary_tree.h"
#include "test.h"

START_TEST(test_binary_tree_new) {
    TEST_INFO;
    BinaryTree *t = binary_tree_new();

    ck_assert_ptr_ne(t, NULL);

    // linked_list_free(&t);

    // ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_binary_tree_insert) {
    TEST_INFO;
    BinaryTree *t = binary_tree_new();

    binary_tree_insert(t, 1);
    binary_tree_insert(t, 3);
    binary_tree_insert(t, 2);
    binary_tree_insert(t, 4);

    binary_tree_print(t);

    // linked_list_free(&t);

    // ck_assert_ptr_eq(t, NULL);
}
END_TEST

Suite *binary_tree_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Binary Tree");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_binary_tree_new);
    tcase_add_test(tc_core, test_binary_tree_insert);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* TEST_BINARY_TREE_H */
