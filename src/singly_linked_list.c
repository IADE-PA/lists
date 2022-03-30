#include <stddef.h>
#include <stdlib.h>

#include "list.h"

typedef struct Node_* Node;
struct Node_ {
    Node next;
    void* element;
};

struct List_ {
    Node head;
    Node tail;
    size_t size;
};

// Creates a new list.
List list_create() {
    List list = malloc(sizeof(struct List_));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Destroys a list.
void list_destroy(List list) {
    Node node = list->head;
    while (node != NULL) {
        Node next = node->next;
        free(node);
        node = next;
    }
    free(list);
}

// Returns true iff the list contains no elements.
bool list_is_empty(List list) {
    return false;
}

// Returns the number of elements in the list.
size_t list_size(List list) {
    return 0;
}

// Returns the first element of the list.
void* list_get_first(List list) {
    return NULL;
}

// Returns the last element of the list.
void* list_get_last(List list) {
    return NULL;
}

// Returns the element at the specified position in the list.
// Range of valid positions: 0, ..., size()-1.
void* list_get(List list, size_t position) {
    return NULL;
}

// Returns the position in the list of the
// first occurrence of the specified element,
// or -1 if the specified element does not
// occur in the list.
int list_find(List list, void* element) {
    return 0;
}

// Inserts the specified element at the first position in the list.
void list_insert_first(List list, void* element) {
}

// Inserts the specified element at the last position in the list.
void list_insert_last(List list, void* element) {
}

// Inserts the specified element at the specified position in the list.
// Range of valid positions: 0, ..., size().
// If the specified position is 0, insert corresponds to insertFirst.
// If the specified position is size(), insert corresponds to insertLast.
void list_insert(List list, void* element, size_t position) {
}

// Removes and returns the element at the first position in the list.
void* list_remove_first(List list) {
    return NULL;
}

// Removes and returns the element at the last position in the list.
void* list_remove_last(List list) {
    return NULL;
}

// Removes and returns the element at the specified position in the list.
// Range of valid positions: 0, ..., size()-1.
void* list_remove(List list, size_t position) {
    return NULL;
}

// Removes all elements from the list.
void list_make_empty(List list) {
}
