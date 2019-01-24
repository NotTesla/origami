#ifndef __COMMON_MACROS_H__
#define __COMMON_MACROS_H__

// appends two symbols together
#define APPEND(x, y) x ## y

// define an array list
#define ARRAY_LIST(x) APPEND(arraylist_, x)

#endif // __COMMON_MACROS_H__