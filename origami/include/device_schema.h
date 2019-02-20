#ifndef __DEVICE_SETTINGS_H__
#define __DEVICE_SETTINGS_H__

#include "camera.h"
#include "rusty_ints.h"
#include "basic_tuples.h"

enum AntiAliasing {
    NONE = 0,
    MSAA_X2 = 2,
    MSAA_X4 = 4,
    MSAA_X8 = 8,
    MSAA_X12 = 12,
};

enum WindowMode {
    FULL_SCREEN = 0x01,
    WINDOWED = 0x02,
    FIXED_WINDOW = 0x04,
};

enum Vsync {
    OFF = 0x00,
    ON = 0x01,
};

typedef enum CursorMode {
    DEFAULT = 0x01,
    LOCKED = 0x02,
    CUSTOM = 0x04,
} CursorMode;

typedef enum PixelDepth {
    RGB = 0x01,
    RGBA = 0x02,
} PixelDepth;

typedef struct Bitmap {
    u8* pixels;
    PixelDepth pixel_depth;
    struct u16_2t size;
} Bitmap;

typedef struct Cursor {
    Bitmap* bitmap;
    struct u16_2t hotspot;
} Cursor;

struct DeviceSettings {
    const char* window_title;
    enum WindowMode window_mode;
    struct u32_2t window_size;
    struct f32_3t clear_color;
    enum Vsync vsync_state;
    enum AntiAliasing anti_aliasing;
};

struct Device {
    struct Camera camera;
    struct Input* input;
    f32 dt;
    // Hide the glfwWindow behind a void* to avoid polluting with glfw and gl functions
    void* _glfw;
};

#endif // __DEVICE_SETTINGS_H__