#include "utils.h"

void memset_skip(void* ptr, u8 value, size_t num, size_t skip) {
    size_t _it = 0;
    do {
        *((u8*)ptr) = value;
        ((u8*)ptr) += skip;
    } while (++_it < num);
}
