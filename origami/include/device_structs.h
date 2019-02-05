#ifndef __DEVICE_STRUCTS_H__
#define __DEVICE_STRUCTS_H__

#include "rusty_ints.h"
#include "basic_tuples.h"

typedef enum AntiAliasing {
    NONE = 0,
    MSAA_X2 = 2,
    MSAA_X4 = 4,
    MSAA_X8 = 8,
    MSAA_X12 = 12,
} AntiAliasing;

typedef enum WindowMode {
    FULL_SCREEN = 0x01,
    WINDOWED = 0x02,
    FIXED_WINDOW = 0x04,
} WindowMode;

typedef enum Vsync {
    OFF = 0x00,
    ON = 0x01,
} Vsync;

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

typedef struct Vertex {
    struct f32_4t position;
    struct f32_4t color;
} Vertex;

#endif // __DEVICE_STRUCTS_H__