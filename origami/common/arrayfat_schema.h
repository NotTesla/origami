// #include INTERFACE as well to include the relevant arrayfat functions
// The proper way to import this header is as follows:

// if you need to access the arraylist struct in a header (*.h):
// - your_file.h
// #define TYPE [Your Type]
// #include "arrayfat_schema.h"
// - your_file.c
// #define TYPE [Your Type]
// #include "arrayfat_interface.h"

// if you only need access to arraylist from a implementation file (*.c):
// - your_file.c
// #define TYPE [Your Type]
// #define INTERFACE
// #include "arrayfat_schema.h"

#ifndef TYPE
#error "arrayfat_schema.h was included, but TYPE was undefined"
#else

#include "rusty_ints.h"
#include "common_macros.h"

struct ARRAY_FAT(TYPE) {
    TYPE* data;
    size_t len;
};

#ifdef INTERFACE
#undef INTERFACE
#include "arrayfat_interface.h"
#endif

#undef TYPE
#endif
