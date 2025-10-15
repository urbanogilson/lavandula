# Environment Variables

An environment variable refers to data defined separately from your application and is usually injected into it so it can be used. Example of this are database credentials, passwords, or port configurations.

You can inject environment variables into your application using a .env file.

Call the `useDotenv` function to parse an environment variable file in the current directory.

```c
useDotenv(".env");
```

Then, you can call the `env` function to retrieve a specific environment variable.

```c
char *dbUser = env("DB_USER");
char *dbPass = env("DB_PASS");
```