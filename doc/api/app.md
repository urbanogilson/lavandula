# App

The app is structure that holds all of your web app configuration data. There are two valid ways you can setup an app.

You can all `createApp` directly, with no additional configuration.

```c
App app = createApp();
```

Or you can construct an app through the application builder.

```c
AppBuilder builder = createBuilder();
App app = build(builder);
```

If your application requires little to no configuration, then use `createApp` as a builder may not be required. If you would like to utilise various application features such as CORS or global middleware, then you would be better with the builder method.

The `runApp` method is used to run your web application and start the web server.

```c
runApp(&app);
```