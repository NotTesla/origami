#ifndef __INPUT_H__
#define __INPUT_H__

#include "rusty_ints.h"

/// <summary>
/// The current state of an input event
/// </summary>
typedef enum EventState
{
    /// <summary>
    /// The event began this frame
    /// </summary>
    PRESS = 1,

    /// <summary>
    /// The event will continue this frame
    /// </summary>
    TICK = 2,

    /// <summary>
    /// The event ends this frame
    /// </summary>
    RELEASE = 0,

    /// <summary>
    /// The event was cancelled this frame
    /// </summary>
    CANCEL = 4
} EventState;

typedef struct KeyData
{
    i32 keycode;
} KeyData;


#endif // __INPUT_H__