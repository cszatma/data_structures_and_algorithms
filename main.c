#include <stdio.h>
#include "tests/linked_list_test.h"
#include "tests/list_stack_test.h"
#include "tests/array_stack_test.h"

int main() {
    run_linked_list_tests();
    run_list_stack_tests();
    run_array_stack_tests();

    return 0;
}