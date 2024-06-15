#ifndef _ROUTES_H_
#define _ROUTES_H_

#include "dict.h"
#include "include.h"
#include "response.h"

extern struct node *routes; // active and allocated struct containg all the routes

void addRoutes();
char * getFileContents(const char *fileName);

void getGJSongInfo_php(Response *response);
void downloadGJLevel22_php(Response *response);
void Page404(Response *response);
void rootRoute(Response *response);

#endif // _ROUTES_H_