#include "jms_parser.h"
#include <stdlib.h>
#include <stdio.h>

struct jms_parser
{
    jms_vector* tokens;
};

jms_parser* jms_parser_init(jms_vector* lexedTokens)
{
    if (!lexedTokens)
    {
        fprintf(stderr, "[%s]: Error: lexedTokens cannot be NULL.\n", __FUNCTION__);
        return NULL;
    }

    jms_parser* parser = (jms_parser*)malloc(sizeof(jms_parser));
    if (!parser) {
        fprintf(stderr, "Error: Failed to allocate memory for jms_parser.\n");
        return NULL;
    }

    parser->tokens = lexedTokens;
    return parser;
}

void jms_parser_del(jms_parser* self) {
    if (!self) {
        return;
    }

    // Assuming jms_vector is managed externally and should not be freed here.
    free(self);
}

void jms_parser_parse(jms_parser* self) {
    if (!self || !self->tokens) {
        fprintf(stderr, "Error: Invalid parser or tokens.\n");
        return;
    }

    // Example parsing logic (to be replaced with actual implementation)
    printf("Parsing %zu tokens...\n", jms_vector_size(self->tokens));

    for (size_t i = 0; i < jms_vector_size(self->tokens); ++i) {
        void* token = jms_vector_get(self->tokens, i);
        // Process the token (placeholder logic)
        printf("Processing token %zu...\n", i);
    }

    printf("Parsing completed.\n");
}