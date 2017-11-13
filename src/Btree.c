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

int findKey(Node *node, int k) {
    int idx=0;
    while (idx < node->n && node->records[idx].key < k)
        ++idx;
    return idx;
}
 
// A function to remove the key k from the sub-tree rooted with this node
void removeNode(Node *node, int k, int t) {
    int idx = findKey(node, k);
 
    // The key to be removed is present in this node
    if (idx < node->n && node->records[idx].key == k) {
 
        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (node->isLeaf)
            removeFromLeaf(node, idx, t);
        else
            removeFromNonLeaf(node, idx, t);
    }
    else {
 
        // If this node is a leaf node, then the key is not present in tree
        if (node->isLeaf) {
            return;
        }
 
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==node->n)? true : false );
 
        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (node->children[idx]->n < t)
            fill(node, idx, t);
 
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > node->n)
            removeNode(node->children[idx-1], k, t);
        else
            removeNode(node->children[idx], k, t);
    }
    return;
}
 
// A function to remove the idx-th key from this node - which is a leaf node
void removeFromLeaf (Node *node, int idx, int t) {
 
    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i < node->n; ++i)
        node->records[i-1] = node->records[i];
 
    // Reduce the count of keys
    node->n--;
 
    return;
}
 
// A function to remove the idx-th key from this node - which is a non-leaf node
void removeFromNonLeaf(Node *node, int idx, int t) {
 
    int k = node->records[idx].key;
 
    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (node->children[idx]->n >= t) {
        Data* pred = getPred(node, idx);
        node->records[idx] = *pred;
        removeNode(node->children[idx], pred->key, t);
    }
 
    // If the child C[idx] has less that t keys, examine C[idx+1].
    // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[idx+1]
    // Replace k by succ
    // Recursively delete succ in C[idx+1]
    else if  (node->children[idx+1]->n >= t) {
        Data* succ = getSucc(node, idx);
        node->records[idx] = *succ;
        removeNode(node->children[idx+1], succ->key, t);
    }
 
    // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else {
        merge(node, idx, t);
        removeNode(node->children[idx], k, t);
    }
    return;
}
 
// A function to get predecessor of node->records[idx].key
Data *getPred(Node *node, int idx) {
    // Keep moving to the right most node until we reach a leaf
    Node *cur=node->children[idx];
    while (!cur->isLeaf)
        cur = cur->children[cur->n];
 
    // Return the last key of the leaf
    return &cur->records[cur->n-1];
}
 
Data *getSucc(Node *node, int idx) {
 
    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    Node *cur = node->children[idx+1];
    while (!cur->isLeaf)
        cur = cur->children[0];
 
    // Return the first key of the leaf
    return &cur->records[0];
}
 
// A function to fill child C[idx] which has less than t-1 keys
void fill(Node *node, int idx, int t) {
 
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && node->children[idx-1]->n>=t)
        borrowFromPrev(node, idx);
 
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (idx!=node->n && node->children[idx+1]->n>=t)
        borrowFromNext(node, idx);
 
    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else {
        if (idx != node->n)
            merge(node, idx, t);
        else
            merge(node, idx-1, t);
    }
    return;
}
 
// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void borrowFromPrev(Node *node, int idx) {
 
    Node *child=node->children[idx];
    Node *sibling=node->children[idx-1];
 
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
 
    return;
}
 
// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void borrowFromNext(Node *node, int idx) {
 
	Node *child=node->children[idx];
    Node *sibling=node->children[idx+1];
 
    // node->records[idx].key is inserted as the last key in C[idx]
    child->records[(child->n)] = node->records[idx];
 
    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->isLeaf))
        child->children[(child->n)+1] = sibling->children[0];
 
    //The first key from sibling is inserted into node->records[idx].key
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
 
    return;
}
 
// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void merge(Node *node, int idx, int t) {
    Node *child = node->children[idx];
    Node *sibling = node->children[idx+1];
 
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
    // to fill the gap created by moving node->records[idx].key to C[idx]
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
    free(sibling);
    return;
}
 