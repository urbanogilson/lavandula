#include <stdio.h>

#include "include/lavender_transpiler.h"

LavenderTranspiler newTranspiler(SchemaNode *nodes, int nodeCount) {
    LavenderTranspiler transpiler = {
        .nodes = nodes,
        .nodeCount = nodeCount,
    };

    return transpiler;
}

void transpileSchema(const SchemaNode *nodes, int nodeCount)
{
    for (int i = 0; i < nodeCount; i++) {
        const SchemaNode *node = &nodes[i];
        if (node->type == SCHEMA_NODE_MODEL) {
            printf("Transpiling model: %s\n", node->model.name);
            for (int j = 0; j < node->model.columnCount; j++) {
                const ColumnDefinition *col = &node->model.columns[j];
                printf("  Column: %s of type %s\n", col->name, col->type);
            }
        } else {
            printf("Unknown schema node type: %d\n", node->type);
        }
    }
}