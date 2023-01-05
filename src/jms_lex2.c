#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "jms_lex.h"
#include "jms_utils/jms_vector.h"
#include "jms_utils/jms_str.h"

typedef struct Lexer {
    jms_str* fileContents;
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
    free(self);
}

bool isEndOfString(char curChar)
{
    return curChar == '\0';
}

bool isNotEndOfString(char curChar)
{
    return !isEndOfString(curChar);
}

static const int JMS_LEX_NEXT_SUCCESS = 0;
static const int JMS_LEX_NEXT_EOF = 1;

/**
 * @brief returns either JMS_LEX_NEXT_SUCCESS (0) or an error code
 */
static int jms_nextToken(Lexer* self)
{
    self->curCharIndex++;

    if (self->curCharIndex < jms_str_len(self->fileContents))
    {
        self->curChar = jms_str_charAt(self->fileContents, self->curCharIndex);
        
        if (self->curChar == '\n')
        {
            self->line++;
        }
        // TODO - commented out temporarily in order to see valgrind info.
        //  the issue that this printf was created for is not yet resolved.
        //
        // printf("[jms_lex2.%s]: .current == %c\n", __FUNCTION__, self->curChar);

        return JMS_LEX_NEXT_SUCCESS;
    }
    else
    {
        // else, we are at the end of file
        self->curChar = '\0';

        printf("[jms_lex2.%s]: .current == %c\n", __FUNCTION__, self->curChar);
        return JMS_LEX_NEXT_EOF;
    }
}

static jms_str* jms_readToken(Lexer* self)
{
    jms_str*    token = jms_str_init("");

    jms_nextToken(self);
    if (self->curChar == '\0')
    {
        return NULL;
    }
    
    // fileContents appears to be correct.. leaving in just in case
    //  I need to debug it again
    //
    // printf("[jms_lex2.%s]: fileContents == %s", __FUNCTION__,
    //     jms_str_cStr(self->fileContents));

    // skip junk
    while (true)
    {
        if (isspace(self->curChar))
        {
            if (self->curChar == '\n')
            {
                // this line was also just blank space
                //  (newline should be the last char
                //  of the string)
                jms_str_append_ch(token, '\n');

                self->line ++;
                jms_nextToken(self);

                return token;
            }
        }
        else if (isEndOfString(self->curChar))
        {
            // this line was just blank space
            return NULL;
        }
        else
        {
            // non-space char was found
            break;
        }
        
        self->curChar++;
    }

    // categorize

    // commented out because i dont think it's needed
    //
    //char start = self->curChar;
    int32_t startIndex = self->curCharIndex;

    if (self->curChar == '\"')
    {
        bool endingQuoteFound = false;

        while (isNotEndOfString(self->curChar))
        {
            if (self->curChar != '\"')
            {
                endingQuoteFound = true;
                break;
            }

            if (jms_nextToken(self) != JMS_LEX_NEXT_SUCCESS)
            {
                break;
            }
        }

        if (!endingQuoteFound)
        {
            fprintf(stderr, "Unclosed string.\n");
            abort();
        }

        jms_nextToken(self);
    } else
    {
        while (!isspace(self->curChar))
        {
            if (isEndOfString(self->curChar))
            {
                break;
            }

            jms_str_append_ch(token, self->curChar);
            
            //printf("[jms_lex2.%s]", __FUNCTION__);
            if (jms_nextToken(self) != JMS_LEX_NEXT_SUCCESS)
            {
                break;
            }
        }
    }

    // // spit out token
    // const char* end = lexer->current;
    // size_t len = end - start;

    // char* str = malloc(len + 1);
    // memcpy(str, start, len);
    // str[len] = '\0';

    return token;
}

static jms_vector* jms_lexAllLines(jms_lexer* self, jms_str* source_string)
{
    // commenting out and replacing with *self*..
    //  leaving in in case this update breaks stuff
    //
    //Lexer*      lexer       = jms_lex_init();
    jms_vector* tokens      = jms_vec_init(sizeof(jms_str*));
    jms_str*    token_str;

    self->curChar = jms_str_charAt(source_string, 0);

    printf("[jms_lex2.%s]: .current == %c\n", __FUNCTION__, self->curChar);
    
    while ((token_str = jms_readToken(self)) != NULL)
    {
        if (jms_str_charAt(token_str, 0) != '\n')
        {
            jms_vec_add(tokens, token_str);
        }
    }

    return tokens;
}

jms_vector* jms_lexFile(jms_lexer* self, const char* filePath)
{
    jms_vector* result  = NULL;
    FILE* file          = fopen(filePath, "r");
    char* buffer;


    if (file == NULL)
    {
        fprintf(stderr, "Error opening input file \"%s\". Please check that "
            "the path and file exist.", filePath);
    }
    else
    {
        char code;

        // c stdlib uses long, not int64_t :(
        long bytesInFile;
        
        
        self->curCharIndex = -1;
        fseek(file, 0L, SEEK_END);
        bytesInFile = ftell(file);

        fseek(file, 0L, SEEK_SET);	
        buffer = (char*) calloc(bytesInFile, sizeof(char));	

        fread(buffer, sizeof(char), bytesInFile, file);
        fclose(file);

        jms_str_set_cStr(self->fileContents, buffer);

        printf("\njms_lex2.jms_lexFile: fileContents == \n>[\n%s\n]<\n\n",
            jms_str_cStr(self->fileContents));

        result = jms_lexAllLines(self, self->fileContents);
    }

    return result;
}