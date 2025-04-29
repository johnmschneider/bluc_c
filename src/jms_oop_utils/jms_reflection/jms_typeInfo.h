#ifndef JMS_TYPEINFO_H
#define JMS_TYPEINFO_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "../../jms_utils/jms_ptr_annotations.h"
#include "../../jms_utils/jms_str.h"

struct jms_typeInfo;
typedef struct jms_typeInfo jms_typeInfo;

/**
 * @brief creates a new typeInfo object
 * @param typeName - the "type name" of the object we're storing type info for
 */
JMS_XFER_PTR(jms_typeInfo) jms_typeInfo_init(
    JMS_OWNED_PTR(const char)           typeName);

/**
 * @brief deletes a typeInfo object and frees any memory
 */
void jms_typeInfo_del(JMS_OWNED_PTR(jms_typeInfo) self);

/**
 * @brief returns a bool indicating whether the static constructor was called
 */
bool jms_typeInfo_wasStaticCtorCalled(JMS_OWNED_PTR(jms_typeInfo) self);

/**
 * @brief sets the value of the "wasStaticCtorCalled" bool
 */
void jms_typeInfo_setStaticCtorCalled(JMS_OWNED_PTR(jms_typeInfo) self, bool value);

/**
 * @brief returns the type name of the object
 */
JMS_BORROWED_PTR(const char) jms_typeInfo_typeName(JMS_BORROWED_PTR(jms_typeInfo) self);

#endif // JMS_TYPEINFO_H