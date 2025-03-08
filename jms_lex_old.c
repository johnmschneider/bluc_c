#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "jms_lex.h"
#include "jms_utils/jms_vector.h"
#include "jms_utils/jms_strUtil.h"

static void lexLine(jms_vector* lexedTokens, char* lineBuffer)
{
    char    tokenBuffer [JMS_LEX_BUFFER_SIZE]   = {0};
    size_t  tokStart = 0;
    bool    lastCharWasSpace = false;
    size_t  i;

    for (i = 0; i < JMS_LEX_BUFFER_SIZE; i++)
    {
        char curChar = lineBuffer[i];
        if (curChar == '\0' || curChar == '\n')
        {
            break;
        }

        if (isspace(curChar))
        {
            tokenBuffer[i] = '\0';

            if (!lastCharWasSpace && i != 0)
            {
                char* trimmedStrOnHeap = jms_strUtil_substrToHeap(tokenBuffer, 
                    tokStart, i - 1);
                jms_vec_add(lexedTokens, trimmedStrOnHeap);

                lastCharWasSpace = true;
            }
            
            tokStart = i + 1;
        }
        else
        {
            tokenBuffer[i] = curChar;
            lastCharWasSpace = false;
        }
    }

    if (!lastCharWasSpace && i != 0)
    {
        // add the very last token
        char* trimmedStrOnHeap = jms_strUtil_substrToHeap(tokenBuffer, 
                tokStart, i - 1);
            jms_vec_add(lexedTokens, trimmedStrOnHeap);
    }
}

// @param lexedTokens - [out] value of the sub-function
static void lexAllLines(jms_vector* lexedTokens, FILE* file)
{
    char lineBuffer[JMS_LEX_BUFFER_SIZE] = {0};
    size_t line = 1;

    while (!feof(file))
    {
        printf("\n\nlexAllLines: line == %zu\n", line);
        fgets   (lineBuffer, JMS_LEX_BUFFER_SIZE, file);
        lexLine(lexedTokens, lineBuffer);
        line++;
    }
}

jms_vector* jms_lexFile(const char* filePath)
{
    jms_vector* lexedTokens = jms_vec_init(sizeof(char*));
    FILE*       file;

    file = fopen(filePath, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error opening input file \"%s\". Please check that "
            "the path and file exist.", filePath);
    }
    else
    {
        lexAllLines (lexedTokens, file);
        fclose      (file);
    }

    return lexedTokens;
}