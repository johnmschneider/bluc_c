#ifndef JMS_KEYWORDS_H
#define JMS_KEYWORDS_H

char* JMS_KW_defaultTypes[] = 
{
    "bool", "char", "i8", "i16", "i32", "i64", "u8", "u16", "u32",
    "u64", "f32", "f64"
};

char* JMS_KW_reservedWords[] =
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

char* JMS_KW_reservedLexemes[] = 
{
    "(", ")", "[", "]", "{", "}", "=", ";", "+", "-", "/", "*", "%"
    "#", ",", "<", ">", ".", "&", "|"
};

#endif