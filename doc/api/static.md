# Static Files

Static files are non-changing files that you are able to serve to the user. You can serve static files with the following setup:

```c
appRoute(home, ctx) {
    char *html = readFile("home.html");
    return html ? ok(html, TEXT_HTML) : notFound("Content not found...", TEXT_HTML);
}
```

We first read the content of the file, using `readFile`. Lastly, we make some checks and return the content. And that's it!

Since this is a piece of code that you may use frequently within your application, Lavandula provides the following macro to simplify a static file endpoint. Note that the content type will be `text/html` when using this macro.

```c
appRouteStatic(home, "home.html");
```