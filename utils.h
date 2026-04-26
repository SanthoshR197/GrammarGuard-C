#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Allocates memory and exits on failure.
 */
void* safe_malloc(size_t size);

/**
 * @brief Trims leading and trailing whitespace from a string.
 * Modifies the string in place.
 */
char* trim_whitespace(char* str);

/**
 * @brief Duplicates a string using safe_malloc.
 */
char* duplicate_string(const char* str);

#endif
