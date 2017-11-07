// specify the value of t during compilation

/*
$ gcc -Dt=3 -c 1_struct.c
$ gcc -Dt=3 -c 1_test.c
$ gcc 1_struct.o 1_test.o
*/


#include <stdio.h>
#include <stdlib.h>
#include "1_struct.h"

int main()
{
//	printf("t : %d\n", t);
//	printf("size node : %lu\n", sizeof(node_t));
//	printf("size tree : %lu\n", sizeof(treenode_t));

	tree_t *tt;
	tt = create_tree("mytree.dat");

	// for testing only; 
	treenode_t temp;
	temp.n = 2 * t; // degree
	for(int i = 0; i < temp.n - 1; ++i)
	{
		temp.x[i].key = 3;
		temp.c[i] = -1;
	}
	temp.c[temp.n - 1] = -1;
	write_file(tt, &temp, -1);temp.c[temp.n - 1] = 1;
	write_file(tt, &temp, -1);temp.c[temp.n - 1] = -12;
	write_file(tt, &temp, -1);temp.c[temp.n - 1] = -13;
	write_file(tt, &temp, -1);temp.c[temp.n - 1] = -14;
	write_file(tt, &temp, -1);temp.c[temp.n - 1] = -15;
	
	treenode_t new_temp;
	read_file(tt, &new_temp, 2);
	disp_node(&new_temp);


}
