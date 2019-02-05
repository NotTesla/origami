#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include "rusty_ints.h"
#include "basic_tuples.h"
#include "input_schema.h"

#include "app.h"

#define TYPE i32
#include "arraylist_schema.h"

struct Input {
    struct arraylist_i32 pressed_keys;
    struct f64_2t mouse_position;
    struct f64_2t mouse_delta;
    struct App* app;
};

struct Input input_init(struct App* app);

void input_on_key_state_change(struct Input* self, enum EventState state, struct KeyData key);

void input_update_mouse(struct Input* self, struct f64_2t mouse_position);

void input_send_key_events(struct Input* self);

#endif // __INPUT_HANDLER_H__