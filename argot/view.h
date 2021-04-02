/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_VIEW_H
#define		_VIEW_H
#include	"byte.h"
#include	"int.h"
#include	"utf8.h"

/*
extern	OPERATOR	opview[4];
*/

typedef	struct
{	VMETA		*host,*view,*head,*tail,*from,*size;
}	VIEWD;

/*	.view maps
	Map 0	not a map, but a reference into another variable's map 0
	map 1	VIEWD
*/

__attribute__((always_inline))
static	inline	 VIEWD *	viewd	(VMETA *A)
{	return	(VIEWD *)	A->dataaddr;
}

/*
static	void	reval_from	(VMETA *);
static	void	revise_from	(VMETA *);
*/

static	void	reval_from	(VMETA *A){A->value.i=A->host->textaddr-A->host->host->textaddr;}
static	void	revise_from	(VMETA *A){A->host->textaddr=A->host->host->textaddr+A->value.i;}

static	void	reval_size	(VMETA *A){A->value.i=A->host->textlen;}
static	void	revise_size	(VMETA *A){A->host->textlen=A->value.i;}

__attribute__((always_inline))
static	inline	void	viewsubnew	(VMETA *A)
{	VMETA		*B,*C;
	B=
	var_new_sub		(".view",A);
	B->op=			opview;
	B->textaddr=		A->textaddr;
	B->textlen=		A->textlen;
	B->textsize=		0xffffffff;
	B->io.flag=		textmapuse;
	map_add			(B,0,PAGE);
	VIEWD		*d=
	viewd			(B);
	d->host=		A;
	d->view=		B;

	C=
	var_new_sub		(".head",B);
	C->op=			opview+1;
	C->io.flag=		textmapuse;
	C->dataaddr=		B->dataaddr;
	d->head=		C;
	map_add			(C,PAGE,0);

	C=
	var_new_sub		(".tail",B);
	C->op=			opview+2;
	C->io.flag=		textmapuse;
	C->dataaddr=		B->dataaddr;
	d->tail=		C;
	map_add			(C,PAGE,0);

	C=
	var_new_sub		(".from",B);
	int4init		(C);
	C->reval=		reval_from;
	C->revise=		revise_from;
	C->dataaddr=		B->dataaddr;
	d->from=		C;

	C=
	var_new_sub		(".size",B);
	int4init		(C);
	C->dataaddr=		B->dataaddr;
	C->reval=		reval_size;
	C->revise=		revise_size;
	d->size=		C;
}
#endif
