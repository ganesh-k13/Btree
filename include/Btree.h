#include <string.h>
#include "Node.h"
#define ALLOC(x) (x*)malloc(sizeof(x))

#ifndef BTREE_H
#define BTREE_H
typedef struct Btree {
	char fname[20];
	FILE *fp;
	int root;
	int next_pos;
}Btree;

Btree* BTree_init(char *fname);
// void BTree_destroy(Btree* tree);
// void splitChild(Btree* tree, Node* x, int i, Node* y);
void insert_non_full(Btree* tree, Node *node, Data* record);
void insert(Btree* tree, Data* record);
// void traverse(Btree* tree, Node* root);
#endif