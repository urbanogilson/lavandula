
#include "include/lavandula.h"

typedef struct {
    char name[100];
    char password[100];
} User;

User rowToUser(DbRow row) {
    User user;
    strcpy(user.name, row.col_values[0]);
    strcpy(user.password, row.col_values[1]);

    return user;
}

Json userToJson(User user) {
    JsonBuilder *builder = jsonBuilder();
    jsonPutString(builder, "name", user.name);
    jsonPutString(builder, "password", user.password);

    return jsonObject(builder);
}

appRoute(getUsers) {
    DbResult *result = dbQueryRows(ctx.dbContext, "select * from users;");
    returnIfNull(result, "Database query failed");

    JsonBuilder *root = jsonBuilder();
    JsonArray array = jsonArray();
    jsonPutArray(root, "users", &array);
    
    for (int i = 0; i < result->row_count; i++) {
        jsonArrayAppend(&array, userToJson(rowToUser(result->rows[i])));
    }

    char *json = jsonStringify(root);
    freeJsonBuilder(root);

    return ok(json);
}

appRoute(createUser) {
    JsonBuilder *builder = jsonParse(ctx.request.body);

    char *name = jsonGetString(builder, "name");
    char *password = jsonGetString(builder, "password");

    bool result = dbExec(ctx.dbContext, "insert into users (name, password) values (?, ?);", name, password);
    
    char *json = jsonStringify(builder);
    freeJsonBuilder(builder);

    return ok(json);
}

int main(int argc, char *argv[]) {
    AppBuilder builder = createBuilder();
    useSqlLite3(&builder, "init.db");
    
    App app = build(builder);

    get(&app, "/getUsers", getUsers);
    post(&app, "/createUser", createUser);

    runApp(&app);

    return 0;
}