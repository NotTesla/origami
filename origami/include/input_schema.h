#ifndef __INPUT_SCHEMA_H__
#define __INPUT_SCHEMA_H__

#include "rusty_ints.h"

// The current state of an input event
enum EventState {
    // The event ends this frame
    RELEASE = 0,

    // The event began this frame
    PRESS = 1,

    // The event will continue this frame
    TICK = 2,

    // The event was cancelled this frame
    CANCEL = 4
};

struct KeyData {
    i32 keycode;
};

#endif // __INPUT_SCHEMA_H__