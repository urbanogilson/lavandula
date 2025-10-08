# Lavandula

**Lavandula** is a lightweight, fast, and intuitive C web framework designed for building modern web applications quickly. It focuses on simplicity, performance, and productivity, providing all the essentials without the bloat of heavier frameworks.


## Example

```c
HttpResponse home(HttpRequest _) {
    return ok("Hello, World!");
}

int main() {
    // Initialize the application builder
    AppBuilder builder = createBuilder();
    
    // Build the application
    App app = build(builder);

    // Define routes
    get(&app, "/home", home);

    // Run the application
    runApp(&app);

    // Cleanup leftover resources
    cleanupApp(&app);

    return 0;
}
```


## Features

- Controller and routing system
- HTTP endpoint support (GET, POST, etc)
- Controller middleware pipeline
- Minimal dependencies (pure C)
- Quick project scaffolding via the CLI
- Built-in unit testing framework
- Environment variable support
- Built-in logging
- SQLite integration
- Built-in JSON library

## In Progress

- Route specific vs global middleware

- Session cookies
- CORS policy configuration

- Lavender ORM
- Embedded Lavandula (ELA) HTML templating engine


## Future

- Rate Limiting
- Static file serving
- PostgreSL, MySQL integrations, etc
- Potential dependency injection framework
- Route/Available endpoint listing
- JSON model and function scaffolding
  - lavu model User name:string age:int
  - generates User struct, JSON serialization, CRUD endpoints in user_controller.c
  - URL parameter parsing and routing


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

You should now be able to run the Lavu CLI tool. Refer to `api.md` for how to use Lavu.


## Getting Started

1. Create a new project

```
lavu new myProject
```

Output:

```
Setting up Lavandula project 'myProject'...

-> Created myProject/lavandula.yml
-> Created myProject/app/app.c
-> Created myProject/app/controllers/home.c
-> Created myProject/app/routes.c
-> Created myProject/makefile
-> Created myProject/tests/tests.c

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

Lavandula is registered under the MIT License.e