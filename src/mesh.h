#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "tuple_structs.h"

#define TYPE f32_2t
#include "arraylist_schema.h"

#define TYPE i32
#include "arraylist_schema.h"

struct Shader {
    u32 gl_program;
    u32 gl_mat4_id;
    u32 gl_color3f;
};

struct Mesh {
    u32 gl_vbuffer;
    u32 gl_varray;

    // TODO: move this to a separate shader class
    u32 gl_program;
    u32 gl_mat4_id;
    u32 gl_color3f;
    u32 gl_camera;

    f32 mat4x4[16];

    struct arraylist_i32 indices;
    struct arraylist_f32_2t vertices;
};

// initialize a mesh with a given set of vertices
// vertices - the vertex array
// len      - the length of the vertex array
struct Mesh mesh_with_vertices(const f32_2t* vertices, usize len);

// frees a mesh heap allocated resources
void mesh_free(struct Mesh* mesh);

// draw a mesh
void mesh_draw(struct Mesh* self);

// change the color of a mesh
void mesh_recolor(struct Mesh* mesh, u8 color);

#endif // __MATERIAL_H__
