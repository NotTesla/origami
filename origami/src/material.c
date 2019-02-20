#include "material.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

const char* fragment =
"#version 450 core\n"

"uniform vec4 albedo;\n"
"uniform sampler2D image;\n"
"varying vec2 _uv;\n"

"void main(void) {\n"
"   gl_FragColor = albedo.rgba * texture(image, _uv).rgba;\n"
"}";

const char* vertex =
"#version 450 core\n"
"layout(location = 0) in highp vec2 position;\n"

"uniform mat4 mvp;\n"
"uniform float zdex;\n"
"varying vec2 _uv;\n"

"void main(void) {\n"

"   vec2 vertex = position * 0.0009765625;\n"
"   gl_Position = mvp * vec4(vertex.xy, zdex, 1.0);\n"

"   _uv = vertex.xy;\n"
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

struct Material material_with_shader(const char* shader) {
    struct Material self;

    self.gl_program = create_program(fragment, vertex);
    self.gl_uni_mvp = glGetUniformLocation(self.gl_program, "mvp");
    self.gl_uni_zdex = glGetUniformLocation(self.gl_program, "zdex");
    self.gl_uni_albedo = glGetUniformLocation(self.gl_program, "albedo");
    self.gl_uni_texture = glGetUniformLocation(self.gl_program, "texture");

    return self;
}