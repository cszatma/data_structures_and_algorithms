//
// Created by Christopher Szatmary on 2018-12-09.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_ARRAY_STACK_H
#define DATA_STRUCTURES_AND_ALGORITHMS_ARRAY_STACK_H

typedef struct {
    int *data;
    size_t length;
    size_t capacity;
} array_stack;

// Construction
array_stack *array_stack_alloc();
int array_stack_init(array_stack *stack, int *values, size_t length);
array_stack *array_stack_new(int *values, size_t length);

// Deletion
void array_stack_deinit(array_stack *stack);
void array_stack_dealloc(array_stack **stack);
void array_stack_delete(array_stack **stack);

// Resizing
int array_stack_reserve_capacity(array_stack *stack, size_t capacity);
int array_stack_clean_up(array_stack *stack);

// Accessing
int array_stack_peak(array_stack *stack);

// Mutation
int array_stack_push(array_stack *stack, int value);
int array_stack_pop(array_stack *stack);

#endif //DATA_STRUCTURES_AND_ALGORITHMS_ARRAY_STACK_H
