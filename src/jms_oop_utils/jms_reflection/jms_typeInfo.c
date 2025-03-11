#include "jms_typeInfo.h"
#include "../jms_object.h"

struct jms_typeInfo
{
    JMS_OWNED_PTR(jms_object)
        base;

    bool wasStaticCtorCalled;
};

JMS_XFER_PTR(jms_typeInfo) jms_typeInfo_init(const char *typeName)
{
    jms_typeInfo *self = malloc(sizeof(jms_typeInfo));
    self->base = jms_object_init_str((jms_object*)self, "jms_typeInfo");

    self->wasStaticCtorCalled = false;

    return self;
}

bool jms_typeInfo_wasStaticCtorCalled(JMS_OWNED_PTR(jms_typeInfo) self)
{
    return self->wasStaticCtorCalled;
}

void jms_typeInfo_setStaticCtorCalled(JMS_OWNED_PTR(jms_typeInfo) self, bool value)
{
    self->wasStaticCtorCalled = value;
}
