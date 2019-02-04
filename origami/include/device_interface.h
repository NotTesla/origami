#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "app.h"
#include "device_structs.h"
#include "tuple_structs.h"

void device_init(struct App* app, const char* title);

i32 device_run(struct Device* self);

void device_set_clear_color(struct Device* self, f32_3t rgb);

void device_set_cursor_mode(struct Device* self, CursorMode mode);

void device_set_cursor(struct Device* self, Cursor* cursor);

void device_set_title(struct Device* self, const char* title);

void device_set_vsync(struct Device* self, Vsync state);

void device_set_anti_aliasing(struct Device* self, AntiAliasing aliasing);

#endif // __DEVICE_H__