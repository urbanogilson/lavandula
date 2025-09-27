#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"
#include "http.h"

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
}

void runServer(Server *server) {
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
                route = &r;
                break;
            }
        }

        if (!route) {
            const char *notFound = "404 not found";
            write(clientSocket, notFound, strlen(notFound));
            close(clientSocket);
            continue;
        }

        Page page = route->controller();

        int totalLength = 0;
        char *bodyContent = malloc(1);
        bodyContent[0] = '\0';

        for (int i = 0; i < page.bodyCount; i++) {
            char *html = page.body[i].render(&page.body[i]);
            totalLength += strlen(html);
            bodyContent = realloc(bodyContent, totalLength + 1);
            strcat(bodyContent, html);

            free(html);
        }

        char fullPage[BUFFER_SIZE];
        snprintf(fullPage, sizeof(fullPage),
            "<!DOCTYPE html><html><head><title>%s</title></head><body>%s</body></html>",
            page.title, bodyContent
        );

        free(bodyContent);

        char header[256];
        snprintf(header, sizeof(header),
                 "HTTP/1.1 200 OK\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n"
                 "Content-Length: %zu\r\n\r\n",
                 strlen(fullPage));

        write(clientSocket, header, strlen(header));
        write(clientSocket, fullPage, strlen(fullPage));
        
        close(clientSocket);
    }
}