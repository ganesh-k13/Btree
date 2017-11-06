#include "../include/Btree.h"

Btree* BTree_init(char *fname) { 
	
	Btree *tree = ALLOC(Btree);
	strcpy(tree->fname, fname);
	tree->fp = fopen(fname, "a+");
	tree->root = 0;
	tree->next_pos = 0;
	return tree;
}

#if 0
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

#endif

#if 1
// void insert_non_full(Btree* tree, Node *node, Data *record) {
	
	// int i = (node->n)-1;
	
	// if(node->isLeaf) {
		// while(i >=0 && node->records[i].key > record->key) {
			// node->records[i+1] = node->records[i];
			// i--;
		// }
		
		// node->records[i+1] = *record;
		// node->n++;
	// }
	
	// else {
		// while( i>= 0 && node->records[i].key > record->key) {
			// i--;
		// }
		
		// if(node->children[i+1]->n == (2*tree->t-1)) {
			// splitChild(tree, node, i+1, node->children[i+1]);
			
			// if(node->records[i+1].key < record->key) {
				// i++;
			// }
		// }
		
		// insert_non_full(tree, node->children[i+1], record);
	// }
	
// }

void insert(Btree* tree, Data *record) {
	
	if(!(tree->next_pos)) {
		tree->root = tree->next_pos;
		Node *root_node = node_init(true, tree->next_pos);
		root_node->records[0] = *record;
		root_node->n++;
		write_file(tree, root_node, root_node->pos);
		tree->next_pos++;
	}
	
	else {
		if(tree->root->n == (2*tree->t-1)) {
			Node *new_root = node_init(false, tree->next_pos);
			// tree-next_pos++;
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
#endif

#if 0
void traverse(Btree* tree, int root) {
	
	int i;
	Node *temp = malloc(sizeof(Node));
	
	read_file(tree, temp, root);
	
	disp_node(temp);
	
	for(i = 0; i < temp->n; i++) {
		if(!root->isLeaf) {
			traverse(tree, root->children[i]);
		}
		
		printf("%d\n", root->records[i].key);
	}
	
	if(!root->isLeaf) {
		traverse(tree, root->children[i]);
	}
}
#endif