// cross-platform includes
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/socket.h>
#endif // _WIN32