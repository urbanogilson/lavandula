#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

JsonBuilder jsonBuilder() {
    JsonBuilder builder = {};

    return builder;
}

void freeJsonBuilder(JsonBuilder *builder) {
    for (int i = 0; i < builder->jsonCount; i++) {
        Json json = builder->json[i];

        if (json.type == JSON_STRING && json.value != NULL) {
            free(json.value);
        } else if ((json.type == JSON_OBJECT || json.type == JSON_ARRAY) && json.object != NULL) {
            freeJsonBuilder(json.object);
            free(json.object);
        }

        if (json.key != NULL) {
            free(json.key);
        }
    }

    free(builder->json);
    builder->json = NULL;
    builder->jsonCount = 0;
    builder->jsonCapacity = 0;
}

void addJson(JsonBuilder *builder, Json json) {
    if (builder->jsonCount >= builder->jsonCapacity) {
        builder->jsonCapacity = builder->jsonCapacity == 0 ? 1 : builder->jsonCapacity * 2;
        builder->json = realloc(builder->json, sizeof(Json) * builder->jsonCapacity);
    }
    builder->json[builder->jsonCount++] = json;
}

Json makeJson(char *key, JsonType type) {
    return (Json){
        .type = type,
        .key = strdup(key),
    };
}

void jsonAddString(JsonBuilder *builder, char *key, char *value) {
    Json json = makeJson(key, JSON_STRING);
    json.value = strdup(value);

    addJson(builder, json);
}

void jsonAddBool(JsonBuilder *builder, char *key, bool value) {
    Json json = makeJson(key, value ? JSON_TRUE : JSON_FALSE);
    json.boolean = value;

    addJson(builder, json);
}

void jsonAddInteger(JsonBuilder *builder, char *key, int value) {
    Json json = makeJson(key, JSON_NUMBER);
    json.integer = value;

    addJson(builder, json);
}

void jsonAddNull(JsonBuilder *builder, char *key) {
    Json json = makeJson(key, JSON_NULL);

    addJson(builder, json);
}

void jsonAddObject(JsonBuilder *builder, char *key, JsonBuilder *object) {
    Json json = makeJson(key, JSON_OBJECT);
    json.object = object;

    addJson(builder, json);
}

void jsonAddArray(JsonBuilder *builder, char *key, JsonBuilder *array) {
    Json json = makeJson(key, JSON_ARRAY);
    json.object = array;

    addJson(builder, json);
}

char *jsonStringify(JsonBuilder *builder) {
    int capacity = 2;
    int length = 0;
    char *json = malloc(capacity);

    json[length++] = '{';
    for (int i = 0; i < builder->jsonCount; i++) {
        Json node = builder->json[i];
        char buffer[256];

        switch (node.type) {
            case JSON_STRING:
                snprintf(buffer, sizeof(buffer), "\"%s\": \"%s\"", node.key, node.value);
                break;
            case JSON_TRUE:
                snprintf(buffer, sizeof(buffer), "\"%s\": true", node.key);
                break;
            case JSON_FALSE:
                snprintf(buffer, sizeof(buffer), "\"%s\": false", node.key);
                break;
            case JSON_NUMBER:
                snprintf(buffer, sizeof(buffer), "\"%s\": %d", node.key, node.integer);
                break;
            case JSON_NULL:
                snprintf(buffer, sizeof(buffer), "\"%s\": null", node.key);
                break;
            case JSON_ARRAY:
                snprintf(buffer, sizeof(buffer), "\"%s\": []", node.key);
                break;
            case JSON_OBJECT: {
                char *nestedJson = jsonStringify(node.object);
                snprintf(buffer, sizeof(buffer), "\"%s\": %s", node.key, nestedJson);
                free(nestedJson);
                break;
            }
            default:
                buffer[0] = '\0';
                break;
        }

        int bufferLength = strlen(buffer);
        if (length + bufferLength + 2 > capacity) {
            capacity = (length + bufferLength + 2) * 2;
            json = realloc(json, capacity);
        }

        memcpy(json + length, buffer, bufferLength);
        length += bufferLength;

        if (i < builder->jsonCount - 1) {
            json[length++] = ',';
            json[length++] = ' ';
        }
    }

    return "{}";
}

void jsonPrintNode(Json json) {
    switch (json.type) {
        case JSON_STRING:
            printf("\"%s\": \"%s\"", json.key, json.value);
            break;
        case JSON_TRUE:
            printf("\"%s\": true", json.key);
            break;
        case JSON_FALSE:
            printf("\"%s\": false", json.key);
            break;
        case JSON_NUMBER:
            printf("\"%s\": %d", json.key, json.integer);
            break;
        case JSON_NULL:
            printf("\"%s\": null", json.key);
            break;
        case JSON_ARRAY:
            break;
        case JSON_OBJECT:
            printf("\"%s\": ", json.key);
            jsonPrint(json.object);
            break;
        default:
            break;
    }
}

void jsonPrint(JsonBuilder *builder) {
    printf("{");
    for (int i = 0; i < builder->jsonCount; i++) {
        jsonPrintNode(builder->json[i]);

        if (i < builder->jsonCount - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}