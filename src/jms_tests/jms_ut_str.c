#include "jms_unitTests.h"
#include "jms_ut_str.h"
#include "../jms_utils/jms_str.h"
#include "../jms_utils/jms_strUtil.h"

static void jms_ut_strInit(void)
{
    const char* testVal = "test123";

    jms_str* test = jms_str_init(testVal);

    JMS_ASSERT(jms_str_len(test) == 7,                  "jms_ut_strInit");
    JMS_ASSERT(jms_cstrEq(jms_str_cStr(test), testVal),  "jms_ut_strInit");

    jms_str_del(test);
}

static void jms_ut_eqCStr()
{
    const char* testVal = "aubergine";

    jms_str* test = jms_str_init(testVal);
    JMS_ASSERT(jms_str_eq_cStr(test, "aubergine"),  "jms_ut_eqCStr");

    jms_str_del(test);
}

/**
 * @brief test string concatenation with other strings
 */
static void jms_ut_catStr()
{
    const char* testVal1 = "apple";
    const char* testVal2 = "orange";

    jms_str* test1 = jms_str_init(testVal1);
    jms_str* test2 = jms_str_init(testVal2);

    jms_str_append_s(test1, test2);
    JMS_ASSERT(jms_str_eq_cStr(test1, "appleorange"), "jms_ut_catStr");

    jms_str_del(test1);
    jms_str_del(test2);
}

static void jms_ut_strLen()
{
    const char* testVal = "green";
    jms_str* test = jms_str_init(testVal);

    JMS_ASSERT(jms_str_len(test) == 5, __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_strCharAt()
{

}

void jms_ut_str(void)
{
    jms_ut_strInit();
    jms_ut_eqCStr();
    jms_ut_catStr();
    jms_ut_strLen();
}