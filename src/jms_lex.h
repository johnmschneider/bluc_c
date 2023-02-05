#ifndef JMS_LEX_H
#define JMS_LEX_H

#include "jms_utils/jms_vector.h"
#include "jms_utils/jms_ptr_annotations.h"

#define JMS_LEX_BUFFER_SIZE 1024

//struct jms_lexer;
//typedef struct jms_lexer jms_lexer;

struct Lexer;
typedef struct Lexer jms_lexer;

JMS_XFER_PTR(jms_lexer)  
            jms_lex_init();
void        jms_lex_del(JMS_OWNED_PTR(jms_lexer) self);

JMS_XFER_PTR(jms_vector) jms_lexFile(jms_lexer* self, const char* filePath);

#endif