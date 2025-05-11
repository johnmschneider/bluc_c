#ifndef JMS_PARSER_H
#define JMS_PARSER_H

#include "../jms_utils/jms_vector.h"

struct jms_parser;
typedef struct jms_parser jms_parser;

JMS_XFER_PTR(jms_parser)    jms_parser_init (JMS_BORROWED_PTR(jms_vector) lexedTokens);
void                        jms_parser_del  (jms_parser* self);

/**
 * @brief Calls the vtable for this parser (or sub-parser) and parses
 *  as many tokens as possible to finish matching this parser's grammar rule.
 * 
 * @param self The parser instance.
 * @return A vector jms_astNode representing the abstract syntax tree.
 */
JMS_XFER_PTR(jms_vector)    jms_parser_parse(jms_parser* self);

#endif