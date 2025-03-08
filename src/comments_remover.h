#ifndef COMMENTS_REMOVER_H
#define COMMENTS_REMOVER_H
#include "jms_utils/jms_ptr_annotations.h"
#include "jms_utils/jms_str.h"
#include "jms_utils/jms_vector.h"

JMS_XFER_PTR(jms_str) jms_cremover_run(JMS_BORROWED_PTR(jms_str) linesOfFile);

#endif