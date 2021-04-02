/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"sort.h"

	CALIGN	SORT_INDEX	*sort_same	(SORT_INDEX *v,int i,uint8_t s)
{	SORT_INDEX	*a,*b;
	for			(a=v,b=a+1,i--;i>0;b++,i--)
	if			(compare(a,b)!=0)
	{	a->next=	b;
		a=		b;
	}
	else
	a->again++;
	return			v;
}

/* unrolling the loops did not help */

__attribute__((always_inline))
static	inline	int	compare	(SORT_INDEX const * const a,
				 SORT_INDEX const * const b)
{	uint64_t	*A=	a->text;
	uint64_t	*B=	b->text;

	if		yay	(a->len!=b->len)	return	1;

	uint64_t	c=	*A;
	uint64_t	d=	*B;

	if		yay	(c!=d)			return	1;

	intptr_t	L=	a->len;
	void		*C=	A;

	for			(C+=L-8;C>(void *)A;)
	{	c=		*(++A);
		d=		*(++B);
		if	nay	(c!=d)			return	1;
	}
							return	0;
}
