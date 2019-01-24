#ifndef __APP_H__
#define __APP_H__

#include "input.h"
#include "tuple_structs.h"

typedef struct Device {
    // Hide the glfwWindow behind a void* to avoid polluting with glfw and gl functions
    void* _glfw;
} Device;

typedef struct App {

    Device device;
} App;

void app_on_device_init(App* self);

void app_on_key_event(App* self, EventState state, KeyData data);

void app_on_touch_event(App* self, EventState state, f64_2t pos);

void app_on_file_dropped(App* self, const char* filename, const char* ext);

void app_on_window_resized(App* self, u32_2t size);

#endif // __APP_H__
