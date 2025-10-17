
# Middleware

Lavandula provides an API for defining controller middleware within your application. Middleware is code that is injected into the request pipeline before the controller endpoint is hit.

There are two types of middleware you can use within your app.

## Global Middleware

Global middleware automatically applies to all routes in your application.

An example may be a validation middleware to ensure that a specific field is always present in a request.

The following

```
HttpResponse myMiddleware(RequestContext ctx, MiddlewareHandler *middleware) {
    printf("Global middleware: Before request processing\n");
    
    return next(ctx, middleware);
}

int main() {
    AppBuilder builder = createBuilder();

    // sets up global middleware
    useGlobalMiddleware(&builder, myMiddleware);
    
    usePort(&builder, 3001);
    App app = build(builder);

    runApp(&app);
}
```

Now, every route will use the `myMiddleware` global middleware.

## Local Middleware

Local middleware is applied only to specific routes in your application.

An example of this may be authentication for all routes involving retrieving data, apart from the `login` route.

To apply local middleware, you can utilise the return type of `get` and `post` methods, etc, and call `useRouteMiddleware` with the route as an argument. Only that route will have the middleware applied to it.

```c
Route homeRoute = get(&app, "/home", home);
useRouteMiddleware(&homeRoute, logger);
```

<br/>

Example of a custom middleware:

```c
HttpResponse myMiddleware(RequestContext ctx, MiddlewareHandler *middleware) {
    // Perform some action before the controller
    printf("Request received: %s\n", req.path);

// Call the next handler in the pipeline
    return next(ctx, middleware);
}
```

## Library Middleware

Lavandula provides some common middleware functions to use in your application.

### Console Logger

The logger middleware logs the method and route every time the web server is hit. This is useful for debugging purposes.

```c
AppBuilder builder = createBuilder();
useGlobalMiddleware(&builder, consoleLogger);
```

### JSON Body Validator

The JSON body middleware validates the presence of a JSON body. A bad request will be returned otherwise.

```c
Route rootRoute = root(&app, home);
useLocalMiddleware(&rootRoute, validateJsonBody);
```