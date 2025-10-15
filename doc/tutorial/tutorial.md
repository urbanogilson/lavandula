# Lavandula Tutorial

This document will walk you through creating a sample application with Lavandula, following conventions and best practices. We will create a simple web application that connects to a Sqlite3 database and serves JSON content.


## What is Lavandula?

Lavandula is a framework that makes building maintainable backends in C faster and more scalable (and fun). If you have used .NET before, then you will be familiar with some of the concepts used in the framework. The framework also takes some inspiration from Express and Rails.

The core of lavandula is a customisable web server. You can define routes to serve various types of content within your application. On top of this are various tools such as a route handler, middleware pipeline, environment variable parser, logger, and even an ORM, to make your development easier.

## Project Setup

Follow the installation and setup guide in `setup.md`.

Change directory into where you want the new project to be created.

```bash
cd projects
lavu new sampleApp
cd sampleApp
```

You should see the following folder structure automatically generated:

```
.
├── app
│   ├── controllers
│   │   ├── controllers.h
│   │   └── home.c
│   ├── app.c
│   ├── routes.c
│   └── routes.h
├── tests
│   └── tests.c
├── lavandula.yml
├── makefile
└── README.md
```

#### `Lavandula.yml`

This file is your project configuration file and contains things such as the project name and version.


#### `/app/app.c`

This file contains your top-level app code which will run your web application through `runApp`.


#### `/app/routes.h`

You likely wont have to alter this file. It is just a header file exposing the `registerRoutes` method.

#### `/app/routes.c`

This file contains a pre-generated method called `registerRoutes`. Every time you want to add a new route in your application, add another route method call inside here.


#### `/app/controllers/controllers.h`

This file exposes all of your controllers to the router. Every time you add a new controller, add the declaration inside here so the router can access it.

#### `/app/controllers/home.c`

This is a feature-specific file and contains controllers related to 'home'.


<br/>

Run the application.

```bash
lavu run
```

You should see

```
Lavandula Server is running! -> http://127.0.0.1:8080
```

## Sample Project Brief

The project we will build in this tutorial is hopefully a familiar one. We are going to be building a todo application, where the user can add, remove, update, and view the todos inside of a database.


## Data Modelling

We want to create a model for the data we are representing in our software. In our case, we want to create a todo model. This is done by simply creating a struct to hold the data fields we want to represent.

```
typedef struct {
  char *name;
  int   id;
} TodoItem;
```

Our todo model has a name, so the user can write what they need to do, and an ID so we can keep our todo items unique and identifiable.

## Controllers

A controller is a method that will be called when a specific endpoint in our application is hit.

To start, we will just have one endpoint, which will be to retrieve all todos in the database. However, we will eventually have a controller to handle creating, editing, and deleting a todo item.

```
appRoute(getTodos) {
    return ok("ok");
}
```


## Routing

Now we need to register this controller to a route in our application so that it can be routed to the correct endpoint. We will register this controller to the '/todos' route.

```
void registerRoutes(App app) {
    // ..
    get(&app, "/todos", getTodos);
}
```

Let's now test our application serves the correct content when accessing the '/todos' route.

Visit 'http://127.0.0.1:8080/todos' and ensure the following output on the webpage.

```
ok
```

## Integrating Sqlite3

We are going to be integrating a Sqlite3 database into our application. The database will hold a table that has all of our todo items inside of it.

You can install Sqlite3 with the following command.

```
sudo apt install libsqlite3-dev sqlite3
```

Include this header file in your project.

```c
#include <sqlite3.h>
```

Sqlite3 requires the use of a single *.db file, so lets create that now. I am going to call mine 'todo.db'.

Now add the following line in main.c. And it's as easy as that. Your application will now be able to interact with a Sqlite3 database.

```c
useSqlLite3(&builder, "todo.db");
```

Lets's set up our database with a table for our todo model and some example data.

```sql
create table Todos (
    id int not null,
    title text not null,
)

insert into Todos(id, title)
values (0, 'First Todo!'), (1, 'Second Todo!'), (2, 'Third Todo!')
```


In our controller, lets add the following code to retrieve all the todo items. The query method used below will return database result which a pointer to any rows that were retrieved and the number of rows in the pointer.

```c
DbResult *result = dbQueryRows(ctx.dbContext, "select * from Todos", NULL, 0);
if (!result) {
    return internalServerError("Failed to query database");
}
```

The end goal here is to return some JSON content to the user calling the endpoint. So we are going to have to transform the database rows into JSON so we can return it in the HTTP response.

We can make use of two helper methods here for converting our SQL rows into todo objects, and then our todo objects into JSON.

Here is the method for converting a database row into a todo struct.

```c
Todo rowToTodo(DbRow *row) {
    Todo todo = {
        .name = strdup(row->col_values[0]),
        .id = atoi(row->col_values[1])
    };

    return todo;
}
```

We can call this method for each row returned from the database.

```c
for (int i = 0; i < result->row_count; i++) {
    Todo todo = rowToTodo(&result->rows[i]);

    // ..
}
```

Lavandula provides a built-in JSON serialization library, allowing you to easily create JSON objects from C data.

Start by initializing a JsonBuilder. This holds the root of your JSON data. From here you can add key-value pairs into the object by calling 'jsonPut...' methods. Lastly, to convert the builder into a JSON object, we call the 'jsonObject' method.

```c
Json todoToJson(Todo todo) {
    JsonBuilder *builder = jsonBuilder();
    jsonPutString(builder, "name", todo.name);
    jsonPutInteger(builder, "id", todo.id);

    return jsonObject(builder);
}
```

Because we are going to have multiple todo objects, we require a JSON array. First, we create a root JSON builder, and then we create and add a JSON array into the root builder.

```c
JsonBuilder *root = jsonBuilder();

JsonArray array = jsonArray();
jsonPutArray(root, "todos", &array);

for (int i = 0; i < result->row_count; i++) {
    Todo todo = rowToTodo(&result->rows[i]);
    jsonArrayAppend(&array, todoToJson(todo));
}
```

For each todo object, we append it into the array.

Now we need to convert the JSON object into data that can be returned back to the client.

```c
char *json = jsonStringify(root);
freeJsonBuilder(root);
```

Lastly, we return an 'ok' to indicate the request was successful, along with the retrieved JSON content.

```c
return ok(json);
```

Now, call the get endpoint we created and validate that the todos are returned in the HTTP response.


## Final Remarks

Hopefully you found that simple enough. The framework is designed to make doing high level operations like this in a language like C much easier.