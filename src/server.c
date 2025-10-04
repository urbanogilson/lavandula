#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"
#include "http.h"
#include "middleware.h"

#define BUFFER_SIZE 4096

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

void runServer(Server *server, MiddlewareHandler middleware) {
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
            } else {
                const char *notFound = "404 not found";
                write(clientSocket, notFound, strlen(notFound));
                close(clientSocket);
                continue;
            }
        }

        bool x = next(parser.request, &middleware);

        if (!x) {
            const char *forbidden = "403 forbidden";
            write(clientSocket, forbidden, strlen(forbidden));
            close(clientSocket);
            continue;
        }

        HttpResponse res = route->controller(parser.request);

        const char *contentType = "application/json";
        int contentLength = strlen(res.content);

        char header[512];
        snprintf(header, sizeof(header),
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: %s\r\n"
                "Content-Length: %d\r\n"
                "Connection: close\r\n"
                "\r\n",
                contentType, contentLength);

        write(clientSocket, header, strlen(header));
        write(clientSocket, res.content, contentLength);

        close(clientSocket);
    }
}