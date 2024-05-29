#include "response.h"
#include "include.h"

// msg to self: content-length should NOT include null char
// also make sure to add error checking for the fp so the server doesn't die :)

#define MAX_TOKEN_HEADERS 5 // change later so post requests work

/*
* TOKENS
* 0: contains method (GET, POST)
* 1: contains route, ("/", "/getGJSongInfo.php")
*/

// has to be reworked cause of post requests and need to properly parse request with spaces and colons
char **tokeniseRequest(char *request) {
    static char *tokens[MAX_TOKEN_HEADERS]; // i feel like this might cause a memory issue sometime later, hopefully it is fine for now
    char *saver;
    int i = 0;

    tokens[i] = strtok_s(request, " ", &saver);

    while (tokens[i] != NULL && i != MAX_TOKEN_HEADERS-1) 
        tokens[++i] = strtok_s(NULL, " ", &saver);

    return tokens;
}

void ResponseBuilder(char *request, Response *response) {
    char **epic = tokeniseRequest(request);
    printf("%s\n", epic[1]);

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