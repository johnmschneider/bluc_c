#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
        printf("[%s]: d[%zu] = s[%zu] = `%c`\n", __FUNCTION__, charsCopied, i, source[i]);
        charsCopied++;
    }

    printf("[%s]: copied %zu chars\n", __FUNCTION__, (charsCopied - 1));
    
    destination[charsCopied] = '\0';

    printf("[%s]: destination length == %zu\n", __FUNCTION__, strlen(destination));
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
    printf("jms_strUtil_substrToHeap: startIndex == %zu, stopIndex == %zu\n", startIndex, stopIndex);

    // Add 1 to make the length "inclusive" of the stopIndex.
    size_t  len     = (stopIndex + 1) - startIndex;

    printf("[%s]: len == %zu\n", __FUNCTION__, len);

    char*   copy    = calloc(len + SPACE_FOR_NULL_TERM, sizeof(char));
    
    printf("[%s]: allocated %zu bytes\n", __FUNCTION__, len + SPACE_FOR_NULL_TERM);

    jms_strUtil_substr(copy, source, startIndex, stopIndex);

    return copy;
}

bool jms_strUtil_cstrEq(const char* str1, const char* str2)
{
    return strcmp(str1, str2) == 0;
}