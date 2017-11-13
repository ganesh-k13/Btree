#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Node.h"
#include "Btree.h"

#define MILLION 1E6

Btree* build(long len);
void print_function(Data *record);
void enter_data(Data* record, int id_num, char country[], char Grate[], int Score, int Rate);
Data *get_data(char *filepath, int len);
double accum_time(struct timespec requestStart, struct timespec requestEnd);
void print_function(Data *node);