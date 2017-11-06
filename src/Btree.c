#include "../include/Btree.h"

Btree* BTree_init(char *fname) { 
	
	Btree *tree = ALLOC(Btree);
	strcpy(tree->fname, fname);
	tree->fp = fopen(fname, "r+");
	tree->root = 0;
	tree->next_pos = 0;
	return tree;
}

#if 0
void BTree_destroy(Btree* tree) {
	node_destroy(tree->root, tree->t);
	free(tree);
}


#endif

#if 1
void splitChild(Btree* tree, Node* x, int i, Node* y) {
	Node* z = node_init(y->isLeaf, tree->next_pos);
	tree->next_pos++;
	z->n = t - 1;
	
	int j;
	for(j = 0; j < t-1; j++) {
		z->records[j] = y->records[j+t];
	}
	
	if(!y->isLeaf) {
		for(j = 0; j < t; j++) {
			z->children[j] = y->children[j+t];
		}
	}
	
	y->n = t - 1;
	
	for(j = x->n; j >= i+1; j--) {
		x->children[j+1] = x->children[j];
	}
	
	x->children[i+1] = z->pos;
	
	for(j = x->n-1; j >= i; j--) {
		x->records[j+1] = x->records[j];
	}
	
	x->records[i] = y->records[t - 1];
	
	x->n++;
	
	// printf("%d %d %d\n", x->pos, y->pos, z->pos);
	
	write_file(tree, x, x->pos);
	write_file(tree, y, y->pos);
	write_file(tree, z, z->pos);
	
	
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
		// printf("N:%d\n", node->n);
		write_file(tree, node, node->pos);
		
	}
	
	else {
		while( i>= 0 && node->records[i].key > record->key) {
			i--;
		}
		
		Node *c_i = malloc(sizeof(Node));
		
		read_file(tree, c_i, node->children[i+1]);
		
		if(c_i->n == (2*t-1)) {
			splitChild(tree, node, i+1, c_i);
			
			if(node->records[i+1].key < record->key) {
				i++;
			}
		}
		
		insert_non_full(tree, c_i, record);
	}
	
}

void insert(Btree* tree, Data *record) {
	
	if(!(tree->next_pos)) {
		tree->root = tree->next_pos;
		Node *root_node = node_init(true, tree->next_pos);
		tree->next_pos++;
		root_node->records[0] = *record;
		root_node->n++;
		write_file(tree, root_node, root_node->pos);
		
	}
	
	else {
		Node *root = malloc(sizeof(Node));
		read_file(tree, root, tree->root);
		if(root->n == (2*t-1)) {
			Node *new_root = node_init(false, tree->next_pos);
			tree->next_pos++;
			new_root->children[0] = tree->root;
			// printf("n:%d", new_root->children[0]);
			splitChild(tree, new_root, 0, root);
			
			int i = 0;
			if(new_root->records[0].key < record->key)
				i++;
			
			Node *c_i = malloc(sizeof(Node));
			
			read_file(tree, c_i, new_root->children[i]);
			
			insert_non_full(tree, c_i, record);
			
			tree->root = new_root->pos;
			// disp_node(new_root);
		}
		
		else {
			
			insert_non_full(tree, root, record);
			// disp_node(root);
		}
		
		
	}
	
}

#endif

#if 1
void traverse(Btree* tree, int root) {
	
	
	if(-1 == root) {
		
		return;
	}
	
	Node *to_print = malloc(sizeof(Node));
	
	read_file(tree, to_print, root);
	
	disp_node(to_print);
	
	for(int i = 0; i < 2*t; i++) {
		traverse(tree, to_print->children[i]);
	}
	
}
#endif

Data* search_recursive(Btree* tree, int key, Node* root) {
	int i = 0;
	
	while(i < root->n && key > root->records[i].key)
		i++;
	
	if(i < root->n && key == root->records[i].key)
		return &root->records[i];
	
	else if(root->isLeaf)
		return NULL;
	else {
		Node* c_i = malloc(sizeof(Node));
		read_file(tree, c_i, root->children[i]);
		return search_recursive(tree, key, c_i);
	}
}

Data* search(Btree* tree, int key) {
	Node* root = malloc(sizeof(Node));
	read_file(tree, root, tree->root);
	
	Data* res = search_recursive(tree, key, root);
	
	if(!res) {
		printf("Not Found\n");
	}
	
	else {
		printf("Res: %d\n", res->key);
	}
	
	
}