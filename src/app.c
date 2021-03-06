#include "app.h"
#include "device_structs.h"
#include "device_interface.h"
#include "tuple_interface.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void app_on_device_init(App* self) {
    device_set_clear_color(&self->device, f32_3t_new(.95f, .95f, 1.0f));
    device_set_vsync(&self->device, ON);

    const usize width = 20;
    const usize height = 20;
    const usize dimens = width * height;

    // width * height * depth
    u8 pixels[20 * 20 * 4] = { 0 };
    memset_skip(pixels + 0, 128, dimens, 4); // set red
    memset_skip(pixels + 1, 160, dimens, 4); // set green
    memset_skip(pixels + 2, 255, dimens, 4); // set blue
    memset_skip(pixels + 3, 255, dimens, 4); // set alpha

    Bitmap bitmap;
    bitmap.pixels = pixels;
    bitmap.pixel_depth = RGBA;
    bitmap.size = u16_2t_new(width, height);

    Cursor cursor;
    cursor.bitmap = &bitmap;
    cursor.hotspot = u16_2t_new(0, 0);

    device_set_cursor(&self->device, &cursor);
}

void app_on_file_dropped(App* self, const char* filename, const char* extension) {
    printf("file dropped with name: %s, extension: %s\n", filename, extension);
}

void app_on_key_event(App* self, EventState state, KeyData key) {
    printf("key event\n");
}

void app_on_touch_event(App* self, EventState state, f64_2t pos) {
    //printf("touch event\n");
}

void app_on_window_resized(App* self, u32_2t size) {
    printf("Window Resized: (%u, %u)\n", size.x, size.y);
}
