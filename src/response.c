#include "response.h"
#include "include.h"

void ResponseBuilder(char *request, Response *response) {
    strncpy_s(response->headers, 65, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 16\r\n\r\n", 65);

    response->content = calloc(16, sizeof(char));
    strncpy_s(response->content, 16, "<h1>yoo hi</h1>", 16);
    
    response->contentLength = 16;
}