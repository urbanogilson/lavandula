#ifndef json_h
#define json_h

#include <stdbool.h>

typedef struct JsonBuilder JsonBuilder;

typedef enum {
    JSON_NULL,
    JSON_TRUE,
    JSON_FALSE,
    JSON_NUMBER,
    JSON_STRING,
    JSON_ARRAY,
    JSON_OBJECT,
} JsonType;

typedef struct {
    JsonType type;
    char    *key;
    
    union {
        char *value;
        bool boolean;
        int integer;
        JsonBuilder *object;
        JsonBuilder *array;
    };
} Json;

struct JsonBuilder {
    Json *json;

    int jsonCount;
    int jsonCapacity;
};

JsonBuilder jsonBuilder();
void freeJsonBuilder(JsonBuilder *builder);

void jsonAddString(JsonBuilder *builder, char *key, char *value);
void jsonAddBool(JsonBuilder *builder, char *key, bool value);
void jsonAddInteger(JsonBuilder *builder, char *key, int value);
void jsonAddNull(JsonBuilder *builder, char *key);
void jsonAddObject(JsonBuilder *builder, char *key, JsonBuilder *object);
void jsonAddArray(JsonBuilder *builder, char *key, JsonBuilder *array);

char *jsonStringify(JsonBuilder *builder);

void jsonPrint(JsonBuilder *builder);

#endif