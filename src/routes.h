#ifndef _ROUTES_H_
#define _ROUTES_H_

#define MAX_ROUTE_SIZE 32

struct node {
    char key[MAX_ROUTE_SIZE];
    struct node *left, *right;
};

struct node *newNode(char *item);

struct node *insert(struct node *node, char *key);
#define addRoute insert

struct node *search(struct node *root, char *key);

void addRoutes(struct node *root);

#endif // _ROUTES_H_