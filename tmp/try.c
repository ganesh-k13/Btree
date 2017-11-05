#include <stdio.h>
#include <string.h>

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