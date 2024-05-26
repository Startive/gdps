// cross-platform includes
#pragma once

#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/socket.h>
#endif // _WIN32