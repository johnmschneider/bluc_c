#ifndef JMS_RESULT_H
#define JMS_RESULT_H

#include "jms_ptr_annotations.h"

struct jms_result;
typedef struct jms_result jms_result;

// This constructor is private, it shouldn't be exposed in the header file.
// @see jms_result_success or jms_result_failure instead
// 
// private JMS_XFER_PTR(jms_result)    jms_result_init (void);

void                        jms_result_del  (JMS_OWNED_PTR(jms_result) self);

#endif