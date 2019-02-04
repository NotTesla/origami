#include "device_interface.h"

#include "tuple_structs.h"
#include "file_utils.h"
#include "glad/glad.h"
#include "mesh.h"

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
    f64_2t pos = { .x = x,.y = y };
    app_on_touch_event(((struct App*)glfwGetWindowUserPointer(window)), TICK, pos);
}

// notifies the app when a key state changes
// window: the active glfw window
// key: The[keyboard key](@ref keys) that was pressed or released.
// scancode: The system - specific scancode of the key.
// action: `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
// mods: Bit field describing which[modifier keys](@ref mods) were
static void on_key_click(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
    KeyData data = { .keycode = key };
    app_on_key_event((struct App*)glfwGetWindowUserPointer(window), (EventState)action, data);
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
        f64_2t pos = { .x = 0,.y = 0 };
        app_on_touch_event((struct App*)glfwGetWindowUserPointer(window), CANCEL, pos);
    }
}

/* TODO: update documentation style of this function
*@param[in] button The[mouse button](@ref buttons) that was pressed or
*released.
*  @param[in] action One of `GLFW_PRESS` or `GLFW_RELEASE`.
*  @param[in] mods Bit field describing which[modifier keys](@ref mods) were
*  held down.
*/
static void on_mouse_button(GLFWwindow* window, i32 button, i32 action, i32 mods) {
    // cache cursor instead?
    f64 x, y;
    glfwGetCursorPos(window, &x, &y);
    f64_2t pos = { .x = x,.y = y };

    app_on_touch_event((struct App*)glfwGetWindowUserPointer(window), (EventState)action, pos);
}

// notifies the app when a file is droped onto the window
// window: the active glfw window
// count: the number of files dropped
// files: a 2d array of the dropped file's names
static void on_file_drop(GLFWwindow* window, i32 count, const char** files) {
    for (i32 i = 0; i < count; ++i) {
        app_on_file_dropped((struct App*)glfwGetWindowUserPointer(window), files[i], get_extension(files[i]));
    }
}

// notifies the app when the window is resized
// window: the active glfw window
// width: the width in pixels of the window
// height: the height in pixels of the window
static void on_window_resize(GLFWwindow* window, i32 width, i32 height) {
    u32_2t size = { .x = width,.y = height };
    app_on_window_resized((struct App*)glfwGetWindowUserPointer(window), size);
}

// TODO: temporary, used for testing purposes
// later, `App::Device` should own an arraylist<struct Mesh*> 
struct Mesh m;

// initialize the window with a given app and window title
// 
void device_init(struct App* app, const char* title) {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
        exit(-1);

    glfwWindowHint(GLFW_SAMPLES, 12);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 1024, title, NULL, NULL);

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

    i32_2t square[4] = {
        { .x = 0,   .y = 0   },
        { .x = 0,   .y = 512 },
        { .x = 512, .y = 512 },
        { .x = 512, .y = 0   }
    };

    m = mesh_with_vertices(square, 4);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    app->device._glfw = window;

    app_on_device_init(app);
}

i32 device_run(struct Device* self) {

    // TODO: use matrix.h -> clear
    f32 camera[4][4] = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 1.0f },
    };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose((GLFWwindow*)self->_glfw)) {
        //g_vertex_buffer_data[7] = (sin(glfwGetTime()) + 1) / 2.0f + .5f;

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        mesh_draw(&m, camera);
        
        /* Swap front and back buffers */
        glfwSwapBuffers((GLFWwindow*)self->_glfw);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void device_set_clear_color(struct Device* self, f32_3t rgb) {
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

void device_set_vsync(struct Device* self, Vsync state) {
    glfwSwapInterval(state);
}

void device_set_anti_aliasing(struct Device* self, AntiAliasing aliasing) {

}
