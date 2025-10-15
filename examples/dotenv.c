#include "lavandula.h"

int main() {
    // Parse .env file and load environment variables
    useDotenv(".env");

    // Get environment variables
    char *dbUser = env("DB_USER");
    char *dbPass = env("DB_PASS");

    App app = createApp();
    runApp(&app);

    return 0;
}