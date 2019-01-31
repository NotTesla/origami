#ifndef __TUPLE_STRUCTS_H__
#define __TUPLE_STRUCTS_H__

#include "rusty_ints.h"

#define STRUCT_2TUPLE(x) x##_2t
#define STRUCT_3TUPLE(x) x##_3t
#define STRUCT_4TUPLE(x) x##_4t

#define DEF_2TUPLE(TYPE) \
typedef struct STRUCT_2TUPLE(TYPE) { \
    TYPE x, y; \
} STRUCT_2TUPLE(TYPE);

#define DEF_3TUPLE(TYPE) \
typedef struct STRUCT_3TUPLE(TYPE) { \
    TYPE x, y, z; \
} STRUCT_3TUPLE(TYPE);

#define DEF_4TUPLE(TYPE) \
typedef struct STRUCT_4TUPLE(TYPE) { \
    TYPE x, y, z, w; \
} STRUCT_4TUPLE(TYPE);

/* * * * * * * * * * * *
 * struct definitions  *
 * * * * * * * * * * * */

// 2-tuples
DEF_2TUPLE(u64);
DEF_2TUPLE(u32);
DEF_2TUPLE(u16);
DEF_2TUPLE(u8);

DEF_2TUPLE(i64);
DEF_2TUPLE(i32);
DEF_2TUPLE(i16);
DEF_2TUPLE(i8);

DEF_2TUPLE(f64);
DEF_2TUPLE(f32);

// 3-tuples
DEF_3TUPLE(u64);
DEF_3TUPLE(u32);
DEF_3TUPLE(u16);
DEF_3TUPLE(u8);

DEF_3TUPLE(i64);
DEF_3TUPLE(i32);
DEF_3TUPLE(i16);
DEF_3TUPLE(i8);

DEF_3TUPLE(f64);
DEF_3TUPLE(f32);

// 4-tuples
DEF_4TUPLE(u64);
DEF_4TUPLE(u32);
DEF_4TUPLE(u16);
DEF_4TUPLE(u8);

DEF_4TUPLE(i64);
DEF_4TUPLE(i32);
DEF_4TUPLE(i16);
DEF_4TUPLE(i8);

DEF_4TUPLE(f64);
DEF_4TUPLE(f32);

#endif // __TUPLE_STRUCTS_H__