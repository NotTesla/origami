#include "file_utils.h"
#include <stdlib.h>
#include <stdio.h>

static inline long get_file_size_from_file(FILE* f) {
    if (fseek(f, 0, SEEK_END) != 0) {
        return 0;
    }

    long size = ftell(f);
    if (size == -1) {
        return 0;
    }
    return size;
}

size_t futils_get_size(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        return 0;
    }

    return get_file_size_from_file(f);
}

free_str futils_dump(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        return NULL;
    }

    const size_t len = get_file_size_from_file(f);
    char* contents = (char*)malloc(len);

    if (contents == NULL || fread(contents, 1, len, f) != len) {
        exit(-1);
    }

    return contents;
}

const char* get_extension(const char* filename) {
    size_t i = 0;
    size_t extensionIndex = 0;
    char c;
    while ((c = filename[i++]) != '\0') {
        if (!extensionIndex && c == '.') {
            extensionIndex = i;
        }
        else if (c == '/' || c == '\\') {
            extensionIndex = 0;
        }
    }

    return &filename[extensionIndex];
}
