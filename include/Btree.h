#include "Node.h"

typedef struct Btree {
	Node *root;
	int t;
}Btree;

Btree* BTree_init(int t);
void BTree_destroy(Btree* tree);
void splitChild(Btree* tree, Node* x, int i, Node* y);
void insert_non_full(Btree* tree, Node *node, Data* record);
void insert(Btree* tree, Data* record);
void traverse(Btree* tree, Node* root);