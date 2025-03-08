#include <string.h>
#include <stdlib.h>
#include "jms_strUtil.h"

static const size_t SPACE_FOR_NULL_TERM = 1;

/**
 * Copies a substring from the source to the destination string. Adds a null
 *  terminator. *Not* bounds-checked or safe.
 */
void jms_strUtil_substr(char* destination, const char* source, 
    size_t startIndex, size_t endIndex)
{
    size_t charsCopied = 0;

    for (size_t i = startIndex; i <= endIndex; i++)
    {
        destination[charsCopied] = source[i];
        charsCopied++;
    }

    destination[charsCopied] = '\0';
}

/**
 * @brief Concatenates two strings together. Returns a new string.
 * @remarks Caller is responsible for freeing the memory. For safety, the max length of the strings is 8192 chars.
 */
char* jms_strUtil_concat(const char* s1, const char* s2)
{
    size_t  len1    = strnlen(s1, 8192);
    size_t  len2    = strnlen(s2, 8192);
    size_t  total   = len1 + len2;
    char*   copy    = malloc(sizeof(char) * (total + SPACE_FOR_NULL_TERM));

    strcpy(copy, s1);
    strcat(copy, s2);

    return copy;
}

char* jms_strUtil_substrToHeap(const char* source, size_t startIndex, size_t stopIndex)
{
    //printf("jms_strUtil_substrToHeap: startIndex == %zu, stopIndex == %zu\n", startIndex, stopIndex);

    size_t  len     = stopIndex - startIndex;
    char*   copy    = malloc(sizeof(char) * (len + SPACE_FOR_NULL_TERM));
    
    jms_strUtil_substr(copy, source, startIndex, stopIndex);

    return copy;
}

bool jms_strUtil_cstrEq(const char* str1, const char* str2)
{
    return strcmp(str1, str2) == 0;
}