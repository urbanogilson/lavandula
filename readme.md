# Lavandula

**Lavandula** is a lightweight C web framework designed for building fast and simple web applications. It provides a small, intuitive API to define routes and run a HTTP server without the complexity of heavier frameworks. The framework is subtly inspired by .NET and Ruby on Rails.

<br/>

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
- Controller middleware
- Minimal dependencies (pure C)
- Quick project scaffolding via the CLI
- Built-in unit testing framework
- Environment variable support
- Built-in logging
- SQLite integration
- Built-in JSON library

## In Progress

- CORS policy configuration
- Potential ORM framework


## Future

- PostgreSL, MySQL integrations, etc
- Potential dependency injection framework
- Templating engine
- Rate Limiting
- Static file serving
- Session cookies
- Route/Available endpoint listing
- JSON model and function scaffolding
  - lavu model User name:string age:int
  - generates User struct, JSON serialization, CRUD endpoints in user_controller.c


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


## Quick Start

Use the Lavandula CLI with the following command to create a new project.

```
lavu new myProject
```

You should see the following output once run.

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

It automatically generates the following project structure:
```
.
├── app
│   ├── app.c
│   ├── controllers
│   │   └── home.c
│   └── routes.c
├── tests
│   └── tests.c
├── lavandula.yml
└── makefile
```


## Compile and Run

```
lavu run
```

Your app will start on port 3000, and visiting http://localhost:3000/ will display your application.


## Contributing

Contributions are welcome. Feel free to submit pull requests or open issues for feature requests or bugs.

Some things that probably need looking at are:
- memory leaks
- outdated documentation (API changes warrant a docs update)
- The JSON library does not currently support nested lists