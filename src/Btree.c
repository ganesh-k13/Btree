#include "../include/Btree.h"

Btree* BTree_init(int t) { 
	
	Btree *tree = malloc(sizeof(Btree));
	tree->root = NULL; 
	tree->t = t;
	return tree;
}

void BTree_destroy(Btree* tree) {
	node_destroy(tree->root, tree->t);
	free(tree);
}

void splitChild(Btree* tree, Node* x, int i, Node* y) {
	Node* z = node_init(y->isLeaf, tree->t);
	
	z->n = (tree->t) - 1;
	
	int j;
	for(j = 0; j < (tree->t)-1; j++) {
		z->records[j] = y->records[j+tree->t];
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
		x->records[j+1] = x->records[j];
	}
	
	x->records[i] = y->records[tree->t - 1];
	
	x->n++;
}

void insert_non_full(Btree* tree, Node *node, Data *record) {
	
	int i = (node->n)-1;
	
	if(node->isLeaf) {
		while(i >=0 && node->records[i].key > record->key) {
			node->records[i+1] = node->records[i];
			i--;
		}
		
		node->records[i+1] = *record;
		node->n++;
	}
	
	else {
		while( i>= 0 && node->records[i].key > record->key) {
			i--;
		}
		
		if(node->children[i+1]->n == (2*tree->t-1)) {
			splitChild(tree, node, i+1, node->children[i+1]);
			
			if(node->records[i+1].key < record->key) {
				i++;
			}
		}
		
		insert_non_full(tree, node->children[i+1], record);
	}
	
}

void insert(Btree* tree, Data *record) {
	
	if(!(tree->root)) {
		tree->root = node_init(true, tree->t);
		tree->root->records[0] = *record;
		tree->root->n++;
	}
	
	else {
		if(tree->root->n == (2*tree->t-1)) {
			Node *new_root = node_init(false, tree->t);
			new_root->children[0] = tree->root;
			
			splitChild(tree, new_root, 0, tree->root);
			
			int i = 0;
			if(new_root->records[0].key < record->key)
				i++;
			
			insert_non_full(tree, new_root->children[i], record);
			
			tree->root = new_root;
		}
		
		else {
			insert_non_full(tree, tree->root, record);
		}
	}
	
}

void traverse(Btree* tree, Node* root) {
	
	int i;
	for(i = 0; i < root->n; i++) {
		if(!root->isLeaf) {
			traverse(tree, root->children[i]);
		}
		
		printf("%d\n", root->records[i].key);
	}
	
	if(!root->isLeaf) {
		traverse(tree, root->children[i]);
	}
}

Data *search(Node *node, int k) {
    // Find the first key greater than or equal to k
	
    int i = 0;
    while (i < node->n && k > node->records[i].key) {
		i++;
	}
	
    // If the found key is equal to k, return this node
    if (node->records[i].key == k) {
        return &node->records[i];
	}
 
    // If key is not found here and this is a leaf node
    if (node->isLeaf == true) {
        return NULL;
	}
    // Go to the appropriate child
    return search(node->children[i], k);
}
