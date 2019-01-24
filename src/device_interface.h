#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "app.h"
#include "device_structs.h"
#include "tuple_structs.h"

void device_init(App* app, const char* title);

i32 device_run(Device* self);

void device_set_clear_color(Device* self, f32_3t rgb);

void device_set_cursor_mode(Device* self, CursorMode mode);

void device_set_cursor(Device* self, Cursor* cursor);

void device_set_title(Device* self, const char* title);

void device_set_vsync(Device* self, Vsync state);

void device_set_anti_aliasing(Device* self, AntiAliasing aliasing);

#endif // __DEVICE_H__