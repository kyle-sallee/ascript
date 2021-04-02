/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"sort.h"

	CALIGN	SORT_INDEX	*sort_dec	(SORT_INDEX *v,int const i,uint8_t s)
{	return	ksort		(v,i,s);
}

__attribute__((always_inline))
static	inline	int	compare	(SORT_INDEX const * const a,
				 SORT_INDEX const * const b)
{	uint64_t	*A=	a->text;
	uint64_t	*B=	b->text;

	uint64_t	c=	*A;
	uint64_t	d=	*B;

	if			(c>d)	return	-1;
	if			(c<d)	return	1;

	intptr_t	L=	a->len;
	intptr_t	R=	b->len;

	void		*C=	A;

	if			(L<R)
	{	for		(C+=L-8;C>(void *)A;)
		{	c=	*(++A);
			d=	*(++B);
			if	(c >d)	return	-1;
			if	(c <d)	return	1;
		}
					return	-1;
	}
	if			(L>R)
	{	for		(C+=R-8;C>(void *)A;)
		{	c=	*(++A);
			d=	*(++B);
			if	(c >d)	return	-1;
			if	(c <d)	return	1;
		}
					return	1;
	}
	{	for		(C+=L-8;C>(void *)A;)
		{	c=	*(++A);
			d=	*(++B);
			if	(c >d)	return	-1;
			if	(c <d)	return	1;
		}
					return	0;
	}
}
