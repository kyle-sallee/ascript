/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_MDK_H
#define		_A_MDK_H
#include	"int.h"

/*	mdk is a message digest.
	Fast generation rather than
	absolute crpyographic security
	is desired.
*/

SCV			reval_mdk	(VMETA *);
static	inline	void	mdksubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".mdk",A);
	int8init		(B);
	dex8data		(B);
	B->show=		Gz.out.dex8;
	B->reval=		reval_mdk;
}
#endif
