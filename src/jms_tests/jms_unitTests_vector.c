#include <stdlib.h>
#include <stdio.h>

#include "jms_unitTests_vector.h"
#include "../jms_utils/jms_vector.h"

static void jms_unitTest_vec_init(void)
{
    jms_vector* vec = NULL;
    vec = jms_vec_init(sizeof(char));

    JMS_ASSERT(vec != NULL,                 "jms_unitTest_vec_init");
    JMS_ASSERT(jms_vec_elemCount(vec) == 0, "jms_unitTest_vec_init");

    if (vec != NULL)
    {
        jms_vec_del(vec);
    }
}

static void jms_unitTests_vec_add_forceExpand(void)
{
    jms_vector* vec = jms_vec_init(sizeof(int));

    // force an array expansion
    for (int i = 0; i < 10; i++)
    {
        int* intTest2 = malloc(sizeof(int));
        *intTest2 = 600 + i;
        jms_vec_add(vec, intTest2);
    }

    int* vecIndex0 = (int*) jms_vec_get(vec, 0);

    // value right before expansion
    int* vecIndex3 = (int*) jms_vec_get(vec, 3);
    
    // value right after expansion
    int* vecIndex4 = (int*) jms_vec_get(vec, 4);

    JMS_ASSERT((*vecIndex0) == 600, "jms_unitTests_vec_add_forceExpand");
    JMS_ASSERT((*vecIndex3) == 603, "jms_unitTests_vec_add_forceExpand");
    JMS_ASSERT((*vecIndex4) == 604, "jms_unitTests_vec_add_forceExpand");

    jms_vec_del(vec);
}

static void jms_unitTest_vec_add(void)
{
    jms_vector* vec = jms_vec_init(sizeof(int));
    int* intTest    = malloc(sizeof(int));

    *intTest = 452;
    jms_vec_add(vec, intTest);

    int* vecIndex0 = (int*) jms_vec_get(vec, 0);
    JMS_ASSERT((*intTest) == (*vecIndex0), "jms_unitTest_vec_add");
    jms_vec_del(vec);

    printf("\n");
    jms_unitTests_vec_add_forceExpand();
}

static void jms_unitTest_vec_rem(void)
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
        "jms_unitTest_vec_rem");

    JMS_ASSERT(jms_vec_elemCount(vec) == 9, "jms_unitTest_vec_rem");

    // force array to shrink
    for (size_t i = 0; i < 5; i++)
    {
        jms_vec_rem(vec, 4);
    }

    JMS_ASSERT(jms_vec_elemCount(vec) == 4, "jms_unitTest_vec_rem");

    char vecIndex0 = *((char*) jms_vec_get(vec, 0));

    // before shrink
    char vecIndex3 = *((char*) jms_vec_get(vec, 3));

    // at shrink
    void* vecIndex4 = jms_vec_get(vec, 4);

    JMS_ASSERT(vecIndex0 == 'a',    "jms_unitTest_vec_rem");
    JMS_ASSERT(vecIndex3 == 'd',    "jms_unitTest_vec_rem");
    JMS_ASSERT(vecIndex4 == NULL,   "jms_unitTest_vec_rem");

    jms_vec_del(vec);
}

void jms_unitTest_vector(void)
{
    printf("\n");
    jms_unitTest_vec_init();

    printf("\n");
    jms_unitTest_vec_add();

    printf("\n");
    jms_unitTest_vec_rem();
}