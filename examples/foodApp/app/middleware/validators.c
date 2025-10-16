#include "../../lavandula/include/lavandula.h"
#include "middleware.h"

HttpResponse successOrFailureResponse(bool success, char *message) {
    JsonBuilder *builder = jsonBuilder();
    jsonPutBool(builder, "success", success);
    jsonPutString(builder, "message", message);

    char *json = jsonStringify(builder);
    freeJsonBuilder(builder);

    return response(json, HTTP_BAD_REQUEST, APPLICATION_JSON);
}

HttpResponse success(char *message) {
    return successOrFailureResponse(true, message);
}

HttpResponse failure(char *message) {
    return successOrFailureResponse(false, message);

}

middleware(registerUserValidator, ctx, m) {
    JsonBuilder *body = jsonParse(ctx.request.body);
    if (!body) {
        return failure("Error: no JSON body provided.");
    }

    if (!jsonHasKey(body, "username") || !jsonHasKey(body, "password")) {
        freeJsonBuilder(body);
        return failure("Missing 'username' or 'password' in request body");
    }
    freeJsonBuilder(body);

    return next(ctx, m);
}

middleware(loginUserValidator, ctx, m) {
    JsonBuilder *body = jsonParse(ctx.request.body);
    if (!body) {
        return failure("Error: no JSON body provided.");
    }

    if (!jsonHasKey(body, "username") || !jsonHasKey(body, "password")) {
        freeJsonBuilder(body);
        return failure("Missing 'username' or 'password' in request body");
    }
    freeJsonBuilder(body);

    return next(ctx, m);
}

middleware(logoutUserValidator, ctx, m) {
    return next(ctx, m);
}