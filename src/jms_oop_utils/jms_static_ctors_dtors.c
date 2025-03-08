#include <stdio.h>
#include "jms_static_ctors_dtors.h"

static void jms_static_ctor_token(void)
{

}

static void jms_static_dtor_token(void)
{
    fprintf(stderr,
        "[%s]: ERROR, func not implemented", __FUNCTION__);
}

void jms_static_ctors_run(void)
{
    jms_static_ctor_token();
}

void jms_static_dtors_run(void)
{
    jms_static_dtor_token();
}
