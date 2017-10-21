#include "include/Node.h"
#include "include/Btree.h"
#include "include/utils.h"

void test_test() {
	Btree* tree = BTree_init(3);
	
	insert(tree, 5);
	insert(tree, 6);
	insert(tree, 7);
	insert(tree, 8);
	insert(tree, 9);
	insert(tree, 10);
	insert(tree, 4);
	insert(tree, 3);
	insert(tree, 2);
	insert(tree, 1);
	insert(tree, 0);
	insert(tree, 99);
	
	traverse(tree, tree->root);
	
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
