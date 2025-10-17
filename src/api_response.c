#include <stdbool.h>

#include "include/lavandula.h"

char *apiResponse(char *message, bool success) {
    JsonBuilder *builder = jsonBuilder();
    jsonPutBool(builder, "success", success);
    jsonPutString(builder, "message", message);

    char *json = jsonStringify(builder);
    freeJsonBuilder(builder);

    return json;
}

HttpResponse badJsonResponse(char *message) {
    char *json = apiResponse(message, false);
    return badRequest(json, APPLICATION_JSON);
}

middleware(validateJsonBody, ctx, m) {
    JsonBuilder *body = jsonParse(ctx.request.body);
    if (!body) {
        return badJsonResponse("Error: no JSON body provided.");
    }
    freeJsonBuilder(body);

    return next(ctx, m);
}