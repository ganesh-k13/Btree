#include "include/Node.h"
#include "include/Btree.h"
#include "include/utils.h"
#include <unistd.h>

void test_test() {
	Btree* tree = BTree_init("tree.dat");
	
	Data *records = get_data("tmp/small.csv", 50);
	
	for(int i = 0; i < 40; i++) {
		insert(tree, &records[i]);
	}
	// traverse(tree, 0);
	// FILE *fin = fopen(tree->fp, "rb");
	
	// Node temp;
	
	// fread(&temp, sizeof(Node), 1, fin);
	
	// printf("%d", temp.n);
	
	// traverse(tree, 0);
	
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
