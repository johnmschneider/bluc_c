#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
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
    JMS_BORROWED_PTR(jms_str) filePath,
    int32_t lineNum,
    int32_t colNum,
    JMS_BORROWED_PTR(jms_str) wordSoFar)
{
    if (!jms_str_isEmpty(wordSoFar) && !jms_str_isWhitespace(wordSoFar))
    {
        jms_token* token = jms_tok_init(
            jms_str_init_str(filePath),
            lineNum,
            colNum,
            jms_str_init_str(wordSoFar));

        // Function pointers are why we can't have nice things in c. That, and lack of real generics.
        jms_vec_add(lexedTokens, token, ((void (*) (void*))jms_tok_del));

        // Reset the "Word so far" to an empty string.
        jms_str_set_cStr(wordSoFar, "");
    }
}

// TODO - finish implementing
static JMS_XFER_PTR(jms_vector) jms_lex(
        JMS_BORROWED_PTR(jms_lexer) self,
        JMS_BORROWED_PTR(jms_str) filePath)
{
    jms_str* fileTextWithoutComments = jms_cremover_run(self->fileContents);

    i32 lineNum = 1;
    i32 column = 1;
    
    bool
        checkNextToken = false;
    JMS_XFER_PTR(jms_vector)
        lexedTokens = jms_vec_init(sizeof(jms_str*));

    // "Special character" lexemes which will *definitely* be a single character.
    const char* singleTokenLexemes[] =
    {
        "(", ")", "{", "}", "[", "]", ";", ",", "."
    };

    // "Special character" lexemes which *may* be multiple characters.
    const char* multiTokenLexemes[] =
    {
        "=", "==", "!=", "+=", "-=", "*=", "/=", "%=", "<=", ">=", "&&", "||", "++", "--"

    };

    JMS_OWNED_PTR(jms_vector)
        singleTokenLexemesVec = jms_vec_init(sizeof(jms_str*));
    JMS_OWNED_PTR(jms_vector)
        multiTokenLexemesVec = jms_vec_init(sizeof(jms_str*));

    for (size_t i = 0; i < sizeof(singleTokenLexemes)/sizeof(singleTokenLexemes[0]); i++)
    {
        jms_str* lexeme = jms_str_init(singleTokenLexemes[i]);
        jms_vec_add(
            singleTokenLexemesVec,
            lexeme, 
            ((void (*) (void*))jms_str_del));
    }


    JMS_OWNED_PTR(jms_str)
        wordSoFar = jms_str_init("");

    for (size_t i = 0; i < jms_str_len(fileTextWithoutComments); i++)
    {
        char curChar = jms_str_charAt(fileTextWithoutComments, i);

        if (curChar == '\n')
        {
            lineNum++;
            column = 1;
        }
        else
        {
            column++;
        }


        if (isspace(curChar))
        {
            jms_lex_appendIfNotWhitespace(
                lexedTokens,
                filePath,
                lineNum,
                column,
                wordSoFar);
        }
        else
        {
            jms_str_append_ch(wordSoFar, curChar);
        }
    }

    return lexedTokens;
}

JMS_XFER_PTR(jms_vector) jms_lexFile(jms_lexer* self, const char* filePath)
{
    JMS_XFER_PTR(jms_vector)
        lexedTokens;
    JMS_OWNED_PTR(jms_freader)
        reader = jms_freader_init(filePath);

    self->fileContents = jms_freader_readLines(reader);

    if (self->fileContents == NULL)
    {
        fprintf(stderr, "[%s]: Error reading input file \"%s\". Please check that "
            "the path and file exist.\n", __FUNCTION__, filePath);
        lexedTokens = NULL;
    }
    else
    {
        JMS_XFER_PTR(jms_str)
            filePathAsStr = jms_str_init(filePath);

        lexedTokens = jms_lex(self, filePathAsStr);

        jms_str_del(filePathAsStr);
    }

    jms_freader_del(reader);
    
    return lexedTokens;
}