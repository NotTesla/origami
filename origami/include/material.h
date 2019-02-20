#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "rusty_ints.h"

struct Material {
    u32 gl_program;
    u32 gl_uni_mvp;
    u32 gl_uni_albedo;
    u32 gl_uni_texture;
};

struct Material material_with_shader(const char* shader);

#endif // __MATERIAL_H__