#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "jms_unitTests.h"
#include "jms_ut_vector.h"
#include "../jms_utils/jms_vector.h"

static void jms_ut_vec_init(void)
{
    jms_vector* vec = NULL;
    vec = jms_vec_init(sizeof(char));

    JMS_ASSERT(vec != NULL,                 __FUNCTION__);
    JMS_ASSERT(jms_vec_elemCount(vec) == 0, __FUNCTION__);
    JMS_ASSERT(jms_vec_capacity(vec) == 10, __FUNCTION__);

    if (vec != NULL)
    {
        jms_vec_del(vec);
    }
}

static void jms_ut_vec_elemCount(void)
{
    jms_vector* vec               = jms_vec_init(
                                        sizeof(int32_t));
    int32_t     testStartingValue = 300;
    
    for (int i = 0; i < 5; i++)
    {
        int* intTest = malloc(sizeof(int));
        *intTest = testStartingValue + i;
        jms_vec_add(vec, intTest);
    }

    JMS_ASSERT(jms_vec_elemCount(vec) == 5, __FUNCTION__);

    jms_vec_del(vec);
}

static void jms_ut_vec_add_forceExpand(void)
{
    jms_vector* vec             = jms_vec_init(sizeof(int));
    int32_t testStartingValue   = 600;

    // force an array expansion
    for (int i = 0; i < 10; i++)
    {
        int* intTest2 = malloc(sizeof(int));
        *intTest2 = testStartingValue + i;
        jms_vec_add(vec, intTest2);
    }

    int* vecIndex0 = (int*) jms_vec_get(vec, 0);

    // value right before expansion
    int* vecIndex3 = (int*) jms_vec_get(vec, 3);
    
    // value right after expansion
    int* vecIndex4 = (int*) jms_vec_get(vec, 4);

    JMS_ASSERT((*vecIndex0) == 600, __FUNCTION__);
    JMS_ASSERT((*vecIndex3) == 603, __FUNCTION__);
    JMS_ASSERT((*vecIndex4) == 604, __FUNCTION__);

    jms_vec_del(vec);
}

static void jms_ut_vec_add(void)
{
    jms_vector* vec = jms_vec_init(sizeof(int));
    int* intTest    = malloc(sizeof(int));

    *intTest = 452;
    jms_vec_add(vec, intTest);

    int* vecIndex0 = (int*) jms_vec_get(vec, 0);
    JMS_ASSERT((*intTest) == (*vecIndex0), __FUNCTION__);
    jms_vec_del(vec);

    printf("\n");
    jms_ut_vec_add_forceExpand();
}

static void jms_ut_vec_get(void)
{
    jms_vector* vec = jms_vec_init(sizeof(int));
    int* intTest    = malloc(sizeof(int));

    *intTest = 457;
    jms_vec_add(vec, intTest);

    int* vecIndex0 = (int*) jms_vec_get(vec, 0);
    JMS_ASSERT((*intTest) == (*vecIndex0), __FUNCTION__);
    jms_vec_del(vec);
}

static void jms_ut_vec_rem(void)
{
    jms_vector* vec = jms_vec_init(sizeof(char));

    for (size_t i = 'a'; i < 'a' + 10; i++)
    {
        char* charTest  = malloc(sizeof(char));
        *charTest = i;
        jms_vec_add(vec, charTest);
    }

    int lastIndex = jms_vec_elemCount(vec) - 1;
    jms_vec_rem(vec, lastIndex);

    // test just removing the element, no array shrink
    JMS_ASSERT(jms_vec_get(vec, lastIndex) == NULL,
        __FUNCTION__);

    JMS_ASSERT(jms_vec_elemCount(vec) == 9, __FUNCTION__);

    // force array to shrink
    for (size_t i = 0; i < 5; i++)
    {
        jms_vec_rem(vec, 4);
    }

    JMS_ASSERT(jms_vec_elemCount(vec) == 4, __FUNCTION__);

    char vecIndex0 = *((char*) jms_vec_get(vec, 0));

    // before shrink
    char vecIndex3 = *((char*) jms_vec_get(vec, 3));

    // at shrink
    void* vecIndex4 = jms_vec_get(vec, 4);

    JMS_ASSERT(vecIndex0 == 'a',    __FUNCTION__);
    JMS_ASSERT(vecIndex3 == 'd',    __FUNCTION__);
    JMS_ASSERT(vecIndex4 == NULL,   __FUNCTION__);

    jms_vec_del(vec);
}

void jms_ut_vector(void)
{
    printf("\n");
    jms_ut_vec_init();

    printf("\n");
    jms_ut_vec_elemCount();

    printf("\n");
    jms_ut_vec_add();

    printf("\n");
    jms_ut_vec_get();

    printf("\n");
    jms_ut_vec_rem();
}