#include <stdlib.h>
#include <stdarg.h>
#include "jms_vector.h"
#include "jms_str.h"
#include "stdbool.h"

typedef struct jms_vec_chunk
{
    /**
     * NULL if not yet initialized
     */
    void* data;

    /**
     * Destructor for any given element of the data. If NULL, then no destructor is called.
     */
    void (*destructor) (void* self);
} jms_vec_chunk;


struct jms_vector
{
    /**
     * Size of each element (in bytes)
     */
    int32_t elemSize;
    int32_t lastElemIndex;

    /*
     * How many elements we currently have space for.
     * An array of pointers.
     */
    int32_t maxElems;
    jms_vec_chunk* elements;
};

struct jms_vector* jms_vec_init(int32_t elemSize)
{
    int32_t     startElemStorage = 10;
    jms_vector* vec = malloc(sizeof(struct jms_vector));

    vec->elemSize       = elemSize;
    vec->lastElemIndex  = -1;
    vec->maxElems       = 10;
    vec->elements       = malloc(startElemStorage * sizeof(jms_vec_chunk));

    for (int32_t i = 0; i < startElemStorage; i++)
    {
        vec->elements[i].data = NULL;
    }

    return vec;
}

void jms_vec_del(jms_vector* self)
{
    for (i32 i = 0; i < self->lastElemIndex; i++)
    {
        jms_vec_chunk* element = self->elements[i].data;

        if (element != NULL && element->destructor != NULL)
        {
            element->destructor(element->data);
        }
    }

    free(self->elements);
    self->elements = NULL;

    free(self);
}

int32_t jms_vec_elemCount(jms_vector* self)
{
    return self->lastElemIndex + 1;
}

int32_t jms_vec_capacity(jms_vector* self)
{
    return self->maxElems;
}

static void jms_vec_allocMoreSpace(jms_vector* self)
{
    int32_t newestElem = self->lastElemIndex;
    self->maxElems *= 2;
    self->elements = realloc(self->elements, self->maxElems * 
        sizeof(jms_vec_chunk));

    for (int32_t i = newestElem; i < self->lastElemIndex; i++)
    {
        self->elements[i].data = NULL;
    }
}

void jms_vec_add(jms_vector* self, void* element, void (*destructor) (void* self))
{
    self->lastElemIndex++;

    if (self->lastElemIndex > self->maxElems/2)
    {
        jms_vec_allocMoreSpace(self);
    }

    jms_vec_chunk chunk
        = self->elements[self->lastElemIndex];
    chunk.data
        = element;
    chunk.destructor
        = destructor;
}

void jms_vec_addAll(jms_vector* self, i32 count, ...)
{
    va_list args;
    va_start(args, count);

    for (i32 i = 0; i < count; i++)
    {
        void* currentArg = va_arg(args, void*);
        jms_vec_add(self, currentArg);
    }

    va_end(args);
}

void* jms_vec_get(jms_vector* self, int32_t index)
{
    if (index > self->lastElemIndex)
    {
        return NULL;
    }
    
    return self->elements[index].data;
}

void* jms_vec_find(jms_vector* self, void* searchCriteria, bool (*comparer)(void*, void*))
{
    for (int32_t i = 0; i <= self->lastElemIndex; i++)
    {
        void* actualElement = self->elements[i].data;
        bool isEqual = comparer(searchCriteria, actualElement);

        if (isEqual)
        {
            return actualElement;
        }
    }

    return NULL;
}

/**
 * @param index - the index to shift all of the elements into
 *      (i.e. the empty space left by deleting an element) 
 */
static void jms_vec_shiftLeft(jms_vector* self, int32_t index)
{
    for (int32_t i = index + 1; i <= self->lastElemIndex; i++)
    {
        self->elements[i - 1].data = self->elements[i].data;
    }

    // If we didn't delete this, we'd just end up with a duplicate
    //  reference to the pointer in maxElems - 2.
    self->elements[self->maxElems - 1].data = NULL;
}

static void jms_vec_shrink(jms_vector* self)
{
    int32_t newEndIndex = self->maxElems/2;
    self->maxElems = newEndIndex;
    self->elements = realloc(self->elements, newEndIndex * 
        sizeof(jms_vec_chunk));
}

void jms_vec_rem(jms_vector* self, int32_t index)
{
    void* data = self->elements[index].data;
    if (data != NULL)
    {
        free(data);
    }

    jms_vec_shiftLeft(self, index);

    if (self->lastElemIndex < self->maxElems/2)
    {
        jms_vec_shrink(self);
    }

    // set data to NULL *after* array shrink in case
    //  realloc gives it a new value
    self->elements[index].data = NULL;
    self->lastElemIndex--;
}