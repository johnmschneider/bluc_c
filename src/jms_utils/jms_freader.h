#ifndef JMS_FREADER_H
#define JMS_FREADER_H
#include "jms_ptr_annotations.h"
#include "jms_str.h"

struct jms_freader;
typedef struct jms_freader jms_freader;

JMS_XFER_PTR(jms_freader)   jms_freader_init(
    JMS_BORROWED_PTR(const char) filepath
);

void                        jms_freader_del(
    JMS_OWNED_PTR(jms_freader) self
);

JMS_XFER_PTR(jms_str)       jms_freader_readLines(
    JMS_BORROWED_PTR(jms_freader) self
);

#endif