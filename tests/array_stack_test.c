//
// Created by Christopher Szatmary on 2018-12-10.
//

#include "../utils/minunit.h"
#include "../utils/error.h"
#include "../data_structures/stack/array_stack.h"
#include "array_stack_test.h"

static array_stack *stack = NULL;
static int arr[] = { 1, 2, 3, 4, 5};

static void test_setup() {
    stack = array_stack_new(arr, sizeof(arr) / sizeof(int));
}

static void test_teardown() {
    array_stack_delete(&stack);
}

MU_TEST(test_length) {
    mu_assert(stack->length == 5, "stack length should be 5");
}

MU_TEST(test_capacity) {
    mu_assert(stack->capacity == 5, "stack capacity should be 5");
}

MU_TEST(test_reserve_capacity) {
   array_stack_reserve_capacity(stack, 20);
    mu_assert(stack->capacity == 20, "stack capacity should now be 20");
}

MU_TEST(test_reserve_capacity_odd) {
    array_stack_reserve_capacity(stack, 15);
    mu_assert(stack->capacity == 16, "stack capacity should now be 16");
}

MU_TEST(test_reserve_lower) {
    int status = array_stack_reserve_capacity(stack, 3);
    mu_assert(stack->capacity == 5, "stack capacity should still be 5");
    mu_assert_int_eq(status, SPACE_ALREADY_ALLOCATED);
}

MU_TEST(test_peak) {
    mu_assert(array_stack_peak(stack) == 5, "top element should be 5");
}

MU_TEST(test_push) {
    array_stack_push(stack, 8);
    mu_assert(array_stack_peak(stack) == 8, "top element should now be 8");
    mu_assert(stack->length == 6, "stack length should now be 6");
    mu_assert(stack->capacity == 10, "stack capacity should now be 10");
}

MU_TEST(test_pop) {
    mu_assert(array_stack_pop(stack) == 5, "removed value should be 5");
    mu_assert(stack->length == 4, "stack length should now be 4");
    mu_assert(array_stack_peak(stack) == 4, "top element should now be 4");
}

MU_TEST_SUITE(array_stack_tests) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_length);
    MU_RUN_TEST(test_capacity);
    MU_RUN_TEST(test_reserve_capacity);
    MU_RUN_TEST(test_reserve_capacity_odd);
    MU_RUN_TEST(test_reserve_lower);
    MU_RUN_TEST(test_peak);
    MU_RUN_TEST(test_push);
    MU_RUN_TEST(test_pop);
}

void run_array_stack_tests() {
    MU_RUN_SUITE(array_stack_tests);
    MU_REPORT();
}