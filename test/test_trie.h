#ifndef TEST_TRIE_H
#define TEST_TRIE_H

#include <check.h>

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

Suite *trie_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Max Heap");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_trie_new);
    tcase_add_test(tc_core, test_trie_insert);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* TEST_TRIE_H */
