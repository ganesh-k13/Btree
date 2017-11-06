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

typedef struct Node {
	bool isLeaf;
	int n;
	Data* records;
	struct Node** children;
}Node;

Node* node_init(bool isLeaf, int t) {
	Node *node = malloc(sizeof(Node));
	node->isLeaf = isLeaf;
	node->n = 0;
	node->records = malloc(sizeof(Data) * (2 * t - 1));
	node->children = malloc(sizeof(Node*) * (2 * t));
	
	return node;
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
	
	// int t = 3, i, j;
	// Data *records;
	// Node **nodes = malloc(sizeof(Node*)*10);
	
	// records = get_data("small.csv", 50);
	
	
	// for(i = 0; i < 10; i++) {
		// nodes[i] = node_init(false, t);
		// for(j = 0; j < 5; j++) {
			// nodes[i]->records[j] = records[5*i+j];
		// }
	// }
	
	// FILE *fout = fopen ("nodes.dat", "wb");
	
	// for(i = 0; i < 10; i++) {
		// fwrite(nodes[i], sizeof(Node), 1, fout);
		// for(j = 0; j < 5; j++) {
			// fwrite(records+(i*5+j), sizeof(Data), 1, fout);
		// }
	// }
	
	// close(fout);
	
	// records = records+49;
	
	// printf("R:%d\n", records[0].key);
	
	int t = 3, i, j;
	long seg_size = sizeof(Node)+sizeof(Data)*(2*t-1);
	Data in_records;
	FILE *fin = fopen ("nodes.dat", "rb");
	// fpos_t pos;
	// // // fseek(fin, seg_size, SEEK_SET);
	
	
	// Node **in_nodes = malloc(sizeof(Node*)*10);
	
	// for(i = 0; i < 10; i++) {
		// in_nodes[i] = node_init(false, t);
		// fread(in_nodes[i], sizeof(Node), 1, fin);
		// // fread(in_records, sizeof(Data)*5, 1, fin);
		// in_nodes[i] = node_init(false, t);
		// for(j = 0; j < 2*t-1; j++) {
			// fread(&in_records, sizeof(Data), 1, fin);
			// in_nodes[i]->records[j] = in_records;
			// // printf("%d\n", in_records.key);
		// }
		// fgetpos (fin,&pos);
		// printf("%d %d\n", pos, sizeof(Node));
	// }
	
	// printf("%d\n", in_nodes[0]->records[1].key);
	
	seg_size = sizeof(Node)+sizeof(Data)*(2*t-1);
	fseek(fin, 164, SEEK_SET);
	
	printf("S:%d\n", seg_size);
	Node *node = node_init(false, t);
	fread(node, sizeof(Node), 1, fin);
	node->records = node_init(false, t);;
	
	for(j = 0; j < 2*t-1; j++) {
		fread(&in_records, sizeof(Data), 1, fin);
		node->records[j] = in_records;
		printf("%d\n", in_records.key);
	}
	
	printf("%d\n", node->records[0].key);
	
}











#if 0
int main() {
	
	Data **records;
	Node **nodes;
	int t = 3, i, j;
	records = get_data(records, "small.csv");
	
	nodes = malloc(sizeof(Node*)*10);
	// printf("%d\n", records[49]->key);
	
	for(i = 0; i < 10; i++) {
		nodes[i] = node_init(false, t);
		for(j = 0; j < 2*t-1; j++) {
			nodes[i]->records[j] = *records[i*5+j];
		}
	}
	
	// printf("%d\n", nodes[9]->records[4].key);
	
	FILE *fout = fopen ("nodes.dat", "wb");
	
	for(i = 0; i < 10; i++) {
		fwrite(nodes[i], sizeof(Node), 1, fout);
		fwrite(records+(i*5), sizeof(Data)*(2*t-1), 1, fout);
	}
	
	records = records+49;
	
	printf("R:%d\n", records[0].key);
	
	close(fout);
	
	FILE *fin = fopen("nodes.dat", "rb");
	
	Node **in_nodes = malloc(sizeof(Node*)*10);
	Data *in_record = malloc(sizeof(Data)*(2*t-1));
	
	for(i = 0; i < 10; i++) {
		in_nodes[i] = node_init(false, t);
		fread(in_nodes[i], sizeof(Node), 1, fin);
		fread(in_record, sizeof(Data)*(2*t-1), 1, fin);
		
		for(j = 0; j < 2*t-1; j++) {
			nodes[i]->records[j] = *in_records[j];
		}
	}
	
	printf("%d\n", in_nodes[2]->records[1].key);
	
	// long size_of_rec = (sizeof(Node)+sizeof(Data)*(2*t-1));
	
	// fseek(fin, size_of_rec*1, SEEK_SET);
	
	// Node *in_node = node_init(true, t);
	// Data *in_rec = malloc(sizeof(Data));

	// fread(in_node, sizeof(Node), 1, fin);
	// fread(in_rec, sizeof(Data), 1, fin);
	
	// // in_node->records = in_rec;
	
	// printf("%s\n", in_rec->country);
	// printf("%d\n", nodes[9]->records[4].key);
	// fwrite(records, sizeof(Data), 50, fout);
	
	// close(fout);
	
	
	// FILE *fin = fopen("nodes.dat", "r");
	
	// fread(records, sizeof(Data), 50, fin);
	
	// printf("%d\n", records[49]->key);
	
	
	// FILE
}
#endif

#if 0
struct foo {
	char name[20];
};



int main() {
	struct foo f;
	struct foo *b;
	b = malloc(sizeof(struct foo));
	strcpy(b->name, "name");
	
	f = *b;
	
	printf("%s\n", f.name);
}
#endif