#include <stdlib.h>
#include "jms_object.h"
#include "jms_stdint.h"
#include "jms_vector.h"

jms_vector* jms_object_typeMetadata = NULL;

struct jms_object
{
    JMS_OWNED_PTR(jms_str) typeName;
    void (*staticCtor) (JMS_OWNED_PTR(jms_object) self);
};

static bool jms_object_wasStaticCtorCalled(JMS_OWNED_PTR(jms_object) self);

static void jms_object_staticCtor(JMS_OWNED_PTR(jms_object) self);

static void jms_object_noOpStaticCtor(JMS_OWNED_PTR(jms_object) self);

static bool jms_object_vectorTypeInfoComparer(
    JMS_BORROWED_PTR(void) typeName,
    JMS_BORROWED_PTR(void) element);

jms_object* jms_object_init_str(jms_str* typeName)
{
    if (jms_object_typeMetadata == NULL)
    {
        jms_object_typeMetadata = jms_vec_init(sizeof(bool));
    }

    jms_object* self
            = malloc(sizeof(jms_object));
    self->typeName
            = typeName;
    self->staticCtor
            = jms_object_noOpStaticCtor;
    return self;
}

jms_object* jms_object_init_str_func(
    JMS_BORROWED_PTR(jms_str) typeName,
    void (*staticCtor) (JMS_OWNED_PTR(jms_object) self))
{
    jms_object* self
            = jms_object_init_str(typeName);

    self->staticCtor = staticCtor;

    jms_object_staticCtor(self);

    return self;
}

void jms_object_del(JMS_OWNED_PTR(jms_object) self)
{
    jms_str_del(self->typeName);
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
    bool isTrue = true;
    jms_vec_add(jms_object_typeMetadata, &isTrue);
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
    bool isTrue = true;
    jms_vec_add(jms_object_typeMetadata, &isTrue);
}

static bool jms_object_wasStaticCtorCalled(JMS_OWNED_PTR(jms_object) self)
{
    bool wasStaticCtorCalled = *(bool*)jms_vec_get(jms_object_typeMetadata, 0);

    return wasStaticCtorCalled;
}

static bool jms_object_vectorTypeInfoComparer(
    JMS_BORROWED_PTR(void) typeName,
    JMS_BORROWED_PTR(void) element)
{
    return jms_str_eq_s(
        ((jms_str*)typeName),
        ((jms_object*)element)->typeName);
}