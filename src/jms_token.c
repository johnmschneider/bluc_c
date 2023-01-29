#include <string.h>
#include <stdlib.h>
#include "jms_token.h"
#include "jms_utils/jms_ptr_annotations.h"
#include "jms_utils/jms_str.h"

struct jms_token
{
    JMS_OWNED_PTR(jms_str)  filePath;
    JMS_OWNED_PTR(jms_str)  text;
    i32                     lineNumber;
    i32                     colNumber;
};

JMS_XFER_PTR(jms_token) jms_tok_init_cStr(
    JMS_BORROWED_PTR(const char) filePath,
    int lineNumber,
    int colNumber,
    JMS_BORROWED_PTR(const char) text)
{
    jms_token* self = malloc(sizeof(jms_token));

    self->filePath      = jms_str_init(filePath);
    self->text          = jms_str_init(text);

    self->lineNumber    = lineNumber;
    self->colNumber     = colNumber;

    return self;
}

JMS_XFER_PTR(jms_token) jms_tok_init_s(
    JMS_BORROWED_PTR(jms_str) filePath,
    int lineNumber,
    int colNumber,
    JMS_BORROWED_PTR(jms_str) text)
{
    jms_token* self = malloc(sizeof(jms_token));

    self->filePath      = filePath;
    self->text          = text;

    self->lineNumber    = lineNumber;
    self->colNumber     = colNumber;

    return self;
}

void jms_tok_del(jms_token *self)
{
    free(self->filePath);
    free(self->text);
    free(self);
}

JMS_BORROWED_PTR(jms_str) jms_tok_getFilePath(jms_token* self)
{
    return self->filePath;
}

int jms_tok_getLineNum(jms_token* self)
{
    return self->lineNumber;
}

int jms_tok_getColNum(jms_token* self)
{
    return self->colNumber;
}

JMS_BORROWED_PTR(jms_str) jms_tok_getText(jms_token* self)
{
    return self->text;
}