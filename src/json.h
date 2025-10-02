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
void freeJsonBuilder(JsonBuilder *jsonBuilder);

void jsonAddString(JsonBuilder *jsonBuilder, char *key, char *value);
void jsonAddBool(JsonBuilder *jsonBuilder, char *key, bool value);
void jsonAddInteger(JsonBuilder *jsonBuilder, char *key, int value);
void jsonAddNull(JsonBuilder *jsonBuilder, char *key);
void jsonAddObject(JsonBuilder *jsonBuilder, char *key, JsonBuilder *object);
void jsonAddArray(JsonBuilder *jsonBuilder, char *key, JsonBuilder *array);

char *jsonStringify(JsonBuilder *jsonBuilder);

void jsonPrint(JsonBuilder *jsonBuilder);

#endif