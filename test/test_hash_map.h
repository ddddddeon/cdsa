#ifndef TEST_HASH_MAP_H
#define TEST_HASH_MAP_H

#include <check.h>

#include "../src/hash_map.h"
#include "test.h"

START_TEST(test_hash_map_new) {
    TEST_INFO;
    HashMap *h = hash_map_new();

    ck_assert_ptr_ne(h, NULL);

    //    hash_map_free(&h);
    //    ck_assert_ptr_eq(h, NULL);
}
END_TEST

START_TEST(test_hash_map_set_get) {
    TEST_INFO;
    HashMap *h = hash_map_new();

    const char *expected = "cool";
    hash_map_set(h, "chris", (void *)expected);

    const char *value = (const char *)hash_map_get(h, "chris");
    printf("%s\n", value);

    ck_assert_ptr_ne(value, NULL);
    ck_assert_str_eq(value, expected);

    const char *should_be_null = (const char *)hash_map_get(h, "sirhc");
    ck_assert_ptr_eq(should_be_null, NULL);

    const char *new_expected = "very cool";
    hash_map_set(h, "chris", (void *)new_expected);
    const char *new_value = (const char *)hash_map_get(h, "chris");
    ck_assert_str_eq(new_value, new_expected);

    //    hash_map_free(&h);
}
END_TEST

Suite *hash_map_suite(void) {
    Suite *suite;
    TCase *tc_core;

    suite = suite_create("Hash Map");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_hash_map_new);
    tcase_add_test(tc_core, test_hash_map_set_get);

    suite_add_tcase(suite, tc_core);

    return suite;
}

#endif /* !TEST_HASH_MAP_H */
