#include "include/Node.h"
#include "include/Btree.h"
#include "include/utils.h"
#include <unistd.h>

void test_search_build(long len, int key) {
    
    struct timespec requestStart, requestEnd;

    Btree* tree = BTree_init("tree.dat", false);
    
    Data *records = get_data("tmp/dataset.csv", len);
    int i;
    
    clock_gettime(CLOCK_REALTIME, &requestStart);
    for(i = 0; i < len; i++) {
        insert(tree, &records[i]);
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    
    
    printf("\nTree built in: %f ms\n", accum_time(requestStart, requestEnd));
    
    clock_gettime(CLOCK_REALTIME, &requestStart);
    Data *res = search(tree, key);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    
    print_function(res);
    
    
    printf("Result found in: %f ms\n\n", accum_time(requestStart, requestEnd));
    // printf("\n%d\n", search(tree, key)->key);
    
    FILE *fout = fopen("meta.dat", "w");
    fwrite(tree, sizeof(Btree), 1, fout);
    close(fout);
    BTree_destroy(tree);
    
    return;
}

void test_build(long len) {
    struct timespec requestStart, requestEnd;

    Btree* tree = BTree_init("tree.dat", false);
    
    Data *records = get_data("tmp/dataset.csv", len);
    int i;
    
    clock_gettime(CLOCK_REALTIME, &requestStart);
    for(i = 0; i < len; i++) {
        insert(tree, &records[i]);
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    
    FILE *fout = fopen("meta.dat", "w");
    fwrite(tree, sizeof(Btree), 1, fout);
    
    close(fout);
    
    BTree_destroy(tree);
    printf("\nTree built in: %f ms\n", accum_time(requestStart, requestEnd));
}

void test_search(int key) {
    struct timespec requestStart, requestEnd;
    
    Btree* tree = BTree_init("tree.dat", true);
    
    clock_gettime(CLOCK_REALTIME, &requestStart);
    Data *res = search(tree, key);
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    
    print_function(res);
    
    BTree_destroy(tree);
    printf("Result found in: %f ms\n\n", accum_time(requestStart, requestEnd));
    
    return;
}

void test_test(long len, int key) {
    
    Btree* tree = BTree_init("tree.dat", true);
    
    // Data *records = get_data("tmp/dataset.csv", len);
    // int i;
    // for(i = 0; i < len; i++) {
        // insert(tree, &records[i]);
    // }
    // traverse(tree, tree->root);
    // FILE *fin = fopen(tree->fp, "rb");
    
    // Node temp;
    
    // fread(&temp, sizeof(Node), 1, fin);
    
    // printf("%d", temp.n);
    
    // traverse(tree, tree->root);
    
    // for(int i = 0; i < len; i++) {
        // search(tree, records[i].key);
    // }
    
    // search(tree, key);
    
	Node n;
	long length = sizeof(n);
	printf("%ld\n", length);
	return;
	
    Data *records = get_data("tmp/dataset.csv", len);
    
    for(int i = 0; i < len; i++) {
        removeFromTree(tree, records[i].key);
        // res = search(tree, key);
        // print_function(res);
    }
    
    
	BTree_destroy(tree);
    
    return;
}

void test_delete(int key) {
    struct timespec requestStart, requestEnd;
    
    Btree* tree = BTree_init("tree.dat", true);
    
    printf("Node to delete:\n");
    Data *res = search(tree, key);
    print_function(res);
    
	clock_gettime(CLOCK_REALTIME, &requestStart);
	bool isDelete = removeFromTree(tree, key);
	clock_gettime(CLOCK_REALTIME, &requestEnd);
	
    if(isDelete) {
        printf("Delete successful\n");
    }
	  
    else {
        printf("Delete unsuccessful\n");
    }
    printf("Result found in: %f ms\n\n", accum_time(requestStart, requestEnd));
	BTree_destroy(tree);
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
