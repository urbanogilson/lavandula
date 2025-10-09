#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/router.h"
#include "include/server.h"

// 1xx Informational responses
HttpResponse httpContinue(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_CONTINUE
    };
}

HttpResponse switchingProtocols(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_SWITCHING_PROTOCOLS
    };
}

HttpResponse processing(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PROCESSING
    };
}

HttpResponse earlyHints(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_EARLY_HINTS
    };
}

// 2xx Success responses
HttpResponse ok(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_OK
    };
}

HttpResponse created(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_CREATED
    };
}

HttpResponse accepted(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_ACCEPTED
    };
}

HttpResponse nonAuthoritativeInformation(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NON_AUTHORITATIVE_INFORMATION
    };
}

HttpResponse noContent(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NO_CONTENT
    };
}

HttpResponse resetContent(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_RESET_CONTENT
    };
}

HttpResponse partialContent(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PARTIAL_CONTENT
    };
}

HttpResponse multiStatus(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_MULTI_STATUS
    };
}

HttpResponse alreadyReported(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_ALREADY_REPORTED
    };
}

HttpResponse imUsed(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_IM_USED
    };
}

// 3xx Redirection responses
HttpResponse multipleChoices(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_MULTIPLE_CHOICES
    };
}

HttpResponse movedPermanently(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_MOVED_PERMANENTLY
    };
}

HttpResponse found(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_FOUND
    };
}

HttpResponse seeOther(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_SEE_OTHER
    };
}

HttpResponse notModified(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NOT_MODIFIED
    };
}

HttpResponse useProxy(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_USE_PROXY
    };
}

HttpResponse temporaryRedirect(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_TEMPORARY_REDIRECT
    };
}

HttpResponse permanentRedirect(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PERMANENT_REDIRECT
    };
}

// 4xx Client error responses
HttpResponse badRequest(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_BAD_REQUEST
    };
}

HttpResponse unauthorized(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_UNAUTHORIZED
    };
}

HttpResponse paymentRequired(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PAYMENT_REQUIRED
    };
}

HttpResponse forbidden(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_FORBIDDEN
    };
}

HttpResponse notFound(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NOT_FOUND
    };
}

HttpResponse methodNotAllowed(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_METHOD_NOT_ALLOWED
    };
}

HttpResponse notAcceptable(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NOT_ACCEPTABLE
    };
}

HttpResponse proxyAuthenticationRequired(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PROXY_AUTHENTICATION_REQUIRED
    };
}

HttpResponse requestTimeout(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_REQUEST_TIMEOUT
    };
}

HttpResponse conflict(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_CONFLICT
    };
}

HttpResponse gone(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_GONE
    };
}

HttpResponse lengthRequired(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_LENGTH_REQUIRED
    };
}

HttpResponse preconditionFailed(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PRECONDITION_FAILED
    };
}

HttpResponse payloadTooLarge(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PAYLOAD_TOO_LARGE
    };
}

HttpResponse uriTooLong(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_URI_TOO_LONG
    };
}

HttpResponse unsupportedMediaType(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_UNSUPPORTED_MEDIA_TYPE
    };
}

HttpResponse rangeNotSatisfiable(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_RANGE_NOT_SATISFIABLE
    };
}

HttpResponse expectationFailed(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_EXPECTATION_FAILED
    };
}

HttpResponse imATeapot(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_IM_A_TEAPOT
    };
}

HttpResponse misdirectedRequest(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_MISDIRECTED_REQUEST
    };
}

HttpResponse unprocessableEntity(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_UNPROCESSABLE_ENTITY
    };
}

HttpResponse locked(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_LOCKED
    };
}

HttpResponse failedDependency(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_FAILED_DEPENDENCY
    };
}

HttpResponse tooEarly(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_TOO_EARLY
    };
}

HttpResponse upgradeRequired(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_UPGRADE_REQUIRED
    };
}

HttpResponse preconditionRequired(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_PRECONDITION_REQUIRED
    };
}

HttpResponse tooManyRequests(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_TOO_MANY_REQUESTS
    };
}

HttpResponse requestHeaderFieldsTooLarge(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE
    };
}

HttpResponse unavailableForLegalReasons(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_UNAVAILABLE_FOR_LEGAL_REASONS
    };
}

// 5xx Server error responses
HttpResponse internalServerError(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_INTERNAL_SERVER_ERROR
    };
}

HttpResponse notImplemented(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NOT_IMPLEMENTED
    };
}

HttpResponse badGateway(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_BAD_GATEWAY
    };
}

HttpResponse serviceUnavailable(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_SERVICE_UNAVAILABLE
    };
}

HttpResponse gatewayTimeout(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_GATEWAY_TIMEOUT
    };
}

HttpResponse httpVersionNotSupported(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_HTTP_VERSION_NOT_SUPPORTED
    };
}

HttpResponse variantAlsoNegotiates(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_VARIANT_ALSO_NEGOTIATES
    };
}

HttpResponse insufficientStorage(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_INSUFFICIENT_STORAGE
    };
}

HttpResponse loopDetected(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_LOOP_DETECTED
    };
}

HttpResponse notExtended(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NOT_EXTENDED
    };
}

HttpResponse networkAuthenticationRequired(char *content) {
    return (HttpResponse){
        .content = content,
        .status = HTTP_NETWORK_AUTHENTICATION_REQUIRED
    };
}

HttpResponse response(char *content, HttpStatusCode status) {
    return (HttpResponse) {
        .content = content,
        .status = status
    };
}

Router initRouter() {
    Router router = {
        .routeCapacity = 1,
        .routeCount = 0,
        .routes = malloc(sizeof(Route))
    };

    return router;
}

void freeRouter(Router *router) {
    if (!router) return;

    for (int i = 0; i < router->routeCount; i++) {
        Route route = router->routes[i];
        free(route.path);
        
        if (route.middleware) {
            free(route.middleware->handlers);
            free(route.middleware);
        }
    }

    free(router->routes);
}

Route route(Router *router, HttpMethod method, char *path, Controller controller) {
    MiddlewareHandler *middleware = malloc(sizeof(MiddlewareHandler));
    *middleware = (MiddlewareHandler){
        .handlers = malloc(sizeof(MiddlewareFunc) * 1),
        .count = 0,
        .capacity = 1,
        .current = 0,
        .finalHandler = controller
    };

    Route route = {
        .method = method,
        .path = strdup(path),
        .controller = controller,
        .middleware = middleware
    };

    if (router->routeCount >= router->routeCapacity) {
        router->routeCapacity *= 2;
        router->routes = realloc(router->routes, sizeof(Route) * router->routeCapacity);
    }
    router->routes[router->routeCount++] = route;

    return route;
}

Route *findRoute(Router router, char *path) {
    for (int i = 0; i < router.routeCount; i++) {
        Route route = router.routes[i];

        if (strcmp(route.path, path) == 0) {
            return &router.routes[i];
        }
    }

    return NULL;
}