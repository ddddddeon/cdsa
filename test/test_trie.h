#ifndef TEST_TRIE_H
#define TEST_TRIE_H

#include <check.h>

#include "../src/queue.h"
#include "../src/trie.h"
#include "test.h"

START_TEST(test_trie_new) {
    TEST_INFO;
    Trie *t = trie_new();

    ck_assert_ptr_ne(t, NULL);

    trie_free(&t);
    ck_assert_ptr_eq(t, NULL);
}
END_TEST

START_TEST(test_trie_insert) {
    TEST_INFO;
    Trie *t = trie_new();

    trie_insert(t, "chris");
    trie_insert(t, "cool");
    trie_insert(t, "cooler");

    ck_assert(trie_search(t, "chris"));
    ck_assert(trie_search(t, "cool"));
    ck_assert(trie_search(t, "cooler"));
    ck_assert(!trie_search(t, "coolest"));
    ck_assert(!trie_search(t, "coo"));

    trie_free(&t);
}
END_TEST

START_TEST(test_trie_delete) {
    TEST_INFO;
    Trie *t = trie_new();

    trie_insert(t, "chris");
    trie_insert(t, "cool");
    trie_insert(t, "cooler");

    trie_delete(t, "cool");

    ck_assert(!trie_search(t, "cool"));
    ck_assert(trie_search(t, "cooler"));

    trie_insert(t, "cool");
    trie_delete(t, "cooler");

    ck_assert(trie_search(t, "cool"));
    ck_assert(!trie_search(t, "cooler"));

    trie_free(&t);
}
END_TEST

START_TEST(test_trie_autocomplete) {
    TEST_INFO;
    Trie *t = trie_new();

    trie_insert(t, "chris");
    trie_insert(t, "cool");
    trie_insert(t, "cooler");

    Queue *q = trie_autocomplete(t, "coo");
    ck_assert_int_eq(queue_size(q), 2);

    const char *word1 = (const char *)queue_dequeue(q);
    const char *word2 = (const char *)queue_dequeue(q);

    ck_assert_str_eq(word1, "cooler");
    ck_assert_str_eq(word2, "cool");

    Queue *q2 = trie_autocomplete(t, "c");
    ck_assert_int_eq(queue_size(q2), 3);

    const char *word4 = (const char *)queue_dequeue(q2);
    const char *word5 = (const char *)queue_dequeue(q2);
    const char *word6 = (const char *)queue_dequeue(q2);

    ck_assert_str_eq(word4, "chris");
    ck_assert_str_eq(word5, "cooler");
    ck_assert_str_eq(word6, "cool");

    trie_free(&t);
}
END_TEST

Suite *trie_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Trie");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_trie_new);
    tcase_add_test(tc_core, test_trie_insert);
    tcase_add_test(tc_core, test_trie_delete);
    tcase_add_test(tc_core, test_trie_autocomplete);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* TEST_TRIE_H */
