#include "../include/Btree.h"

Btree* BTree_init(int t) { 
	
	Btree *tree = malloc(sizeof(Btree));
	tree->root = NULL; 
	tree->t = t;
	return tree;
}

void splitChild(Btree* tree, Node* x, int i, Node* y) {
	Node* z = node_init(y->isLeaf, tree->t);
	
	z->n = (tree->t) - 1;
	
	int j;
	for(j = 0; j < (tree->t)-1; j++) {
		z->keys[j] = y->keys[j+tree->t];
	}
	
	if(!y->isLeaf) {
		for(j = 0; j < tree->t; j++) {
			z->children[j] = y->children[j+tree->t];
		}
	}
	
	y->n = tree->t - 1;
	
	for(j = x->n; j >= i+1; j--) {
		x->children[j+1] = x->children[j];
	}
	
	x->children[i+1] = z;
	
	for(j = x->n-1; j >= i; j--) {
		x->keys[j+1] = x->keys[j];
	}
	
	x->keys[i] = y->keys[tree->t - 1];
	
	x->n++;
}

void insert_non_full(Btree* tree, Node *node, int key) {
	
	int i = (node->n)-1;
	
	if(node->isLeaf) {
		while(i >=0 && node->keys[i] > key) {
			node->keys[i+1] = node->keys[i];
			i--;
		}
		
		node->keys[i+1] = key;
		node->n++;
	}
	
	else {
		while( i>= 0 && node->keys[i] > key) {
			i--;
		}
		
		if(node->children[i+1]->n == (2*tree->t-1)) {
			splitChild(tree, node, i+1, node->children[i+1]);
			
			if(node->keys[i+1] < key) {
				i++;
			}
		}
		
		insert_non_full(tree, node->children[i+1], key);
	}
	
}

void insert(Btree* tree, int key) {
	
	if(!(tree->root)) {
		tree->root = node_init(true, tree->t);
		tree->root->keys[0] = key;
		tree->root->n++;
	}
	
	else {
		if(tree->root->n == (2*tree->t-1)) {
			Node *new_root = node_init(false, tree->t);
			new_root->children[0] = tree->root;
			
			splitChild(tree, new_root, 0, tree->root);
			
			int i = 0;
			if(new_root->keys[0] < key)
				i++;
			
			insert_non_full(tree, new_root->children[i], key);
			
			tree->root = new_root;
		}
		
		else {
			insert_non_full(tree, tree->root, key);
		}
	}
	
}

void traverse(Btree* tree, Node* root) {
	
	int i;
	for(i = 0; i < root->n; i++) {
		if(!root->isLeaf) {
			traverse(tree, root->children[i]);
		}
		
		printf("%d\n", root->keys[i]);
	}
	
	if(!root->isLeaf) {
		traverse(tree, root->children[i]);
	}
}
