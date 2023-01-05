#include <stdlib.h>
#include <stdio.h>
#include "jms_array.h"
#define JMS_CHECKED_ARRAYS

typedef struct jms_arr_chunk
{
    void* data;
} jms_arr_chunk;

struct jms_array
{
    size_t          elemSize;
    size_t          elemCount;
    jms_arr_chunk*  elements;
};

jms_array* jms_arr_init(size_t elemSize, size_t length)
{
    jms_array* arr = malloc(sizeof(struct jms_array));
    
    arr->elemSize   = elemSize;
    arr->elemCount  = length;
    arr->elements   = malloc(sizeof(jms_arr_chunk) * length);

    for (size_t i = 0; i < length; i++)
    {
        // initialize each chunk's data to NULL so we know
        // what parts of the array we need to free
        arr->elements[i].data = NULL;
    }

    return arr;
}

void jms_arr_del(jms_array* self)
{
    for (size_t i = 0; i < self->elemCount; i++)
    {
        if (self->elements[i].data != NULL)
        {
            free(self->elements[i].data);
            self->elements[i].data = NULL;
        }
    }

    free(self->elements);
    self->elements = NULL;
    
    free(self);
}

void* jms_arr_get(jms_array* self, size_t index)
{
#ifdef JMS_CHECKED_ARRAYS
    if (index < 0 || index > self->elemCount)
    {
        fprintf(stderr, "jms_arr_get: index %zu is out of array bounds "
            "which are [0, %zu)", index, self->elemCount);
        return NULL;
    }
#endif

    return self->elements[index].data;
}

void jms_arr_set(jms_array* self, size_t index, void* data)
{
#ifdef JMS_CHECKED_ARRAYS
    if (index < 0 || index > self->elemCount)
    {
        fprintf(stderr, "jms_arr_set: index %zu is out of array bounds "
            "which are [0, %zu)", index, self->elemCount);
        return;
    }
#endif

    self->elements[index].data = data;
}

size_t jms_arr_len (jms_array* self)
{
    return self->elemCount;
}