#include "input_handler.h"
#include "app.h"

#include <stdio.h>

#define TYPE i32
#include "arraylist_interface.h"

struct Input input_init(struct App* app) {
    struct Input self;
    self.app = app;
    self.mouse_delta = (struct f64_2t){.x = 0, .y = 0};
    self.mouse_delta = (struct f64_2t){.x = 0, .y = 0};
    self.pressed_keys = arraylist_i32_with_capacity(10);

    return self;
}

void input_on_key_state_change(struct Input* self, enum EventState state, struct KeyData key) {
    if (state == PRESS) {
        arraylist_i32_push(&self->pressed_keys, key.keycode);
        app_on_key_event(self->app, state, key);
    } else if (state == RELEASE) {
        arraylist_i32_erase(&self->pressed_keys, key.keycode);
        app_on_key_event(self->app, state, key);
    }
}

void input_send_key_events(struct Input* self) {
    for (size_t i = 0; i < self->pressed_keys.len; ++i) {
        app_on_key_event(
            self->app,
            TICK,
            (struct KeyData){.keycode = self->pressed_keys.data[i] });
    }
}

void input_update_mouse(struct Input* self, struct f64_2t mouse_position) {

}
