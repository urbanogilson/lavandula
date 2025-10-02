# Lavandula

**Lavandula** is a lightweight, minimalist C web framework designed for building fast and simple web applications. It provides a small, intuitive API to define routes and run a HTTP server without the complexity of heavier frameworks. The framework is subtly inspired by .NET and Ruby on Rails.

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

- Intuitive routing system
- HTTP endpoint support (GET, POST, etc)
- Controller middleware
- Minimal dependencies (pure C)
- Quick project scaffolding via the CLI
- Route and model generation via the CLI
- Built-in testing framework


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
lavu new myProject
```

You should see the following output once run.

```
Setting up Lavandula project 'myProject'...

-> Created t/lavandula.yml
-> Created t/app/app.c
-> Created t/app/controllers/home.c
-> Created t/app/routes.c
-> Created t/makefile
-> Created t/tests/tests.c

🎉 Lavandula project 'myProject' setup finished successfully!

Next steps:
  1. cd myProject
  2. Compile your project (e.g., gcc app.c -o app)
  3. Run your app: ./app
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