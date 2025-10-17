#include "include/middleware.h"
#include "include/api_response.h"
#include "include/validator.h"

JsonValidator createValidator() {
    return (JsonValidator) {
        .rules = malloc(sizeof(JsonValidationRule)),
        .ruleCount = 0,
        .ruleCapacity = 1
    };
}

void freeValidator(JsonValidator *validator) {
    free(validator->rules);
    validator->ruleCapacity = 0;
}

void addRule(JsonValidator *v, const char *field, const char *message) {
    if (v->ruleCount >= v->ruleCapacity) {
        v->ruleCapacity *= 2;
        v->rules = realloc(v->rules, sizeof(JsonValidationRule) * v->ruleCapacity);
    }

    v->rules[v->ruleCount].field = strdup(field);
    v->rules[v->ruleCount].message = strdup(message);

    v->ruleCount++;
}

bool validateRequired(JsonBuilder *builder, char *field) {
    return jsonHasKey(builder, field);
}

void required(JsonValidator *v, const char *field) {
    char message[256];
    snprintf(message, sizeof(message), "The field '%s' is required.", field);
    addRule(v, field, message);
}

char *validate(JsonValidator *v, JsonBuilder *body) {
    if (!body) return "Request body is missing or malformed.";

    for (int i = 0; i < v->ruleCount; i++) {
        JsonValidationRule rule = v->rules[i];

        if (!validateRequired(body, rule.field)) {
            return rule.message;
        }
    }

    return NULL;
}