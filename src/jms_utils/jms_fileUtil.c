#include <stdio.h>
#include "jms_fileUtil.h"

jms_str* jms_readFile(const char* filePath)
{
    FILE*       file    = fopen(filePath, "r");
    jms_str*    result  = jms_str_init("");

    
}