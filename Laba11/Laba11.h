#ifndef Laba11
#define Laba11

#include <stdio.h>
#include <stdlib.h>

union header;
char* alloc(unsigned nbytes);
void afree(char* ap);
static union header* morecore(unsigned nu);

#endif // !Laba11

