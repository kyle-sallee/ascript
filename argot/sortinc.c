/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"sort.h"

	CALIGN	SORT_INDEX	*sort_inc	(SORT_INDEX *v,int const i,uint8_t s)
{	return	ksort		(v,i,s);
}

/* unrolling the loops did not help */

__attribute__((always_inline))
static	inline	int	compare	(SORT_INDEX const * const a,
				 SORT_INDEX const * const b)
{	uint64_t	*A=	a->text;
	uint64_t	*B=	b->text;

	uint64_t	c=	*A;
	uint64_t	d=	*B;

	if			(c<d)	return	-1;
	if			(c>d)	return	1;

	intptr_t	L=	a->len;
	intptr_t	R=	b->len;

	void		*C=	A;

	if			(L<R)
	{	for		(C+=L-8;C>(void *)A;)
		{	c=	*(++A);
			d=	*(++B);
			if	(c <d)	return	-1;
			if	(c >d)	return	1;
		}
					return	-1;
	}
	else
	if			(L>R)
	{	for		(C+=R-8;C>(void *)A;)
		{	c=	*(++A);
			d=	*(++B);
			if	(c <d)	return	-1;
			if	(c >d)	return	1;
		}
					return	1;
	}
	else
	{	for		(C+=L-8;C>(void *)A;)
		{	c=	*(++A);
			d=	*(++B);
			if	(c <d)	return	-1;
			if	(c >d)	return	1;
		}
					return	0;
	}
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	int	compareo	(SORT_INDEX const * const a,
				 SORT_INDEX const * const b)
{	uint64_t	*A=	a->text;
	uint64_t	*B=	b->text;

	uint64_t	c=	*A;
	uint64_t	d=	*B;

	if			(c<d)	return	-1;
	if			(c>d)	return	1;

	intptr_t	L=	a->len;
	intptr_t	R=	b->len;

	if			(L<R)
	{	for		(L-=8;L>0;L-=8)
		{	c=	*(++A);
			d=	*(++B);
			if	(c <d)	return	-1;
			if	(c >d)	return	1;
		}
					return	-1;
	}
	else
	if			(L>R)
	{	for		(R-=8;R>0;R-=8)
		{	c=	*(++A);
			d=	*(++B);
			if	(c <d)	return	-1;
			if	(c >d)	return	1;
		}
					return	1;
	}
	else
	{	for		(L-=8;L>0;L-=8)
		{	c=	*(++A);
			d=	*(++B);
			if	(c==d)	continue;
			if	(c <d)	return	-1;
					return	1;
		}
					return	0;
	}
}
