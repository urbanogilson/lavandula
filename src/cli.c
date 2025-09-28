#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "cli.h"

#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

void newProject(char *name) {
    if (!name || strlen(name) == 0) {
        printf(RED "Error: Project name cannot be empty.\n" RESET);
        return;
    }

    char tempDir[256];
    snprintf(tempDir, sizeof(tempDir), "%s", name);

    printf(YELLOW "\nSetting up Lavandula project '%s'...\n\n" RESET, tempDir);
    if (mkdir(tempDir, 0755) != 0) {
        perror("Failed to create project directory");
        return;
    }

    char controllersDir[256];
    snprintf(controllersDir, sizeof(controllersDir), "%s/controllers", tempDir);
    if (mkdir(controllersDir, 0755) != 0) {
        perror("Failed to create controllers directory");
        return;
    }
    printf(GREEN "-> Setup directories created successfully!\n" RESET);

    char appFile[256];
    snprintf(appFile, sizeof(appFile), "%s/app.c", tempDir);
    FILE *fp = fopen(appFile, "w");
    if (!fp) {
        perror("Error creating app.c");
        return;
    }
    fprintf(fp,
        "#include \"../src/lavandula.h\"\n"
        "#include \"routes.c\"\n\n\n"
        "int main() {\n"
        "    App app = init(3000);\n\n"
        "    registerRoutes(app);\n\n"
        "    runApp(&app);\n"
        "    cleanupApp(&app);\n\n"
        "    return 0;\n"
        "}\n"
    );
    fclose(fp);
    printf(GREEN "-> Created app.c\n" RESET);

    char homeControllerFile[256];
    snprintf(homeControllerFile, sizeof(homeControllerFile), "%s/controllers/home_controller.c", tempDir);
    FILE *hcFp = fopen(homeControllerFile, "w");
    if (!hcFp) {
        perror("Error creating home_controller.c");
        return;
    }
    fprintf(hcFp, 
        "#include \"../src/lavandula.h\"\n\n"
        "Page home() {\n"
        "    Page p = page(\"Home\");\n"
        "    text(&p, \"Hello, World!\");\n\n"
        "    return p;\n"
        "}\n"
    );
    fclose(hcFp);
    printf(GREEN "-> Created controllers/home_controller.c\n" RESET);

    char routesFile[256];
    snprintf(routesFile, sizeof(routesFile), "%s/routes.c", tempDir);
    FILE *routesFp = fopen(routesFile, "w");
    if (!routesFp) {
        perror("Error creating routes.c");
        return;
    }
    fprintf(routesFp, 
        "#include \"../src/lavandula.h\"\n"
        "#include \"controllers/home_controller.c\"\n\n"
        "void registerRoutes(App app) {\n"
        "    route(&app.server.router, HTTP_GET, \"/\", home);\n"
        "}\n"
    );
    fclose(routesFp);
    printf(GREEN "-> Created routes.c\n" RESET);

    char makefile[256];
    snprintf(makefile, sizeof(makefile), "%s/makefile", tempDir);
    FILE *makefileFp = fopen(makefile, "w");
    if (!makefileFp) {
        perror("Error creating makefile");
        return;
    }
    fprintf(makefileFp, 
        "SRCS = app.c routes.c $(wildcard controllers/*.c)\n"
        "CFLAGS = -Wall -Wextra\n\n"
        "all:\n"
        "	gcc $(SRCS) $(CFLAGS) -o a\n"
    );
    fclose(makefileFp);
    printf(GREEN "-> Created makefile\n" RESET);

    printf(GREEN "\n🎉 Lavandula project '%s' setup finished successfully!\n" RESET, name);
    printf(YELLOW "\nNext steps:\n" RESET);
    printf("  1. cd %s\n", tempDir);
    printf("  2. Compile your project (e.g., gcc app.c -o app)\n");
    printf("  3. Run your app: ./app\n\n");
}