#ifndef JMS_STRUTIL_H
#define JMS_STRUTIL_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "jms_ptr_annotations.h"

/**
 * Copies a substring from the source to the destination string. Adds a null
 *  terminator. *Not* bounds-checked or safe.
 */
void    jms_strUtil_substr(
            JMS_BORROWED_PTR(char)          destination,
            JMS_BORROWED_PTR(const char)    source, 
            size_t startIndex,
            size_t endIndex);

char*   jms_strUtil_substrToHeap(
            JMS_BORROWED_PTR(const char) source,
            size_t startIndex, 
            size_t stopIndex);

/**
 * @brief Concatenates two strings together. Returns a new string.
 */
char*   jms_strUtil_concat(
            JMS_BORROWED_PTR(const char) s1,
            JMS_BORROWED_PTR(const char) s2);

/**
 * @brief returns whether the *values* of the two strings are the same.
 *  case-sensitive.
 */
bool    jms_strUtil_cstrEq(const char* str1, const char* str2);

char*   jms_strUtil_itoa(int32_t);

#endif