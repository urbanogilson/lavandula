#ifndef router_h
#define router_h

#include "http.h"
#include "context.h"

// forward declaration
typedef struct MiddlewareHandler MiddlewareHandler;

typedef HttpResponse (*Controller)(AppContext);

typedef struct {
    HttpMethod method;
    char      *path;

    Controller controller;
    MiddlewareHandler *middleware;
} Route;

typedef struct {
    Route *routes;
    int    routeCount;
    int    routeCapacity;
} Router;

Router initRouter();
void freeRouter(Router *router);

Route route(Router *router, HttpMethod method, char *path, Controller controller);

Route *findRoute(Router router, char *routePath);

HttpResponse response(char *content, HttpStatusCode);

// 1xx Informational responses
HttpResponse httpContinue(char *content);
HttpResponse switchingProtocols(char *content);
HttpResponse processing(char *content);
HttpResponse earlyHints(char *content);

// 2xx Success responses
HttpResponse ok(char *content);
HttpResponse created(char *content);
HttpResponse accepted(char *content);
HttpResponse nonAuthoritativeInformation(char *content);
HttpResponse noContent(char *content);
HttpResponse resetContent(char *content);
HttpResponse partialContent(char *content);
HttpResponse multiStatus(char *content);
HttpResponse alreadyReported(char *content);
HttpResponse imUsed(char *content);

// 3xx Redirection responses
HttpResponse multipleChoices(char *content);
HttpResponse movedPermanently(char *content);
HttpResponse found(char *content);
HttpResponse seeOther(char *content);
HttpResponse notModified(char *content);
HttpResponse useProxy(char *content);
HttpResponse temporaryRedirect(char *content);
HttpResponse permanentRedirect(char *content);

// 4xx Client error responses
HttpResponse badRequest(char *content);
HttpResponse unauthorized(char *content);
HttpResponse paymentRequired(char *content);
HttpResponse forbidden(char *content);
HttpResponse notFound(char *content);
HttpResponse methodNotAllowed(char *content);
HttpResponse notAcceptable(char *content);
HttpResponse proxyAuthenticationRequired(char *content);
HttpResponse requestTimeout(char *content);
HttpResponse conflict(char *content);
HttpResponse gone(char *content);
HttpResponse lengthRequired(char *content);
HttpResponse preconditionFailed(char *content);
HttpResponse payloadTooLarge(char *content);
HttpResponse uriTooLong(char *content);
HttpResponse unsupportedMediaType(char *content);
HttpResponse rangeNotSatisfiable(char *content);
HttpResponse expectationFailed(char *content);
HttpResponse imATeapot(char *content);
HttpResponse misdirectedRequest(char *content);
HttpResponse unprocessableEntity(char *content);
HttpResponse locked(char *content);
HttpResponse failedDependency(char *content);
HttpResponse tooEarly(char *content);
HttpResponse upgradeRequired(char *content);
HttpResponse preconditionRequired(char *content);
HttpResponse tooManyRequests(char *content);
HttpResponse requestHeaderFieldsTooLarge(char *content);
HttpResponse unavailableForLegalReasons(char *content);

// 5xx Server error responses
HttpResponse internalServerError(char *content);
HttpResponse notImplemented(char *content);
HttpResponse badGateway(char *content);
HttpResponse serviceUnavailable(char *content);
HttpResponse gatewayTimeout(char *content);
HttpResponse httpVersionNotSupported(char *content);
HttpResponse variantAlsoNegotiates(char *content);
HttpResponse insufficientStorage(char *content);
HttpResponse loopDetected(char *content);
HttpResponse notExtended(char *content);
HttpResponse networkAuthenticationRequired(char *content);

#endif