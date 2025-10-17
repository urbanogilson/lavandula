#ifndef api_response_h
#define api_response_h

#include "lavandula.h"

/*
** Provides a standardized API response in JSON format.
** 
*/

middleware(validateJsonBody, ctx, m);

HttpResponse badJsonResponse(char *message);

#endif