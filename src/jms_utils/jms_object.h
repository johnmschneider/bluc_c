#ifndef JMS_OBJECT_H
#define JMS_OBJECT_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "jms_ptr_annotations.h"
#include "jms_str.h"

struct jms_object;
typedef struct jms_object jms_object;

/**
 * @brief creates a new object
 * @param typeName - the name of the type of the object
 */
JMS_XFER_PTR(jms_object) jms_object_init_str(
    JMS_OWNED_PTR(jms_str) typeName);

JMS_XFER_PTR(jms_object) jms_object_init_str_func(
    JMS_OWNED_PTR(jms_str) typeName,
    JMS_OWNED_FPTR(void, staticCtor, JMS_BORROWED_PTR(jms_object) self));

/**
 * @brief deletes an object
 */
void jms_object_del(JMS_OWNED_PTR(jms_object) self);

#endif // JMS_OBJECT_H