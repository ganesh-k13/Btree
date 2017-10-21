#include <stdio.h>
#include <stdbool.h>

#ifndef NODE_H
#define NODE_H

typedef struct Node {
	bool isLeaf;
	int n;
	int* keys;
	struct Node** children;
}Node;

#endif

Node* node_init(bool isLeaf, int t);
void node_destroy(Node *node, int t);