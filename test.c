#include "include/Node.h"
#include "include/Btree.h"
#include "include/utils.h"

void test_build() {
	
}

void test_search() {
	
}

void test_search_build() {
	
}

void test_delete() {
	
}

void test_test(long len, int key) {
	Btree* tree = BTree_init(3);
	int i;
	
	Data *records;
	
	records = get_data("tmp/small.csv", len);
	
	// printf("%d\n", records[0]->key);
	
	for(i = 0; i < 50; i++) {
		insert(tree, &records[i]);
	}
	
	traverse(tree, tree->root);
	
	// BTree_destroy(tree);
	
	
	return;
}

void verbose() {
	
}

void run_tests(char** args, int no_of_args) {
    int i = 0;
    char ptr[10];
    
    if(no_of_args == 0) {
        verbose();
    }
    
    if(!strcmp(args[0], "-sb")) {
        test_search_build(strtol(args[1], ptr, 10), strtol(args[2], ptr, 10));  
    }
    
    if(!strcmp(args[0], "-b")) {
        test_build(strtol(args[1], ptr, 10));
    }
    
    if(!strcmp(args[0], "-s")) {
        test_search(strtol(args[1], ptr, 10));
    }
    
    if(!strcmp(args[0], "-d")) {
        test_delete(strtol(args[1], ptr, 10));
    }
    
    if(!strcmp(args[0], "-t")) {
        test_test(strtol(args[1], ptr, 10), strtol(args[2], ptr, 10));
    }
}
int main(int argl, char** argv) {
    
    run_tests(argv + 1, argl - 1);
    
    return 0;
}
