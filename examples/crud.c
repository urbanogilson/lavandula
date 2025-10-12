
#include "include/lavandula.h"

typedef struct {
    int id;
    char title[100];
    bool completed;
} Todo;

Todo rowToTodo(DbRow row) {
    Todo todo;
    todo.id = atoi(row.colValues[0]);
    strcpy(todo.title, row.colValues[1]);
    todo.completed = atoi(row.colValues[2]);

    return todo;
}

Json todoToJson(Todo todo) {
    JsonBuilder *builder = jsonBuilder();
    jsonPutInteger(builder, "id", todo.id);
    jsonPutString(builder, "title", todo.title);
    jsonPutBool(builder, "completed", todo.completed);

    return jsonObject(builder);
}

appRoute(getTodos) {
    DbResult *result = dbQueryRows(ctx.dbContext, "select * from todos;", NULL, 0);
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

appRoute(createTodo) {
    JsonBuilder *builder = jsonParse(ctx.request.body);

    if (!jsonHasKey(builder, "title")) {
        return internalServerError("Missing 'title' in request body");
    }

    char *name = jsonGetString(builder, "title");
    bool completed = jsonGetBool(builder, "completed");

    DbParam params[] = {
        PARAM_TEXT(name),
        PARAM_BOOL(completed)
    };

    bool result = dbExec(ctx.dbContext, "insert into todos (title, completed) values (?, ?);", params, 2);

    if (!result) {
        return internalServerError("Failed to create todo");
    }

    return ok("");
}

appRoute(updateTodo) {
    JsonBuilder *builder = jsonParse(ctx.request.body);

    if (!jsonHasKey(builder, "id")) {
        return internalServerError("Missing 'id' in request body");
    }

    int id = jsonGetInteger(builder, "id");
    char *title = jsonGetString(builder, "title");
    bool completed = jsonGetBool(builder, "completed");

    DbParam params[] = {
        PARAM_TEXT(title),
        PARAM_BOOL(completed),
        PARAM_INT(id)
    };

    bool result = dbExec(ctx.dbContext, "update todos set title = ?, completed = ? where id = ?;", params, 3);

    if (!result) {
        return internalServerError("Failed to update todo");
    }

    return ok("");
}

appRoute(deleteTodo) {
    JsonBuilder *builder = jsonParse(ctx.request.body);

    if (!jsonHasKey(builder, "id")) {
        return internalServerError("Missing 'id' in request body");
    }

    int id = jsonGetInteger(builder, "id");

    DbParam params[] = {
        PARAM_INT(id)
    };

    bool result = dbExec(ctx.dbContext, "delete from todos where id = ?;", params, 1);

    if (!result) {
        return internalServerError("Failed to delete todo");
    }

    return ok("");
}

appRoute(getTodo) {
    JsonBuilder *builder = jsonParse(ctx.request.body);

    if (!jsonHasKey(builder, "id")) {
        return internalServerError("Missing 'id' in request body");
    }

    int id = jsonGetInteger(builder, "id");

    DbParam params[] = {
        PARAM_INT(id)
    };

    DbResult *result = dbQueryRows(ctx.dbContext, "select * from todos where id = ?;", params, 1);
    returnIfNull(result, "Database query failed");

    if (result->rowCount == 0) {
        return internalServerError("Todo not found");
    }

    JsonBuilder *root = jsonBuilder();

    Json todo = todoToJson(rowToTodo(result->rows[0]));
    jsonPutJson(root, "todo", todo);

    char *json = jsonStringify(root);

    return ok(json);
}

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