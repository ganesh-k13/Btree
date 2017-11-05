#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Node.h"

#define MILLION 1E6

void enter_data(Data* record, int id_num, char country[], char status[], int num1, int num2);
Data **get_data(Data **data, char *filepath);
double accum_time(struct timespec requestStart, struct timespec requestEnd);
