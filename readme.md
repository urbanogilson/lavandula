# Lavandula

**Lavandula** is a lightweight, minimalist C web framework designed for building fast and simple web applications. It provides a small, intuitive API to define routes and run a HTTP server without the complexity of heavier frameworks.

<br/>

```c
int main() {
    AppBuilder builder = createBuilder();
    usePort(&builder, 3001);
    useMiddleware(&builder, logger);

    dotenv();

    char *dbUser = env("DB_USER");
    char *dbPass = env("DB_PASS");

    App app = build(builder);

    get(&app, "/get", index);

    runApp(&app);

    dotenvClean();
    cleanupApp(&app);

    return 0;
}
```


## Features

- Intuitive routing system
- HTTP endpoint support (GET, POST, etc)
- Minimal dependencies (pure C)
- Quick project scaffolding via the CLI


## Installation

1. Clone the repository:

```bash
git clone https://github.com/ashtonjamesd/lavandula.git
cd lavandula
```

... todo


## Quick Start

Use the Lavandula CLI with the following command to create a new project.

```
lavandula new myProject
```

You should see the following output once run.

```
Setting up Lavandula project 'myProject'...

-> Setup directories created successfully!
-> Created app.c
-> Created controllers/home_controller.c
-> Created routes.c
-> Created makefile

🎉 Lavandula project 'myProject' setup finished successfully!

Next steps:
  1. cd myProject
  2. Compile your project (e.g., gcc app.c -o app)
  3. Run your app: ./app
```

It automatically generates:
- `app.c`
- `routes.c`
- `controllers/home_controller.c`


## Compile and Run

```
make
./<exe>
```

Your app will start on port 3000, and visiting http://localhost:3000/ will display your application.


## Project Structure

```
myproject/
├── app.c                  # Main application file
├── routes.c               # Route registration
├── controllers/
│   └── home_controller.c  # Example page controller
└── makefile               # Project makefile
```


## Contributing

Contributions are welcome. Feel free to submit pull requests or open issues for feature requests or bugs.