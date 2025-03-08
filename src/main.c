#include <stdio.h>
#include <stdlib.h>
#include "jms_oop_utils/jms_static_ctors_dtors.h"
#include "jms_utils/jms_vector.h"
#include "jms_tests/jms_unitTests.h"
#include "jms_lex.h"
#include "jms_utils/jms_str.h"

#define JMS_UNIT_TESTS_ON
#define JMS_DEBUG_FILENAME "src/test.bluc"

int run_program(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    jms_static_ctors_run();
    int result = run_program(argc, argv);
    jms_static_dtors_run();

    return result;
}

int run_program(int argc, char* argv[])
{
    printf("main: before jms_unitTests_run\n");
#ifdef JMS_UNIT_TESTS_ON
    jms_unitTests_run();
#endif
    fflush(stdout);
    printf("main: after jms_unitTests_run\n");


#ifdef JMS_DEBUG_FILENAME
    char* filePath = JMS_DEBUG_FILENAME;
#else
    if (argc < 1)
    {
        fprintf(stderr, "no file specified\n");
        return 1;
    }

    printf("filePath == %s\n", argv[1]);
    char*       filePath = argv[1];
#endif

    printf("main: before lexFile\n");
    jms_lexer*  lexer       = jms_lex_init();
    jms_vector* lexedTokens = jms_lexFile(lexer, filePath);
    printf("main: after lexFile\n");

    //printf("main.c/main: elemCount(lexedTokens) == %zu",
    //    jms_vec_elemCount(lexedTokens));

    if (lexedTokens != NULL)
    {
        printf("main: before print loop\n");
        for (size_t i = 0; i < jms_vec_elemCount(lexedTokens); i++)
        {
            jms_str* elem = jms_vec_get(lexedTokens, i);
            char* cStr = jms_str_cStr(elem);
            printf("main: token %zu: %s\n", i, cStr);
        }

        jms_vec_del(lexedTokens);
    }
    else
    {
        fprintf(stderr, "[%s]: Error lexing tokens\n",
            __func__);
    }
    printf("main: after print loop\n");
    
    jms_lex_del(lexer);

    fflush(stdout);
    fflush(stderr);
    
    return 0;
}