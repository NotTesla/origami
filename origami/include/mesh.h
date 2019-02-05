#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "basic_tuples.h"
#include "shape.h"

struct Material {
    u32 gl_program;
    u32 uni_color;
    u32 shader_camera;
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
    u32 gl_tex_buffer;

    // TODO: move this to a separate shader class
    u32 gl_program;
    u32 gl_mat4_id;
    u32 gl_color3f;
    u32 gl_texture;
    u32 gl_camera;

    f32 mat4x4[16];
    struct Shape shape;
};

// initialize a mesh with a given set of vertices
// vertices - the vertex array
// len      - the length of the vertex array
struct Mesh mesh_with_vertices(const struct i32_2t* vertices, size_t len);

// frees a mesh heap allocated resources
void mesh_free(struct Mesh* mesh);

// draw a mesh
void mesh_draw(struct Mesh* self, f32 camera[4][4]);

// change the color of a mesh
void mesh_recolor(struct Mesh* mesh);

#endif // __MATERIAL_H__
