#ifndef LAVENDER_AST_H
#define LAVENDER_AST_H

typedef enum {
    SCHEMA_NODE_MODEL,
} SchemaNodeType;

typedef struct {
    char *name;
} ModelDeclaration;

typedef struct {
    SchemaNodeType type;

    union {
        ModelDeclaration model;
    };

} SchemaNode;

// AST utility functions
void freeSchemaNode(SchemaNode *node);
void printSchemaNode(const SchemaNode *node);

#endif