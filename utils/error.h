//
// Created by Christopher Szatmary on 2018-12-08.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_ERROR_H
#define DATA_STRUCTURES_AND_ALGORITHMS_ERROR_H

#define LIST_NOT_EMPTY -1
#define LIST_EMPTY -2
#define DOES_NOT_EXIST -3
#define INVALID_INDEX -4
#define LENGTHS_DIFFERENT -5
#define SPACE_ALREADY_ALLOCATED -6
#define CANNOT_REDUCE_SIZE -7

const char *get_error(int code);
void fatal_error(int code);
void fatal_error_print(int code, const char *restrict format, ...);

#endif //DATA_STRUCTURES_AND_ALGORITHMS_ERROR_H
