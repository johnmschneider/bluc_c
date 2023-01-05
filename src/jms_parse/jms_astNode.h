#ifndef JMS_ASTNODE_H
#define JMS_ASTNODE_H
#include "../jms_utils/jms_vector.h"

struct jms_astNode;
typedef struct jms_astNode jms_astNode;

jms_astNode*    jms_astNode_init    (char* text);
void            jms_astNode_del     (jms_astNode* self);

/**
 * Get the source code/text for this token. DO NOT FREE THE CHAR*, it is
 *  on the stack. Should be treated as read-only.
 */
const char*     jms_astNode_text        (jms_astNode* self);
jms_vector*     jms_astNode_getChildren (jms_astNode* self);
void            jms_astNode_addChild    (jms_astNode* self, jms_astNode* child);

#endif