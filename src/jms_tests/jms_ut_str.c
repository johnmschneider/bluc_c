#include <stdio.h>
#include "jms_unitTests.h"
#include "jms_ut_str.h"
#include "../jms_utils/jms_str.h"
#include "../jms_utils/jms_strUtil.h"

static void jms_ut_strInit(void)
{
    const char* testVal = "test123";

    jms_str* test = jms_str_init(testVal);

    JMS_ASSERT(jms_str_len(test) == 7,                  __FUNCTION__);
    JMS_ASSERT(jms_cstrEq(jms_str_cStr(test), testVal),  __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_cat_s()
{
    const char* testVal1 = "apple";
    const char* testVal2 = "orange";

    jms_str* test1 = jms_str_init(testVal1);
    jms_str* test2 = jms_str_init(testVal2);

    jms_str_append_s(test1, test2);
    JMS_ASSERT(jms_str_eq_cStr(test1, "appleorange"), __FUNCTION__);

    jms_str_del(test1);
    jms_str_del(test2);
}

static void jms_ut_str_cat_cs()
{
    const char* testVal1 = "apple2";
    const char* testVal2 = "orange";

    jms_str* test1 = jms_str_init(testVal1);

    jms_str_append_cs(test1, testVal2);
    JMS_ASSERT(jms_str_eq_cStr(test1, "apple2orange"), __FUNCTION__);

    jms_str_del(test1);
}

static void jms_ut_str_cat_ch()
{
    const char* testVal1 = "tomat";
    char        testVal2 = 'o';

    jms_str* test1 = jms_str_init(testVal1);

    jms_str_append_ch(test1, testVal2);
    JMS_ASSERT(jms_str_eq_cStr(test1, "tomato"), __FUNCTION__);

    jms_str_del(test1);
}

/**
 * @brief test string concatenation with other strings
 */
static void jms_ut_str_cat()
{
    jms_ut_str_cat_s();
    jms_ut_str_cat_cs();
    jms_ut_str_cat_ch();
}

static void jms_ut_str_cStr()
{
    const char* testVal = "potato";

    jms_str* test = jms_str_init(testVal);

    JMS_ASSERT(jms_str_eq_cStr(test, "potato"), __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_eqS()
{
    const char* testVal = "potato stew";

    jms_str* test   = jms_str_init(testVal);
    jms_str* test2  = jms_str_init(testVal); // testVal should be strcpy'd

    JMS_ASSERT(jms_str_eq_s(test, test2), __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_eqCStr()
{
    const char* testVal = "tomato stew";

    jms_str* test = jms_str_init(testVal);

    JMS_ASSERT(jms_str_eq_cStr(test, "tomato stew"), __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_len()
{
    const char* testVal = "green";
    jms_str* test = jms_str_init(testVal);

    JMS_ASSERT(jms_str_len(test) == 5, __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_charAt()
{
    const char* testVal = "blorange";
    jms_str* test = jms_str_init(testVal);

    JMS_ASSERT(jms_str_charAt(test, 2) == 'o', __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_setCStr()
{
    const char* testVal1 = "aubergine";
    const char* testVal2 = "eggplant";

    jms_str* test = jms_str_init(testVal1);
    jms_str_set_cStr(test, testVal2);

    JMS_ASSERT(jms_str_eq_cStr(test, "eggplant"), __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_strIsEmpty()
{
    jms_str* test = jms_str_init("");

    JMS_ASSERT(jms_str_isEmpty(test), __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_strIsNotEmpty()
{
    jms_str* test = jms_str_init("pizza");

    JMS_ASSERT_FAIL(jms_str_isEmpty(test), __FUNCTION__);

    jms_str_del(test);
}

static void jms_ut_str_IsWhitespaceReturnsTrue()
{
    jms_str* oneWhitespace      = jms_str_init(" ");
    jms_str* severalWhitespaces = jms_str_init("\n\t ");

    JMS_ASSERT(
        jms_str_isWhitespace(oneWhitespace),
        __FUNCTION__);
    JMS_ASSERT(
        jms_str_isWhitespace(severalWhitespaces),
        __FUNCTION__);

    jms_str_del(oneWhitespace);
    jms_str_del(severalWhitespaces);
}

static void jms_ut_str_IsWhitespaceReturnsFalse()
{
    jms_str* noWhitespaces
        = jms_str_init("buffalo_sauce");

    jms_str* oneWhitespaceBefore
        = jms_str_init(" a");

    jms_str* twoWhitespacesBefore
        = jms_str_init("\n\t x");

    jms_str* oneWhitespaceBetween
        = jms_str_init("buffalo sauce");


    JMS_ASSERT_FAIL(
        jms_str_isWhitespace(noWhitespaces),
        __FUNCTION__);

    JMS_ASSERT_FAIL(
        jms_str_isWhitespace(oneWhitespaceBefore),
        __FUNCTION__);

    JMS_ASSERT_FAIL(
        jms_str_isWhitespace(twoWhitespacesBefore),
        __FUNCTION__);
        
    JMS_ASSERT_FAIL(
        jms_str_isWhitespace(oneWhitespaceBetween),
        __FUNCTION__);

    jms_str_del(noWhitespaces);
    jms_str_del(oneWhitespaceBefore);
    jms_str_del(twoWhitespacesBefore);
    jms_str_del(oneWhitespaceBetween);
}

void jms_ut_str(void)
{
    jms_ut_strInit();
    
    printf("\n");
    jms_ut_str_cat();

    printf("\n");
    jms_ut_str_eqS();
    jms_ut_str_eqCStr();
    printf("\n");
    
    jms_ut_str_cStr();
    jms_ut_str_len();
    jms_ut_str_charAt();
    jms_ut_str_setCStr();
    jms_ut_str_strIsEmpty();
    jms_ut_str_strIsNotEmpty();
    
    printf("\n");
    jms_ut_str_IsWhitespaceReturnsTrue();
    jms_ut_str_IsWhitespaceReturnsFalse();
    printf("\n");
}