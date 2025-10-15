
# Routing

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