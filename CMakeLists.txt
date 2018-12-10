cmake_minimum_required(VERSION 3.13)
project(data_structures_and_algorithms C)

set(CMAKE_C_STANDARD 11)

add_executable(data_structures_and_algorithms main.c data_structures/linked_list/linked_list.c data_structures/linked_list/linked_list.h utils/error.h utils/error.c utils/minunit.h tests/linked_list_test.c tests/linked_list_test.h data_structures/stack/list_stack.c data_structures/stack/list_stack.h tests/list_stack_test.c tests/list_stack_test.h data_structures/stack/array_stack.c data_structures/stack/array_stack.h tests/array_stack_test.c tests/array_stack_test.h)