#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "jms_lex.h"
#include "jms_token.h"
#include "jms_utils/jms_vector.h"
#include "jms_utils/jms_str.h"
#include "jms_utils/jms_ptr_annotations.h"

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
        jms_token* token = jms_tok_init_s(
            filePath,
            lineNum,
            colNum,
            wordSoFar);
    }
}

static jms_vector* jms_lex(jms_lexer* self)
{
    // TODO - finish implementing
    linesOfFile = //
    int32_t lineNum = 1;
    
    jms_vector* lexedTokens = jms_vec_init(sizeof(jms_str*));

    return NULL;
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
        // TODO - refactor this all out to a jms_freader class
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

        result = jms_lex(self);
    }

    return result;
}