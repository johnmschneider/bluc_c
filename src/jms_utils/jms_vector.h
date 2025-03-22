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
i32         jms_vec_elemCount   (jms_vector* self);

/**
 * @brief Returns the maximum number of elements that can be stored
 *  with the currently allocated memory for the vector.
 */
i32         jms_vec_capacity    (jms_vector* self);

/**
 * @brief Add *element* to the vector. The vector will manage the pointer.
 */
void        jms_vec_add         (jms_vector* self, void* element);

/**
 * @brief Add all elements from the *var args* to the vector. The vector will manage the pointers. The var args should be of a pointer type.
 * @param self - the vector to add to.
 * @param count - the number of elements in the variadic arguments. C varargs are dumb and can't determine this automatically.
 * @param ... - the elements to add.
 */
void        jms_vec_addAll      (jms_vector* self, i32 count, ...);

/**
 * @brief Get the value at *index* from the vector.
 */
void*       jms_vec_get         (jms_vector* self, i32 index);

/**
 * @brief Finds an element in the vector using the given searchCriteria and comparison function.
 *      The format/type of searchCriteria is determined by the comparison function.
 */
void*       jms_vec_find        (jms_vector* self, void* searchCriteria, bool (*comparer)(void*, void*));

/**
 * @brief Delete the value at *index* from the vector. Free's the pointer.
 */
void        jms_vec_rem         (JMS_BORROWED_PTR(jms_vector) self, i32 index);

#endif