#include "../include/Btree.h"
//132
Btree* BTree_init(char *fname, bool mode) { 
	
	//Flase: Create new
	Btree *tree = ALLOC(Btree);
	if(!mode) {
		strcpy(tree->fname, fname);
		tree->fp = fopen(fname, "r+");
		tree->root = 0;
		tree->next_pos = 0;
		return tree;
	}

	//True: Use existing
	
	FILE *fin = fopen("meta.dat", "r");
	fread(tree, sizeof(Btree), 1, fin);
	close(fin);
	tree->fp = fopen(fname, "r+");
	return tree;
}

#if 1
void BTree_destroy(Btree* tree) {
	close(tree->fp);
	free(tree);
}


#endif

#if 1
void splitChild(Btree* tree, Node* x, int i, Node* y) {
	Node* z = malloc(sizeof(Node)); node_init(z, y->isLeaf, tree);
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
	
	
	write_file(tree, x, x->pos);
	write_file(tree, y, y->pos);
	write_file(tree, z, z->pos);
	free(z);
	
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
		write_file(tree, node, node->pos);
		
	}
	
	else {
		while( i >= 0 && node->records[i].key > record->key) {
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
		read_file(tree, c_i, node->children[i+1]);
		insert_non_full(tree, c_i, record);
		free(c_i);
	}
	
}

void insert(Btree* tree, Data *record) {
	
	if(!(tree->next_pos)) {
		tree->root = tree->next_pos;
		Node *root_node = malloc(sizeof(Node)); node_init(root_node, true, tree);
		root_node->records[0] = *record;
		root_node->n++;
		write_file(tree, root_node, root_node->pos);
		free(root_node);
	}
	
	else {
		Node *root = malloc(sizeof(Node));
		read_file(tree, root, tree->root);
		if(root->n == (2*t-1)) {
			
			Node *new_root = malloc(sizeof(Node)); node_init(new_root, false, tree);
			new_root->children[0] = tree->root;
			
			splitChild(tree, new_root, 0, root);
			
			int i = 0;
			if(new_root->records[0].key < record->key) {
				i++;
			}
			
			Node *c_i = malloc(sizeof(Node));
			read_file(tree, c_i, new_root->children[i]);
			insert_non_full(tree, c_i, record);
			
			tree->root = new_root->pos;
			
			write_file(tree, root, root->pos);
			
			free(new_root);
		}
		
		else {
			
			insert_non_full(tree, root, record);
			
		}
		
		free(root);
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
	
	free(to_print);
	
}
#endif

Data* search_recursive(Btree* tree, int key, Node* root) {
	int i = 0;
	
	while(i < root->n && key > root->records[i].key)
		i++;
	
	
	if(i < root->n && key == root->records[i].key)
		return &root->records[i];
	
	
	else if(root->isLeaf) {
		return NULL;
	}
	else {
		Node* c_i = malloc(sizeof(Node));
		read_file(tree, c_i, root->children[i]);
		return search_recursive(tree, key, c_i);
	}
}

Data* search(Btree* tree, int key) {
	
	Node* root = malloc(sizeof(Node));
	read_file(tree, root, tree->root);
	
	return search_recursive(tree, key, root);
	 
}

int findKey(Node* node, int k) {
    int idx=0;
    while (idx < node->n && node->records[idx].key < k)
        ++idx;
    return idx;
}

bool removeNode(Btree* tree, Node* node, int k) {
    int idx = findKey(node, k);
	bool res;
    // The key to be removed is present in this node
    if (idx < node->n && node->records[idx].key == k) {
 
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (node->isLeaf)
            res = removeFromLeaf(tree, node, idx);
        else
            res = removeFromNonLeaf(tree, node, idx);
		
		write_file(tree, node, node->pos);
    }
    else {
 
        // If this node is a leaf node, then the key is not present in tree
        if (node->isLeaf) {
            printf("Not Present!\n");
            return false;
        }
 
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==node->n)? true : false );
 
        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
		
		Node *c_i = malloc(sizeof(Node));
		read_file(tree, c_i, node->children[idx]);
		
        if (c_i->n < t)
            fill(tree, node, idx);
 
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > node->n) {
			Node *sibling = malloc(sizeof(Node));
			read_file(tree, sibling, node->children[idx-1]);
            removeNode(tree, sibling, k);
			write_file(tree, sibling, sibling->pos);
		}
        else
            removeNode(tree, c_i, k);
		
		write_file(tree, c_i, c_i->pos);
		res = true;
    }
    return res;
}
 
// A function to remove the idx-th key from this node - which is a leaf node
bool removeFromLeaf (Btree* tree, Node *node, int idx) {
 
    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i<node->n; ++i)
        node->records[i-1] = node->records[i];
 
    // Reduce the count of keys
    node->n--;
 
    return true;
}
 
// A function to remove the idx-th key from this node - which is a non-leaf node
bool removeFromNonLeaf(Btree* tree, Node *node, int idx) {
 
    int k = node->records[idx].key;
	bool res;
	
	Node *child = malloc(sizeof(Node));
	Node *sibling = malloc(sizeof(Node));
	
	read_file(tree, child, node->children[idx]);
	read_file(tree, sibling, node->children[idx-1]);
 
    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (child->n >= t) {
        Data *pred = getPred(tree, node, idx);
        node->records[idx] = *pred;
        res = removeNode(tree, child, pred);
    }
 
    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if  (sibling->n >= t)
    {
        Data *succ = getSucc(tree, node, idx);
        node->records[idx] = *succ;
        res = removeNode(tree, sibling, succ);
    }
 
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else {
        merge(tree, node, idx);
        res = removeNode(tree, child, k);
    }
	
	write_file(tree, child, child->pos);
	write_file(tree, sibling, sibling->pos);
	
    return res;
}
 
// A function to get predecessor of keys[idx]
Data *getPred(Btree* tree, Node *node, int idx) {
    // Keep moving to the right most node until we reach a leaf
	
	Node *curr = malloc(sizeof(Node));
	read_file(tree, curr, node->children[idx]);
    while (!curr->isLeaf)
		read_file(tree, curr, curr->children[curr->n]);
        
    // Return the last key of the leaf
    return &(curr->records[curr->n-1]);
}
 
Data *getSucc(Btree* tree, Node *node, int idx) {
 
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
	Node *curr = malloc(sizeof(Node));
	read_file(tree, curr, node->children[idx]);
    while (!curr->isLeaf)
        read_file(tree, curr, curr->children[0]);
 
    // Return the first key of the leaf
    return &(curr->records[0]);
}
 
// A function to fill child C[idx] which has less than t-1 keys
void fill(Btree* tree, Node *node, int idx) {
 
	Node *c_prev = malloc(sizeof(Node));
	Node *c_succ = malloc(sizeof(Node));
	read_file(tree, c_prev, node->children[idx-1]);
	read_file(tree, c_succ, node->children[idx+1]);
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && c_prev->n>=t)
        borrowFromPrev(tree, node, idx);
 
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx!=node->n && c_succ->n>=t)
        borrowFromNext(tree, node, idx);
 
    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else {
        if (idx != node->n)
            merge(tree, node, idx);
        else
            merge(tree, node, idx-1);
    }
    return;
}
 
// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void borrowFromPrev(Btree* tree, Node *node, int idx) {
	Node *child = malloc(sizeof(Node));
	Node *sibling = malloc(sizeof(Node));
	
	read_file(tree, child, node->children[idx]);
	read_file(tree, sibling, node->children[idx-1]);
	
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key
 
    // Moving all key in C[idx] one step ahead
    for (int i=child->n-1; i>=0; --i)
        child->records[i+1] = child->records[i];
 
    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->isLeaf) {
        for(int i=child->n; i>=0; --i)
            child->children[i+1] = child->children[i];
    }
 
    // Setting child's first key equal to keys[idx-1] from the current node
    child->records[0] = node->records[idx-1];
 
    // Moving sibling's last child as C[idx]'s first child
    if (!node->isLeaf)
        child->children[0] = sibling->children[sibling->n];
 
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    node->records[idx-1] = sibling->records[sibling->n-1];
 
    child->n += 1;
    sibling->n -= 1;
	
	write_file(tree, node, node->pos);
	write_file(tree, child, child->pos);
	write_file(tree, sibling, sibling->pos);
	
    return;
}
 
// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void borrowFromNext(Btree* tree, Node *node, int idx) {
 
	Node *child = malloc(sizeof(Node));
	Node *sibling = malloc(sizeof(Node));
	
	read_file(tree, child, node->children[idx]);
	read_file(tree, sibling, node->children[idx+1]);
 
    // keys[idx] is inserted as the last key in C[idx]
    child->records[(child->n)] = node->records[idx];
 
    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->isLeaf))
        child->children[(child->n)+1] = sibling->children[0];
 
    //The first key from sibling is inserted into keys[idx]
    node->records[idx] = sibling->records[0];
 
    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->n; ++i)
        sibling->records[i-1] = sibling->records[i];
 
    // Moving the child pointers one step behind
    if (!sibling->isLeaf) {
        for(int i=1; i<=sibling->n; ++i)
            sibling->children[i-1] = sibling->children[i];
    }
 
    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;
	
	write_file(tree, node, node->pos);
	write_file(tree, child, child->pos);
	write_file(tree, sibling, sibling->pos);
	
    return;
}
 
// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void merge(Btree* tree, Node *node, int idx) {
    
	Node *child = malloc(sizeof(Node));
	Node *sibling = malloc(sizeof(Node));
	
	read_file(tree, child, node->children[idx]);
	read_file(tree, sibling, node->children[idx+1]);
 
    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->records[t-1] = node->records[idx];
 
    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->n; ++i)
        child->records[i+t] = sibling->records[i];
 
    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->isLeaf) {
        for(int i=0; i<=sibling->n; ++i)
            child->children[i+t] = sibling->children[i];
    }
 
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=idx+1; i<node->n; ++i)
        node->records[i-1] = node->records[i];
 
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=node->n; ++i)
        node->children[i-1] = node->children[i];
 
    // Updating the key count of child and the current node
    child->n += sibling->n+1;
    node->n--;
 
    // Freeing the memory occupied by sibling
    write_file(tree, node, node->pos);
	write_file(tree, child, child->pos);
	write_file(tree, sibling, sibling->pos);
    return;
}

bool removeFromTree(Btree* tree, int key) {
	
	Node *root = malloc(sizeof(Node));
	read_file(tree, root, tree->root);
	return removeNode(tree, root, key);
	
}