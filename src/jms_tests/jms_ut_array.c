#include "jms_unitTests.h"
#include "../jms_utils/jms_array.h"
#include "jms_ut_array.h"

static void jms_ut_arrInit(void)
{
    size_t      testLen = 2;
    jms_array*  arr     = jms_arr_init(sizeof(int), testLen);
    
    JMS_ASSERT(arr != NULL,                 "jms_ut_arrInit");
    JMS_ASSERT(jms_arr_len(arr) == testLen, "jms_ut_arrInit");

    jms_arr_del(arr);
}

static void jms_ut_arrDel(void)
{
    // there's no way to really test the dtor at the moment
}

void jms_ut_array(void)
{
    jms_ut_arrInit();
    jms_ut_arrDel();
}