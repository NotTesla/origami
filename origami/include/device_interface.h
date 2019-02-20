#ifndef __DEVICE_H__
#define __DEVICE_H__

#include "app.h"
#include "device_schema.h"
#include "basic_tuples.h"

void device_init(const struct DeviceSettings settings, struct App* app);

int device_consume(struct App* app);

void device_set_clear_color(struct Device* self, struct f32_3t rgb);

void device_set_cursor_mode(struct Device* self, CursorMode mode);

void device_set_cursor(struct Device* self, Cursor* cursor);

void device_set_title(struct Device* self, const char* title);

void device_set_vsync(struct Device* self, enum Vsync state);

void device_set_anti_aliasing(struct Device* self, enum AntiAliasing aliasing);

#endif // __DEVICE_H__