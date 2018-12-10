//
// Created by Christopher Szatmary on 2018-12-09.
//

#include "../utils/minunit.h"
#include "../data_structures/linked_list/linked_list.h"
#include "linked_list_test.h"

static linked_list *list = NULL;
static int arr[] = { 1, 2, 3, 4, 5 };

static void test_setup() {
    list = linked_list_new(arr, sizeof(arr) / sizeof(int));
}

static void test_teardown() {
    linked_list_delete(&list);
}

MU_TEST(test_length) {
    mu_assert(list->length == 5, "list length should be 5");
}

MU_TEST(test_first) {
    mu_assert(linked_list_first(list) == 1, "first element should be 1");
}

MU_TEST(test_last) {
    mu_assert(linked_list_last(list) == 5, "last element should be 5");
}

MU_TEST(test_element) {
    mu_assert(linked_list_element(list, 2) == 3, "element at index 2 should be 3");
}

MU_TEST(test_element_negative_index) {
    mu_assert(linked_list_element(list, -2) == 4, "element at index -2 should be 4");
}

MU_TEST(test_append) {
    linked_list_append(list, 10);
    mu_assert(linked_list_last(list) == 10, "last element should now be 10");
    mu_assert(list->length == 6, "list length should now be 6");
}

MU_TEST(test_prepend) {
    linked_list_prepend(list, -20);
    mu_assert(linked_list_first(list) == -20, "first element should now be 20");
    mu_assert(list->length == 6, "list length should now be 6");
}

MU_TEST(test_insert) {
    linked_list_insert(list, 77, 2);
    mu_assert(linked_list_element(list, 2) == 77, "element at index 2 should now be 77");
    mu_assert(list->length == 6, "list length should now be 6");
}

MU_TEST(test_insert_negative) {
    linked_list_insert(list, 15, -3);
    mu_assert(linked_list_element(list, 2) == 15, "element at index -3 should now be 15");
    mu_assert(list->length == 6, "list length should now be 6");
}

MU_TEST(test_remove_last) {
    mu_assert(linked_list_remove_last(list) == 5, "removed value should be 5");
    mu_assert(list->length == 4, "list length should now be 4");
    mu_assert(linked_list_last(list) == 4, "last element should now be 4");
}

MU_TEST(test_remove_first) {
    int first = linked_list_remove_first(list);
    mu_assert(first == 1, "removed value should be 1");
    mu_assert(list->length == 4, "list length should now be 4");
    mu_assert(linked_list_first(list) == 2, "last element should now be 2");
}

MU_TEST(test_remove) {
    int element = linked_list_remove(list, 2);
    mu_assert(element == 3, "removed value should be 3");
    mu_assert(list->length == 4, "list length should now be 4");
    mu_assert(linked_list_element(list, 2) == 4, "the element at index 2 should now be 4");
}

MU_TEST_SUITE(linked_list_tests) {
    MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_length);
    MU_RUN_TEST(test_first);
    MU_RUN_TEST(test_last);
    MU_RUN_TEST(test_element);
    MU_RUN_TEST(test_element_negative_index);

    MU_RUN_TEST(test_append);
    MU_RUN_TEST(test_prepend);
    MU_RUN_TEST(test_insert);
    MU_RUN_TEST(test_insert_negative);

    MU_RUN_TEST(test_remove_last);
    MU_RUN_TEST(test_remove_first);
    MU_RUN_TEST(test_remove);
}

void run_linked_list_tests() {
    MU_RUN_SUITE(linked_list_tests);
    MU_REPORT();
}
