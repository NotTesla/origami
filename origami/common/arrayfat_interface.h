// Warning: never include this in a header file

#ifndef TYPE
#error "arrayfat_interface.h was included, but TYPE was undefined"
#else

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "common_macros.h"

#define ARRAY ARRAY_FAT(TYPE)

#define WITH_CAPACITY(x) APPEND(x, _with_capacity)
// Initialize an arrayARRAY with a given capacity
// capacity: the capacity to initialize the ARRAY with
//
// return: a ARRAY with a given capacity, of length 0
struct ARRAY WITH_CAPACITY(ARRAY)(size_t capacity) {
    if (capacity == 0) capacity = 1;
    struct ARRAY self;
    self.data = (TYPE*)malloc(sizeof(TYPE) * capacity);
    if (!self.data) {
        exit(-1);
    }

    self.len = capacity;
    return self;
}

#define WITH_ARRAY(x) APPEND(x, _with_array)
// Initialize an arrayARRAY with a given array
// arr: the data to fill the arrayARRAY with
// len: the length of the initial array
//
// return: an array containing arr
struct ARRAY WITH_ARRAY(ARRAY)(const TYPE* arr, size_t len) {
    struct ARRAY self = WITH_CAPACITY(ARRAY)(len);
    memcpy(self.data, arr, sizeof(TYPE) * len);
    self.len = len;

    return self;
}

#define FREE(x) APPEND(x, _free)
// free the internal array from memory
void FREE(ARRAY)(struct ARRAY* self) {
    free(self->data);
    self->len = 0;
}

// TODO: set/get individual elements
// TODO: add/remove/insert range of elements

#undef TYPE
#undef ARRAY

#endif