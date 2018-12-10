//
// Created by Christopher Szatmary on 2018-12-08.
//

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "../../utils/error.h"

/* Helpers */

/**
 * Allocates and initializes a new list_node.
 * @param value The data value the node should have.
 * @param next A pointer to the next node.
 * @param previous A pointer to the previous node.
 * @return A pointer to the newly created node.
 */
static list_node *node_new(int value, list_node *next, list_node *previous) {
    list_node *node = malloc(sizeof(list_node));

    // Ensure the allocation succeeded, then initialize the node
    if (node != NULL) {
        node->data = value;
        node->next = next;
        node->previous = previous;
    }

    return node;
}

/* Construction */

/**
 * Allocates a linked list.
 * @return A pointer to the allocated linked list.
 */
linked_list *linked_list_alloc() {
    linked_list *list = malloc(sizeof(linked_list));

    // Ensure the allocation succeeded, then set the default values
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
    }

    return list;
}

/**
 * Initializes a linked list using an array.
 * @param list A pointer to the list to initialize.
 * @param values An array of values to populate the list.
 * @param length The length of the values array.
 * @return An integer indicating the status.
 */
int linked_list_init(linked_list *list, int *values, size_t length) {
    // Just return if no elements in the array
    if (length == 0) {
        return EXIT_SUCCESS;
    }

    // Abort if the list isn't empty
    if (list->head != NULL) {
        return LIST_NOT_EMPTY;
    }

    // Loop through each element in the array and create a node to add to the list
    list_node *current = node_new(values[0], NULL, NULL);
    list->head = current;
    for (int i = 1; i < length; i++) {
        list_node *next = node_new(values[i], NULL, current);
        current->next = next;
        current = next;
    }

    list->tail = current;
    list->length = length;

    return EXIT_SUCCESS;
}

/**
 * Allocates and initializes a linked list using an array.
 * @param values An array of values to populate the list.
 * @param length he length of the values array.
 * @return A pointer to the newly created linked list.
 */
linked_list *linked_list_new(int *values, size_t length) {
    linked_list *list = linked_list_alloc();
    linked_list_init(list, values, length);
    return list;
}

/* Deletion */

/**
 * Deinitializes a linked list and deallocates each node inside it.
 * @param list The linked list to deinitialize.
 */
void linked_list_deinit(linked_list *list) {
    // Loop through each node and deallocate it
    list_node *current = list->head;
    while (current != NULL) {
        list_node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

/**
 * Deallocates the given linked list pointer.
 * @param list A pointer to a linked list pointer.
 */
void linked_list_dealloc(linked_list **list) {
    free(*list);
    *list = NULL;
}

/**
 * Deinitializes a linked list and then deallocates it.
 * @param list A pointer to a linked list pointer.
 */
void linked_list_delete(linked_list **list) {
    linked_list_deinit(*list);
    linked_list_dealloc(list);
}

/* Accessing */

/**
 * Gets the node at the given index in a linked list.
 * Supports reverse indexing through negative numbers.
 * @param list A pointer to the linked_list.
 * @param index The index of the node to access.
 * @return A pointer to the node at that index.
 */
list_node *linked_list_node(linked_list *list, int index) {
    int list_length = (int)list->length;
    int max_index = list_length - 1;
    int min_index = list_length * -1;

    // Ensure that a valid index was given.
    if (index < min_index || index > max_index) {
        fatal_error_print(INVALID_INDEX, "Index out of range\n");
    }

    int real_index = index < 0 ? list_length + index : index;

    list_node *current;
    if (real_index <= max_index / 2) {
        current = list->head;
        for (int i = 0; i < real_index; i++) {
            current = current->next;
        }
    } else {
        current = list->tail;
        for (int i = max_index; i > real_index; i--) {
            current = current->previous;
        }
    }

    return current;
}

/**
 * Retrieves the first element in the linked list.
 * @param list A pointer to the linked list.
 * @return The first element in the list.
 */
int linked_list_first(linked_list *list) {
    if (list->head == NULL) {
        fatal_error_print(LIST_EMPTY, "Can't get first element from empty list");
    }

    return list->head->data;
}

/**
 * Retrieves the last element in the linked list.
 * @param list A pointer to the linked list.
 * @return The last element in the list.
 */
int linked_list_last(linked_list *list) {
    if (list->tail == NULL) {
        fatal_error_print(LIST_EMPTY, "Can't get last element from empty list");
    }

    return list->tail->data;
}

/**
 * Retrieves the element at the given index in the linked list.
 * Supports reverse indexing through negative numbers.
 * @param list A pointer to the linked list.
 * @param index The index of the element to retrieve.
 * @return The element at the given index.
 */
int linked_list_element(linked_list *list, int index) {
    return linked_list_node(list, index)->data;
}

/**
 * Prints a linked list in order.
 * @param list A pointer to the linked list.
 * @param new_line A boolean indicating whether or not to add a newline character.
 */
void linked_list_print(linked_list *list, bool new_line) {
    list_node *current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL");

    if (new_line) {
        printf("\n");
    }
}

/**
 * Prints a linked list in reverse order.
 * @param list A pointer to the linked list.
 * @param new_line A boolean indicating whether or not to add a newline character.
 */
void linked_list_print_rev(linked_list *list, bool new_line) {
    list_node *current = list->tail;
    while (current != NULL) {
        printf("%d <- ", current->data);
        current = current->previous;
    }

    printf("NULL");

    if (new_line) {
        printf("\n");
    }
}

/* Mutation */

/**
 * Ensures the linked list has the correct length stored.
 * If the length stored is incorrect it will be corrected.
 * @param list A pointer to the linked list.
 * @return An integer indicating whether or not there was an difference found.
 */
int linked_list_ensure_len(linked_list *list) {
    size_t count = 0;
    list_node *current = list->head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    if (count != list->length) {
        list->length = count;
        return LENGTHS_DIFFERENT;
    }

    return EXIT_SUCCESS;
}

/**
 * Adds a value to the end of a list.
 * @param list A pointer to the linked list.
 * @param value The value to add to the list.
 */
void linked_list_append(linked_list *list, int value) {
    if (list->tail == NULL) {
        list->tail = node_new(value, NULL, NULL);
        list->head = list->tail;
        list->length = 1;
        return;
    }

    list_node *new_node = node_new(value, NULL, list->tail);
    list->tail->next = new_node;
    list->tail = new_node;
    list->length++;
}

/**
 * Adds a value to the beginning of a list.
 * @param list A pointer to the linked list.
 * @param value The value to add to the list.
 */
void linked_list_prepend(linked_list *list, int value) {
    if (list->head == NULL) {
        list->head = node_new(value, NULL, NULL);
        list->tail = list->head;
        list->length = 1;
        return;
    }

    list_node *new_node = node_new(value, list->head, NULL);
    list->head->previous = new_node;
    list->head = new_node;
    list->length++;
}

/**
 * Inserts a value into a linked list.
 * Supports reverse indexing through negative numbers.
 * @param list A pointer to the linked list.
 * @param value The value to insert into the list.
 * @param index The index at which to insert the value.
 */
void linked_list_insert(linked_list *list, int value, int index) {
    int list_length = (int)list->length;
    int real_index = index < 0 ? list_length + index : index;

    if (real_index == 0) {
        linked_list_prepend(list, value);
    } else if (real_index == list_length) {
        linked_list_append(list, value);
    } else {
        list_node *previous_node = linked_list_node(list, real_index - 1);
        list_node *next_node = previous_node->next;
        list_node *new_node = node_new(value, next_node, previous_node);
        previous_node->next = new_node;
        next_node->previous = new_node;
        list->length++;
    }
}

/**
 * Removes the last element in a linked list.
 * @param list A pointer to the linked list.
 * @return The element that was removed.
 */
int linked_list_remove_last(linked_list *list) {
    if (list->tail == NULL) {
        fatal_error_print(LIST_EMPTY, "Can't remove last element from an empty list");
    }

    list_node *node = list->tail;
    list->tail = node->previous;
    list->tail->next = NULL;

    int data = node->data;
    free(node);
    list->length--;

    return data;
}

/**
 * Removes the first element in a linked list.
 * @param list A pointer to the linked list.
 * @return The element that was removed.
 */
int linked_list_remove_first(linked_list *list) {
    if (list->head == NULL) {
        fatal_error_print(LIST_EMPTY, "Can't remove first element from an empty list");
    }

    list_node *node = list->head;
    list->head = node->next;
    list->head->previous = NULL;

    int data = node->data;
    free(node);
    list->length--;

    return data;
}

/**
 * Removes the element at the given index in a linked list.
 * Supports reverse indexing through negative numbers.
 * @param list A pointer to the linked list.
 * @return The element that was removed.
 */
int linked_list_remove(linked_list *list, int index) {
    int list_length = (int)list->length;
    int real_index = index < 0 ? list_length + index : index;

    if (real_index == 0) {
        return linked_list_remove_first(list);
    } else if (real_index == list_length - 1) {
        return linked_list_remove_last(list);
    } else {
        list_node *node_to_remove = linked_list_node(list, index);
        list_node *previous_node = node_to_remove->previous;
        list_node *next_node = node_to_remove->next;
        previous_node->next = next_node;
        next_node->previous = previous_node;

        int data = node_to_remove->data;
        free(node_to_remove);
        list->length--;

        return data;
    }
}
