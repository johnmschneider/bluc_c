#ifndef JMS_LEX_H
#define JMS_LEX_H

#include "jms_utils/jms_vector.h"

#define JMS_LEX_BUFFER_SIZE 1024

//struct jms_lexer;
//typedef struct jms_lexer jms_lexer;

struct Lexer;
typedef struct Lexer jms_lexer;

jms_lexer*  jms_lex_init();
void        jms_lex_del(jms_lexer* self);

jms_vector* jms_lexFile(jms_lexer* self, const char* filePath);

#endif