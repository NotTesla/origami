#include "mesh.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

const char* fragment =
"#version 450 core\n"

"varying vec4 _albedo;\n"
"varying vec2 _uv;\n"

"void main(void) {\n"
"    //gl_FragColor = _albedo;\n"
"   gl_FragColor.rgba = vec4(_uv.x, 0.0, 0.0, 1.0);\n"
"}";

const char* vertex =
"#version 450 core\n"
"layout(location = 0) in highp vec2 position;\n"

"uniform mat4 camera;\n"
"uniform mat4 transform;\n"
"uniform vec4 albedo;\n"

"varying vec2 _uv;\n"
"varying vec4 _albedo;\n"
"void main(void) {\n"

"    vec2 adjusted_pos = position * 0.01;\n"
"    gl_Position = transform * vec4(adjusted_pos.xy, 0, 1.0);\n"

"    _uv = adjusted_pos.xy;\n"
"    _albedo = albedo;\n"
"}";

GLuint compile_shader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);

    const GLint src_len = (GLint)strlen(src);
    const GLsizei count = 1;

    // TODO: create shader struct for these values, alloc with longer lifetime than any particular "mesh"
    // maybe have a resources header that caches all of the shaders, textures, etc that are loaded
    glShaderSource(shader, count, &src, &src_len);
    glCompileShader(shader);
    
    { // log shader compile
        GLchar log[256];
        GLsizei log_len;
        glGetShaderInfoLog(shader, 256, &log_len, log);
        if (log_len != 0) {
            printf("glGetShaderInfoLog()\n%s\n-------\n", log);
        }
    }
    return shader;
}

GLuint create_program(const char* fsh, const char* vsh) {
    GLuint program = glCreateProgram();

    // compile vertex and fragment shaders
    GLuint shaders[2] = {
        compile_shader(GL_VERTEX_SHADER, vsh),
        compile_shader(GL_FRAGMENT_SHADER, fsh)
    };

    for (u32 i = 0; i < 2; ++i) {
        glAttachShader(program, shaders[i]);
    }

    glLinkProgram(program);

    { // log program link
        GLchar log[256];
        GLsizei log_len;
        glGetProgramInfoLog(program, 256, &log_len, log);
        if (log_len > 0) {
            printf("glGetProgramInfoLog()\n%s\n-------\n", log);
        }
    }

    for (u32 i = 0; i < 2; ++i) {
        glDetachShader(program, shaders[i]);
        glDeleteShader(shaders[i]);
    }

    return program;
}

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

static const f32 mat[16] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

void mult(f32 mat[16], f32_3t m) {
    mat[12] = m.x;
    mat[13] = m.y;
    mat[14] = m.z;
    mat[15] = 1.0f;
}

struct Mesh mesh_with_vertices(const i32_2t* vertices, size_t len) {
    u32_3t tris[2] = {
        {.x=0, .y=1, .z=3},
        {.x=1, .y=3, .z=2}
    };

    struct Mesh mesh;
    mesh.shape = shape_init_basic(vertices, len, tris, 2);

    create_vertex_buffer(&mesh);
    mesh.gl_program = create_program(fragment, vertex);

    mesh.gl_camera = glGetUniformLocation(mesh.gl_program, "camera");
    mesh.gl_mat4_id = glGetUniformLocation(mesh.gl_program, "transform");
    mesh.gl_color3f = glGetUniformLocation(mesh.gl_program, "albedo");

    memcpy(mesh.mat4x4, mat, 16 * sizeof(f32));

    return mesh;
}

void mesh_free(struct Mesh* mesh) {
    shape_free(&mesh->shape);
}

void mesh_draw(struct Mesh* self, f32 camera[4][4]) {

    // TODO: consider batching multiple meshes that share the same material
    // into a hashmap<gl_program, arraylist<Mesh>>, then iterate through hashmap
    // call use program, then iterate through it's arraylist and draw meshes
    // if performance becomes an issue here
    glUseProgram(self->gl_program);

    f32_3t offs = { 
        .x = (f32)cos(glfwGetTime() * 2.0f) * .1f,
        .y = (f32)sin(glfwGetTime() * 2.0f) * .1f,
        .z = 0.0f
    };
    mult(self->mat4x4, offs);

    //self->shape.hull.data[0].x = (i32)(offs.x * 100);
    //self->shape.hull.data[0].y = (i32)(offs.y * 100);

    //glBufferData(
    //    GL_ARRAY_BUFFER,
    //    self->shape.hull.len * sizeof(*self->shape.hull.data),
    //    self->shape.hull.data,
    //    GL_STATIC_DRAW);

    // TODO: uncomment to use camera
    //glUniformMatrix4fv(self->shader->gl_camera, 1, GL_FALSE, camera);

    glUniformMatrix4fv(self->gl_mat4_id, 1, GL_FALSE, self->mat4x4);

    f32 col[4] = { offs.x, 0.0f, .5f, 1.0f };
    glUniform4fv(self->gl_color3f, 1, col);

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
