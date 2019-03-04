#include "shape.h"

#include <stdlib.h>

#include "clipper_wrapper.hpp"
#include "poly2tri_wrapper.hpp"

//#include "clipper.h"

#define DATA_DEF vert
#define LIST_DEF OriVertices
#define LIST_ALIAS vertices
#include "arraylist_interface.h"

#define DATA_DEF tri
#include "arraylist_interface.h"

#define DATA_DEF OriVertices
#define LIST_ALIAS polygon
#include "arraylist_interface.h"

struct Shape shape_init_basic(
    const vert* hull, size_t h_len,
    const tri* tris, size_t t_len) {

    struct Shape self;
    self.polygon.len = self.polygon.capacity = 0;
    polygon_push(&self.polygon, vertices_with_array(hull, h_len));
    self.indices = arraylist_tri_with_array(tris, t_len);

    self.polygon.data = NULL;
    self.polygon.len = 0;
    return self;
}

struct Shape shape_copy(struct Shape* cp) {
    struct Shape self;

    // copy the shape hull and holes
    self.polygon = polygon_with_array(cp->polygon.data, cp->polygon.len);

    for (size_t i = 0; i < self.polygon.len; ++i) {
        self.polygon.data[i] = 
            vertices_with_array(
                cp->polygon.data[i].data,
                cp->polygon.data[i].len);
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

    for (size_t i = 0; i < self->polygon.len; ++i) {
        vertices_free(self->polygon.data + i);
    }
}

bool shape_bool_union(struct Shape* self, struct Shape* other) {
    clipper_push_shape(ptSubject, self->polygon.data[0]);
    
    self->indices = poly2tri_solve(self->polygon);
    // TODO: make clipper calls here
    

    return false;
}

bool shape_bool_subtraction(struct Shape* self, struct Shape* other) {
    // TODO: make clipper calls here
    return false;
}
