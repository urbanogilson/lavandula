#include "../../lavandula/include/lavandula.h"
#include "middleware.h"

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

middleware(registerUserValidator, ctx, m) {
    JsonBuilder *body = jsonParse(ctx.request.body);
    if (!body) {
        return badJsonResponse("Error: no JSON body provided.");
    }

    if (!jsonHasKey(body, "username") || !jsonHasKey(body, "password")) {
        freeJsonBuilder(body);
        return badJsonResponse("Missing 'username' or 'password' in request body");
    }
    freeJsonBuilder(body);

    return next(ctx, m);
}

middleware(loginUserValidator, ctx, m) {
    JsonBuilder *body = jsonParse(ctx.request.body);
    if (!body) {
        return badJsonResponse("Error: no JSON body provided.");
    }

    if (!jsonHasKey(body, "username") || !jsonHasKey(body, "password")) {
        freeJsonBuilder(body);
        return badJsonResponse("Missing 'username' or 'password' in request body");
    }
    freeJsonBuilder(body);

    return next(ctx, m);
}

middleware(logoutUserValidator, ctx, m) {
    return next(ctx, m);
}