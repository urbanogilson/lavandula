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


## Data Modelling

We want to create a model for the data we are representing in our software. In our case, we want to create a todo model.

```
typedef struct {
  char *name;
  int   id;
} TodoItem;
```

Our todo model has a name, so the user can write what they need to do, and an ID so we can keep our todo items unique and identifiable.

## Controllers

A controller is a method that will be called when a specific endpoint in our application is hit.

To start, we will just have one endpoint, which will be to retrieve all todos in the database.

```
// all controllers must follow this function signature
HttpResponse getTodos(AppContext ctx) {
    return ok("ok");
}
```


## Routing

Now we need to register this controller to a route in our application. We will register this controller to the '/todos' route.

```
void registerRoutes(App app) {
    root(&app, home);
    get(&app, "/todos", getTodos);
}
```

Let's now test our application serves the correct content when accessing the '/todos' route.

Visit 'http://127.0.0.1:8080/todos' and ensure the following output on the webpage.

```
ok
```

## Integrating Sqlite3

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

Lets's set up our database.

```sql
// create Todos () etc ...
```


In our controller, lets add the following code to retrieve all the todo items.

```c
DbResult *result = dbQueryRows(ctx.dbContext, "select * from Todos");
if (!result) {
    return internalServerError("Failed to query database");
}
```

We can make use of two helper methods here for converting our SQL rows into todo objects, and then our todo objects into JSON.

Our method for converting 

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

For each todo object, we call 'jsonArrayAppend' to add it into the array.

Now we need to convert the JSON object into data that can be returned back to the client.

```c
char *json = jsonStringify(root);
freeJsonBuilder(root);
```

Lastly, we return an 'ok' to indicate the request was successful, along with the retrieved JSON content.

```c
return ok(json);
```