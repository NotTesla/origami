#include "device_interface.h"

#include "input_handler.h"
#include "file_utils.h"
#include "glad/glad.h"
#include "mesh.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define DATA_DEF struct Mesh
#define LIST_DEF struct arraylist_Mesh
#define LIST_ALIAS arraylist_Mesh
#include "arraylist_interface.h"

// prints an error and error code from glfw
// error: the error code
// description: a description of the error
static void error_callback(i32 error, const char* description) {
    fprintf(stderr, "GLFW error code (%d)\n%s", error, description);
}

// notifies the app when the cursor moves
// window: the active glfw window
// x: the x position of the cursor
// y: the y position of the cursor
static void on_cursor_move(GLFWwindow* window, f64 x, f64 y) {
    app_on_touch_event(
        ((struct App*)glfwGetWindowUserPointer(window)),
        TICK,
        (struct f64_2t){ .x = x,.y = y });
}

// notifies the app when a key state changes
// window: the active glfw window
// key: The[keyboard key](@ref keys) that was pressed or released.
// scancode: The system - specific scancode of the key.
// action: `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
// mods: Bit field describing which[modifier keys](@ref mods) were
static void on_key_click(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
    input_on_key_state_change(
        ((struct App*)glfwGetWindowUserPointer(window))->device.input,
        (enum EventState)action, (struct KeyData){.keycode=key});
}

// TODO: unfinished
// notifies the app when a keyboard character is clicked
// probably useful for things like text edit boxes
// window: the active glfw window
// utf_32: the utf-32 code of the key that was pressed
static void on_char_click(GLFWwindow* window, u32 utf_32) {

}

// gets cursor enter/leave window state changes, and notifies the app to cancel
// when the cursor leaves the window
// window: the active glfw window
// entered: the enter state of the cursor
static void on_cursor_enter(GLFWwindow* window, i32 entered) {
    if (!entered) {
        app_on_touch_event(
            (struct App*)glfwGetWindowUserPointer(window),
            CANCEL,
            (struct f64_2t){ .x = 0,.y = 0 });
    }
}

// notifies the app when the mouse click state changes
// window: the active glfw window
// button: the mouse button that was pressed
// action: one of `GLFW_PRESS` or `GLFW_RELEASE`
// mods: bit flags of modifier keys (shift, ctrl, etc)
static void on_mouse_button(GLFWwindow* window, i32 button, i32 action, i32 mods) {
    // cache cursor instead?
    f64 x, y;
    glfwGetCursorPos(window, &x, &y);

    app_on_touch_event(
        (struct App*)glfwGetWindowUserPointer(window),
        (enum EventState)action,
        (struct f64_2t){ .x = x,.y = y });
}

// notifies the app when a file is droped onto the window
// window: the active glfw window
// count: the number of files dropped
// files: a 2d array of the dropped file's names
static void on_file_drop(GLFWwindow* window, i32 count, const char** files) {
    for (i32 i = 0; i < count; ++i) {
        app_on_file_dropped(
            (struct App*)glfwGetWindowUserPointer(window),
            files[i],
            futils_get_ext(files[i]));
    }
}

// notifies the app when the window is resized
// window: the active glfw window
// width: the width in pixels of the window
// height: the height in pixels of the window
static void on_window_resize(GLFWwindow* window, i32 width, i32 height) {
    app_on_window_resized(
        (struct App*)glfwGetWindowUserPointer(window),
        (struct u32_2t){ .x = width,.y = height });
}

// initialize the window with a given app and window title
// 
void device_init(const struct DeviceSettings settings, struct App* app) {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    glfwWindowHint(GLFW_SAMPLES, 12);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(
        settings.window_size.x,
        settings.window_size.y,
        settings.window_title,
        NULL,
        NULL);

    if (!window) {
        glfwTerminate();
        exit(-1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /* Set the window's input callbacks */
    glfwSetWindowUserPointer(window, app);
    glfwSetCursorPosCallback(window, on_cursor_move);
    glfwSetKeyCallback(window, on_key_click);
    glfwSetCharCallback(window, on_char_click);
    glfwSetCursorEnterCallback(window, on_cursor_enter);
    glfwSetMouseButtonCallback(window, on_mouse_button);
    glfwSetDropCallback(window, on_file_drop);
    glfwSetWindowSizeCallback(window, on_window_resize);
    glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON_MODE);

    i32 ico[16] = {
        0,0x00FFFFFF,0xFFFF00FF,0,
        0xFF00FFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,
        0,0xFFFFFFFF,0xFFFF00FF,0,
        0,0xFFFFFFFF,0xFF00FFFF,0
    };

    struct GLFWimage glfw_icon;
    glfw_icon.width = 4;
    glfw_icon.height = 4;
    glfw_icon.pixels = (u8*)ico;

    glfwSetWindowIcon(window, 1, &glfw_icon);

    vert square[4] = {
        { .x = -512,   .y = -512},
        { .x = -512,   .y = 512 },
        { .x = 512,.y = 512 },
        { .x = 512,.y = -512}
    };
    vert square_cursor[4] = {
        { .x = -32,.y = -32},
        { .x = -32,.y = 32 },
        { .x = 32, .y = 32 },
        { .x = 32, .y = -32}
    };

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    app->device._glfw = window;
    
    app->device.camera = camera_with_perspective(60.0f,
        settings.window_size.x / settings.window_size.y,
        .125f, 320.0f);

    app->device.input = malloc(sizeof(struct Input));
    struct Input in = input_init(app);
    memcpy(app->device.input, &in, sizeof(struct Input));
    
    app->meshes = arraylist_Mesh_with_capacity(10);
    arraylist_Mesh_push(&app->meshes, mesh_with_vertices(square, 4));
    arraylist_Mesh_push(&app->meshes, mesh_with_vertices(square_cursor, 4));

    device_set_clear_color(&app->device, settings.clear_color);
    device_set_anti_aliasing(&app->device, settings.anti_aliasing);
    device_set_vsync(&app->device, settings.vsync_state);

    app_on_device_init(app);
}

int device_consume(struct App* self) {

    f32 last_frame = 0.0f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose((GLFWwindow*)self->device._glfw)) {
        
        self->device.dt = glfwGetTime() - last_frame;
        last_frame = glfwGetTime();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = 0; i < self->meshes.len; ++i) {
            mesh_draw(&self->meshes.data[i], &self->device.camera);
        }
        
        /* Swap front and back buffers */
        glfwSwapBuffers((GLFWwindow*)self->device._glfw);

        /* Poll for and process events */
        glfwPollEvents();

        input_send_key_events(self->device.input);
    }

    glfwTerminate();
    return 0;
}

void device_set_clear_color(struct Device* self, struct f32_3t rgb) {
    glClearColor(rgb.x, rgb.y, rgb.z, 1.0f);
}

void device_set_cursor_mode(struct Device* self, CursorMode mode) {
    // TODO: implement this method properly
    int cursor_mode = GLFW_CURSOR_NORMAL;
    //switch (mode) {
    //case DEFAULT:
    //    cursor_mode = GLFW_CURSOR_NORMAL;
    //    break;
    //case LOCKED:
    //    cursor_mode = GLFW_CURSOR_DISABLED;
    //    break;
    //case CUSTOM:

    //    break;
    //}
    glfwSetInputMode((GLFWwindow*)self->_glfw, GLFW_CURSOR, cursor_mode);
}

void device_set_cursor(struct Device* self, Cursor* cursor) {
    
    /* create a cursor */
    GLFWimage image;
    image.pixels = cursor->bitmap->pixels;
    image.width = cursor->bitmap->size.x;
    image.height = cursor->bitmap->size.y;
    GLFWcursor* glfw_cursor = glfwCreateCursor(&image, cursor->hotspot.x, cursor->hotspot.y);
    if (glfw_cursor != NULL) {
        glfwSetCursor((GLFWwindow*)self->_glfw, glfw_cursor);
    }

}

void set_icon(struct Device* self, Bitmap* icon) {
    GLFWimage image;
    image.pixels = icon->pixels;
    image.width = icon->size.x;
    image.height = icon->size.y;

    glfwSetWindowIcon((GLFWwindow*)self->_glfw, 1, &image);
}

void device_set_title(struct Device* self, const char* title) {
    glfwSetWindowTitle((GLFWwindow*)self->_glfw, title);
}

void device_set_vsync(struct Device* self, enum Vsync state) {
    glfwSwapInterval(state);
}

void device_set_anti_aliasing(struct Device* self, enum AntiAliasing aliasing) {

}
