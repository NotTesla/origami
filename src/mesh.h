#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "tuple_structs.h"

#define TYPE f32_2t
#include "arraylist_schema.h"

#define TYPE u32_3t
#include "arraylist_schema.h"

struct Shader {
    u32 gl_program;
    u32 gl_mat4_id;
    u32 gl_color3f;
};

struct Shape {
    struct arraylist_u32_3t indices;
    struct arraylist_f32_2t vertices;
};

// TODO: Mesh should be split into multiple components
// Shape(memcpy)    - vertex and triangle buffers
// Material(shared) - gl_program, attributes (gl_camera, gl_color, etc)
// Mesh             - index and vertex buffers, vertex array
// - - - -
// Have a camera* passed into the mesh_draw method, camera* is probably just f32[4][4]...
struct Mesh {
    u32 gl_vbuffer;
    u32 gl_ibuffer;
    u32 gl_varray;

    // TODO: move this to a separate shader class
    u32 gl_program;
    u32 gl_mat4_id;
    u32 gl_color3f;
    u32 gl_camera;

    f32 mat4x4[16];
    struct Shape hull;
};

// initialize a mesh with a given set of vertices
// vertices - the vertex array
// len      j- the length of the vertex array
struct Mesh mesh_with_vertices(const f32_2t* vertices, usize len);

// frees a mesh heap allocated resources
void mesh_free(struct Mesh* mesh);

// draw a mesh
void mesh_draw(struct Mesh* self, f32 camera[4][4]);

// change the color of a mesh
void mesh_recolor(struct Mesh* mesh);

#endif // __MATERIAL_H__
