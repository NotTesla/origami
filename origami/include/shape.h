#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "rusty_ints.h"
#include "basic_tuples.h"

#include <stdbool.h>

typedef struct u32_3t tri;
#define TYPE tri
#include "arraylist_schema.h"

typedef struct i32_2t vert;
#define TYPE vert
#include "arraylist_schema.h"

typedef struct arraylist_vert Vertices;
#define TYPE Vertices
#include "arrayfat_schema.h"

struct Shape {
    struct arraylist_vert hull;
    struct array_Vertices holes;
    struct arraylist_tri indices;
};

struct Shape shape_init_basic(const vert* hull, size_t h_len, const tri* tris, size_t t_len);

// copy a given shape and return the copy
struct Shape shape_copy(struct Shape* cp);

// copy a given shape onto the heap and return the copy
struct Shape* shape_copy_heap(struct Shape* cp);

// this should be called when a shape goes out of scope for the last time
void shape_free(struct Shape* self);

// perform a 2d boolean union on two shapes
// self = (self + other)
// return true if the shapes intersect 
bool shape_bool_union(struct Shape* self, struct Shape* other);

// perform a 2d boolean subtraction on two shapes
// self = (self - other)
// return true if the shapes intersect
bool shape_bool_subtraction(struct Shape* self, struct Shape* other);

#endif // __SHAPE_H__