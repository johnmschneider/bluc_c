#include "jms_typeInfo.h"
#include "../jms_object.h"

struct jms_typeInfo
{
    bool wasStaticCtorCalled;
    const char* typeName;
};

JMS_XFER_PTR(jms_typeInfo) jms_typeInfo_init(const char *typeName)
{
    jms_typeInfo *self = malloc(sizeof(jms_typeInfo));
    
    self->wasStaticCtorCalled = false;
    self->typeName = typeName;

    return self;
}

void jms_typeInfo_del(JMS_OWNED_PTR(jms_typeInfo) self)
{
    free(self);
}

bool jms_typeInfo_wasStaticCtorCalled(JMS_OWNED_PTR(jms_typeInfo) self)
{
    return self->wasStaticCtorCalled;
}

void jms_typeInfo_setStaticCtorCalled(JMS_OWNED_PTR(jms_typeInfo) self, bool value)
{
    self->wasStaticCtorCalled = value;
}

JMS_BORROWED_PTR(const char) jms_typeInfo_typeName(JMS_BORROWED_PTR(jms_typeInfo) self)
{
    return self->typeName;
}