#include "mesh.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/affine.h>
#include <cglm/mat4.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"
struct Material m;
void create_vertex_buffer(struct Mesh* self) {
    
    // generate vertex array
    glGenVertexArrays(1, &self->gl_varray);
    glBindVertexArray(self->gl_varray);

    // generate vertex buffer
    glGenBuffers(1, &self->gl_vbuffer);
    glBindBuffer(
        GL_ARRAY_BUFFER,
        self->gl_vbuffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        self->shape.hull.len * sizeof(*self->shape.hull.data),
        self->shape.hull.data,
        GL_STATIC_DRAW);

    // generate index buffer
    glGenBuffers(1, &self->gl_ibuffer);
    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        self->gl_ibuffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        self->shape.indices.len * sizeof(*self->shape.indices.data),
        self->shape.indices.data,
        GL_STATIC_DRAW);
}

void mult(f32 mat[16], struct f32_3t m) {
    mat[12] = m.x;
    mat[13] = m.y;
    mat[14] = m.z;
    mat[15] = 1.0f;
}

#define WIDTH 16
#define HEIGHT 16
u8 tex[WIDTH * HEIGHT * 4];
struct Mesh mesh_with_vertices(const struct i32_2t* vertices, size_t len) {
    struct u32_3t tris[2] = {
        {.x=0, .y=1, .z=3},
        {.x=1, .y=3, .z=2}
    };

    struct Mesh mesh;
    mesh.shape = shape_init_basic(vertices, len, tris, 2);

    create_vertex_buffer(&mesh);

    // TODO: I'm surprised this works... material should be alloced onto the heap, no?
    m = material_with_shader("");
    mesh.material = &m;
    // - - - - - - - -

    glm_mat4_identity(mesh.transform);

    glm_translate_z(mesh.transform, -5.0f);

    const i32 dimens = WIDTH * HEIGHT;
    memset_skip(tex + 3, 255, dimens, 4); // set alpha
    memset_skip(tex + 1, 160, dimens, 3); // set green
    memset_skip(tex + 2, 255, dimens, 4); // set blue
    memset_skip(tex + 0, 0,  dimens / 2, 6); // set red

    glGenTextures(1, &mesh.gl_tex_buffer);
    glBindTexture(GL_TEXTURE_2D, mesh.gl_tex_buffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return mesh;
}

void mesh_free(struct Mesh* mesh) {
    shape_free(&mesh->shape);
}

void mesh_draw(struct Mesh* self, struct Camera* camera) {

    glUseProgram(self->material->gl_program);

    struct f32_3t offs = { 
        .x = (f32)cos(glfwGetTime() * 2.0f) * .1f,
        .y = (f32)sin(glfwGetTime() * 2.0f) * .1f,
        .z = 0.0f
    };
    // mult(self->mat4x4, offs);

    //self->shape.hull.data[0].x = (i32)(offs.x * 100);
    //self->shape.hull.data[0].y = (i32)(offs.y * 100);

    glBufferData(
        GL_ARRAY_BUFFER,
        self->shape.hull.len * sizeof(*self->shape.hull.data),
        self->shape.hull.data,
        GL_STATIC_DRAW);
    //glBufferData(
    //    GL_ARRAY_BUFFER,
    //    self->shape.hull.len * sizeof(*self->shape.hull.data),
    //    self->shape.hull.data,
    //    GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, self->gl_tex_buffer);
    glUniform1i(self->material->gl_uni_texture, 0);

    mat4 mvp;
    glm_mat4_mul(camera->view, self->transform, mvp);
    glm_mat4_mul(camera->projection, mvp, mvp);

    glUniformMatrix4fv(self->material->gl_uni_mvp, 1, GL_FALSE, &mvp[0][0]);

    glUniform4fv(self->material->gl_uni_albedo, 1, (f32[4]){ 1.0f, 1.0f, 1.0f, 1.0f });

    // begin vertex attribute : position
    glEnableVertexAttribArray(0);

    // bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, self->gl_vbuffer);
    glVertexAttribPointer(
        0, 2, GL_INT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->gl_ibuffer);
    glDrawElements(GL_TRIANGLES, (GLsizei)self->shape.indices.len * 3, GL_UNSIGNED_INT, (void*)0);

    // end vertice attribute : position
    glDisableVertexAttribArray(0);
}
