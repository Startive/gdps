#include "routes.h"

struct node *routes = NULL;

void addRoutes() {
    routes = insert(routes, "/", rootRoute);
    insert(routes, "/getGJSongInfo.php", getGJSongInfo_php);
    insert(routes, "/downloadGJLevel22.php", downloadGJLevel22_php);
}

char * getFileContents(const char* fileName) {
    FILE *fp = fopen(fileName, "r");

    if (!fp) {
        puts("Exiting program now as file does not exist.");
        exit(1);
    }

    int contentLength = 512;
    char *fileData = calloc(contentLength, sizeof(char));

    size_t bytesRead = 0;
    do {
        bytesRead = fread(fileData, sizeof(char), contentLength, fp);
        if (bytesRead > 0) {
            contentLength *= 2;
            fileData = realloc(fileData, contentLength);
        }
    } while (bytesRead > 0);

    fclose(fp);
    fp = NULL;

    return fileData;
}

void rootRoute(Response *response) {
    response->content = getFileContents("html/index.html");

    snprintf(response->headers, 1023, "HTTP/1.1 200 OK\r\n\
    Content-Type: text/html\r\n\
    Content-Length: %zu\r\n\r\n", strlen(response->content));
}

void Page404(Response *response) {
    response->content = getFileContents("html/404.html");

    snprintf(response->headers, 1023, "HTTP/1.1 200 OK\r\n\
    Content-Type: text/html\r\n\
    Content-Length: %zu\r\n\r\n", strlen(response->content));
}

void getGJSongInfo_php(Response *response) {
    printf("Hello from getgjsonginfophp\n");
}

void downloadGJLevel22_php(Response *response) {
    printf("hello from downloadgjlevel24,veworp;smf0u, gdh\n");
}