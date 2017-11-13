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

void removeNode(Node *node, int k, int t);

// A function to remove the key present in idx-th position in
// this node which is a leaf
void removeFromLeaf(Node *node, int idx, int t);

// A function to remove the key present in idx-th position in
// this node which is a non-leaf node
void removeFromNonLeaf(Node *node, int idx, int t);

// A function to get the predecessor of the key- where the key
// is present in the idx-th position in the node
Data* getPred(Node *node, int idx);

// A function to get the successor of the key- where the key
// is present in the idx-th position in the node
Data* getSucc(Node *node, int idx);

// A function to fill up the child node present in the idx-th
// position in the C[] array if that child has less than t-1 keys
void fill(Node *node, int idx, int t);

// A function to borrow a key from the C[idx-1]-th node and place
// it in C[idx]th node
void borrowFromPrev(Node *node, int idx);

// A function to borrow a key from the C[idx+1]-th node and place it
// in C[idx]th node
void borrowFromNext(Node *node, int idx);

// A function to merge idx-th child of the node with (idx+1)th child of
// the node
void merge(Node *node, int idx, int t);

int findKey(Node *node, int k);