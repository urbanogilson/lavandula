#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/server.h"
#include "include/http.h"
#include "include/middleware.h"
#include "include/context.h"
#include "include/sql.h"

#define BUFFER_SIZE 4096

HttpResponse defaultNotFoundController(AppContext context) {
    (void)context;
    return (HttpResponse) {
        .content = "Not Found",
        .status = HTTP_NOT_FOUND
    };
}

Server initServer(int port) {
    Server server;
    server.port = port;
    server.fileDescriptor = -1;

    server.router = initRouter();

    return server;
}

void freeServer(Server *server) {
    if (!server) return;

    if (server->fileDescriptor >= 0) {
        close(server->fileDescriptor);
        server->fileDescriptor = -1;
    }

    freeRouter(&server->router);
}

void runServer(Server *server, MiddlewareHandler middleware, DbContext *dbContext) {
    if (!server) return;
    
    server->fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server->fileDescriptor < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server->fileDescriptor, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(server->port);

    if (bind(server->fileDescriptor, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server->fileDescriptor, 10) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Lavandula Server is running! -> http://127.0.0.1:%d\n", server->port);

    while (1) {
        struct sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        int clientSocket = accept(server->fileDescriptor, (struct sockaddr *)&clientAddr, &clientLen);
        if (clientSocket < 0) {
            perror("accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            perror("read failed");
            close(clientSocket);
            continue;
        }

        HttpParser parser = parseRequest(buffer);

        Route *route = NULL;
        for (int i = 0; i < server->router.routeCount; i++) {
            Route r = server->router.routes[i];

            if (strcmp(r.path, parser.request.resource) == 0) {
                route = &server->router.routes[i];
                break;
            }
        }

        if (!route) {
            Route *notFoundRoute = NULL;
            for (int i = 0; i < server->router.routeCount; i++) {
                Route r = server->router.routes[i];

                if (strcmp(r.path, "/404") == 0) {
                    notFoundRoute = &server->router.routes[i];
                    break;
                }
            }

            if (notFoundRoute) {
                route = notFoundRoute;
            }
        }

        AppContext context = appContext(parser.request);
        context.dbContext = dbContext;

        middleware.current = 0;
        middleware.finalHandler = route ? route->controller : defaultNotFoundController;

        HttpResponse response = next(context, &middleware);

        const char *contentType = "application/json";
        int contentLength = strlen(response.content);

        const char *statusText = httpStatusCodeToStr(response.status);

        char header[512];
        snprintf(header, sizeof(header),
                "HTTP/1.1 %s\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %d\r\n"
                "Connection: close\r\n"
                "\r\n",
                statusText, contentType, contentLength
        );

        write(clientSocket, header, strlen(header));
        write(clientSocket, response.content, contentLength);

        close(clientSocket);
    }
}