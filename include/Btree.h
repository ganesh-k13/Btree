#include "Node.h"

#ifndef BTREE_H
#define BTREE_H

typedef struct Btree {
	Node *root;
	int t;
}Btree;
#endif

Btree* BTree_init(int t);
void BTree_destroy(Btree* tree);
void splitChild(Btree* tree, Node* x, int i, Node* y);
void insert_non_full(Btree* tree, Node *node, Data* record);
void insert(Btree* tree, Data* record);
void traverse(Btree* tree, Node* root);
Data *search(Node *node, int k);