#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "1_struct.h"
#define ALLOC(x) (x*)malloc(sizeof(x))



tree_t* create_tree(char* fname)
{
	tree_t *p;
	p = ALLOC(tree_t); 
	strcpy(p->fname, "fname");	
	// create a new tree; does not take care of reading an existing tree
	p->fp = fopen(fname, "a+");
	p->root = 0;
	p->next_pos = 0;
	return p;
}

void write_file(tree_t* ptr_tree, treenode_t* p, int pos) // pos = -1; use next_pos
{
	if(pos == -1)
	{
		pos = ptr_tree->next_pos++;
	}
	fseek(ptr_tree->fp, pos * sizeof(treenode_t), 0);
	fwrite(p, sizeof(treenode_t), 1, ptr_tree->fp);
	
}

void read_file(tree_t* ptr_tree, treenode_t* p, int pos)
{
	fseek(ptr_tree->fp, pos * sizeof(treenode_t), 0);
	fread(p, sizeof(treenode_t), 1, ptr_tree->fp);
}

void disp_node(treenode_t* p)
{
	printf("keys\n");
	for(int i = 0; i < p->n - 1; i++)
	{
		printf("%d ", p->x[i].key);
	}
	printf("\n");
	printf("links\n");
	for(int i = 0; i < p->n; i++)
	{
		printf("%d ", p->c[i]);
	}
	printf("\n");
}



