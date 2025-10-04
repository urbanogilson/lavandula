# Lavandula Tutorial

This document will walk you through creating a sample application with Lavandula, following conventions and best practices. We will create a simple web application that connects to a Sqlite3 database and serves JSON content.


## Project Setup

Follow the installation and setup guide in `setup.md`.

Change directory into where you want the new project to be created.

```bash
cd projects
lavu new sampleApp
cd sampleApp
```

You should see the following structure:

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

Run the application.

```bash
lavu run
```

You should see

```
Lavandula Server is running! -> http://127.0.0.1:8080
```

## Integrating PostgreSQL

