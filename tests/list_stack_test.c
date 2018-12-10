//
// Created by Christopher Szatmary on 2018-12-09.
//

#include "../utils/minunit.h"
#include "../data_structures/stack/list_stack.h"
#include "list_stack_test.h"

static list_stack *stack = NULL;
static int arr[] = { 1, 2, 3, 4, 5};

static void test_setup() {
    stack = list_stack_new(arr, sizeof(arr) / sizeof(int));
}

static void test_teardown() {
    list_stack_delete(&stack);
}

MU_TEST(test_length) {
    mu_assert(stack->length == 5, "stack length should be 5");
}

MU_TEST(test_peak) {
    mu_assert(list_stack_peak(stack) == 5, "top element should be 5");
}

MU_TEST(test_push) {
    list_stack_push(stack, 10);
    mu_assert(list_stack_peak(stack) == 10, "top element should now be 10");
    mu_assert(stack->length == 6, "stack length should now be 6");
}

MU_TEST(test_pop) {
    mu_assert(list_stack_pop(stack) == 5, "removed value should be 5");
    mu_assert(stack->length == 4, "stack length should now be 4");
    mu_assert(list_stack_peak(stack) == 4, "top element should now be 4");
}

MU_TEST_SUITE(list_stack_tests) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_length);
    MU_RUN_TEST(test_peak);
    MU_RUN_TEST(test_push);
    MU_RUN_TEST(test_pop);
}

void run_list_stack_tests() {
    MU_RUN_SUITE(list_stack_tests);
    MU_REPORT();
}