#include <string.h>
#include <stdlib.h>
#include "jms_oop_utils/jms_object.h"
#include "jms_token.h"
#include "jms_utils/jms_ptr_annotations.h"
#include "jms_utils/jms_str.h"

jms_token* jms_tok_BLUC_SOF = NULL;

struct jms_token
{
    JMS_OWNED_PTR(jms_object)
        objectBase;
    JMS_OWNED_PTR(jms_str)
        filePath;
    JMS_OWNED_PTR(jms_str)
        text;
    i32
        lineNumber;
    i32
        colNumber;
};

static void jms_tok_staticInit(JMS_OWNED_PTR(jms_object) self);

JMS_XFER_PTR(jms_token) jms_tok_init(
    JMS_OWNED_PTR(jms_str) filePath,
    int lineNumber,
    int colNumber,
    JMS_OWNED_PTR(jms_str) text)
{
    jms_token* self
            = malloc(sizeof(jms_token));
    self->objectBase
            = jms_object_init_str_func(
                "jms_token",
                &jms_tok_staticInit);

    self->filePath      = filePath;
    self->text          = text;

    self->lineNumber    = lineNumber;
    self->colNumber     = colNumber;

    return self;
}

static void jms_tok_staticInit(JMS_OWNED_PTR(jms_object) self)
{
    jms_tok_BLUC_SOF
        = jms_tok_init(
                jms_str_init("N/A"),
                0,
                0,
                jms_str_init("___BLUC_SOF"));
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