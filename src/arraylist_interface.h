// Warning: never include this in a header file

#ifndef TYPE
#error "arraylist_interface.h was included, but TYPE was undefined"
#else

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "common_macros.h"

#define LIST ARRAY_LIST(TYPE)

#define PUSH(x) APPEND(x, _push)
// Push an item onto the top of the vector
// self: the given list
// item: the item to add
void PUSH(LIST)(struct LIST* self, TYPE item) {
    usize capacity = self->capacity;

    if (self->len == capacity) {
        capacity *= 2;
        self->data = (TYPE*)realloc(self->data, sizeof(TYPE) * capacity);
        if (!self->data) {
            exit(-1);
        }

        self->capacity = capacity;
    }
    self->data[self->len++] = item;
}

#define POP(x) APPEND(x, _pop)
// Pop an item off the top of the vector
// self: the given list
//
// return: the item that was popped
TYPE POP(LIST)(struct LIST* self) {
    // TODO: implement error handling
    // TODO: create a rust-style "option" type
    usize index = self->len - 1;
    --self->len;
    return self->data[index];
}

#define REMOVE_AT(x) APPEND(x, _remove_at)
// Removes an item at the given index, and returns it
// shifts all elements after it to replace it
// self:  the list to act on
// index: the index to remove the item at
//
// return: the item that was removed
TYPE REMOVE_AT(LIST)(struct LIST* self, usize index) {
    TYPE item = self->data[index];
    --self->len;
    memcpy(&self->data[index], &self->data[index + 1], sizeof(TYPE) * (self->len - index));
    return item;
}

#define WITH_CAPACITY(x) APPEND(x, _with_capacity)
// Initialize a arraylist with a given capacity
// capacity: the capacity to initialize the list with
//
// return: a list with a given capacity, of length 0
struct LIST WITH_CAPACITY(LIST)(usize capacity) {
    if (capacity == 0) capacity = 1;
    struct LIST self;
    self.data = (TYPE*)malloc(sizeof(TYPE) * capacity);
    if (!self.data) {
        exit(-1);
    }

    self.len = 0;
    self.capacity = capacity;
    return self;
}

#define WITH_ARRAY(x) APPEND(x, _with_array)
// Initialize an arraylist with a given array
// arr: the data to fill the arraylist with
// len: the length of the initial array
//
// return: an arraylist containing arr
struct LIST WITH_ARRAY(LIST)(const TYPE* arr, usize len) {
    struct LIST self = WITH_CAPACITY(LIST)(len);
    memcpy(self.data, arr, sizeof(TYPE) * len);
    self.len = len;

    return self;
}

#define FREE(x) APPEND(x, _free)
// 
// 
// 
void FREE(LIST)(struct LIST* self) {
    free(self->data);
}

// TODO: set/get individual elements
// TODO: add/remove/insert range of elements

#undef TYPE
#undef LIST

#endif