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

Btree* BTree_init(char *fname, bool mode);
// void BTree_destroy(Btree* tree);
// void splitChild(Btree* tree, Node* x, int i, Node* y);
void insert_non_full(Btree* tree, Node *node, Data* record);
void insert(Btree* tree, Data* record);
void traverse(Btree* tree, int root);
Data* search(Btree* tree, int key);
Data* search_recursive(Btree* tree, int key, Node* root);
bool removeFromTree(Btree* tree, int key);
void merge(Btree* tree, Node *node, int idx);
void borrowFromNext(Btree* tree, Node *node, int idx);
void borrowFromPrev(Btree* tree, Node *node, int idx);
void fill(Btree* tree, Node *node, int idx);
Data *getSucc(Btree* tree, Node *node, int idx);
Data *getPred(Btree* tree, Node *node, int idx);
bool removeFromNonLeaf(Btree* tree, Node *node, int idx);
bool removeFromLeaf (Btree* tree, Node *node, int idx);
bool removeNode(Btree* tree, Node* node, int k);
int findKey(Node* node, int k);
// void delete_recursive(Btree* tree, int key, Node* node);
// void delete_key(Btree* tree, int k);
#endif