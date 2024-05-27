// WIN32 IMPLEMENTATION
// or maybe just do a bunch of #ifdefs for linux and windows
// but ill probably make another file that is just for unix so its cleaner

#include <stdio.h>
#include <memory.h>

#include "include.h"
#include "response.h"
#include "error.h"

#define PORT 5555

void HandleConnection(SOCKET connection) {
    char buffer[1024] = {0};

    int result = recv(connection, buffer, 1024, 0);

    if (result == SOCKET_ERROR) {
        closesocket(connection);
        puts("An error occured with recieve on a thread.");
        ExitThread(1);
    } else {
        ResponseBuilder();
    }

    printf("%s", buffer);

    send(connection, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 16\r\n\r\n", 65, 0);
    send(connection, "<h1>yoo hi</h1>", 16, 0);

    closesocket(connection);

    ExitThread(0);
}

int main(void) {
    WSADATA wsadata; ZeroMemory(&wsadata, sizeof(WSADATA));
    int result = 0;
    int opt = 1; // idk what this does???

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
    struct sockaddr_in addr; ZeroMemory(&addr, sizeof(struct sockaddr_in));
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
        printf("Now listening on port http://127.0.0.1:%i\n\n", PORT); // make sure to add the actual PORT in sprintf later

    // accept and handle connection
    struct sockaddr client; ZeroMemory(&client, sizeof(struct sockaddr)); // unused for now, contains info about client.
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

    /*
    closesocket(sockfd);
    closesocket(connection);
    WSACleanup();
    */

    return 0;
}