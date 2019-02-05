#ifndef __TUPLE_STRUCTS_H__
#define __TUPLE_STRUCTS_H__

#define STRUCT_2TUPLE(x) x##_2t
#define STRUCT_3TUPLE(x) x##_3t
#define STRUCT_4TUPLE(x) x##_4t

#define DEF_2TUPLE(TYPE) \
struct STRUCT_2TUPLE(TYPE) { \
    TYPE x, y; \
}

#define DEF_3TUPLE(TYPE) \
struct STRUCT_3TUPLE(TYPE) { \
    TYPE x, y, z; \
}

#define DEF_4TUPLE(TYPE) \
struct STRUCT_4TUPLE(TYPE) { \
    TYPE x, y, z, w; \
}

#endif // __TUPLE_STRUCTS_H__