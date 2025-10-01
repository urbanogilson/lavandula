#include "../src/lavandula.h"

int main() {
    AppBuilder builder = createBuilder();

    // Parse .env file and load environment variables
    dotenv();

    // Get environment variables
    char *dbUser = env("DB_USER");
    char *dbPass = env("DB_PASS");

    App app = build(builder);

    runApp(&app);

    // Clean up environment variables
    dotenvClean();
    cleanupApp(&app);

    return 0;
}