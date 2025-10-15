# Static Content

Static content refers to resources that are unchanging, such as images or HTML files.

To serve static content, first call `readFile` to get the content of the file. Then return the content of the file with the correct content type header.

```c
appRoute(home) {
    char *html = readFile("home.html");
    return ok(html, TEXT_HTML);
}
```

Since this may be code that is used repetitively within your application, you can use the `appRouteStatic` macro to do the exact same as the above.

```c
appRouteStatic(home, "home.html");
```

Don't forget to register the route:

```c
get(&app, "/home", home);
```

Now, when you go to `/home`, you will see the content inside of `home.html`.

Next: [API Documentation](../api.md)