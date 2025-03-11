#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "comments_remover.h"
#include "jms_lex.h"
#include "jms_token.h"
#include "jms_utils/jms_freader.h"
#include "jms_utils/jms_vector.h"
#include "jms_utils/jms_str.h"
#include "jms_utils/jms_ptr_annotations.h"
#include "jms_utils/jms_stdint.h"

typedef struct Lexer {
    JMS_OWNED_PTR(jms_str) fileContents;
    char curChar;
    int curCharIndex;

    int line;
} Lexer;

jms_lexer* jms_lex_init()
{
    jms_lexer* self = malloc(sizeof(jms_lexer));

    self->curCharIndex  = 0;
    self->line          = 1;
    self->fileContents  = jms_str_init("");

    return self;
}

void jms_lex_del(jms_lexer* self)
{
    free(self->fileContents);
    free(self);
}

/**
 * Global function - no class instance needed
 */
static void jms_lex_appendIfNotWhitespace(
    JMS_BORROWED_PTR(jms_vector) lexedTokens,
    JMS_OWNED_PTR(jms_str) filePath,
    int32_t lineNum,
    int32_t colNum,
    JMS_OWNED_PTR(jms_str) wordSoFar)
{
    if (!jms_str_isEmpty(wordSoFar) && !jms_str_isWhitespace(wordSoFar))
    {
        jms_token* token = jms_tok_init(
            filePath,
            lineNum,
            colNum,
            wordSoFar);

        jms_vec_add(lexedTokens, token);
    }
}

// TODO - finish implementing
static JMS_XFER_PTR(jms_vector) jms_lex(jms_lexer* self)
{
    jms_str* fileTextWithoutComments = jms_cremover_run(self->fileContents);

    i32 lineNum = 1;
    i32 column = 1;
    
    bool checkNextToken = false;
    jms_vector* lexedTokens = jms_vec_init(sizeof(jms_str*));

    jms_vec_add(lexedTokens, jms_tok_BLUC_SOF);
    
    return NULL;
}

JMS_XFER_PTR(jms_vector) jms_lexFile(jms_lexer* self, const char* filePath)
{
    JMS_XFER_PTR(jms_vector)
                    lexedTokens;
    jms_freader*    reader      = jms_freader_init(filePath);

    self->fileContents = jms_freader_readLines(reader);

    if (self->fileContents == NULL)
    {
        fprintf(stderr, "[%s]: Error reading input file \"%s\". Please check that "
            "the path and file exist.\n", __FUNCTION__, filePath);
        lexedTokens = NULL;
    }
    else
    {
        lexedTokens = jms_lex(self);
    }

    jms_freader_del(reader);
    
    return lexedTokens;
}