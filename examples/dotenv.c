#include "lavandula.h"

int main() {
    AppBuilder builder = createBuilder();

    // Parse .env file and load environment variables
    useDotenv(".env");

    // Get environment variables
    char *dbUser = env("DB_USER");
    char *dbPass = env("DB_PASS");

    App app = build(builder);

    runApp(&app);

    return 0;
}