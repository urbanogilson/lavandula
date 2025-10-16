# Routing

Routing is how you can control the way your application responds to client requests. Each route will define a URI path that can be accessed by a user. Each path usually returns some form of a resource such as a HTML or JSON.

To define a route, use the `appRoute` macro and put the name of the controller as an argument.

```c
appRoute(home, ctx) {
    return ok("", TEXT_PLAIN);
}
```

Registering a get endpoint for that specific route looks like this. The `get` function recieves three arguments. The first is the app itself so the route can be registered. Then the URI and lastly the controller endpoint.

```c
get(&app, "/home", home)
```

You can define routes for other HTTP methods such as `POST`, `DELETE`, etc.

```c
post(&app, "/somePost", somePostController)
delete(&app, "/someDelete", someDeleteController)
```

Each controller endpoint must return a valid `HttpResponse`. To make this easier, Lavandula defines a collection of methods that you call direectly in your controller to return a specific HTTP response.

You saw one earlier: `ok`.

Each of these methods takes in content you want to return and a format for the content. In this case, we return plain text and the plain text content type header.

See all content type headers [here](../api/http.md).

```
notFound("Something was not found", TEXT_PLAIN);
```

For a full list of the methods you can use, see the [Routing API](../api/routing.md).

Next: [Static Content](4_static_content.md)