#ifndef _ROUTES_H_
#define _ROUTES_H_

#include "dict.h"
#include "include.h"

extern struct node *routes; // active and allocated struct containg all the routes

void addRoutes();

void runNULL(void *function); // runs a null function thats declared as: "void *function;" 

void *getGJSongInfo_php();
void *rootRoute();

#endif // _ROUTES_H_