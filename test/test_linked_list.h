#ifndef TEST_LINKED_LIST_H
#define TEST_LINKED_LIST_H

#include <check.h>

#include "../src/linked_list.h"
#include "test.h"

START_TEST(test_linked_list_new) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    ck_assert_ptr_ne(l, NULL);

    linked_list_free(&l);

    ck_assert_ptr_eq(l, NULL);
}
END_TEST

START_TEST(test_linked_list_insert_end) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    const char *first = "first";
    const char *second = "second";

    linked_list_insert_end(l, (void *)first);
    linked_list_insert_end(l, (void *)second);

    ck_assert_int_eq(linked_list_size(l), 2);
    ck_assert_ptr_eq(linked_list_last(l), second);
    ck_assert_ptr_eq(linked_list_first(l), first);
}
END_TEST

START_TEST(test_linked_list_insert_beginning) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    const char *first = "first";
    const char *second = "second";

    linked_list_insert_beginning(l, (void *)first);
    linked_list_insert_beginning(l, (void *)second);

    ck_assert_int_eq(linked_list_size(l), 2);
    ck_assert_ptr_eq(linked_list_last(l), first);
    ck_assert_ptr_eq(linked_list_first(l), second);
}
END_TEST

START_TEST(test_linked_list_insert_at) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    const char *first = "first";
    const char *second = "second";
    const char *third = "third";
    const char *fourth = "fourth";
    const char *fifth = "fifth";
    const char *sixth = "sixth";

    linked_list_insert_end(l, (void *)first);
    linked_list_insert_end(l, (void *)second);
    linked_list_insert_end(l, (void *)third);
    linked_list_insert_at(l, (void *)fourth, 0);
    linked_list_insert_at(l, (void *)fifth, 1);
    linked_list_insert_at(l, (void *)sixth, 5);

    ck_assert_int_eq(linked_list_size(l), 6);
    ck_assert_ptr_eq(linked_list_first(l), fourth);
    ck_assert_ptr_eq(linked_list_last(l), sixth);
    ck_assert_ptr_eq(linked_list_get(l, 0), fourth);
    ck_assert_ptr_eq(linked_list_get(l, 5), sixth);
}
END_TEST

START_TEST(test_linked_list_update_at) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    const char *first = "first";
    const char *second = "second";
    const char *third = "third";
    const char *fourth = "fourth";
    const char *fifth = "fifth";
    const char *sixth = "sixth";

    linked_list_insert_end(l, (void *)first);
    linked_list_insert_end(l, (void *)second);
    linked_list_insert_end(l, (void *)third);

    linked_list_update_at(l, (void *)fourth, 0);
    linked_list_update_at(l, (void *)fifth, 1);
    linked_list_update_at(l, (void *)sixth, 2);

    ck_assert_int_eq(linked_list_size(l), 3);
    ck_assert_ptr_eq(linked_list_first(l), fourth);
    ck_assert_ptr_eq(linked_list_last(l), sixth);
}
END_TEST

START_TEST(test_linked_list_delete) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    const char *first = "first";
    const char *second = "second";
    const char *third = "third";

    linked_list_insert_end(l, (void *)first);
    linked_list_insert_end(l, (void *)second);
    linked_list_insert_end(l, (void *)third);

    linked_list_delete(l, (void *)third);
    linked_list_delete(l, (void *)first);

    ck_assert_int_eq(linked_list_size(l), 1);
    ck_assert_ptr_eq(linked_list_first(l), second);
    ck_assert_ptr_eq(linked_list_last(l), second);

    linked_list_free(&l);
}
END_TEST

START_TEST(test_linked_list_reverse) {
    TEST_INFO;
    LinkedList *l = linked_list_new();

    const char *first = "first";
    const char *second = "second";
    const char *third = "third";

    linked_list_insert_end(l, (void *)first);
    linked_list_insert_end(l, (void *)second);
    linked_list_insert_end(l, (void *)third);

    linked_list_reverse(l);

    ck_assert_ptr_eq(linked_list_last(l), first);
    ck_assert_ptr_eq(linked_list_first(l), third);

    linked_list_free(&l);
}
END_TEST

Suite *linked_list_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Linked List");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_linked_list_new);
    tcase_add_test(tc_core, test_linked_list_insert_end);
    tcase_add_test(tc_core, test_linked_list_insert_beginning);
    tcase_add_test(tc_core, test_linked_list_insert_at);
    tcase_add_test(tc_core, test_linked_list_update_at);
    tcase_add_test(tc_core, test_linked_list_delete);
    tcase_add_test(tc_core, test_linked_list_reverse);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* !TEST_LINKED_LIST_H */
