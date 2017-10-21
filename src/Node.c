#include "../include/Node.h"

Node* node_init(bool isLeaf, int t) {
	Node *node = malloc(sizeof(Node));
	node->isLeaf = isLeaf;
	node->n = 0;
	node->keys = malloc(sizeof(int) * (2 * t - 1));
	node->children = malloc(sizeof(Node*) * (2 * t));
	
	return node;
}

