// WIN32 IMPLEMENTATION

#include <stdio.h>
#include <Windows.h>

int main(int argc, char **argv) {
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 

    return 0;
}
