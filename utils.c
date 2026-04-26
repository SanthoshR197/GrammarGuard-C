#include "utils.h"

void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr && size > 0) {
        fprintf(stderr, "Fatal Error: Memory allocation of %zu bytes failed\n", size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    end[1] = '\0';

    return str;
}

char* duplicate_string(const char* str) {
    if (!str) return NULL;
    size_t len = strlen(str);
    char* dup = (char*)safe_malloc(len + 1);
    memcpy(dup, str, len + 1);
    return dup;
}
