/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"sort.h"

	CALIGN	SORT_INDEX	*sort_long	(SORT_INDEX *v,int const i,uint8_t s)
{	return	ksort		(v,i,s);
}

__attribute__((always_inline))
static	inline	int	compare	(SORT_INDEX const * const a,
				 SORT_INDEX const * const b)
{	if	(a->len>b->len)
	return	-1;
	return	1;
}
