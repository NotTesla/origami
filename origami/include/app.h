#ifndef __APP_H__
#define __APP_H__

#include "input_schema.h"
#include "input_handler.h"
#include "device_schema.h"
#include "basic_tuples.h"
#include "mesh.h"

#define TYPE struct Mesh
#define ALIAS Mesh
#include "arraylist_schema.h"

struct App {
    struct Device device;
    struct DeviceSettings device_settings;
    struct arraylist_Mesh meshes;
};

// initialize an app with arguments
// 
struct App app_with_args(const char** argv, size_t argc);

int app_consume(struct App self);

void app_on_device_init(struct App* self);

void app_on_key_event(struct App* self, enum EventState state, struct KeyData data);

void app_on_touch_event(struct App* self, enum EventState state, struct f64_2t pos);

void app_on_file_dropped(struct App* self, const char* filename, const char* ext);

void app_on_window_resized(struct App* self, struct u32_2t size);

#endif // __APP_H__
