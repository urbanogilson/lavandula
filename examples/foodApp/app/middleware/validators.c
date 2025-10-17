#include "../../lavandula/include/lavandula.h"
#include "middleware.h"
#include "api_response.h"
#include "validator.h"

middleware(registerUserValidator, ctx, m) {
    JsonValidator v = createValidator();

    required(&v, "username");
    required(&v, "name");
    required(&v, "password");

    char *error = validate(&v, ctx.body);
    if (error) {
        return apiFailure(error);
    }
    freeValidator(&v);

    return next(ctx, m);
}

middleware(loginUserValidator, ctx, m) {
    JsonValidator v = createValidator();

    required(&v, "username");
    required(&v, "password");

    char *error = validate(&v, ctx.body);
    if (error) {
        return apiFailure(error);
    }
    freeValidator(&v);

    return next(ctx, m);
}