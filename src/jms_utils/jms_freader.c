#include <stdlib.h>
#include <stdio.h>
#include "jms_freader.h"
#include "jms_str.h"

struct jms_freader
{
    JMS_OWNED_PTR(jms_str) filePath;
};

JMS_XFER_PTR(jms_freader) jms_freader_init(
    JMS_BORROWED_PTR(const char) filePath)
{
    jms_freader* self = malloc(sizeof(jms_freader));
    self->filePath = jms_str_init(filePath);

    return self;
}

void jms_freader_del(JMS_OWNED_PTR(jms_freader) self)
{
    jms_str_del(self->filePath);
    free(self);
}

static long jms_freader_getBytesInFile(FILE* file)
{
    fseek(file, 0L, SEEK_END);
    long bytesInFile = ftell(file);

    fseek(file, 0L, SEEK_SET);	

    return bytesInFile;
}

JMS_XFER_PTR(jms_str) jms_freader_readLines(
    JMS_BORROWED_PTR(jms_freader) self)
{
    JMS_XFER_PTR(jms_str) fileContents
                        = NULL;
    char* filePath      = jms_str_cStr(self->filePath);
    FILE* file          = fopen(filePath, "r");
    char* buffer;

    if (file == NULL)
    {
        fprintf(stderr, "[%s]: Error opening input "
            "file \"%s\". Please check that the path and file "
            "exist.", __func__, filePath);
        return NULL;
    }
    else
    {
        // c stdlib uses long, not int64_t :(
        long bytesInFile;

        fileContents    = jms_str_init("");        
        bytesInFile     = jms_freader_getBytesInFile(file);
        buffer          = (char*) calloc(bytesInFile, sizeof(char));

        fread(buffer, sizeof(char), bytesInFile, file);
        fclose(file);

        jms_str_set_cStr(fileContents, buffer);

        printf("\n[%s]: fileContents == \n>[\n%s\n]<\n\n",
            __func__, jms_str_cStr(fileContents));
    }

    return fileContents;
}