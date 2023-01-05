#ifndef JMS_VECTOR_H
#define JMS_VECTOR_H

#include <stdint.h>

struct jms_vector;
typedef struct jms_vector jms_vector;

jms_vector* jms_vec_init    (int32_t elemSize);
void        jms_vec_del     (jms_vector* self);

/**
 * Returns how many elements are currently being stored.
 */
int32_t     jms_vec_elemCount   (jms_vector* self);
void        jms_vec_add         (jms_vector* self, void* element);
void*       jms_vec_get         (jms_vector* self, int32_t index);

/**
 * Delete the value at *index* from the vector. Free's the pointer.
 */
void        jms_vec_rem         (jms_vector* self, int32_t index);

#endif