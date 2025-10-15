# Application Environment

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