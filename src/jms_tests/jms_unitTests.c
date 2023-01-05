#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "jms_unitTests.h"
#include "jms_unitTests_vector.h"
#include "jms_ut_array.h"
#include "jms_ut_str.h"

/**
 * @brief how many assertions have failed. if JMS_ASSERT_FAIL was
 *  called and the result was true, then it counts as a failed
 *  assertion here.
 */
static int32_t jms_failedAsserts = 0;

/**
 * @brief how many assertions have passed. if JMS_ASSERT_FAIL was
 *  called and the result was false, then it counts as a passed
 *  assertion here.
 */
static int32_t jms_passedAsserts = 0;

bool jms_assert(bool assertion, const char* funcName,
                const char* whatWasTested)
{
    if (assertion)
    {
        printf("jms_unitTests.assert, success: {%s}, \t\t%s\n", funcName, 
            whatWasTested);
        jms_passedAsserts++;
    }
    else
    {
        fprintf(stderr, "jms_unitTests.assert, FAILURE: {%s}, \t\t%s\n", funcName, 
            whatWasTested);
        jms_failedAsserts++;
    }

    return assertion;
}

bool jms_assertFail(bool assertion,const char* funcName,
                        const char* whatWasTested)
{
    if (!assertion)
    {
        printf("jms_unitTests.assertFail, success: {%s}, \t\t%s\n", funcName, 
            whatWasTested);
        jms_passedAsserts++;
    }
    else
    {
        fprintf(stderr, "jms_unitTests.assertFail, FAILURE: {%s}, \t\t%s\n", funcName, 
            whatWasTested);
        jms_failedAsserts++;
    }

    return assertion;
}

void jms_unitTests_nextUnit(void)
{
    printf("\n");
}

void jms_unitTests_run(void)
{
    printf("\n====\njms_unitTests_run: starting unit tests...\n====\n");

    jms_unitTest_vector();
    jms_unitTests_nextUnit();

    jms_ut_array();
    jms_unitTests_nextUnit();

    jms_ut_str();
    jms_unitTests_nextUnit();

    printf("\n====\njms_unitTests_run: unit tests finished\n");
    printf("%d tests passed, %d tests failed", jms_passedAsserts, jms_failedAsserts);
    printf("\n====\n\n");
}