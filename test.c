#include "include/Node.h"
#include "include/Btree.h"
#include "include/utils.h"
#include <unistd.h>

void test_test() {
	Btree* tree = BTree_init("tree.dat");
	
	int len = 22;
	Data *records = get_data("tmp/dataset.csv", len);
	int i;
	for(i = 0; i < len; i++) {
		insert(tree, &records[i]);
	}
	insert(tree, &records[i-1]);
	// traverse(tree, 0);
	// FILE *fin = fopen(tree->fp, "rb");
	
	// Node temp;
	
	// fread(&temp, sizeof(Node), 1, fin);
	
	// printf("%d", temp.n);
	
	traverse(tree, tree->root);
	
	for(int i = 0; i < len; i++) {
		search(tree, records[i].key);
	}
	
	return;
}

void verbose() {
	
}

void run_tests(char** args, int no_of_args) {
    int i = 0;
	
	if(no_of_args == 0) {
		verbose();
	}
	
    if(!strcmp(args[0], "-t")) {
        test_test();
    }
}

int main(int argl, char** argv) {
    
    run_tests(argv + 1, argl - 1);
    
    return 0;
}
