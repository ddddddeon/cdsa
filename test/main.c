#include <check.h>
#include <stdio.h>

#include "test_array.h"
#include "test_binary_tree.h"
#include "test_linked_list.h"
#include "test_max_heap.h"
#include "test_ordered_set.h"
#include "test_queue.h"
#include "test_stack.h"

int main(int argc, char* argv[]) {
    int number_failed;
    SRunner* runner;

    Suite* array_tests = array_suite();
    Suite* linked_list_tests = linked_list_suite();
    Suite* ordered_set_tests = ordered_set_suite();
    Suite* stack_tests = stack_suite();
    Suite* queue_tests = queue_suite();
    Suite* binary_tree_tests = binary_tree_suite();
    Suite* max_heap_tests = max_heap_suite();

    runner = srunner_create(array_tests);
    srunner_add_suite(runner, linked_list_tests);
    srunner_add_suite(runner, ordered_set_tests);
    srunner_add_suite(runner, stack_tests);
    srunner_add_suite(runner, queue_tests);
    srunner_add_suite(runner, binary_tree_tests);
    srunner_add_suite(runner, max_heap_tests);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0) ? 0 : 1;
}
