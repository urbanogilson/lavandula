# Lavandula Tutorial

This document will walk you through creating a sample application with Lavandula, following conventions and best practices.


## Prerequisites

Ensure you have:
  - Make
  - A C Compiler


## Project Setup

Follow the installation and setup guide in `setup.md`.

Change directory into where you want the new project to be created.

```bash
cd projects
lavu new sampleApp
cd sampleApp
```

You should see the following structure:
  - app.c
  - home.c
  - lavandula.yml
  - makefile
  - routes.c

Run the application.

```bash
lavu run
```


## Integrating PostgreSQL

