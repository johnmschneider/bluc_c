#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "jms_lex.h"
#include "jms_utils/jms_vector.h"
#include "jms_utils/jms_strUtil.h"

struct jms_lexer
{
    char    tokenBuffer [JMS_LEX_BUFFER_SIZE];
    size_t  line;
    size_t  tokStart;
    char    curChar;
    bool    lastCharWasSpace;

    /**
     * True if a string was just pushed (in the last iteration of the loop)
     *  to the lexed tokens list
     */
    //bool        lastCharWasString;
    //bool        inString;
    size_t      i;
    jms_vector* lexedTokens;

};

jms_lexer* jms_lex_init()
{
    jms_lexer* self = malloc(sizeof(jms_lexer));

    for (size_t i = 0; i < JMS_LEX_BUFFER_SIZE; i++)
    {
        self->tokenBuffer[i] = '\0';
    }

    self->tokStart          = 0;
    self->lastCharWasSpace  = false;
    self->lastCharWasString = false;
    self->inString          = false;
    self->lexedTokens       = jms_vec_init(sizeof(char*));

    return self;
}

void jms_lex_del(jms_lexer* self)
{
    free(self->lexedTokens);
    free(self);
}

static void jms_handleSpace(jms_lexer* self)
{
    if (!self->lastCharWasSpace && !self->lastCharWasString && 
                self->i != 0)
    {
        char* trimmedStrOnHeap = jms_substrToHeap(self->tokenBuffer, 
            self->tokStart, self->i - 1);
        jms_vec_add(self->lexedTokens, trimmedStrOnHeap);

        self->lastCharWasSpace = true;
    }
    
    self->lastCharWasString = false;
    self->tokStart = self->i + 1;
    self->tokenBuffer[self->i] = '\0';
}

static void jms_handleNotSpace(jms_lexer* self)
{
    self->tokenBuffer[self->i] = self->curChar;
    self->lastCharWasSpace = false;

    if (self->curChar != '"')
    {
        self->lastCharWasString = false;
        return;
    }

    if (self->inString)
    {
        // end of string

        char* trimmedStrOnHeap = jms_substrToHeap(
            self->tokenBuffer, self->tokStart, self->i);
        jms_vec_add(self->lexedTokens, trimmedStrOnHeap);

        self->lastCharWasString = true;
    }
    // else start of string falls thru and gets inverted here, that's all
    //  we need to do for a start-of-string token

    self->inString = !self->inString;
}

static void jms_pushTokenIfItsReady(jms_lexer* self)
{
    if (!self->lastCharWasSpace && self->i != 0)
    {
        // add the very last token
        char* trimmedStrOnHeap = jms_substrToHeap(self->tokenBuffer, 
            self->tokStart, self->i - 1);
        jms_vec_add(self->lexedTokens, trimmedStrOnHeap);
    }
}

static void jms_lexLine(jms_lexer* self, char* lineBuffer)
{
    self->tokStart = 0;

    for (self->i = 0; self->i < JMS_LEX_BUFFER_SIZE; self->i++)
    {
        self->curChar = lineBuffer[self->i];

        if (self->curChar == '\0' || self->curChar == '\n')
        {
            break;
        }

        if (isspace(self->curChar))
        {
            jms_handleSpace(self);
        }
        else
        {
            jms_handleNotSpace(self);
        }
    }

    jms_pushTokenIfItsReady(self);
}

// @param lexedTokens - [out] value of the sub-function
static void jms_lexAllLines(jms_lexer* self, FILE* file)
{
    char lineBuffer[JMS_LEX_BUFFER_SIZE] = {0};
    self->line = 1;

    while (!feof(file))
    {
        printf      ("\n\njms_lexAllLines: line == %zu\n", self->line);
        fgets       (lineBuffer, JMS_LEX_BUFFER_SIZE, file);
        jms_lexLine (self, lineBuffer);
        self->line++;
    }
}

jms_vector* jms_lexFile(jms_lexer* self, const char* filePath)
{
    FILE* file = fopen(filePath, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening input file \"%s\". Please check that "
            "the path and file exist.", filePath);
    }
    else
    {
        jms_lexAllLines (self, file);
        fclose          (file);
    }

    return self->lexedTokens;
}