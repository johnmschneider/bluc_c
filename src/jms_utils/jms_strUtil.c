#include <string.h>
#include <stdlib.h>
#include "jms_strUtil.h"

static const size_t SPACE_FOR_NULL_TERM = 1;

/**
 * Copies a substring from the source to the destination string. Adds a null
 *  terminator. *Not* bounds-checked or safe.
 */
void jms_substr(char* destination, const char* source, 
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

char* jms_substrToHeap(const char* source, size_t startIndex, size_t stopIndex)
{
    //printf("jms_substrToHeap: startIndex == %zu, stopIndex == %zu\n", startIndex, stopIndex);

    size_t  len     = stopIndex - startIndex;
    char*   copy    = malloc(sizeof(char) * (len + SPACE_FOR_NULL_TERM));
    
    jms_substr(copy, source, startIndex, stopIndex);

    return copy;
}

bool jms_cstrEq(const char* str1, const char* str2)
{
    return strcmp(str1, str2) == 0;
}