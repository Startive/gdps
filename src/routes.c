#include "routes.h"

struct node *routes = NULL;

void *getGJSongInfo_php() {
    printf("Hello from getgjsonginfophp\n");

    return NULL;
}

void *rootRoute() {
    printf("Hello from root route\n");

    return NULL;
}

void addRoutes() {
    routes = insert(routes, "/", rootRoute);
    insert(routes, "/getGJSongInfo.php", getGJSongInfo_php);
}


void runNULL(void *function) {
    ((void(*)())function)();
}