# Error Handling

You have the freedom to handle errors however you like. However, Lavandula provides a interface for returning JSON errors from your controllers.

Errors returned from Lavandula have two fields, a `success` boolean and a `message` string.

Currently, to return an error from the 
```
return apiResponse("missing body in request");
```

This is a method commonly used in middleware. The point of it is to refrain from returning plain text error messages as JSON is easier to work with and standardise.

Here is an example of this used in some middleware.

```
middleware(validateJsonBody, ctx, m) {
    if (!ctx.hasBody) {
        return apiResponse("Error: no JSON body provided.");
    }

    return next(ctx, m);
}
```