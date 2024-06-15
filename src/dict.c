#include "dict.h"
#include <stdlib.h>
#include <string.h>

struct node *initNode(char *key, void *value) {
    struct node *temp = (struct node*)
    malloc(sizeof(struct node));

    strncpy(temp->key, key, MAX_KEY_SIZE);
    temp->value = value;

    return temp;
}

struct node *insert(struct node *node, char *key, void *value)
{
    // if tree is empty
    if (node == NULL) {
        return initNode(key, value);
    }

    // recursive function omg
    if (strncmp(key, node->key, MAX_KEY_SIZE) > 0) {
        node->left = insert(node->left, key, value);
    } else if (strncmp(key, node->key, MAX_KEY_SIZE) < 0) {
        node->right = insert(node->right, key, value);
    }

    return (struct node*)NULL;
}

struct node *search(struct node *root, const char *key) {
    // the best case
    if (root == NULL || strncmp(root->key, key, MAX_KEY_SIZE) == 0) {
        return root;
    }

    // key is greater
    if (strncmp(root->key, key, MAX_KEY_SIZE) > 0) {
        return search(root->right, key);
    }

    // key is smaller
    return search(root->left, key);
}