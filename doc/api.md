# Lavandula API

This document provides information on how to use the Lavandula API for web application development.


## Overview

A starter application may look like this:

```c
#include "lavandula.h"

HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}

int main() {
    AppBuilder builder = createBuilder();
    App app = build(builder);

    get(&app, "/home", home);

    runApp(&app);
    cleanupApp(&app);

    return 0;
}
```

Let's break down each part of the program.

This line creates an instance of the application builder. From here, you can call various builder functions that are part of the API to customise your application behaviour. More on this later.

```c
AppBuilder builder = createBuilder();
```

Once the application has been configured, the `build` method is called to produce an `App`. This represents your web application.

```c
App app = build(builder);
```

Before running the app, we need to add some routes so we can serve content from the web application. The line below defines a route for a GET request. The route path is defined as `/home` and a controller function is given to the route. This is the function that runs when a user visits that URL.

The function must return a `HttpResponse` and take in a `HttpRequest`.

```c
get(&app, "/home", home);
```

This line starts the web server. Most of the application runtime is spent inside this function.

```c
runApp(&app);
```

Once the app terminates, you should call this function to clean up leftover resources in memory.

```c
cleanupApp(&app);
```

Try running the above example and expect the following output when you navigate to `/home`.

```
Hello, World!
```

Lavandula also provides a more minimal interface for creating web applications without a builder object. Calling the `createApp` function will return you an app directly without the need for a builder.

```c
#include "lavandula.h"

appRoute(home) {
    return ok("Hello, World");
}

int main(void) {
    App app = createApp();
    root(&app, home);

    runApp(&app);
}
```

To make life easier when defining routes in your application, you can use the `appRoute` macro. The example above generates the following signature. The variable for accessing the `RequestContext` will be by convention named `ctx` when using the `appRoute` macro.

```c
appRoute(home) -> HttpResponse home(RequestContext ctx)
```



## Application Builder

The application builder methods are how you configure your web application. This involves things like CORS, the application port, middleware, etc.

```c
// configures the port the application runs on
void usePort(AppBuilder *builder, int port);

// adds a layer of middleware into the controller pipeline
void useMiddleware(AppBuilder *builder, MiddlewareFunc);
```

Once you have finished configuring your application, call the `build` method to create an instance of your web application.

```c
AppBuilder builder = createBuilder();

// ..

App app = build(builder);
```


## Controllers

Controllers represent the different endpoints in your application. Each controller takes in a request and returns a response.

```c
// example controller
HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}
```

The following functions can be used to conveniently return responses from controllers:

```c
// returns content with 200 OK
HttpResponse ok(char *content);

// returns content with 401
HttpResponse badRequest(char *content);

// returns content with a custom response code
HttpResponse response(char *content, HttpStatusCode);
```

Here is an example using the `response` function.

```c
HttpResponse error(HttpRequest _) {
    return response("I am a teapot.", HTTP_IM_A_TEAPOT);
}
```


## Routing

The Lavandula API provides six routing functions, each corresponding to a HTTP method. These functions register the controllers you have created to your web application.

```c
void get(App *app, char *path, Controller controller);
void post(App *app, char *path, Controller controller);
void put(App *app, char *path, Controller controller);
void delete(App *app, char *path, Controller controller);
void patch(App *app, char *path, Controller controller);
void options(App *app, char *path, Controller controller);
```

There are two additional special routes you can define in your web application. The first is the root url, which can be set with:

```c
root(&app, home);
```

The second is the route for when a resource requested cannot be found.

```c
HttpResponse notFound(HttpRequest _) {
    return response("Not Found", HTTP_NOT_FOUND);
}

routeNotFound(&app.server.router, notFound);
```


## Middleware

Lavandula provides an API for defining controller middleware within your application. Middleware is code that is injected into the request pipeline before the controller endpoint is hit.

You can use the `useMiddleware` function to add middleware into the pipeline.

```c
// Lavandula logging middleware
useMiddleware(&builder, logger);
```

A middleware function has the following signature:

```c
typedef HttpResponse (*MiddlewareFunc)(HttpRequest req, Controller next);
```

Middleware can perform actions such as logging, authentication, or modifying the request/response before passing control to the next handler.

Example of a custom middleware:

```c
HttpResponse myMiddleware(HttpRequest req, Controller next) {
    // Perform some action before the controller
    printf("Request received: %s\n", req.path);
    // Call the next handler in the pipeline
    return next(req);
}
```


## Environment Variables

You can inject environment variables into your application using a .env file.

Call the `useDotenv` function to parse an environment variable file in the current directory. Then, you can call the `env` function to retrieve a specific environment variable.

```c
useDotenv(".env");

char *dbUser = env("DB_USER");
char *dbPass = env("DB_PASS");

// ..
```

## Static Files

Static files are non-changing files that you are able to serve to the user. You can serve static files with the following setup:

```c
appRoute(home) {
    char *html = readFile("home.html");
    return html ? ok(html, TEXT_HTML) : notFound("Content not found...", TEXT_HTML);
}
```

We first read the content of the file, using `readFile`. Lastly, we make some checks and return the content. And that's it!

Since this is a piece of code that you may use frequently within your application, Lavandula provides the following macro to simplify a static file endpoint. Note that the content type will be `text/html` when using this macro.

```c
appRoutePage(home, "home.html");
```


## CORS policy configuration

Lavandula provides an API to configure the CORS policy for your web application.

An example CORS policy configuration can be seen below.

```c
CorsConfig policy = corsPolicy();

// only allow requests from this origin
allowOrigin(&policy, "www.example.com");

// only allow the requests to be of these HTTP actions
allowMethod(&policy, HTTP_GET);
allowMethod(&policy, HTTP_POST);

// apply the policy to the application builder
useCorsPolicy(&builder, policy);
```

To allow any origin to access your application, use the following method.

```c
allowAnyOrigin(&policy);
```

To allow any method in your application, use the following method.

```c
allowAnyMethod(&policy);
```

If you would like to allow any method and any origin, then you can eliminate the above with this one-liner.

```c
useCorsPolicy(&builder, corsAllowAll());
```


## Testing your App

Lavandula provides a built-in testing framework for writing unit tests for your application.

The following example defines a new test that is being run.

```c
void testOne() {
    int x = 10;
    expect(x, toBe(10));
}

runTest(testOne);
testResults();
```

Call `runTest` with a function pointer argument to run a test. Call `testResults` to see the outcome of all of your tests.


## JSON

Lavandula provides a built-in JSON API for manipulating JSON objects within your web application.

Create a json builder object to start.

```c
JsonBuilder jsonBuilder = jsonBuilder();
```

You can construct the JSON object calling various `jsonAdd...` methods. The following example adds a json pair with the key 'greeting' and the value 'Hello, World!'.

```c
jsonAddString(&jsonBuilder, "greeting", "Hello, World!");
```

These are all the valid methods you can use to add values into the JSON object.

```c
void jsonAddString(JsonBuilder *jsonBuilder, char *key, char *value);
void jsonAddBool(JsonBuilder *jsonBuilder, char *key, bool value);
void jsonAddNumber(JsonBuilder *jsonBuilder, char *key, double value);
void jsonAddNull(JsonBuilder *jsonBuilder, char *key);
void jsonAddObject(JsonBuilder *jsonBuilder, char *key, JsonBuilder *object);
void jsonAddArray(JsonBuilder *jsonBuilder, char *key, JsonBuilder *array);
```

This example constructs a 'todo' JSON object.

```c
JsonBuilder jBuilder = jsonBuilder();
jsonAddString(&jBuilder, "name", "This is a task!");
jsonAddNumber(&jBuilder, "age", 30);

jsonPrint(&jBuilder);
```

If we run this, we should see the following output.

```json
{"name": "This is a task!", "age": 30.000000}
```


## Application Environment

You can set the environment of your application with the following:

```c
useEnvironment(&builder, ENV_DEVELOPMENT);
```

Macros defined in `environment.h` evaluate to strings. So, you could just pass the raw string "DEVELOPMENT" into `useEnvironment`. They are just there for convenience. Feel free to use your own custom environments, such as "STAGING", etc.

```
#define ENV_DEVELOPMENT "DEVELOPMENT"
#define ENV_PRODUCTION "PRODUCTION"
#define ENV_TESTING "TESTING"
```

You can inspect the application environment using the following methods

```
bool isDevelopment(AppBuilder *builder);
bool isProduction(AppBuilder *builder);
bool isTesting(AppBuilder *builder);
```

Reasons that you may want to use a specific environment could be the use of verbose logging for development.

```c
if (isDevelopment(&builder)) {
    useVerboseLogging(&builder);
}
```


## Lavu

Lavu (lah-voo), the Lavandula CLI, can help you to quickly scaffold and setup your project.

Run the following command to create a new project.

```bash
lavu new <project_name>
```

Run the application.

```bash
lavu run
```

Note that `lavu run` will only work if the current working directory is the same as `lavandula.yml`.

You should see:

```
Lavandula Server is running! -> http://127.0.0.1:3000
```