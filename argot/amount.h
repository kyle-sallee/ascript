/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_AMOUNT_H
#define		_A_AMOUNT_H
#include	"int.h"

__attribute__((always_inline))
static	inline	 uint32_t *	amountdata	(VMETA *A)
{	return	(uint32_t *)	A->dataaddr;
}

__attribute__((always_inline))
static	inline	void	amountbytesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".amount.byte",A);
	int4init			(B);
	map_add				(B,0,0x100*sizeof(uint32_t));
}

__attribute__((always_inline))
static	inline	void	amountutf8subnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".amount.utf8",A);
	int4init			(B);
	map_add				(B,0,0x110000*sizeof(uint32_t));
}

__attribute__((always_inline))
static	inline	void	amountwordsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".amount.word",A);
	int4init			(B);
}
#endif
