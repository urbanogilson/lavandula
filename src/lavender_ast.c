#include <stdlib.h>
#include <stdio.h>
#include "include/lavender_ast.h"

void freeSchemaNode(SchemaNode *node) {
    if (!node) return;
    
    switch (node->type) {
        case SCHEMA_NODE_MODEL:
            free(node->model.name);
            break;
    }
}

void printSchemaNode(const SchemaNode *node) {
    if (!node) return;
    
    printf("Node: Type=%d\n", node->type);
    
    switch (node->type) {
        case SCHEMA_NODE_MODEL:
            printf("  Model Name: %s\n", node->model.name);
            break;
    }
}