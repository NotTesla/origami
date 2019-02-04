#include "utils.h"

void memset_skip(void* ptr, u8 value, size_t num, size_t skip) {
    u8* _ptr = (u8*)ptr;
    size_t _it = 0;
    do {
        *_ptr = value;
        _ptr += skip;
    } while (++_it < num);
}
