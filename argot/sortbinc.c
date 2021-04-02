/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"sort.h"

	CALIGN	SORT_INDEX	*sortb_inc	(SORT_INDEX *v,uint32_t b)
{	return	bsort		(v,b);
}

/* unrolling the loops did not help */

__attribute__((always_inline))
static	inline	int	compare	(SORT_INDEX const * const a,
				 SORT_INDEX const * const b)
{	return		0;
}
