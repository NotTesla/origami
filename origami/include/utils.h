#ifndef __UTILS_H__
#define __UTILS_H__

#include "rusty_ints.h"

// set every other number of bytes to a given value at an address
// ptr: the address of the first value to set
// value: the value to set each byte to
// num: the number of bytes to set
// skip: how many bytes to skip before setting another one
void memset_skip(void* ptr, u8 value, size_t num, size_t skip);

#endif // __UTILS_H__
