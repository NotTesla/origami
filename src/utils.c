#include "utils.h"

void memset_skip(void* ptr, u8 value, usize num, usize skip) {
    usize _it = 0, o = 0;
    do {
        *((u8*)ptr + o) = value;
        o += skip;
    } while (++_it < num);
}
