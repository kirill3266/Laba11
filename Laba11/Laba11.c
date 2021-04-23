#include "Laba11.h"
#define NALLOC 128 /*#units to allocate at once*/

typedef int align; //выполняет выравнивание
union header { //заголовок пустого блока
	struct {
		union header* ptr; //следующий пустой бло
		unsigned size; //размер этого пустого блока
	} s;
	align x; /*force alignment of blocks*/
};
typedef union header header;

static header base; //стартовый пустой список
static header* allocp = NULL; //последний выделенный блок

char* alloc(unsigned nbytes)//хранилище аллокатора общего назначение
{
	header* morecore();
	register header* p, * g;
	register int nunits;
	nunits = 1 + (nbytes + sizeof(header) - 1) / sizeof(header);
	if ((g = allocp) == NULL) { /*no free list yet*/
		base.s.ptr = allocp = g = &base;
		base.s.size = 0;
	}
	for (p = g -> s.ptr; ; g = p, p = p->s.ptr) {
		if (p->s.size >= nunits) { //достаточно большой
			if (p->s.size == nunits) 
				g->s.ptr = p->s.ptr;
			else { /*allocate tail end*/
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			allocp = g;
			return((char*)(p + 1));
		}
		if (p == allocp) /*wrapped around free list*/
			if ((p = morecore(nunits)) == NULL)
				return(NULL); /*none left*/
	}
}

static header* morecore(unsigned nu) /*ask system for memory*/
{
	register char* cp;
	register header* up;
	register int rnu;
	rnu = NALLOC * ((nu + NALLOC - 1) / NALLOC);
	cp = calloc(rnu , sizeof(header));
	if (cp == NULL) /*no space at all*/
		return(NULL);
	up = (header*)cp;
	up->s.size = rnu;
	afree((char*)(up + 1));
	return(allocp);
}

void afree(char* ap) /*put block ap in free list*/
{
	register header* p, * g;
	p = (header*)ap - 1; /*point to header*/
	for (g = allocp; !(p > g && p > g->s.ptr); g = g->s.ptr)
		if (g >= g->s.ptr && (p > g || p < g->s.ptr))
			break; /*at one end or other*/
	if (p + p->s.size == g->s.ptr) {/*join to upper nbr*/
		p->s.size += g->s.ptr->s.size;
		p->s.ptr = g->s.ptr->s.ptr;
	}
	else
		p->s.ptr = g->s.ptr;
	if (g + g->s.size == p) { /*join to lower nbr*/
		g->s.size += p->s.size;
		g->s.ptr = p->s.ptr;
	}
	else
		g->s.ptr = p;
	allocp = g;
	//*ap= 0;
}
