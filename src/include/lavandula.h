#ifndef lavandula_h
#define lavandula_h

// common headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cli.h"
#include "server.h"
#include "dotenv.h"
#include "middleware.h"
#include "logger.h"
#include "lavandula_test.h"
#include "json.h"
#include "cors.h"
#include "environment.h"
#include "sql.h"
#include "lavender.h"
#include "utils.h"
#include "auth.h"

#include "version.h"

typedef struct {
    Server             server;
    int                port;

    bool               verboseLogging; 
    bool               useHttpsRedirect;
    char              *environment;
    bool               useLavender;     
    MiddlewareHandler  middleware;
    CorsConfig         corsPolicy;
    DbContext         *dbContext;
    BasicAuthenticator auth;
} App;

typedef struct {
    App app;
} AppBuilder;

AppBuilder createBuilder();

// sets the port for the application (default is 3000)
void usePort(AppBuilder *builder, int port);

// adds a middleware function to the application pipeline
void useMiddleware(AppBuilder *builder, MiddlewareFunc);

// enables verbose logging for requests and responses
void useVerboseLogging(AppBuilder *builder);

// loads environment variables from a .env file
void useDotenv(char *path);

// adds CORS policy to the application
void useCorsPolicy(AppBuilder *builder, CorsConfig);

// adds a default permissive CORS policy to the application
void useDefaultCorsPolicy(AppBuilder *builder);

// enables HTTPS redirection for all incoming HTTP requests
void useHttpsRedirect(AppBuilder *builder);

// sets the application environment (development, production, testing)
void useEnvironment(AppBuilder *builder, char *env);

// integrates SQLite3 database with the application
void useSqlLite3(AppBuilder *builder, char *dbPath);

// integrates Lavender ORM with the application
void useLavender(AppBuilder *builder);

//
// void useIpRateLimiter(AppBuilder *builder);

//
void useBasicAuth(AppBuilder *builder);

bool isDevelopment(AppBuilder *builder);
bool isProduction(AppBuilder *builder);
bool isTesting(AppBuilder *builder);

App build(AppBuilder builder);

void runApp(App *app);
void cleanupApp(App *app);

void get(App *app, char *path, Controller controller);
void post(App *app, char *path, Controller controller);
void put(App *app, char *path, Controller controller);
void delete(App *app, char *path, Controller controller);
void patch(App *app, char *path, Controller controller);
void options(App *app, char *path, Controller controller);

// copy Rails essentially lmao
void resource(App *app, char *resource, Controller (*controllerFactory)());

// defines a special route for handling 404s
void routeNotFound(App *app,  Controller controller);

// defines a special route for handling the root path
void root(App *app, Controller controller);


#endif