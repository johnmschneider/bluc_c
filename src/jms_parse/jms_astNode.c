#include <stdint.h>
#include <stdlib.h>
#include "jms_astNode.h"
#include "../jms_utils/jms_vector.h"
#include "jms_astNodeType.h"

struct jms_astNode
{
    /**
     * Basically the class ID for this type of node.
     */
    jms_astNodeType     nodeTypeID;
    char*               text;
    jms_vector*         children;
};

jms_astNode* jms_astNode_init(char* text)
{
    jms_astNode* self = malloc(sizeof(jms_astNode));
}

void jms_astNode_del(jms_astNode* self)
{

}

const char* jms_astNode_text(jms_astNode* self)
{

}

jms_vector*     jms_astNode_getChildren (jms_astNode* self);
void            jms_astNode_addChild    (jms_astNode* self, jms_astNode* child);