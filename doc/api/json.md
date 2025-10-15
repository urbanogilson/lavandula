# JSON

Lavandula provides a built-in JSON API for manipulating JSON objects within your web application.

Create a json builder object to start.

```c
JsonBuilder jsonBuilder = jsonBuilder();
```

You can construct the JSON object calling various `jsonAdd...` methods. The following example adds a json pair with the key 'greeting' and the value 'Hello, World!'.

```c
jsonAddString(&jsonBuilder, "greeting", "Hello, World!");
```

These are all the valid methods you can use to add values into the JSON object.

```c
void jsonAddString(JsonBuilder *jsonBuilder, char *key, char *value);
void jsonAddBool(JsonBuilder *jsonBuilder, char *key, bool value);
void jsonAddNumber(JsonBuilder *jsonBuilder, char *key, double value);
void jsonAddNull(JsonBuilder *jsonBuilder, char *key);
void jsonAddObject(JsonBuilder *jsonBuilder, char *key, JsonBuilder *object);
void jsonAddArray(JsonBuilder *jsonBuilder, char *key, JsonBuilder *array);
```

This example constructs a 'todo' JSON object.

```c
JsonBuilder jBuilder = jsonBuilder();
jsonAddString(&jBuilder, "name", "This is a task!");
jsonAddNumber(&jBuilder, "age", 30);

jsonPrint(&jBuilder);
```

If we run this, we should see the following output.

```json
{"name": "This is a task!", "age": 30.000000}
```