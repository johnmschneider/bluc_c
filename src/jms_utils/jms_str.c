#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "jms_str.h"
#include "jms_strUtil.h"

struct jms_str
{
    /**
     * @brief size of the string *not including* null term
     * 
     *  null terminator will be added in calls to .cStr()
     */
    size_t  length;
    char*   value;
};

jms_str* jms_str_init(const char* source)
{
    jms_str* self = malloc(sizeof(jms_str));

    size_t len = 0;
    while (true)
    {
        if (source[len] == '\0')
        {
            break;
        }

        len++;
    }

    self->length = len;

    // len + 1 for null term
    self->value = malloc((len + 1) * sizeof(char));

    strcpy(self->value, source);

    return self;
}

void jms_str_del(jms_str* self)
{
    free(self->value);
    free(self);
}

size_t jms_str_len(jms_str* self)
{
    // - self->value is corrupted
    // - investigating error in calling functions now
    // - leaving here in case this debug message is needed again
    //
    //printf("[jms_str.%s]: fileContents ==\n>[\n%s\n]<\n", __FUNCTION__, self->value);
    return self->length;
}

void jms_str_append_s(jms_str* self, jms_str* thingToAppend)
{
    // add 1 for null term
    char* newVal = malloc(self->length + thingToAppend->length + 1);
    
    if (self->length > 0)
    {
        strcpy(newVal, self->value);
    }

    strcat(newVal, thingToAppend->value);

    free(self->value);

    self->value = newVal;
    self->length = self->length + thingToAppend->length;
}

void jms_str_append_cs(jms_str* self, const char* cStr)
{
    size_t cStrLen = strlen(cStr);

    // add 1 for null term
    char* newVal = malloc(self->length + cStrLen + 1);
    
    if (self->length > 0)
    {
        strcpy(newVal, self->value);
    }
    else
    {
        newVal[0] = '\0';
    }

    strcat(newVal, cStr);
    free(self->value);
    self->value     = newVal;
    self->length    += cStrLen;
}

void jms_str_append_ch(jms_str* self, char thingToAppend)
{
    char cStr[2] = {thingToAppend, '\0'};

    jms_str_append_cs(self, cStr);
}

char* jms_str_cStr(jms_str* self)
{
    return self->value;
}

bool jms_str_eq_s(jms_str* self, jms_str* other)
{
    return jms_cstrEq(jms_str_cStr(self), jms_str_cStr(other));
}

bool jms_str_eq_cStr(jms_str* self, const char* other)
{
    return jms_cstrEq(jms_str_cStr(self), other);
}

char jms_str_charAt(jms_str* self, int32_t index)
{
    return self->value[index];
}

void jms_str_set_cStr(jms_str* self, const char* newValue)
{
    size_t length  = strlen(newValue);
    self->length   = (int32_t) length;

    // add 1 for null terminator
    char* newMemoryLocation = realloc (self->value, (length + 1) * sizeof(char));
    self->value = newMemoryLocation;
    
    // add 1 for null terminator
    memset(self->value, '\0', sizeof(char) * (length + 1));
    strncpy(self->value, newValue, (int32_t) length);
}