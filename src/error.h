#pragma once

#ifndef _ERROR_H_
#define _ERROR_H_

#include "include.h"

void CleanExit(char errmsg[], int errcode, SOCKET *sockfd) {
    printf("Error msg: %s\nError code: %i\n", errmsg, errcode);

    if (sockfd) 
        closesocket(*sockfd);

    WSACleanup();
    exit(1);
}

#endif // _ERROR_H