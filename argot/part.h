/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_PART_H
#define		_A_PART_H
#include	"ambit.h"

typedef	struct
{	VMETA		*ambit;
	VALUE		*now;
	VALUE		*max;
}	PARTDATA;

__attribute__((always_inline))
static	inline	 PARTDATA *	partdata	(VMETA *A)
{	return	(PARTDATA *)	A->text;
}

SCV	show_part			(VMETA *B)
{	VMETA		*A=		B->host;
	PARTDATA	*P=
	partdata			(B);
	int		d=		P->now->i;
	uint32_t	*b=		(uint32_t *)	B->dataaddr;

	B->textaddr=			A->textaddr+b[d];
	B->textlen=			b[d+1]-b[d];
}

__attribute__((always_inline))
static	inline	void	partsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".part",A);
	byteinit			(B);
	B->show=			show_part;
	B->textaddr=			A->textaddr;
	B->textlen=			A->textlen;
	B->textsize=			0xffffffff;
	PARTDATA	*P=
	partdata			(B);

	B=
	P->ambit=
	var_new_sub			(".part.ambit",A);
	ambitsubnew			(B);

	B=
	var_new_sub			(".part.now",A);
	int4init			(B);
	P->now=				&B->value;
/*	B->val=				&P->now;	*/

	B=
	var_new_sub			(".part.max",A);
	int4init			(B);
	P->max=				&B->value;
/*	B->val=				&P->max;	*/
}
#endif
