#include "response.h"
#include "include.h"
#include "routes.h"

// win32 strtok_r fix
#ifdef _WIN32
#define strtok_r strtok_s
#endif // _WIN32

// msg to self: content-length should NOT include null char
// also make sure to add error checking for the fp so the server doesn't die :)

// gives back request line and body (body will be implemented later lol)
void ParseRequest(char *request, Request *splittedReq) {
    char *tokens[32];

    char *saver; // for strtok_s/r
    int i = 0;

    // split main request into tokens
    tokens[i] = strtok_r(request, "\r\n", &saver);

    while (tokens[i] != NULL)
        tokens[++i] = strtok_r(NULL, "\r\n", &saver);

    // split request line into tokens
    i = 0;
    splittedReq->requestLine[i] = strtok_r(tokens[0], " ", &saver);

    while (splittedReq->requestLine[i] != NULL)
        splittedReq->requestLine[++i] = strtok_r(NULL, " ", &saver);
}

void ResponseBuilder(char *headers, Response *response) {
    Request request = {0};
    ParseRequest(headers, &request);

    printf("Requested route is: %s\n", request.requestLine[1]);

    FILE *fp = fopen("html/index.html", "r");

    int contentLength = 512;
    response->content = calloc(contentLength, sizeof(char));

    size_t bytesRead = 0;
    do {
        bytesRead = fread(response->content, sizeof(char), contentLength, fp);
        if (bytesRead > 0) {
            contentLength *= 2;
            response->content = realloc(response->content, contentLength);
        }
    } while (bytesRead > 0);

    snprintf(response->headers, 1024, "HTTP/1.1 200 OK\r\n\
    Content-Type: text/html\r\n\
    Content-Length: %zu\r\n\r\n", strlen(response->content));

    fclose(fp);
    fp = NULL;
}