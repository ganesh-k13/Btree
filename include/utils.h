#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Node.h"
#include "Btree.h"

#define MILLION 1E6

void write_file(Btree* ptr_tree, Node* p, int pos); // pos = -1; use next_pos
void read_file(Btree* ptr_tree, Node* p, int pos);

void print_function(Data *node);
void node_init(Node *node, bool isLeaf, Btree *tree);
void enter_data(Data* record, int id_num, char country[], char Grate[], int Score, int Rate);
Data *get_data(char *filepath, int len);
double accum_time(struct timespec requestStart, struct timespec requestEnd);
