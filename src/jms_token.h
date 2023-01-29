#ifndef JMS_TOKEN_H
#define JMS_TOKEN_H
#include "jms_keywords.h"
#include "jms_utils/jms_ptr_annotations.h"
#include "jms_utils/jms_str.h"
#include "jms_utils/jms_stdint.h"

struct jms_token;
typedef struct jms_token jms_token;


/**
 * @brief ctor for jms_token
 * 
 * @param filePath      - character pointer on the *stack*. 
 *                          creates a deep copy. represents the
 *                          filepath that the token is from
 * @param lineNumber    - the line number   (starts at 1)
 * @param colNumber     - the column number (starts at 1)
 * @param text          - character pointer on the *stack*. 
 *                          creates a deep copy. represents the
 *                          text of the token
 * @return jms_token*   - the instance that was initiated
 */
JMS_XFER_PTR(jms_token) jms_tok_init_cStr(
    JMS_BORROWED_PTR(const char) filePath,
    int lineNumber,
    int colNumber,
    JMS_BORROWED_PTR(const char) text);

JMS_XFER_PTR(jms_token) jms_tok_init_s(
    JMS_BORROWED_PTR(jms_str) filePath,
    int lineNumber,
    int colNumber,
    JMS_BORROWED_PTR(jms_str) text);

void                    jms_tok_del(jms_token* self);


JMS_BORROWED_PTR(jms_str) jms_tok_getFilePath(jms_token* self);

i32 jms_tok_getLineNum(jms_token* self);

i32 jms_tok_getColNum(jms_token* self);

/**
 * @return jms_str* - the text representation of this token.
 *                      returns the actual pointer, *do not free*
 *                      as it's managed by the token class.
 */
JMS_BORROWED_PTR(jms_str) jms_tok_getText(jms_token* self);

#endif