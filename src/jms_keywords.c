#include "jms_keywords.h"
struct jms_keywords
{

};

static char* JMS_KW_defaultTypes[] =
{
    "bool", "char", "i8", "i16", "i32", "i64", "u8", "u16", "u32",
    "u64", "f32", "f64"
};

static char* JMS_KW_reservedWords[] =
{
    // bluc terms
    "class", "extends", "typeof", "pack",
    
    // c terms
    "auto", "break", "case", "const", "continue", "default", "do",
    "else", "enum", "extern", "for", "goto", "if", "inline", 
    "long", "register", "restrict", "return", "short", "signed",
    "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while"
};

static char* JMS_KW_reservedLexemes[] = 
{
    "(", ")", "[", "]", "{", "}", "=", ";", "+", "-", "/", "*", "%"
    "#", ",", "<", ">", ".", "&", "|"
};