//
// Created by Christopher Szatmary on 2018-12-09.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_STACK_H
#define DATA_STRUCTURES_AND_ALGORITHMS_STACK_H

typedef struct node {
    int data;
    struct node *previous;
} stack_node;

typedef struct {
    stack_node *top;
    size_t length;
} list_stack;

// Construction
list_stack *list_stack_alloc();
int list_stack_init(list_stack *stack, int *values, size_t length);
list_stack *list_stack_new(int *values, size_t length);

// Deletion
void list_stack_deinit(list_stack *stack);
void list_stack_dealloc(list_stack **stack);
void list_stack_delete(list_stack **stack);

// Accessing
int list_stack_peak(list_stack *stack);

// Mutation
int list_stack_push(list_stack *stack, int value);
int list_stack_pop(list_stack *stack);


#endif //DATA_STRUCTURES_AND_ALGORITHMS_STACK_H
