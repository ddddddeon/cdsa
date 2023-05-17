#ifndef TEST_BINARY_TREE_H
#define TEST_BINARY_TREE_H

#include <check.h>

#include "../src/binary_tree.h"
#include "test.h"

START_TEST(test_binary_tree_new) {
    TEST_INFO;
    BinaryTree *t = binary_tree_new(10);

    ck_assert_ptr_ne(t, NULL);

    binary_tree_free(&t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_binary_tree_insert) {
    TEST_INFO;

    BinaryTree *t = binary_tree_new(10);
    binary_tree_insert(t, 3);
    binary_tree_insert(t, 12);
    binary_tree_insert(t, 15);
    binary_tree_insert(t, 2);

    /*        10
            3    12
          2        15
    */

    ck_assert_int_eq(binary_tree_value(t), 10);
    ck_assert_int_eq(binary_tree_value(binary_tree_left(t)), 3);
    ck_assert_int_eq(binary_tree_value(binary_tree_right(t)), 12);
    ck_assert_int_eq(binary_tree_value(binary_tree_left(binary_tree_left(t))),
                     2);
    ck_assert_int_eq(binary_tree_value(binary_tree_right(binary_tree_right(t))),
                     15);

    binary_tree_free(&t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_binary_tree_delete) {
    TEST_INFO;
    BinaryTree *t = binary_tree_new(10);
    binary_tree_insert(t, 3);
    binary_tree_insert(t, 12);
    binary_tree_insert(t, 15);
    binary_tree_insert(t, 2);

    binary_tree_delete(&t, 10);
    ck_assert_int_eq(binary_tree_value(t), 12);
    binary_tree_delete(&t, 12);
    ck_assert_int_eq(binary_tree_value(t), 15);
    binary_tree_delete(&t, 2);
    ck_assert_int_eq(binary_tree_value(t), 15);
    binary_tree_delete(&t, 3);
    ck_assert_int_eq(binary_tree_value(t), 15);
    binary_tree_delete(&t, 15);
    ck_assert_ptr_eq(t, NULL);

    binary_tree_free(&t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_binary_tree_search) {
    TEST_INFO;
    BinaryTree *t = binary_tree_new(10);
    binary_tree_insert(t, 3);
    binary_tree_insert(t, 12);
    binary_tree_insert(t, 15);
    binary_tree_insert(t, 2);

    ck_assert(binary_tree_search(t, 15));
    ck_assert(binary_tree_search(t, 2));
    ck_assert(binary_tree_search(t, 10));
    ck_assert(!binary_tree_search(t, 16));
    ck_assert(!binary_tree_search(t, 0));

    binary_tree_free(&t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

Suite *binary_tree_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Binary Tree");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_binary_tree_new);
    tcase_add_test(tc_core, test_binary_tree_insert);
    tcase_add_test(tc_core, test_binary_tree_delete);
    tcase_add_test(tc_core, test_binary_tree_search);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* TEST_BINARY_TREE_H */
