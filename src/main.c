#include "include/lavandula.h"

// typedef struct {
//     char name[100];
//     char password[100];
// } User;

// User rowToUser(DbRow row) {
//     User user;
//     strcpy(user.name, row.col_values[0]);
//     strcpy(user.password, row.col_values[1]);

//     return user;
// }

// Json userToJson(User user) {
//     JsonBuilder *builder = jsonBuilder();
//     jsonPutString(builder, "name", user.name);
//     jsonPutString(builder, "password", user.password);

//     return jsonObject(builder);
// }

// appRoute(getUsers) {
//     JsonBuilder *root = jsonBuilder();

//     JsonArray array = jsonArray();
//     jsonPutArray(root, "todos", &array);

//     DbResult *result = dbQueryRows(ctx.dbContext, "select * from users;");
//     for (int i = 0; i < result->row_count; i++) {
//         jsonArrayAppend(&array, userToJson(rowToUser(result->rows[i])));
//     }

//     char *json = jsonStringify(root);
//     freeJsonBuilder(root);

//     return ok(json);
// }

// appRoute(createUser) {
//     JsonBuilder *builder = jsonParse(ctx.request.body);

//     char *name = jsonGetString(builder, "name");
//     char *password = jsonGetString(builder, "password");

//     // dbExec(ctx.dbContext, "insert into users (name, password) values (?, ?);", name, password);
    
//     char *json = jsonStringify(builder);
//     freeJsonBuilder(builder);

//     return ok(json);
// }

int main(int argc, char *argv[]) {
    // AppBuilder builder = createBuilder();
    // usePort(&builder, 8080);
    // useSqlLite3(&builder, "init.db");
    
    // App app = build(builder);

    // get(&app, "/getUsers", getUsers);
    // post(&app, "/createUser", createUser);

    // runApp(&app);

    if (argc < 2) {
        printf("usage: lavu <command> [options]\n");
        return 1;
    }

    char *option = argv[1];

    if (strcmp(option, "new") == 0) {
        if (argc < 3) {
            printf("error: expected project name after 'new'\n");
            return 1;
        }

        char *projectName = argv[2];
        return newProject(projectName);
    } else if (strcmp(option, "run") == 0) {
        return runProject();
    } else if (strcmp(option, "help") == 0) {
        return help();
    } else if (strcmp(option, "--version") == 0 || strcmp(option, "-v") == 0) {
        return version();
    } else if (strcmp(option, "migrate") == 0) {
        return migrate();
    } else {
        return unknownCommand(option);
    }
}