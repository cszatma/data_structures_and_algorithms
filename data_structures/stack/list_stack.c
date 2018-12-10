//
// Created by Christopher Szatmary on 2018-12-09.
//

#include <stdlib.h>
#include <errno.h>
#include "list_stack.h"
#include "../../utils/error.h"

/* Helpers */

/**
 * Allocates and initializes a new stack_node.
 * @param value The data value the node should have.
 * @param previous A pointer to the previous node.
 * @return A pointer to the newly created node.
 */
static stack_node *node_new(int value, stack_node *previous) {
    stack_node *node = malloc(sizeof(stack_node));

    // Ensure the allocation succeeded, then initialize the node
    if (node != NULL) {
        node->data = value;
        node->previous = previous;
    }

    return node;
}

/* Construction */

/**
 * Allocates a list stack.
 * @return A pointer to the allocated list stack.
 */
list_stack *list_stack_alloc() {
    list_stack *stack = malloc(sizeof(list_stack));

    if (stack != NULL) {
        stack->top = NULL;
        stack->length = 0;
    }

    return stack;
}

/**
 * Initializes a list stack using an array.
 * @param stack A pointer to the stack to initialize.
 * @param values An array of values to populate the stack.
 * @param length The length of the values array.
 * @return An integer indicating the status.
 */
int list_stack_init(list_stack *stack, int *values, size_t length) {
    // Just return if no elements in the array
    if (length == 0) {
        return EXIT_SUCCESS;
    }

    // Abort if the stack isn't empty
    if (stack->top != NULL) {
        return LIST_NOT_EMPTY;
    }

    // Loop through each element in the array and create a node to add to the list
    stack_node *current = node_new(values[0], NULL);

    // Ensure that the node was allocated
    if (current == NULL) {
        return ENOMEM;
    }

    for (size_t i = 1; i < length; i++) {
        stack_node *next = node_new(values[i], current);
        current = next;
    }

    stack->top = current;
    stack->length = length;

    return EXIT_SUCCESS;
}

/**
 * Allocates and initializes a list stack using an array.
 * @param values An array of values to populate the stack.
 * @param length The length of the values array.
 * @return A pointer to the newly created list stack.
 */
list_stack *list_stack_new(int *values, size_t length) {
    list_stack *stack = list_stack_alloc();
    list_stack_init(stack, values, length);
    return stack;
}

/* Deletion */

/**
 * Deinitializes a list stack and deallocates each node inside it.
 * @param stack A pointer to the stack to deinitialize.
 */
void list_stack_deinit(list_stack *stack) {
    // Loop through each node and deallocate it
    stack_node *current = stack->top;
    while (current != NULL) {
        stack_node *previous = current->previous;
        free(current);
        current = previous;
    }

    stack->top = NULL;
    stack->length = 0;
}

/**
 * Deallocates the given list stack pointer.
 * @param stack A pointer to a list stack pointer.
 */
void list_stack_dealloc(list_stack **stack) {
    free(*stack);
    *stack = NULL;
}

/**
 * Deinitializes a list stack and then deallocates it.
 * @param stack A pointer to a list stack pointer.
 */
void list_stack_delete(list_stack **stack) {
    list_stack_deinit(*stack);
    list_stack_dealloc(stack);
}

/* Accessing */

/**
 * Returns the item at the top of the list stack.
 * @param stack A pointer to the list stack.
 * @return The value at the top of the stack.
 */
int list_stack_peak(list_stack *stack) {
    if (stack->top == NULL) {
        fatal_error_print(LIST_EMPTY, "Can't return top of empty stack");
    }

    return stack->top->data;
}

/* Mutation */

/**
 * Pushes an item onto the top of the list stack.
 * @param stack A pointer to the list stack.
 * @param value The value to push onto the stack.
 */
int list_stack_push(list_stack *stack, int value) {
    stack_node *new_node = node_new(value, stack->top);

    if (new_node == NULL) {
        return ENOMEM;
    }

    stack->top = new_node;
    stack->length++;

    return EXIT_SUCCESS;
}

/**
 * Removes an item from the top of the list stack and returns it.
 * @param stack A pointer to the list stack.
 * @return The value removed from the stack.
 */
int list_stack_pop(list_stack *stack) {
    if (stack->top == NULL) {
        fatal_error_print(LIST_EMPTY, "Can't pop the top of empty stack");
    }

    stack_node *node_to_remove = stack->top;
    stack->top = node_to_remove->previous;

    int data = node_to_remove->data;
    free(node_to_remove);
    stack->length--;

    return data;
}