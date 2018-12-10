//
// Created by Christopher Szatmary on 2018-12-08.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_LINKED_LIST_H
#define DATA_STRUCTURES_AND_ALGORITHMS_LINKED_LIST_H

#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *previous;
} list_node;

typedef struct {
    list_node *head;
    list_node *tail;
    size_t length;
} linked_list;

// Construction
linked_list *linked_list_alloc();
int linked_list_init(linked_list *list, int *values, size_t length);
linked_list *linked_list_new(int *values, size_t length);

// Deletion
void linked_list_deinit(linked_list *list);
void linked_list_dealloc(linked_list **list);
void linked_list_delete(linked_list **list);

// Accessing
int linked_list_first(linked_list *list);
int linked_list_last(linked_list *list);
int linked_list_element(linked_list *list, int index);
void linked_list_print(linked_list *list, bool new_line);
void linked_list_print_rev(linked_list *list, bool new_line);

// Mutation
int linked_list_ensure_len(linked_list *list);
void linked_list_append(linked_list *list, int value);
void linked_list_prepend(linked_list *list, int value);
void linked_list_insert(linked_list *list, int value, int index);
int linked_list_remove_last(linked_list *list);
int linked_list_remove_first(linked_list *list);
int linked_list_remove(linked_list *list, int index);

#endif //DATA_STRUCTURES_AND_ALGORITHMS_LINKED_LIST_H
