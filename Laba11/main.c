#include "Laba11.h"

int main() {
	int c;
	int* cd = &c;
	*cd = 5;
	printf("cd's adress before alloc: %p, it's value - %d \n", cd, *cd);
	cd = alloc(sizeof(int));
	*cd = 7;
	printf("cd's adress after alloc: %p, it's value - %d \n", cd, *cd);
	afree(cd);
	cd = alloc(sizeof(int));
	printf("cd's adress after newalloc: %p, it's value - %d \n", cd, *cd);
	cd = alloc(sizeof(int));
	printf("cd's adress after newalloc without free: %p, it's value - %d\n", cd, *cd);
	double* cc = cd;
	printf("cc's adress after cd's newalloc: %p, it's value - %d \n", cc, *cc);
	free(*cd, *cc);
	return 0;
}