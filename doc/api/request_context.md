# Request Context

The request context is the second argument passed into an `appRoute`. It holds data and resources related to the request routed to this controller endpoint. It also contains the instance of your `App`.

Because calling `jsonParse` on the `request.body` is a very common operation, this is done for you and stored as a field in the `RequestContext`. If the body is not present, you can null check the `body` field itself, or use the boolean `hasBody` field.

```c
appRoute(home, ctx) {
    if (!ctx.hasBody) {
        return internalServerError("No body!", TEXT_PLAIN);
    }

    // return the request body for this example
    char *body = jsonStringify(ctx.body);

    return ok(body, TEXT_PLAIN);
}
```

Do not call `freeJsonBuilder` on the ctx.body as this is done for you once the request returns a response. Don't worry if you forget as it will not crash your program.