/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_LIST_H
#define		_A_LIST_H
#include	"ambit.h"

/*
extern	OPERATOR	oplist[4];
*/

/*	type list maps:
	type list single maps:
	type list unique maps:
	text		The list elements, presumably text?
	data		*ELEMENT [0x10000] + all element structures

	type list entire maps:
	text		The list elements, presumably text?
	(VALUE).i		the      element   count, not really used.
*/

typedef	struct	ELEMENT_T
{	uint8_t			*name;		/* the element name */
	struct	ELEMENT_T	*next;		/* next in matrix */
	uint32_t		size;		/* the element size */
	uint32_t		seen;		/* amount seen */
}	ELEMENT;

typedef	struct
{	VMETA		*host,*ambit;
}	LV;

typedef	struct
{	VMETA		*host,*text;
}	LSV;

__attribute__((always_inline))
static	inline	LV	*lv	(VMETA *A){return (LV *)A->text;}
__attribute__((always_inline))
static	inline	LSV	*lsv	(VMETA *A){return (LSV *)A->text;}

static	void	show_list	(VMETA *);
static	void	show_single	(VMETA *);
static	void	show_entire	(VMETA *);
static	void	show_unique	(VMETA *);

__attribute__((always_inline))
static	inline	void	listsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".list",A);
	LV		*a=
	lv				(B);
	a->host=			A;
	B->op=				oplist;
	B->show=			show_list;
	B->textsize=			0;

	VMETA		*C=
	var_new_sub			(".ambit",B);
	a->ambit=			C;
	ambitsubnew			(C);
	C->textaddr[0]=
	C->textaddr['\t']=
	C->textaddr['\n']=		1;
}

__attribute__((always_inline))
static	inline	void	listsinglesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".single",A);
	B->op=				oplist+1;
	B->show=			show_single;
	lsv(B)->host=			A;
	B->textsize=			0;
}

__attribute__((always_inline))
static	inline	void	listentiresubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".entire",A);
	B->op=				oplist+2;
	B->show=			show_entire;
	lsv(B)->host=			A;
	B->textsize=			0;
}

__attribute__((always_inline))
static	inline	void	listuniquesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub			(".unique",A);
	B->op=				oplist+3;
	B->show=			show_unique;
	lsv(B)->host=			A;
	B->textsize=			0;
}

__attribute__((always_inline))
static	inline	ELEMENT **	elm	(VMETA *A)
{	return		(ELEMENT **)	A->dataaddr;
}

__attribute__((always_inline))
static	inline	ELEMENT *	ela	(VMETA *A)
{	return		(ELEMENT *)	(elm(A)+0x10000);
}
#endif
