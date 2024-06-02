#include "routes.h"
#include "include.h"

// Thank you geeksforgeeks, legendary for this algorithm example for me to use
// https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
// Will probably change soon if i need to

struct node *newNode(char *item) {
    struct node *temp =
        (struct node *)malloc(sizeof(struct node));
    
    strncpy(temp->key, item, MAX_ROUTE_SIZE - 1);
    temp->left = temp->right = NULL;

    return temp;
}

struct node *insert(struct node* node, char *key) {
    // gen new node if node is null
    if (node == NULL)
        return newNode(key);

    // recur down the list
    if (strncmp(key, node->key, MAX_ROUTE_SIZE - 1) < 0)
        node->left = insert(node->left, key);
    else if (strncmp(key, node->key, MAX_ROUTE_SIZE - 1) > 0)
        node->right = insert(node->right, key);

    return node;
}

struct node *search(struct node *root, char *key) {
    // best case, if root is null or the key is at root
    if ((root == NULL) || (strncmp(root->key, key, MAX_ROUTE_SIZE - 1) == 0))
        return root;

    // key is greater then the root key
    if (strncmp(root->key, key, MAX_ROUTE_SIZE - 1) < 0)
        return search(root->right, key);

    return search(root->left, key);
}

void addRoutes(struct node *root) {
    root = insert(root, "/hello");
    insert(root, "eskibidi rizz");

    if (search(root, "/haello") == NULL)
        puts("could not found");
    else
        puts("found");
}