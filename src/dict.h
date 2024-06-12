#ifndef _DICT_H_
#define _DICT_H_

#define MAX_KEY_SIZE 64

struct node {
    char key[MAX_KEY_SIZE];
    void *value;

    struct node *left, *right;
};

struct node *initNode(char *key, void *value);

struct node *insert(struct node *node, char *key, void *value);

struct node *search(struct node *root, char *key);

#endif // _DICT_H_