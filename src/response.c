#include "response.h"
#include "include.h"

// msg to self: content-length should NOT include null char
// also make sure to add error checking for the fp so the server doesn't die :)

void ResponseBuilder(char *request, Response *response) {
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

    snprintf(response->headers, 1024, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %i\r\n\r\n", (int)strlen(response->content));

    fclose(fp);
    fp = NULL;
} 