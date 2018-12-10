//
// Created by Christopher Szatmary on 2018-12-09.
//

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "error.h"

const char *get_error(int code) {
    switch (code) {
        case LIST_NOT_EMPTY:
            return "List is not empty";
        case LIST_EMPTY:
            return "List is empty";
        case DOES_NOT_EXIST:
            return "Does not exist";
        case INVALID_INDEX:
            return "Invalid index";
        case LENGTHS_DIFFERENT:
            return "Lengths are different";
        default:
            return "Unknown error occurred";
    }
}

void fatal_error(int code) {
    fprintf(stderr, "FATAL ERROR: %s\n", get_error(code));
    exit(code);
}

void fatal_error_print(int code, const char *restrict format, ...) {
    fprintf(stderr, "FATAL ERROR: ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    exit(code);
}