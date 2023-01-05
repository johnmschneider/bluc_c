
#ifndef JMS_UNITTESTS_H
#define JMS_UNITTESTS_H

#include <stdbool.h>

/**
 * Assert something to be true.
 * Returns `assertion`.
 */
bool jms_assert         (bool assertion, const char* funcName,
                        const char* whatWasTested);

/**
 * Assert something to be false.
 * Returns `assertion`.
 */
bool jms_assertFail     (bool assertion, const char* funcName,
                        const char* whatWasTested);

#define JMS_ASSERT(assertion, funcName) \
    jms_assert(assertion, funcName, #assertion)

#define JMS_ASSERT_FAIL(assertion, funcName) \
    jms_assertFail(assertion, funcName, #assertion)

/**
 * Specifies, in the test output, that the previous unit of testing 
 *  is complete. As of right now, it just prints a newline.
 */
void    jms_unitTests_unitDone  (void);

void    jms_unitTests_run       (void);

#endif