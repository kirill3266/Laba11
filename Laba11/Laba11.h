#ifndef Laba11
#define Laba11


union header;
char* alloc(unsigned nbytes);
void afree(char* ap);
static union header* morecore(unsigned nu);

#endif // !Laba11

