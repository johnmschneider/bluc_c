#ifndef JMS_TESTUNIT_H
#define JMS_TESTUNIT_H
#include <stdbool.h>

struct jms_testUnit;
typedef struct jms_testUnit jms_testUnit;

jms_testUnit*   jms_testUnit_init(void);
void            jms_testUnit_del (jms_testUnit* self);

const char*     jms_testUnit_unitName   (jms_testUnit* self);
bool            jms_testUnit_equals     (jms_testUnit* other);

#endif