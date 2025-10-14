# Lavandula

> ⚠️ **Notice:** Lavandula is still in early development and not ready for production use.  
> Expect frequent breaking changes and incomplete documentation.

**Lavandula** is a lightweight, fast, and intuitive C web framework designed for building modern web applications quickly. It focuses on simplicity, performance, and productivity, providing all the essentials without the bloat of heavier frameworks.


## Example

```c
#include "lavandula.h" 

// define a route for your app
appRoute(home) {
  return ok("Hello, World");
}

int main() {
  // initialise your app
  App app = createApp();

  // register a route in your app
  get(&app, "/home", home);

  // run the app
  runApp(&app);
}
```

### Todo App Example

```c
int main(int argc, char *argv[]) {
  AppBuilder builder = createBuilder();
  useSqlLite3(&builder, "init.db");
  
  App app = build(builder);

  get(&app, "/getTodos", getTodos);
  get(&app, "/getTodo", getTodo);
  post(&app, "/createTodo", createTodo);
  post(&app, "/updateTodo", updateTodo);
  post(&app, "/deleteTodo", deleteTodo);

  runApp(&app);

  return 0;
}
```

### Endpoint Example

```c
appRoute(getTodos) {
    DbResult *result = dbQueryRows(ctx.db, "select * from todos;", NULL, 0);
    returnIfNull(result, "Database query failed");

    JsonBuilder *root = jsonBuilder();
    JsonArray array = jsonArray();
    jsonPutArray(root, "todos", &array);
    
    for (int i = 0; i < result->rowCount; i++) {
        jsonArrayAppend(&array, todoToJson(rowToTodo(result->rows[i])));
    }

    char *json = jsonStringify(root);
    freeJsonBuilder(root);

    return ok(json);
}
```


## Features

- Controller and routing system
- HTTP endpoint support (GET, POST, etc)
- Controller local/global middleware pipeline
- Minimal dependencies (pure C)
- Quick project scaffolding via the CLI
- Built-in unit testing framework
- Environment variable support
- Built-in logging
- SQLite integration
- Built-in JSON library

## In Progress

- Static file serving


## Future

- TLS
- Session cookies
- CORS policy configuration
- Multithreading
- Rate Limiting
- PostgreSL, MySQL integrations, etc


## Installation

To install Lavandula, follow these setps.

1. Clone the repository

```bash
git clone https://github.com/ashtonjamesd/lavandula.git
cd lavandula
```


2. Run the install script

```bash
./install.sh
```

You should see the following:

```bash
[SUCCESS] 🎉 Lavandula installation completed!

Quick Start:
 lavu new my-project # Create a new project
 cd my-project
 lavu run # Run your project

Documentation:
 GitHub: https://github.com/ashtonjamesd/lavandula
```


3. Finish

You should now be able to run the Lavu CLI tool and begin writing your application. Refer to `api.md` for how to use Lavu.


## Getting Started

1. Create a new project

```
lavu new myProject
```

This will set up an application folder structure and copy the Lavandula `/src` directory into the created folder structure. This allows you to easily compile the framework and your app together.

Output:

```
Setting up Lavandula project 'myProject'...

-> Created myProject/lavandula.yml
-> Created myProject/app/app.c
-> Created myProject/app/controllers/controllers.h
-> Created myProject/app/controllers/home.c
-> Created myProject/app/routes.c
-> Created myProject/app/routes.h
-> Created myProject/makefile
-> Created myProject/tests/tests.c
-> Created myProject/README.md
...

🎉 Lavandula project 'myProject' setup finished successfully!

Next steps:
  1. cd myProject
  2. lavu run
```


2. Run

```
lavu run
```

Your application will run on http://localhost:3000/.

3. Read the docs

   - [Developing with Lavandula](doc/tutorial.md)
   - [API Documentation](doc/api.md)


## Contributing

Contributions are welcome. Feel free to submit pull requests or open issues for feature requests or bugs.

Some things that probably need looking at are:
- memory leaks
- outdated and unfinished documentation (API changes warrant a docs update)
- The JSON library does not currently support nested lists
- Some tests need to be written...


## License


Lavandula is registered under the MIT License.


