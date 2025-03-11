#include <stdlib.h>
#include "jms_object.h"
#include "../jms_utils/jms_strUtil.h"
#include "../jms_utils/jms_vector.h"

jms_vector* jms_object_typeMetadata = NULL;

struct jms_object
{
    // We're too low-level to have nice things, like jms_str.
    //  jms_str is a subclass of jms_object, so we can't use it here,
    //  or we'd infinitely recurse.
    JMS_OWNED_PTR(const char)   typeName;
    JMS_OWNED_FPTR(void,        staticCtor, JMS_OWNED_PTR(jms_object) self);
};

static bool jms_object_wasStaticCtorCalled(
    JMS_OWNED_PTR(jms_object) self);

static void jms_object_staticCtor(
    JMS_OWNED_PTR(jms_object) self);

static void jms_object_noOpStaticCtor(
    JMS_OWNED_PTR(jms_object) self);

static bool jms_object_vectorTypeInfoComparer(
    JMS_BORROWED_PTR(void) typeName,
    JMS_BORROWED_PTR(void) element);

static void jms_object_initHelper(
    JMS_OWNED_PTR(jms_object)       self,
    JMS_BORROWED_PTR(jms_object)    subclass,
    JMS_OWNED_PTR(const char)       typeName,
    JMS_OWNED_FPTR(void,            staticCtor, JMS_OWNED_PTR(jms_object) self))
{
    if (jms_object_typeMetadata == NULL)
    {
        jms_object_typeMetadata = jms_vec_init(sizeof(bool));
    }
    
    subclass->typeName
            = typeName;
    subclass->staticCtor
            = staticCtor;

    jms_object_staticCtor(subclass);
}

JMS_XFER_PTR(jms_object) jms_object_init_str(
    JMS_BORROWED_PTR(jms_object)    subclass,
    JMS_OWNED_PTR(const char)       typeName)
{
    jms_object* self
            = malloc(sizeof(jms_object));
    
    jms_object_initHelper(
        self,
        subclass,
        typeName,
         &jms_object_noOpStaticCtor);

    return self;
}

JMS_XFER_PTR(jms_object) jms_object_init_str_func(
    JMS_BORROWED_PTR(jms_object)    subclass,
    JMS_OWNED_PTR(const char)       typeName,
    JMS_OWNED_FPTR(void,            staticCtor, JMS_OWNED_PTR(jms_object) self))
{
    jms_object* self
            = malloc(sizeof(jms_object));

    jms_object_initHelper(
        self,
        subclass,
        typeName,
        staticCtor);

    return self;
}

void jms_object_del(JMS_OWNED_PTR(jms_object) self)
{
    // We can't free the typeName, because it's a const char*, and likely
    //  stored in the readonly .data section of the assembly.

    free(self);
}

/**
 * @brief calls the static constructor for the object
 */
static void jms_object_staticCtor(JMS_OWNED_PTR(jms_object) self)
{
    if (jms_object_wasStaticCtorCalled(self))
    {
        return;
    }

    self->staticCtor(self);
    
    // This is a quirk about generics in raw c. We can't store
    //  a bool in a vector of void pointers, so we have to store
    //  it as a pointer to a bool.
    bool* isTrue = malloc(sizeof(bool));
    *isTrue = true;

    jms_vec_add(jms_object_typeMetadata, isTrue);
}

static void jms_object_noOpStaticCtor(JMS_OWNED_PTR(jms_object) self)
{
    if (jms_object_wasStaticCtorCalled(self))
    {
        return;
    }

    // This is a quirk about generics in raw c. We can't store
    //  a bool in a vector of void pointers, so we have to store
    //  it as a pointer to a bool.
    bool* isTrue = malloc(sizeof(bool));
    *isTrue = true;

    jms_vec_add(jms_object_typeMetadata, isTrue);
}

static bool jms_object_wasStaticCtorCalled(JMS_OWNED_PTR(jms_object) self)
{
    bool *result = NULL;

    if (jms_vec_elemCount(jms_object_typeMetadata) > 0)
    {
        result = (bool*)jms_vec_find(
                jms_object_typeMetadata,
                (void*)(self->typeName),
                &jms_object_vectorTypeInfoComparer);
    }

    bool wasStaticCtorCalled
            = result != NULL && *result;

    return wasStaticCtorCalled;
}

static bool jms_object_vectorTypeInfoComparer(
    JMS_BORROWED_PTR(void) typeName,
    JMS_BORROWED_PTR(void) element)
{
    return jms_strUtil_cstrEq(
        ((const char*)typeName),
        ((jms_object*)element)->typeName);
}