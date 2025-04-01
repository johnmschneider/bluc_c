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
#include "jms_utils/jms_strUtil.h"

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

/// @brief Returns whether the given char is equal to the given cString.
/// @param searchCriteria - The char to compare.
/// @param actualElement - The cString to compare against.
/// @return Whether the char is equal to the first character of the cString, or not.
static bool jms_lex_comparer_charCStr(void* searchCriteria, void* actualElement)
{
    JMS_BORROWED_PTR(char) searchChar   = (char*) searchCriteria;
    JMS_BORROWED_PTR(char) elementAsCStr = (char*) actualElement;
    
    return jms_strUtil_cstrEq(elementAsCStr, searchChar);
}

/// @brief Compares the given jms_str, which should only be a length of 1,
//      to the first character in the given cString.
/// @param searchCriteria - The jms_str to compare. Should only be a length of 1.
/// @param actualElement - The cString to compare against.
/// @return Whether the first character of the cString is equal to the value in jms_str, or not.
static bool jms_lex_comparer_stringChar(void* searchCriteria, void* actualElement)
{
    JMS_BORROWED_PTR(jms_str)
        searchStr = (jms_str*) searchCriteria;
    JMS_BORROWED_PTR(char)
        elementAsCStr = (char*) actualElement;

    return jms_str_eq_ch(searchStr, elementAsCStr[0]);
}

//bool jms_lex_
// TODO - finish implementing
static JMS_XFER_PTR(jms_vector) jms_lex(
        JMS_BORROWED_PTR(jms_lexer) self,
        JMS_BORROWED_PTR(jms_str) filePath)
{
    JMS_OWNED_PTR(jms_str) fileTextWithoutComments
        = jms_cremover_run(self->fileContents);

    printf("[%s]: fileTextWithoutComments == `%s`\n", __FUNCTION__, jms_str_cStr(fileTextWithoutComments));

    i32 lineNum = 1;
    i32 column = 1;
    
    bool
        checkNextToken = false;
    bool
        wasLastCharSpace = false;
    bool
        wasLastCharEscaped = false;
    bool
        isInString = false;

    JMS_XFER_PTR(jms_vector)
        lexedTokens = jms_vec_init(sizeof(jms_str*));

    JMS_OWNED_PTR(jms_vector)
        singleTokenLexemesVec = jms_vec_init(sizeof(char*));
    JMS_OWNED_PTR(jms_vector)
        multiTokenLexemesVec = jms_vec_init(sizeof(char*));

    // "Special character" lexemes which will *definitely* be a single character.
    jms_vec_addAll(singleTokenLexemesVec, 9, NULL, "(", ")", "{", "}", "[", "]", ";", ",", ".");

    // "Special character" lexemes which *may* be multiple characters.
    jms_vec_addAll(multiTokenLexemesVec, 16, NULL, "=", "==", "!=", "+=", "-=", "*=", "/=", "%=", "<=", ">=", "&&", "||", "++", "--", "\\", "\\\\");

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

        if (curChar == '\\')
        {
            if (wasLastCharEscaped)
            {
                // We have a double-escaped character, so we need to add it to the word.
                jms_str_append_ch(wordSoFar, curChar);
                wasLastCharEscaped = false;
            }
            else
            {
                wasLastCharEscaped = true;
                continue;
            }
        }
        
        if (isInString)
        {
            if (curChar == '\"')
            {
                if (wasLastCharEscaped)
                {
                    // We have an escaped quote, so we need to add it to the word.
                    jms_str_append_ch(wordSoFar, curChar);
                }
                else
                {
                    // We have the end of a string literal, so we need to add it to the word.

                    jms_lex_appendIfNotWhitespace(
                        lexedTokens,
                        filePath,
                        lineNum,
                        column,
                        wordSoFar);
                    
                    jms_str_append_ch(wordSoFar, curChar);

                    jms_lex_appendIfNotWhitespace(
                        lexedTokens,
                        filePath,
                        lineNum,
                        column,
                        wordSoFar);
                        
                    isInString = false;
                }
            }
        }
        else if (curChar == '\"')
        {
            if (wasLastCharEscaped)
            {
                // We have an escaped quote, so we need to add it to the word.
                jms_str_append_ch(wordSoFar, curChar);
            }
            else
            {
                // We have the start of a string literal, so we need to add it to the word.
                jms_lex_appendIfNotWhitespace(
                    lexedTokens,
                    filePath,
                    lineNum,
                    column,
                    wordSoFar);

                jms_str_append_ch(wordSoFar, curChar);

                jms_lex_appendIfNotWhitespace(
                    lexedTokens,
                    filePath,
                    lineNum,
                    column,
                    wordSoFar);

                isInString = true;
            }

            wasLastCharEscaped = false;
        }
        else if (curChar == '\r')
        {
            // Ignore carriage returns.
            continue;
        }
        else if (isspace(curChar))
        {
            jms_lex_appendIfNotWhitespace(
                lexedTokens,
                filePath,
                lineNum,
                column,
                wordSoFar);
        }
        else if (jms_vec_find(singleTokenLexemesVec, &curChar, jms_lex_comparer_charCStr))
        {
            jms_lex_appendIfNotWhitespace(
                lexedTokens,
                filePath,
                lineNum,
                column,
                wordSoFar);

            jms_str_append_ch(wordSoFar, curChar);

            jms_lex_appendIfNotWhitespace(
                lexedTokens,
                filePath,
                lineNum,
                column,
                wordSoFar);
        }
        else if (curChar == '=')
        {
            // "=" is a special case, because it can be a single token or part of a multi-token lexeme.
            
            jms_str_append_ch(wordSoFar, curChar);

            // check if we have a multi-token equal, such as *= or ==.
            if (jms_vec_find(multiTokenLexemesVec, wordSoFar, jms_lex_comparer_stringChar))
            {
                jms_lex_appendIfNotWhitespace(
                    lexedTokens,
                    filePath,
                    lineNum,
                    column,
                    wordSoFar);
            }
            else if (i != jms_str_len(fileTextWithoutComments) - 1)
            {
                if (jms_str_charAt(fileTextWithoutComments, i + 1) != '=')
                {
                    // It's not a multi-token lexeme, it's just an '='.
                    jms_lex_appendIfNotWhitespace(
                        lexedTokens,
                        filePath,
                        lineNum,
                        column,
                        wordSoFar);
                }
            }
        }
        else
        {
            if (jms_vec_find(multiTokenLexemesVec, wordSoFar, jms_lex_comparer_stringChar))
            {
                jms_lex_appendIfNotWhitespace(
                    lexedTokens,
                    filePath,
                    lineNum,
                    column,
                    wordSoFar);
            }
            else if (isInString && curChar == '\"' && !wasLastCharEscaped)
            {
                jms_lex_appendIfNotWhitespace(
                    lexedTokens,
                    filePath,
                    lineNum,
                    column,
                    wordSoFar);

                jms_str_append_ch(wordSoFar, curChar);

                isInString = false;
            }
            else if (!isInString && curChar == '\"')
            {
                jms_lex_appendIfNotWhitespace(
                    lexedTokens,
                    filePath,
                    lineNum,
                    column,
                    wordSoFar);

                jms_str_append_cs(wordSoFar, "\"");

                isInString = true;
            }

            jms_str_append_ch(wordSoFar, curChar);
        }
    }

    jms_vec_del(singleTokenLexemesVec);
    jms_vec_del(multiTokenLexemesVec);
    jms_str_del(wordSoFar);
    jms_str_del(fileTextWithoutComments);

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