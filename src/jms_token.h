#ifndef JMS_TOKEN_H
#define JMS_TOKEN_H
#include "jms_keywords.h"

struct jms_token;
typedef struct jms_token jms_token;


/**
 * @brief ctor for jms_token
 * 
 * @param text          - character pointer on the *stack*. 
 *                      creates a deep copy. represents the
 *                      text of the token
 * @param lineNumber    - the line number   (starts at 1)
 * @param colNumber     - the column number (starts at 1)
 * 
 * @return jms_token*   - the instance that was initiated
 */
jms_token*  jms_tok_init(const char* text, int lineNumber, int colNumber);

void        jms_tok_del(jms_token* self);


/**
 * @return const char* - the text representation of this token.
 *                      returns the actual pointer, *do not free*
 *                      as it's managed by the token class.
 */
const char* getText(jms_token* self);

#endif