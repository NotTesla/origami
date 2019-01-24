#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "rusty_ints.h"
#include <string.h>

const f32 identity_f32[4][4] = {
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 1.0f }
};

inline matrix_clear(f32 mat[4][4]) {
    memcpy(mat, identity_f32, 16 * sizeof(f32));
}

#endif // __MATRIX_H__