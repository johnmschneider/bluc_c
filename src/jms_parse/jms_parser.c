#include "jms_parser.h"
#include "../jms_utils/jms_stdint.h"
#include "jms_astNode.h"
#include <stdlib.h>
#include <stdio.h>

struct jms_parser
{
    JMS_BORROWED_PTR(jms_vector) tokens;
};

JMS_XFER_PTR(jms_parser)
    jms_parser_init(    JMS_BORROWED_PTR(jms_vector) lexedTokens)
{
    if (!lexedTokens)
    {
        fprintf(stderr, "[%s]: Error: lexedTokens cannot be NULL.\n", __FUNCTION__);
        return NULL;
    }

    jms_parser* self = (jms_parser*)malloc(sizeof(jms_parser));
    if (!self)
    {
        fprintf(stderr, "Error: Failed to allocate memory for jms_parser.\n");
        return NULL;
    }

    self->tokens = lexedTokens;
    return self;
}

void jms_parser_del(jms_parser* self)
{
    if (!self)
    {
        return;
    }

    // Assuming jms_vector is managed externally and should not be freed here.
    free(self);
}

JMS_XFER_PTR(jms_vector) jms_parser_parse(jms_parser* self)
{
    if (!self || !self->tokens)
    {
        fprintf(stderr, "Error: Invalid parser or tokens.\n");
        return NULL;
    }

    // TODO: Example parsing logic (to be replaced with actual implementation)
    JMS_XFER_PTR(jms_vector)
        ast = jms_vec_init(sizeof(jms_astNode*));
    i32
        tokenCount = jms_vec_elemCount(self->tokens);

    printf("Parsing %d tokens...\n", tokenCount);

    for (size_t i = 0; i < tokenCount; ++i)
    {
        void* token = jms_vec_get(self->tokens, i);

        // Process the token (placeholder logic)
        printf("Processing token %zu...\n", i);
    }

    printf("Parsing completed.\n");

    // Return the AST (currently empty)
    return ast;
}