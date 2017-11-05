#include "../include/Node.h"

Node* node_init(bool isLeaf, int t) {
	Node *node = malloc(sizeof(Node));
	node->isLeaf = isLeaf;
	node->n = 0;
	node->records = malloc(sizeof(Data) * (2 * t - 1));
	node->children = malloc(sizeof(Node*) * (2 * t));
	
	return node;
}

void node_destroy(Node *node, int t) {
	
	if(!node)
		return;
	
	int i;
	for(i = 0; i < 2*t; i++) {
		node_destroy(node->children[i], t);
	}
	
	free(node->records);
	free(node->children);
	free(node);
}
