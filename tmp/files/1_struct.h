#ifndef STRUCT_H
#define STRUCT_H
struct tree
{
	char fname[20];
	FILE *fp;
	int root;
	int next_pos;
};
typedef struct tree tree_t;

struct node
{
	int key;
	// rest
	char country[3];
	char grate[4];
	int score;
	int rate;
};
// 1 , AFG , DIST , 93 , 18
typedef struct node node_t;
struct treenode
{
	int pos; // position in the file; helpful for rewriting
	int n;
	node_t x[2 * t - 1];
	int c[2 * t]; // links
};
typedef struct treenode treenode_t;
tree_t* create_tree(char*);
void insert(node_t* ptr_node);
void delete(int key);

void write_file(tree_t* ptr_tree, treenode_t* p, int pos); // pos = -1; use next_pos
void read_file(tree_t* ptr_tree, treenode_t* p, int pos);

void disp_node(treenode_t* p);
#endif
