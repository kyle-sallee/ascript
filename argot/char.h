/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_CHAR_H
#define		_CHAR_H
#include	"int.h"

/*
extern	OPERATOR	opchar[1];
*/

typedef	struct
{	VMETA		*host,*chad,*from,*size;
}	CHARD;

__attribute__((always_inline))
static	inline	 CHARD *	chard	(VMETA *A)
{	return	(CHARD *)	A->text;
}

SCV	reval_size	(VMETA *A)	{A->value.i=A->host->textlen;}
SCV	revise_size	(VMETA *A)	{A->host->textlen=A->value.i;}

SCV	show_char		(VMETA *A)
{	CHARD		*a=
	chard			(A);
	A->textaddr=		a->host->textaddr+
				a->from->value.i;
}

__attribute__((always_inline))
static	inline	void	charsubnew	(VMETA *A)
{	VMETA		*B,*C;
	B=
	var_new_sub		(".char",A);
	B->op=			opchar;
	B->show=		show_char;
	B->textaddr=		A->textaddr;
	B->textlen=		A->textlen;
	B->textsize=		0xffffffff;

	CHARD		*d=
	chard			(B);
	d->host=		A;
	d->chad=		B;

	C=
	var_new_sub		(".from",B);
	int8init		(C);
	d->from=		C;

	C=
	var_new_sub		(".size",B);
	int8init		(C);
/*	C->val=			(void *)	&B->textlen;	*/
	C->reval=		reval_size;
	C->revise=		revise_size;
	d->size=		C;
}
#endif
