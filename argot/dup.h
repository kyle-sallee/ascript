/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef	_A_DUP_H
#define	_A_DUP_H
#include	"int.h"

__attribute__((unused))
SCV	dupfree			(VMETA *A)
{	int		a=	A->value.i;
	if		nay	(a>2)
	closemust		(a);
	var_free		(A);
}

__attribute__((unused))
static	inline	void	dupsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".dup",A);
	B->value.i=		-1;
	int4init		(B);
	B->free=		dupfree;
}
#endif
