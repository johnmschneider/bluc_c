#include <string.h>
#include <stdlib.h>
#include "jms_token.h"


struct jms_token
{
    char*   text;
    int     lineNumber;
    int     colNumber;
};

jms_token* jms_tok_init(const char* text, int lineNumber, int colNumber)
{
    jms_token* self = malloc(sizeof(jms_token));

    self->text = malloc(strlen(text) * sizeof(char) + 1);
    strcpy(self->text, text);
    
    self->lineNumber    = lineNumber;
    self->colNumber     = colNumber;

    return self;
}

const char* getText(jms_token* self)
{
    return self->text;
}