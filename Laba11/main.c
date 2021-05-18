#include "Laba11.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	int c;
	int* cd = &c;
	*cd = 5;
	printf("cd's adress before alloc: %p, it's value - %d \n", cd, *cd);
	cd = alloc(sizeof(int));
	*cd = 7;
	printf("cd's adress after alloc: %p, it's value - %d \n", cd, *cd);
	return 0;
}