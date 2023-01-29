#ifndef COMMENTS_REMOVER_H
#define COMMENTS_REMOVER_H
#include "jms_utils/jms_ptr_annotations.h"
#include "jms_utils/jms_vector.h"

void jms_cremover_run(JMS_BORROWED_PTR(jms_vector) linesOfFile);

#endif