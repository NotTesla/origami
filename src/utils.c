#include "utils.h"

void memset_skip(void* ptr, u8 value, usize num, usize skip) {
    usize _it = 0;
    do {
        *((u8*)ptr) = value;
        ((u8*)ptr) += skip;
    } while (++_it < num);
}
