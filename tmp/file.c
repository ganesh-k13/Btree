#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct Data {
	int key;
	char country[5];
	char status[10];
	int num1;
	int num2;
}Data;

void enter_data(Data* record, int id_num, char country[], char status[], int num1, int num2) {
	
	record->key = id_num;
	strcpy(record->country, country);
	strcpy(record->status, status);
	record->num1 = num1;
	record->num2 = num2;
	
	return;
}

Data* get_data(char *filepath, int len) {
	
	Data* records = malloc(sizeof(Data)*len);
	char delim = ','; char line[256];
	int file_no = 0;
	int i;
	int key;
	char country[255];
	char status[255];
	int num1;
	int num2;
	
	FILE *fin = fopen(filepath, "r");
	
	while(file_no < 50 && fscanf(fin, "%d,%[^,],%[^,],%d,%d", &key, country, status, &num1, &num2)) {
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


int main() {
	// printf("sssssssss");
	// Data *records = get_data("small.csv", 50);
	
	// printf("%d\n", records[49].key);
	
	// int i;
	// FILE *fout = fopen ("nodes1.dat", "wb");
	
	// fwrite(records, sizeof(Data)*50, 1, fout);
	
	// close(fout);
	
	FILE *fin = fopen("nodes1.dat", "rb");
	
	Data in_record;
	
	fseek(fin, (long)sizeof(Data)*2, SEEK_SET);
	
	fread(&in_record, sizeof(Data), 1, fin);
	
	
	printf("%d\n", in_record.key);
}