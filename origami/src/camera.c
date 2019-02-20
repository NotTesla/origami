#include "camera.h"
#include <cglm/affine.h>
#include <cglm/cam.h>
#include <cglm/util.h>

struct Camera camera_with_perspective(
    float fov_degs, float aspect_ratio, float near_clip, float far_clip) {

    struct Camera camera
        = (struct Camera) {
        .fov_degs = glm_rad(fov_degs),
        .aspect_ratio = aspect_ratio,
        .near_clip = near_clip,
        .far_clip = far_clip,
    };

    glm_mat4_identity(camera.view);
    
    camera_apply(&camera);

    return camera;
}

void camera_apply(struct Camera* self) {
    glm_perspective(
        self->fov_degs,
        self->aspect_ratio,
        self->near_clip,
        self->far_clip,
        self->projection);
}

void camera_translate_by(struct Camera* self, vec3 dir) {
    glm_vec3_negate(dir);
    glm_translate(self->view, dir);
}
