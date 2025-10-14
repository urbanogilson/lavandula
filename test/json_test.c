#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../src/include/lavandula_test.h"
#include "../src/include/json.h"

void testJsonArrayInit() {
    JsonArray array = jsonArray();

    expect(array.items, toBe(NULL));
    expect(array.count, toBe(0));
    expect(array.capacity, toBe(0));
}

void testJsonBuilderInit() {
    JsonBuilder *builder = jsonBuilder();

    expect(builder->json, toBe(NULL));
    expect(builder->jsonCount, toBe(0));
    expect(builder->jsonCapacity, toBe(0));

    freeJsonBuilder(builder);
}

void testJsonBuildStringField() {
    JsonBuilder *builder = jsonBuilder();

    jsonPutString(builder, "string", "The C Programming Language");
    expect(strcmp(jsonGetString(builder, "string"), "The C Programming Language"), toBe(0));

    freeJsonBuilder(builder);
}

void testJsonBuildBoolField() {
    JsonBuilder *builder = jsonBuilder();

    jsonPutBool(builder, "true", true);
    jsonPutBool(builder, "false", false);
    expect(jsonGetBool(builder, "true"), toBe(true));
    expect(jsonGetBool(builder, "false"), toBe(false));

    freeJsonBuilder(builder);
}

void testJsonBuildIntegerField() {
    JsonBuilder *builder = jsonBuilder();

    jsonPutInteger(builder, "positive", 42);
    jsonPutInteger(builder, "zero", 0);
    jsonPutInteger(builder, "negative", -42);

    expect(jsonGetInteger(builder, "positive"), toBe(42));
    expect(jsonGetInteger(builder, "zero"), toBe(0));
    expect(jsonGetInteger(builder, "negative"), toBe(-42));

    freeJsonBuilder(builder);
}

void testJsonBuildNullField() {
    JsonBuilder *builder = jsonBuilder();

    jsonPutNull(builder, "null");
    expect(jsonHasKey(builder, "null"), toBe(true));

    freeJsonBuilder(builder);
}

void testJsonBuildObjectField() {
    JsonBuilder *builder = jsonBuilder();

    JsonBuilder *object = jsonBuilder();
    jsonPutString(object, "title", "Expert C Programming");
    jsonPutInteger(object, "year", 1994);
    jsonPutObject(builder, "book", object);

    JsonBuilder *book = jsonGetJson(builder, "book");
    expect(strcmp(jsonGetString(book, "title"), "Expert C Programming"), toBe(0));
    expect(jsonGetInteger(book, "year"), toBe(1994));

    freeJsonBuilder(builder);
}

void testJsonBuildJsonField() {
    JsonBuilder *builder = jsonBuilder();

    JsonBuilder *json = jsonBuilder();
    jsonPutString(json, "designed by", "Dennis Ritchie");
    jsonPutInteger(json, "year", 1972);
    jsonPutJson(builder, "c", jsonObject(json));

    JsonBuilder *found = jsonGetJson(builder, "c");

    expect(strcmp(jsonGetString(found, "designed by"), "Dennis Ritchie"), toBe(0));
    expect(jsonGetInteger(found, "year"), toBe(1972));

    freeJsonBuilder(builder);
}

void runJsonTests(){
    runTest(testJsonArrayInit);
    runTest(testJsonBuilderInit);
    runTest(testJsonBuildStringField);
    runTest(testJsonBuildBoolField);
    runTest(testJsonBuildIntegerField);
    runTest(testJsonBuildNullField);
    runTest(testJsonBuildObjectField);
    runTest(testJsonBuildJsonField);
}