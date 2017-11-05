#include <stdio.h>
#include <stdbool.h>

#ifndef NODE_H
#define NODE_H

typedef struct Data {
	int key;
	char country[5];
	char status[10];
	int num1;
	int num2;
}Data;

typedef struct Node {
	bool isLeaf;
	int n;
	Data* records;
	struct Node** children;
}Node;

#endif

Node* node_init(bool isLeaf, int t);
void node_destroy(Node *node, int t);