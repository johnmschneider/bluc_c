#ifndef JMS_PARSER_H
#define JMS_PARSER_H

#include "../jms_utils/jms_vector.h"

struct jms_parser;
typedef struct jms_parser jms_parser;

jms_parser* jms_parser_init (jms_vector* lexedTokens);
void        jms_parser_del  (jms_parser* self);

void        jms_parser_parse(jms_parser* self);

#endif