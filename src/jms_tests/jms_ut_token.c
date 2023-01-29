#include "jms_unitTests.h"
#include "jms_ut_token.h"
#include "../jms_token.h"
#include "../jms_utils/jms_ptr_annotations.h"

static void jms_ut_token_initValuesAreCorrect(void)
{
    jms_token* test = jms_tok_init(
        "testfile.bluc",
        2,
        4,
        "var");

    JMS_BORROWED_PTR(jms_str) filePath
        = jms_tok_getFilePath(test);
    
    JMS_BORROWED_PTR(jms_str) text
        = jms_tok_getText(test);


    JMS_ASSERT(
        jms_str_eq_cStr(filePath, "testfile.bluc"),
        __FUNCTION__);

    JMS_ASSERT(
        jms_tok_getLineNum(test) == 2,
        __FUNCTION__);

    JMS_ASSERT(
        jms_tok_getColNum(test) == 4,
        __FUNCTION__);

    JMS_ASSERT(
        jms_str_eq_cStr(text, "var"),
        __FUNCTION__);

    
    jms_tok_del(test);
}

static void jms_ut_tok_getFilePath(void)
{
    jms_token* test = jms_tok_init(
        "potato.txt", 
        0, 
        3, 
        "potato");
    
    JMS_BORROWED_PTR(jms_str) filePath =
        jms_tok_getFilePath(test);

    JMS_ASSERT(
        jms_str_eq_cStr(filePath, "potato.txt"),
        __FUNCTION__);

    jms_tok_del(test);
}

static void jms_ut_tok_getLine(void)
{
    jms_token* test = jms_tok_init(
        "tomato.txt", 
        34, 
        5, 
        "tomato");

    JMS_ASSERT(
        jms_tok_getLineNum(test) == 34,
        __FUNCTION__);
        
    jms_tok_del(test);
}

static void jms_ut_tok_getCol(void)
{
    jms_token* test = jms_tok_init(
        "tomato stew.txt", 
        45,
        42, 
        "is it just tomato sauce?");

    JMS_ASSERT(
        jms_tok_getColNum(test) == 42,
        __FUNCTION__);
        
    jms_tok_del(test);
}

void jms_ut_token(void)
{
    jms_ut_token_initValuesAreCorrect();
    jms_ut_tok_getFilePath();
    jms_ut_tok_getLine();
    jms_ut_tok_getCol();
}