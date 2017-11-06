#include "../include/utils.h"

// Computes time taken given the starting and ending times
double accum_time(struct timespec requestStart, struct timespec requestEnd) {
    
    return ((requestEnd.tv_sec - requestStart.tv_sec)) * 1000 +
            (( requestEnd.tv_nsec - requestStart.tv_nsec ) / MILLION);
}

void enter_data(Data* record, int id_num, char country[], char status[], int num1, int num2) {
	
	record->key = id_num;
	strcpy(record->country, country);
	strcpy(record->status, status);
	record->num1 = num1;
	record->num2 = num2;
	
	return;
}

Data* get_data(char *filepath, int len) {
	
	Data *records = malloc(sizeof(Data)*100);
	char delim = ','; char line[256];
	int file_no = 0;
	int i;
	int key;
	char country[255];
	char status[255];
	int num1;
	int num2;
	
	FILE *fin = fopen(filepath, "r");
	
	while(file_no < 51 && fscanf(fin, "%d,%[^,],%[^,],%d,%d", &key, country, status, &num1, &num2)) {
		// printf("%d %s %s %d %d\n", id_num, country, status, num1, num2);
		enter_data(&records[file_no], key, country, status, num1, num2);
		// printf("%d %d\n", records[file_no]->key, records[file_no]->num2);
		file_no++;
	}
	
	// for(i = 0; i < MILLION; i++) {
		// printf("%s\n", records[i]->country);
	// }
	
	return records;
}