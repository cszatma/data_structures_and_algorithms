//
// Created by Christopher Szatmary on 2018-12-09.
//

#include <stdlib.h>
#include <errno.h>
#include "array_stack.h"
#include "../../utils/error.h"

#define AUTOMATIC 0

/* Helpers */

/**
 * Re-sizes the given array stack to the desired capacity.
 * @param stack A pointer to the array stack.
 * @param size The new capacity of the stack.
 * @return An integer indicating the status.
 */
static int resize_stack(array_stack *stack, size_t capacity) {
    int *new_data = realloc(stack->data, capacity * sizeof(int));

    if (new_data == NULL) {
        return ENOMEM;
    }

    stack->data = new_data;
    stack->capacity = capacity;

    return EXIT_SUCCESS;
}

/**
 * Increases the capacity of the given array stack.
 * @param stack A pointer to the array stack.
 * @param capacity The new size of the stack.
 * If AUTOMATIC the new capacity will be double to current capacity.
 * @return An integer indicating the status.
 */
static int increase_stack_capacity(array_stack *stack, size_t capacity) {
    if (capacity != AUTOMATIC && capacity < stack->capacity) {
        return SPACE_ALREADY_ALLOCATED;
    }

    size_t actual_capacity;
    if (capacity == AUTOMATIC) {
        actual_capacity = stack->capacity == 0 ? 2 : stack->capacity * 2;
    } else {
        actual_capacity = capacity % 2 == 0 ? capacity : capacity + 1;
    }

    return resize_stack(stack, actual_capacity);
}

/* Construction */

/**
 * Allocates an array stack.
 * @return A pointer to the allocated list stack.
 */
array_stack *array_stack_alloc() {
    array_stack *stack = malloc(sizeof(array_stack));

    if (stack != NULL) {
        stack->data = NULL;
        stack->length = 0;
        stack->capacity = 0;
    }

    return stack;
}

/**
 * Initializes an array stack using an array.
 * @param stack A pointer to the stack to initialize.
 * @param values An array of values to populate the stack.
 * @param length The length of the values array.
 * @return An integer indicating the status.
 */
int array_stack_init(array_stack *stack, int *values, size_t length) {
    // Just return if no elements in the array
    if (length == 0) {
        return EXIT_SUCCESS;
    }

    // Abort if the stack isn't empty
    if (stack->length > 0) {
        return LIST_NOT_EMPTY;
    }

    int *data = malloc(length * sizeof(int));

    // Ensure that the array was allocated
    if (data == NULL) {
        return ENOMEM;
    }

    for (size_t i = 0; i < length; i++) {
        data[i] = values[i];
    }

    stack->data = data;
    stack->length = length;
    stack->capacity = length;

    return EXIT_SUCCESS;
}

/**
 * Allocates and initializes an array stack using an array.
 * @param values An array of values to populate the stack.
 * @param length The length of the values array.
 * @return A pointer to the newly created array stack.
 */
array_stack *array_stack_new(int *values, size_t length) {
    array_stack *stack = array_stack_alloc();
    array_stack_init(stack, values, length);
    return stack;
}

/* Deletion */

/**
 * Deinitializes an array stack and deallocates the data array inside it.
 * @param stack A pointer to the stack to deinitialize.
 */
void array_stack_deinit(array_stack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->length = 0;
    stack->capacity = 0;
}

/**
 * Deallocates the given array stack pointer.
 * @param stack A pointer to an array stack pointer.
 */
void array_stack_dealloc(array_stack **stack) {
    free(*stack);
    *stack = NULL;
}

/**
 * Deinitializes an array stack and then deallocates it.
 * @param stack A pointer to an array stack pointer.
 */
void array_stack_delete(array_stack **stack) {
    array_stack_deinit(*stack);
    array_stack_dealloc(stack);
}

/* Resizing */

/**
 * Reserves enough space to store the specified number of elements.
 * @param stack A pointer to the array stack.
 * @param capacity The desired capacity of the stack.
 * @return An integer indicating the status.
 */
int array_stack_reserve_capacity(array_stack *stack, size_t capacity) {
    return increase_stack_capacity(stack, capacity);
}

/**
 * Reduces the size of the data array.
 * @param stack A pointer to the array stack.
 * @return An integer indicating the status.
 */
int array_stack_clean_up(array_stack *stack) {
    size_t half_capacity = stack->capacity / 2;
    if (stack->length < half_capacity) {
        return resize_stack(stack, half_capacity);
    }

    return CANNOT_REDUCE_SIZE;
}

/* Accessing */

/**
 * Returns the item at the top of the array stack.
 * @param stack A pointer to the array stack.
 * @return The value at the top of the stack.
 */
int array_stack_peak(array_stack *stack) {
    if (stack->length == 0) {
        fatal_error_print(LIST_EMPTY, "Can't return top of empty stack");
    }

    return stack->data[stack->length - 1];
}

/* Mutation */

/**
 * Pushes an item onto the top of the array stack.
 * @param stack A pointer to the array stack.
 * @param value The value to push onto the stack.
 */
int array_stack_push(array_stack *stack, int value) {
    // Check if array is full and increase the capacity if it is
    if (stack->length == stack->capacity) {
        if (increase_stack_capacity(stack, AUTOMATIC) == ENOMEM) {
            return ENOMEM;
        }
    }

    stack->data[stack->length] = value;
    stack->length++;

    return EXIT_SUCCESS;
}

/**
 * Removes an item from the top of the array stack and returns it.
 * @param stack A pointer to the array stack.
 * @return The value removed from the stack.
 */
int array_stack_pop(array_stack *stack) {
    if (stack->length == 0) {
        fatal_error_print(LIST_EMPTY, "Can't pop the top of empty stack");
    }

    int data = stack->data[stack->length - 1];
    stack->length--;

    return data;
}

