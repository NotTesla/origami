#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "rusty_ints.h"
#include <cglm/types.h>

struct Camera {
    mat4 projection;
    mat4 view;
    float fov_degs;
    float aspect_ratio;
    float near_clip;
    float far_clip;
};

struct Camera camera_with_perspective(
    float fov_degs, float aspect_ratio, float near_clip, float far_clip);

void camera_apply(struct Camera* self);

void camera_translate_by(struct Camera* self, vec3 dir);

#endif // __CAMERA_H__