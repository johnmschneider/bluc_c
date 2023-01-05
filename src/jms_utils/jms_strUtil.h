#ifndef JMS_STRUTIL_H
#define JMS_STRUTIL_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Copies a substring from the source to the destination string. Adds a null
 *  terminator. *Not* bounds-checked or safe.
 */
void    jms_substr(char* destination, const char* source, 
            size_t startIndex, size_t endIndex);

char*   jms_substrToHeap(const char* source, size_t startIndex, 
            size_t stopIndex);

/**
 * @brief returns whether the *values* of the two strings are the same.
 *  case-sensitive.
 */
bool    jms_cstrEq(const char* str1, const char* str2);

char*   jms_itoa(int32_t);

#endif