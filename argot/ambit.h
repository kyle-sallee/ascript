/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_AMBIT_H
#define		_A_AMBIT_H
#include	"utf8.h"

/*	map 0	0x110000
		when selected
		the int value is 1.
*/

__attribute__((unused))
static	inline	size_t	ambit_total	(uint8_t *a, size_t t, uint8_t *b)
{	uint8_t		c,*e=	a+t;
	size_t		r=	0;

	for			(c=0;e>a;)
	{	c=		b[utf8_in(&a)];
		r+=		(c!=0);
	}
	r+=			(c==0);
	return			r;
}

__attribute__((unused))
static	inline	void	ambitsubnew	(VMETA *A)
{	A->op=		opambit;
	map_add		(A,0x110000,0);
	A->io.flag|=	textmapuse;
/*	A->datause=	1;	*/
}
#endif
