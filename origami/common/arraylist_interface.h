// Warning: never include this in a header file

#ifndef DATA_DEF
#error "arraylist_interface.h was included, but DATA_DEF was undefined"
#else

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "common_macros.h"

#ifndef LIST_DEF
#define LIST_DEF struct ARRAY_LIST(DATA_DEF)
#endif

#ifndef LIST_ALIAS
#define LIST_ALIAS ARRAY_LIST(DATA_DEF)
#endif

#define PUSH(x) APPEND(x, _push)
// Push an item onto the top of the vector
// self: the given list
// item: the item to add
void PUSH(LIST_ALIAS)(LIST_DEF* self, DATA_DEF item) {
    size_t capacity = self->capacity;

    if (self->len == capacity) {
        capacity *= 2;
        self->data = (DATA_DEF*)realloc(self->data, sizeof(DATA_DEF) * capacity);
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
DATA_DEF POP(LIST_ALIAS)(LIST_DEF* self) {
    // TODO: implement error handling
    size_t index = self->len - 1;
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
DATA_DEF REMOVE_AT(LIST_ALIAS)(LIST_DEF* self, size_t index) {
    DATA_DEF item = self->data[index];
    --self->len;
    memcpy(&self->data[index], &self->data[index + 1], sizeof(DATA_DEF) * (self->len - index));
    return item;
}

#define ERASE(x) APPEND(x, _erase)
// Removes a given element from the arraylist
// shifts all elements after it back to replace it
// self: the list to act on
// element: the element to remove from the arraylist
// TODO: add a flag to remove duplicate entries as well
// TODO: a fn* to check equality might be better...
DATA_DEF ERASE(LIST_ALIAS)(LIST_DEF* self, DATA_DEF element) {
    for (size_t i = 0; self->len; ++i) {
        if (memcmp(&self->data[i], &element, sizeof(element)) == 0) {
            return REMOVE_AT(LIST_ALIAS)(self, i);
        }
    }
}

#define INSERT_AT(x) APPEND(x, _insert_at)
// Insert an element into the arraylist at a given index
// self: the list to act on
// item: the item to insert
// index: the index to insert the item
void INSERT_AT(LIST_ALIAS)(LIST_DEF* self, DATA_DEF item, size_t index) {
    if (self->len + 1 >= self->capacity) {
        // TODO: resize should be a method on arraylist
        // this code is duplicated in arraylist::push
        self->capacity *= 2;
        self->data = (DATA_DEF*)realloc(self->data, sizeof(DATA_DEF) * self->capacity);
        if (!self->data) {
            exit(-1);
        }
    }

    ++self->len;
    memcpy(&self->data[index+1], &self->data[index], sizeof(DATA_DEF) * (self->len - index));
    self->data[index] = item;
}

// #define INSERT_RANGE(x) APPEND(x, _insert_range)
// // Inserts a range of elements into the arraylist
// // self: the list to act on
// // range: the elements to insert into the arraylist
// // len: the number of elements to insert into the arraylist
// // index: the index to insert the elments at
// void INSERT_RANGE(x)(struct LIST_DEF* self, DATA_DEF* range, size_t len, size_t index) {
//     if (self->len + len >= self->capacity) {

//     }

// }

#define WITH_CAPACITY(x) APPEND(x, _with_capacity)
// Initialize an arraylist with a given capacity
// capacity: the capacity to initialize the list with
//
// return: a list with a given capacity, of length 0
LIST_DEF WITH_CAPACITY(LIST_ALIAS)(size_t capacity) {
    if (capacity == 0) capacity = 1;
    LIST_DEF self;
    self.data = (DATA_DEF*)malloc(sizeof(DATA_DEF) * capacity);
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
LIST_DEF WITH_ARRAY(LIST_ALIAS)(const DATA_DEF* arr, size_t len) {
    LIST_DEF self = WITH_CAPACITY(LIST_ALIAS)(len);
    memcpy(self.data, arr, sizeof(DATA_DEF) * len);
    self.len = len;

    return self;
}

#define FREE(x) APPEND(x, _free)
// free the internal array from memory
void FREE(LIST_ALIAS)(LIST_DEF* self) {
    free(self->data);
}

// TODO: set/get individual elements
// TODO: add/remove/insert range of elements

#undef DATA_DEF
#undef LIST_DEF
#undef LIST_ALIAS

#endif