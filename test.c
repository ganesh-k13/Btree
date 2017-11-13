#include "include/Node.h"
#include "include/Btree.h"
#include "include/utils.h"

void test_build(long len) {
	struct timespec requestStart, requestEnd;
	
	clock_gettime(CLOCK_REALTIME, &requestStart);
	build(len);
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	// traverse(tree, tree->root);
	printf("\nTree built in: %f ms\n", accum_time(requestStart, requestEnd));
}

void test_search(long len, int key) {
	
	struct timespec requestStart, requestEnd;
	Btree* tree = build(len);
	// traverse(tree, tree->root);
	
	clock_gettime(CLOCK_REALTIME, &requestStart);
	Data *res = search(tree->root, key);
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
	print_function(res);
	
	printf("\nTree built in: %f ms\n", accum_time(requestStart, requestEnd));
}

void test_delete(long len, int key) {
	Btree* tree = build(len);
	
	print_function(search(tree->root, key));
	removeNode(tree->root, key, tree->t);
	print_function(search(tree->root, key));
	
}

void test_test(long len, int key) {
	Btree* tree = BTree_init(3);
	int i;
	
	Data *records;
	
	records = get_data("tmp/small.csv", len);
	
	// printf("%d\n", records[0]->key);
	
	for(i = 0; i < len; i++) {
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
    
    if(!strcmp(args[0], "-b")) {
        test_build(strtol(args[1], ptr, 10));
    }
    
    if(!strcmp(args[0], "-s")) {
        test_search(strtol(args[1], ptr, 10), strtol(args[2], ptr, 10));
    }
    
    if(!strcmp(args[0], "-d")) {
        test_delete(strtol(args[1], ptr, 10), strtol(args[2], ptr, 10));
    }
    
    if(!strcmp(args[0], "-t")) {
        test_test(strtol(args[1], ptr, 10), strtol(args[2], ptr, 10));
    }
}
int main(int argl, char** argv) {
    
    run_tests(argv + 1, argl - 1);
    
    return 0;
}
