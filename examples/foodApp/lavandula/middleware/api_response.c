#include <stdbool.h>

#include "../include/lavandula.h"

char *apiResponse(char *message, bool success) {
    JsonBuilder *builder = jsonBuilder();
    jsonPutBool(builder, "success", success);
    jsonPutString(builder, "message", message);

    char *json = jsonStringify(builder);
    freeJsonBuilder(builder);

    return json;
}

HttpResponse apiSuccess() {
    char *json = apiResponse("Request was successful.", true);
    return ok(json, APPLICATION_JSON);
}

HttpResponse apiFailure(char *message) {
    char *json = apiResponse(message, false);
    return internalServerError(json, APPLICATION_JSON);
}

middleware(validateJsonBody, ctx, m) {
    if (!ctx.hasBody) {
        return apiFailure("Error: no JSON body provided.");
    }

    return next(ctx, m);
}