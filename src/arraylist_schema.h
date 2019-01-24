#ifndef TYPE
#error "arraylist_schema.h was included, but TYPE was undefined"
#else

#include "rusty_ints.h"

#define APPEND(x, y) x##y
#define ARRAY_LIST(x) APPEND(arraylist_, x)
struct ARRAY_LIST(TYPE) {
    TYPE* data;
    usize capacity;
    usize len;
};

#ifdef INTERFACE
#define LIST ARRAY_LIST(TYPE)
#include "arraylist_interface.h"
#undef INTERFACE
#endif

#undef TYPE
#endif
