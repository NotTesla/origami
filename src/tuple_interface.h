#ifndef __TUPLE_FUNCTIONS_H__
#define __TUPLE_FUNCTIONS_H__

#include "rusty_ints.h"
#include "tuple_structs.h"

#define DEC_2TUPLE_NEW(T) STRUCT_2TUPLE(T) T##_2t_new(T x, T y)
#define DEC_3TUPLE_NEW(T) STRUCT_3TUPLE(T) T##_3t_new(T x, T y, T z)
#define DEC_4TUPLE_NEW(T) STRUCT_4TUPLE(T) T##_4t_new(T x, T y, T z, T w)

#define DEF_2TUPLE_NEW(T) DEC_2TUPLE_NEW(T) { \
    STRUCT_2TUPLE(T) val = { .x = x,.y = y }; \
    return val; \
}

#define DEF_3TUPLE_NEW(T) DEC_3TUPLE_NEW(T) { \
    STRUCT_3TUPLE(T) val = { .x = x,.y = y,.z = z }; \
    return val; \
}

#define DEF_4TUPLE_NEW(T) DEC_4TUPLE_NEW(T) { \
    STRUCT_4TUPLE(T) val = { .x = x,.y = y,.z = z,.w = w }; \
    return val; \
}

/* * * * * * * * * * * * *
 * function declarations *
 * * * * * * * * * * * * */

DEC_2TUPLE_NEW(u32);
DEC_2TUPLE_NEW(u16);
DEC_3TUPLE_NEW(f32);

#endif // __TUPLE_FUNCTIONS_H__