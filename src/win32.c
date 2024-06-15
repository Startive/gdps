// WIN32 IMPLEMENTATION
// or maybe just do a bunch of #ifdefs for linux and windows
// but ill probably make another file that is just for unix so its cleaner

#include <memory.h>

#include "include.h"
#include "response.h"
#include "dict.h"

#include "routes.h"

#define PORT 5555

static void CleanExit(char errmsg[], int errcode, SOCKET *sockfd) {
    printf("Error msg: %s\nError code: %i\n", errmsg, errcode);

    if (sockfd) 
        closesocket(*sockfd);

    WSACleanup();
    exit(1);
}

void HandleConnection(SOCKET connection) {
    char buffer[1024] = {0}; // we don't really care if the request is bigger then 1024, all the crucial info will still be in there

    int result = recv(connection, buffer, 1023, 0);

    // if connection has been closed by client or no information has been given we will just close the connection
    if (result == 0) {
        goto end;
    }

    if (result == SOCKET_ERROR) {
        closesocket(connection);
        puts("An error occured while recieving data on a thread, promptly ending thread now.");
        ExitThread(1);
    }

    Response response = {0};
    getResponse(buffer, &response);

    send(connection, response.headers, strlen(response.headers), 0); // please do NOT change strlen to sizeof :)
    send(connection, response.content, strlen(response.content), 0);


    // cleanup
    free(response.content);
    response.content = NULL;

end:
    closesocket(connection);
    ExitThread(0);
}

int main(void) {
    // add routes
    addRoutes();

    // setup server
    WSADATA wsadata = {0};
    int result = 0;
    int opt = 1; // idk what this does lol

    // win32 stuff
    result = WSAStartup(MAKEWORD(2,2), &wsadata);
    if (result != 0) 
        CleanExit("Error with WSAStartup.", result, NULL);

    // Create socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET)
        CleanExit("Error setting up the socket.", WSAGetLastError(), &sockfd);

    // Set sock opt, so we can 'resuse' the address and port
    result = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
    if (result != 0)
        CleanExit("Failed to set sock opt.", WSAGetLastError(), &sockfd);

    // Bind
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;

    result = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (result != 0)
        CleanExit("Binding has failed.", WSAGetLastError(), &sockfd);

    // Listen
    result = listen(sockfd, SOMAXCONN);
    if (result != 0)
        CleanExit("Failed to listen.", WSAGetLastError(), &sockfd);
    else
        printf("Now listening on port http://127.0.0.1:%i!\n\n", PORT);

    // accept and handle connection
    struct sockaddr client = {0}; // unused for now, contains info about client.
    SOCKET connection = 0;

    while (1) {
        SOCKET connection = accept(sockfd, &client, NULL);
        if (connection == INVALID_SOCKET) {
            closesocket(connection);
            CleanExit("Failed to accept the connection!", WSAGetLastError(), &sockfd);
        }

        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HandleConnection, (LPVOID)connection, 0, NULL);
        memset(&client, 0, sizeof(struct sockaddr));
    }
    
    return 1; // if reached then how
}