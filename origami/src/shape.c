#include "shape.h"

#include <stdlib.h>

#include "clipper_wrapper.hpp"

//#include "clipper.h"

#define DATA_DEF vert
#define LIST_DEF Vertices
#define LIST_ALIAS vertices
#include "arraylist_interface.h"

#define DATA_DEF tri
#include "arraylist_interface.h"

#define TYPE Vertices
#include "arrayfat_interface.h"

struct Shape shape_init_basic(
    const vert* hull, size_t h_len,
    const tri* tris, size_t t_len) {

    struct Shape self;
    self.hull = vertices_with_array(hull, h_len);
    self.indices = arraylist_tri_with_array(tris, t_len);

    self.holes.data = NULL;
    self.holes.len = 0;
    return self;
}

struct Shape shape_copy(struct Shape* cp) {
    struct Shape self;
    // copy the shape hull
    self.hull = vertices_with_array(cp->hull.data, cp->hull.len);

    // copy the shape holes
    self.holes = array_Vertices_with_array(cp->holes.data, cp->holes.len);

    for (size_t i = 0; i < self.holes.len; ++i) {
        self.holes.data[i] = 
            vertices_with_array(
                cp->holes.data[i].data,
                cp->holes.data[i].len);
    }

    // copy the shape indices
    self.indices =
        arraylist_tri_with_array(cp->indices.data, cp->indices.len);

    return self;
}

struct Shape* shape_copy_heap(struct Shape* cp) {
    struct Shape* shape = (struct Shape*)malloc(sizeof(struct Shape));
    struct Shape copy = shape_copy(cp);
    memcpy(shape, &copy, sizeof(struct Shape));
    return shape;
}

void shape_free(struct Shape* self) {
    vertices_free(&self->hull);

    for (size_t i = 0; i < self->holes.len; ++i) {
        vertices_free(self->holes.data + i);
    }
}

bool shape_bool_union(struct Shape* self, struct Shape* other) {
    clipper_push_shape(ptSubject, self->hull);
    // TODO: make clipper calls here
    

    return false;
}

bool shape_bool_subtraction(struct Shape* self, struct Shape* other) {
    // TODO: make clipper calls here
    return false;
}
