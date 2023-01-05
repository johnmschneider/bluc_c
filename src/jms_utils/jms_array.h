#ifndef JMS_ARRAY_H
#define JMS_ARRAY_H

#include <stdint.h>
#include <stddef.h>

struct jms_array;
typedef struct jms_array jms_array;

/**
 * Initializes a new array capable of containing *length* 
 *  number of elements. All elements are free'd on a call
 *  to jms_arr_del.
 */
jms_array*  jms_arr_init(size_t elemSize, size_t length);
void        jms_arr_del (jms_array* self);
void*       jms_arr_get (jms_array* self, size_t index);
void        jms_arr_set (jms_array* self, size_t index, void* data);
size_t      jms_arr_len (jms_array* self);

#endif