#ifndef JMS_VECTOR_H
#define JMS_VECTOR_H

#include "jms_ptr_annotations.h"
#include "jms_stdint.h"

struct jms_vector;
typedef struct jms_vector jms_vector;

JMS_OWNED_PTR(jms_vector)
    jms_vec_init                (i32 elemSize);

void
    jms_vec_del                 (JMS_OWNED_PTR(jms_vector) self);

/**
 * @brief Returns how many elements are currently being stored.
 */
i32     jms_vec_elemCount   (jms_vector* self);

/**
 * @brief Returns the maximum number of elements that can be stored
 *  with the currently allocated memory for the vector.
 */
i32     jms_vec_capacity    (jms_vector* self);

/**
 * @brief Add *element* to the vector. The vector will manage the pointer.
 */
void        jms_vec_add         (jms_vector* self, void* element);

/**
 * @brief Get the value at *index* from the vector.
 */
void*       jms_vec_get         (jms_vector* self, i32 index);

/**
 * @brief Find the index of *element* in the vector using the given comparison function.
 */
void*       jms_vec_find        (jms_vector* self, void* element, bool (*comparer)(void*, void*));

/**
 * @brief Delete the value at *index* from the vector. Free's the pointer.
 */
void        jms_vec_rem         (JMS_BORROWED_PTR(jms_vector) self, i32 index);

#endif