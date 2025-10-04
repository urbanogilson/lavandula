#ifndef json_h
#define json_h

#include <stdbool.h>

typedef struct JsonBuilder JsonBuilder;
typedef struct JsonArray JsonArray;

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
        JsonArray   *array;
    };
} Json;

struct JsonArray {
    Json *items;
    int   count;
    int   capacity;
};

struct JsonBuilder {
    Json *json;

    int jsonCount;
    int jsonCapacity;
};

JsonBuilder jsonBuilder();
JsonArray jsonArray();
void freeJsonArray(JsonArray *jsonArray);
void freeJsonBuilder(JsonBuilder *jsonBuilder);

void jsonPutString(JsonBuilder *jsonBuilder, char *key, char *value);
void jsonPutBool(JsonBuilder *jsonBuilder, char *key, bool value);
void jsonPutInteger(JsonBuilder *jsonBuilder, char *key, int value);
void jsonPutNull(JsonBuilder *jsonBuilder, char *key);
void jsonPutObject(JsonBuilder *jsonBuilder, char *key, JsonBuilder *object);
void jsonPutArray(JsonBuilder *jsonBuilder, char *key, JsonArray *array);

void jsonArrayAppend(JsonArray *array, Json value);

Json jsonString(char *value);
Json jsonBool(bool value);
Json jsonInteger(int value);
Json jsonObject(JsonBuilder *builder);
Json jsonArrayJson(JsonArray *array);

char *jsonStringify(JsonBuilder *jsonBuilder);

void jsonPrint(JsonBuilder *jsonBuilder);

#endif