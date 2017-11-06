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
	int pos;
	int n;
	Data records[2*t-1];
	int children[2*t];
}Node;

#endif

Node* node_init(bool isLeaf, int pos);
void disp_node(Node* node);
void node_copy(Node *a, Node *b);
// void node_destroy(Node *node, int t);