// WIN32 IMPLEMENTATION
// or maybe just do a bunch of #ifdefs for linux and windows
// but ill probably make another file that is just for unix so its cleaner

#include <stdio.h>
#include <memory.h>
#include <stdarg.h>
#include <WinSock2.h>

#define PORT 5555

void CleanExit(char errmsg[], int errcode) {
    printf("Error msg: %s\nError code: %i\n", errmsg, errcode);

    WSACleanup();
    exit(1);
}

int main(int argc, char **argv) {
    WSADATA wsadata; ZeroMemory(&wsadata, sizeof(WSADATA));
    int result = 0;
    int opt = 1; // idk what this does???

    // win32 stuff
    result = WSAStartup(MAKEWORD(2,2), &wsadata);
    if (result != 0) 
        CleanExit("Error with WSAStartup.", result);

    // Create socket
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET)
        CleanExit("Error setting up the socket.", WSAGetLastError());

    // Set sock opt, so we can 'resuse' the address and port
    result = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
    if (result != 0)
        CleanExit("Failed to set sock opt.", WSAGetLastError());

    // Bind
    struct sockaddr_in addr; ZeroMemory(&addr, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;

    result = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if (result != 0)
        CleanExit("Binding has failed.", WSAGetLastError());

    // Listen
    result = listen(sockfd, SOMAXCONN);
    if (result != 0)
        CleanExit("Failed to listen on port 5555.", WSAGetLastError());

    return 0;
}