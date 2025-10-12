
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
    DbResult *result = dbQueryRows(ctx.dbContext, "select * from todos;");
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

    char *name = jsonGetString(builder, "title");
    bool completed = jsonGetBool(builder, "completed");

    bool result = dbExec(ctx.dbContext, "insert into todos (title) values (?);", name);
    
    if (!result) {
        return internalServerError("Failed to create todo");
    }

    return ok("");
}

appRoute(updateTodo) {
    JsonBuilder *builder = jsonParse(ctx.request.body);

    int id = jsonGetInteger(builder, "id");
    char *title = jsonGetString(builder, "title");

    bool result = dbExec(ctx.dbContext, "update todos set title = ? where id = ?;", title, id);

    if (!result) {
        return internalServerError("Failed to update todo");
    }

    return ok("");
}

appRoute(deleteTodo) {
    JsonBuilder *builder = jsonParse(ctx.request.body);
    int id = jsonGetInteger(builder, "id");

    bool result = dbExec(ctx.dbContext, "delete from todos where id = ?;", id);

    if (!result) {
        return internalServerError("Failed to delete todo");
    }

    return ok("");
}

int main(int argc, char *argv[]) {
    AppBuilder builder = createBuilder();
    useSqlLite3(&builder, "init.db");
    
    App app = build(builder);

    get(&app, "/getTodos", getTodos);
    post(&app, "/createTodo", createTodo);
    post(&app, "/updateTodo", updateTodo);
    post(&app, "/deleteTodo", deleteTodo);

    runApp(&app);

    return 0;
}