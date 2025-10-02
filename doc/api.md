# Lavandula API

Lavandula is a backend web framework designed to be minimal and provide an intuitive developer experience. The framework is entirely C-based and requires no external dependencies.


## Overview

A starter application may look like this:

```
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

This line creates an instance of the application builder. From here, you can call various builder functions that are part of the Lavandula API to customise your application behaviour. More on this later.

```
AppBuilder builder = createBuilder();
```

Once the application has been configured, the `build` method is called to produce an `App`. This represents your web application.

```
App app = build(builder);
```

Before running the app, we need to add some routes so we can serve content from the web application. The line below defines a route for a GET request. The route path is defined as `/home` and a controller function is given to the route. This is the function that runs when a user visits that URL.

The function must return a `HttpResponse` and take in a `HttpRequest`.

```
get(&app, "/home", home);
```

This line starts the web server. Most the application runtime is spent inside this function.

```
runApp(&app);
```

Once the app terminates, you should call this function to clean up leftover resources in memory.

```
cleanupApp(&app);
```

Try running the above example and expect the following output when you navigate to `/home`.

```
Hello, World!
```


## Application Builder

The application builder methods are how you configure your web application. This involves things like CORS, the application port, rate limiting, etc.

```
// configures the port the application runs on
void usePort(AppBuilder *builder, int port);

// adds a layer of middleware into the controller pipeline
void useMiddleware(AppBuilder *builder, MiddlewareFunc);
```

Once the application configuration is complete, call the `build` method to create an instance of your web application.

```
AppBuilder builder = createBuilder();

// ..

App app = build(builder);
```


## Controllers

Controllers represent the different endpoints in your application. Each controller takes in a request and returns a response.

```
// example controller
HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}
```

The following functions can be used to conveniently return responses from controllers:

```
// returns content with 200 OK
HttpResponse ok(char *content);

// returns content with 401
HttpResponse badRequest(char *content);

// returns content with a custom response code
HttpResponse response(char *content, HttpStatusCode);
```

Here is an example using the `response` function.

```
HttpResponse error(HttpRequest _) {
    return response("I am a teapot.", HTTP_IM_A_TEAPOT);
}
```


## Routing

The Lavandula API provides five routing functions, each corresponding to a HTTP method. These functions register the controllers you have created to your web application.

```
void get(App *app, char *path, Controller controller);
void post(App *app, char *path, Controller controller);
void put(App *app, char *path, Controller controller);
void delete(App *app, char *path, Controller controller);
void patch(App *app, char *path, Controller controller);
```

There are two additional special routes you can define in your web application. The first is the root url, which can be set with:

```
root(&app, home);
```

The second is the route for when a resource requested cannot be found.

```
HttpResponse notFound(HttpRequest _) {
    return response("Not Found", HTTP_NOT_FOUND);
}

routeNotFound(&app.server.router, notFound);
```


## Middleware

Lavandula provides an API for defining controller middleware within your application. Middleware is code that is injected into the request pipeline before the controller endpoint is hit.

You can use the `useMiddleware` function to add middleware into the pipeline.

```
// Lavandula logging middleware
useMiddleware(&builder, logger);
```

A middleware function has the following signature:

```
typedef HttpResponse (*MiddlewareFunc)(HttpRequest req, Controller next);
```

Middleware can perform actions such as logging, authentication, or modifying the request/response before passing control to the next handler.

Example of a custom middleware:

```
HttpResponse myMiddleware(HttpRequest req, Controller next) {
    // Perform some action before the controller
    printf("Request received: %s\n", req.path);
    // Call the next handler in the pipeline
    return next(req);
}
```


## Environment Variables

You can inject environment variables into your application using a .env file.

Call the `dotenv` function to parse a .env file in the current directory. Then, you can call the `env` function to retrieve a specific environment variable.

Note that currently, only a `.env` file is supported, and files like `dev.env` will not be parsed.

```
dotenv();

char *dbUser = env("DB_USER");
char *dbPass = env("DB_PASS");

// ..

dotenvClean();
```

It is recommended that you call `dotenvClean` when you are finished using the variables to free them from memory.


## Testing your App

Lavandula provides a built-in testing framework for writing unit tests for your application.

The following example defines a new test that is being run.

```
void testOne() {
    int x = 10;
    expect(x, toBe(10));
}

runTest(testOne);
testResults();
```

Call `testResults` to see the outcome of all of your tests.


## JSON

Lavandula provides a built-in JSON API for manipulating JSON objects within your web application.

Create a json builder object to start.

```
JsonBuilder builder = jsonBuilder();
```

You can construct the JSON object calling various `jsonAdd...` methods. The following example adds a json pair with the key 'greeting' and the value 'Hello, World!'.

```
jsonAddString(&builder, "greeting", "Hello, World!");
```

These are all the valid methods you can use to add values into the JSON object.

```
void jsonAddString(JsonBuilder *builder, char *key, char *value);
void jsonAddBool(JsonBuilder *builder, char *key, bool value);
void jsonAddNumber(JsonBuilder *builder, char *key, double value);
void jsonAddNull(JsonBuilder *builder, char *key);
void jsonAddObject(JsonBuilder *builder, char *key, JsonBuilder *object);
void jsonAddArray(JsonBuilder *builder, char *key, JsonBuilder *array);
```

Let's construct an example JSON object.

```
JsonBuilder jBuilder = jsonBuilder();
jsonAddString(&jBuilder, "name", "This is a task!");
jsonAddNumber(&jBuilder, "age", 30);

jsonPrint(&jBuilder);
```

If we run this, we should see the following output.

```
{"name": "This is a task!", "age": 30.000000}
```


## Lavu

Lavu (lah-voo), the Lavandula CLI, can help you to quickly scaffold and setup your project.

Run the following command to create a new project.

```
lavu new <project_name>
```

Run the application.

```
lavu run
```

Note that `lavu run` will only work if the current working directory is the same as `lavandula.yml`.

You should see:

```
Lavandula Server is running! -> http://127.0.0.1:3000
```