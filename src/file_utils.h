#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include "rusty_ints.h"
#include <stdio.h>

/* get the size of a file in bytes, returns -1 if an error was encountered */
usize futils_get_size(const char* filename);

/* dumps the file into a string, you are responsible to free it yourself */
free_str futils_dump(const char* filename);

/* get the file extension of a filename, no alloc */
const char* get_extension(const char* filename);

#endif // __FILE_UTILS_H__
