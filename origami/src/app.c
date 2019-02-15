#include "app.h"
#include "device_structs.h"
#include "device_interface.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct f64_2t last;
void app_on_device_init(struct App* self) {
    last = (struct f64_2t){ 0.0f, 0.0f };
    f32 identity[4][4] = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
    memcpy(self->device.camera, identity, 16 * sizeof(f32));

    device_set_clear_color(&self->device, (struct f32_3t){.x=.95f,.y=.95f,.z=1.0f});
    device_set_vsync(&self->device, ON);

    const u16 width = 20;
    const u16 height = 20;
    const u16 dimens = width * height;

    // width * height * depth
    u8 pixels[20 * 20 * 4] = { 0 };
    memset_skip(pixels + 0, 128, dimens, 4); // set red
    memset_skip(pixels + 1, 160, dimens, 4); // set green
    memset_skip(pixels + 2, 255, dimens, 4); // set blue
    memset_skip(pixels + 3, 255, dimens, 4); // set alpha

    Bitmap bitmap;
    bitmap.pixels = pixels;
    bitmap.pixel_depth = RGBA;
    bitmap.size = (struct u16_2t){.x = width, .y = height};

    Cursor cursor;
    cursor.bitmap = &bitmap;
    cursor.hotspot = (struct u16_2t){.x = 0, .y = 0};

    device_set_cursor(&self->device, &cursor);
}

void app_on_file_dropped(struct App* self, const char* filename, const char* extension) {
    printf("file dropped with name: %s, extension: %s\n", filename, extension);
}

void app_on_key_event(struct App* self, enum EventState state, struct KeyData key) {
    f32 cam_speed = self->device.dt * 1.0f;
    switch (key.keycode) {

        // Move camera
        case 87: // w
            self->device.camera[3][1] -= cam_speed;
            break;
        case 68: // d
            self->device.camera[3][0] -= cam_speed;
            break;
        case 83: // s
            self->device.camera[3][1] += cam_speed;
            break;
        case 65: // a
            self->device.camera[3][0] += cam_speed;
            break;

        // Zoom in/out
        case 81: // q
            self->device.camera[0][0] -= cam_speed;
            self->device.camera[1][1] -= cam_speed;
            break;
        case 69: // e
            self->device.camera[0][0] += cam_speed;
            self->device.camera[1][1] += cam_speed;
            break;
        // case 32: // space
    }
}

void app_on_touch_event(struct App* self, enum EventState state, struct f64_2t pos) {
    if (state == TICK) {
        struct f64_2t delta = { (pos.x - last.x), -(pos.y - last.y) };
        last = pos;
        for (int i = 0; i < 4; ++i) {
            vert v = self->device.meshes.data[1].shape.hull.data[i];
            v.x += (i32)(delta.x);
            v.y += (i32)(delta.y);
            self->device.meshes.data[1].shape.hull.data[i] = v;
        }
    }
}

void app_on_window_resized(struct App* self, struct u32_2t size) {
    printf("Window Resized: (%u, %u)\n", size.x, size.y);
}
