#include "device_interface.h"

#include "tuple_structs.h"
#include "file_utils.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "mesh.h"

static void error_callback(i32 error, const char* description) {
    fprintf(stderr, "%s", description);
}

static void on_cursor_move(GLFWwindow* window, f64 x, f64 y) {
    f64_2t pos = { .x = x,.y = y };
    app_on_touch_event(((App*)glfwGetWindowUserPointer(window)), TICK, pos);
}

// @param[in] key The[keyboard key](@ref keys) that was pressed or released.
// @param[in] scancode The system - specific scancode of the key.
// @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
// @param[in] mods Bit field describing which[modifier keys](@ref mods) were
static void on_key_click(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
    KeyData data = { .keycode = key };
    app_on_key_event((App*)glfwGetWindowUserPointer(window), (EventState)action, data);
}

static void on_char_click(GLFWwindow* window, u32 utf_32) {

}

static void on_cursor_enter(GLFWwindow* window, i32 entered) {
    if (!entered) {
        f64_2t pos = { .x = 0,.y = 0 };
        app_on_touch_event((App*)glfwGetWindowUserPointer(window), CANCEL, pos);
    }
}

/*
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

    app_on_touch_event((App*)glfwGetWindowUserPointer(window), (EventState)action, pos);
}

static void on_file_drop(GLFWwindow* window, i32 count, const char** files) {
    for (i32 i = 0; i < count; ++i) {
        app_on_file_dropped((App*)glfwGetWindowUserPointer(window), files[i], get_extension(files[i]));
    }
}

static void on_window_resize(GLFWwindow* window, i32 width, i32 height) {
    u32_2t size = { .x = width,.y = height };
    app_on_window_resized((App*)glfwGetWindowUserPointer(window), size);
}

struct Mesh m;
void device_init(App* app, const char* title) {
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
        exit(-1);
    
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

    f32_2t tri[3] = {
        {.x = -1.0f,.y = -1.0f},
        {.x = 1.0f,.y = -1.0f},
        {.x = 0.0f,.y = 1.0f} };

    m = mesh_with_vertices(tri, 3);

    glEnable(GL_DEPTH_TEST);

    app->device._glfw = window;

    app_on_device_init(app);
}

i32 device_run(Device* self) {

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose((GLFWwindow*)self->_glfw)) {
        //g_vertex_buffer_data[7] = (sin(glfwGetTime()) + 1) / 2.0f + .5f;

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        mesh_draw(&m);
        
        /* Swap front and back buffers */
        glfwSwapBuffers((GLFWwindow*)self->_glfw);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void device_set_clear_color(Device* self, f32_3t rgb) {
    glClearColor(rgb.x, rgb.y, rgb.z, 1.0f);
}

void device_set_cursor_mode(Device* self, CursorMode mode) {
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

void device_set_cursor(Device* self, Cursor* cursor) {
    
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

void set_icon(Device* self, Bitmap* icon) {
    GLFWimage image;
    image.pixels = icon->pixels;
    image.width = icon->size.x;
    image.height = icon->size.y;

    glfwSetWindowIcon((GLFWwindow*)self->_glfw, 1, &image);
}

void device_set_title(Device* self, const char* title) {
    glfwSetWindowTitle((GLFWwindow*)self->_glfw, title);
}

void device_set_vsync(Device* self, Vsync state) {
    glfwSwapInterval(state);
}

void device_set_anti_aliasing(Device* self, AntiAliasing aliasing) {
    switch (aliasing) {
    case NONE:
        glDisable(GL_MULTISAMPLE_ARB);
        break;
    case MSAA_X2:
    case MSAA_X4:
    case MSAA_X8:
    case MSAA_X12:
        glGetIntegerv(GL_SAMPLES, &((GLint)aliasing));
        if (aliasing)
            printf("Context reports MSAA is available with %i samples\n", aliasing);
        else
            printf("Context reports MSAA is unavailable\n");

        glEnable(GL_MULTISAMPLE_ARB);
        break;
    }
}
