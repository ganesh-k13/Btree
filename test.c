#include "include/Node.h"
#include "include/Btree.h"
#include "include/utils.h"

void test_test() {
	Btree* tree = BTree_init("tree.dat");
	
	Data *records = get_data("tmp/small.csv", 50);
	
	insert(tree, &records[0]);
	
	Node* temp = malloc(sizeof(Node));
	read_file(tree, temp, 0);
	
	disp_node(temp);
	
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
