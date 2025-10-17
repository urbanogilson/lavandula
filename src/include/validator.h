#ifndef validator_h
#define validator_h

typedef struct {
    char *field;
    char *message;
} JsonValidationRule;

typedef struct {
    JsonValidationRule *rules;
    int             ruleCount;
    int             ruleCapacity;
} JsonValidator;

JsonValidator createValidator();
void freeValidator(JsonValidator *validator);

void addRule(JsonValidator *v, const char *field, const char *message);
char *validate(JsonValidator *v, JsonBuilder *body);

void required(JsonValidator *v, const char *field);
bool validateRequired(JsonBuilder *builder, char *field);


#endif