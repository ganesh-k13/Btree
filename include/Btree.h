#include "Node.h"

typedef struct Btree {
	Node *root;
	int t;
}Btree;

Btree* BTree_init(int t);
void BTree_destroy(Btree* tree);
void splitChild(Btree* tree, Node* x, int i, Node* y);
void insert_non_full(Btree* tree, Node *node, int key);
void insert(Btree* tree, int key);
void traverse(Btree* tree, Node* root);