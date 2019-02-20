#ifndef __MESH_H__
#define __MESH_H__

#include "basic_tuples.h"
#include "material.h"
#include "camera.h"
#include "shape.h"

#include <cglm/types.h>

struct Mesh {
    u32 gl_vbuffer;
    u32 gl_ibuffer;
    u32 gl_varray;
    u32 gl_tex_buffer;

    mat4 transform;
    struct Material* material;
    struct Shape shape;
};

// initialize a mesh with a given set of vertices
// vertices - the vertex array
// len      - the length of the vertex array
struct Mesh mesh_with_vertices(const struct i32_2t* vertices, size_t len);

// frees a mesh heap allocated resources
void mesh_free(struct Mesh* mesh);

// draw a mesh
void mesh_draw(struct Mesh* self, struct Camera* camera);

// change the color of a mesh
void mesh_recolor(struct Mesh* mesh);

#endif // __MESH_H__
