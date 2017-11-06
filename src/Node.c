#include "../include/Node.h"

#if 1
Node* node_init(bool isLeaf, int pos) {
	Node *node = malloc(sizeof(Node));
	node->isLeaf = isLeaf;
	node->n = 0;
	node->pos = pos;
	for(int i = 0; i < 2*t; i++) {
		node->children[i] = -1;
	}
	
	return node;
}
#endif

void node_copy(Node *a, Node *b) {
	a->isLeaf = b->isLeaf;
	a->pos = b->pos;
	a->n = b->n;
	int i;
	for(i = 0; i < (2*t-1); i++) {
		a->records[i] = b->records[i];
		a->children[i] = b->children[i];
	}
	a->children[i] = b->children[i];
	
}

#if 0
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
#endif

void disp_node(Node* node) {
	
	printf("Keys: \n");
	for(int i = 0; i < node->n; i++) {
		printf("%d ", node->records[i].key);
	}
	
	printf("\n");
	printf("links\n");
	for(int i = 0; i < node->n; i++) {
		printf("%d ", node->children[i]);
	}
	printf("\n");
}