/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_KVP_H
#define		_A_KVP_H
#include	"byte.h"

/*
extern	OPERATOR	opkvp[3];
*
/
/*	type kvp maps:
	data		KVPD	for keys and vals
*/

	struct	ELEMENT_T;
typedef	struct	ELEMENT_T	ELEMENT;
typedef	struct	ELEMENT_T
{		ELEMENT		*next;
		ELEMENT		*link;
		ELEMENT		*with;
		uint8_t		*text;
		size_t		len;
		size_t		size;
		uint16_t	index;
		uint8_t		placed;
}		ELEMENT;

	struct	KVPD_S;
typedef	struct	KVPD_S		KVPD;
typedef	struct	KVPD_S
{		PALIGN
		ELEMENT		*where[0x10000];
		ELEMENT		*chain;
}		KVPD;

typedef	struct
{	VMETA	*kvp;
	VMETA	*ambit;
	VMETA	*key;
	VMETA	*keyall;
	VMETA	*val;
	VMETA	*valall;
}	KVPV;

__attribute__((always_inline))
static	inline	void	kvp_unchain	(ELEMENT *A)
{	ELEMENT		*B;
	for				(;A!=NULL;A=B)
	{	B=			A->next;
		munmap			(A->text,A->size);
		munmap			(A,PAGE);
	}
}

__attribute__((always_inline))
static	inline	KVPV *	kvpv	(VMETA *A){return(KVPV *)A->textaddr;}
__attribute__((always_inline))
static	inline	 KVPD *	keys	(VMETA *A){return(KVPD *)A->dataaddr;}
__attribute__((always_inline))
static	inline	  KVPD * vals	(VMETA *A){return((KVPD *)A->dataaddr)+1;}

SCV	kvpfree		(VMETA *A)
{	kvp_unchain	(keys(A)->chain);
	kvp_unchain	(vals(A)->chain);
	munmap		(A->dataaddr,A->datasize);
	vmeta_free	(A);
}

/*
static	CALIGN	void	vpfree		(VMETA *A)
{	vmeta_free			(A);
}
*/

static	void	show_keymap	(VMETA *);
static	void	show_valmap	(VMETA *);

__attribute__((always_inline))
static	inline	void	kvpsubnew	(VMETA *A)
{	A->op=				opkvp;
	map_add				(A,sizeof(KVPV),sizeof(KVPD)*2);

	A->free=			kvpfree;

	KVPV		*t=
	kvpv				(A);
	t->kvp=				A;

	VMETA		*B=
	var_new_sub			(".ambit",A);
	byteinit			(B);
	B->textlen=			1;
	t->ambit=			B;

	VMETA		*C=
	var_new_sub			(".key",A);
	C->op=				opkvp+1;
	C->io.flag=			textmapuse;
	t->key=				C;
/*	C->free=			vpfree;
*/

	VMETA		*D=
	var_new_sub			(".val",A);
	D->op=				opkvp+2;
	D->io.flag=			textmapuse;
	t->val=				D;
/*	D->free=			vpfree;
*/

	void		*v=
	mmaphuge			(HUGE*0x20,MAP_PRIVATE);

	VMETA		*E=
	var_new_sub			(".key.all",A);
/*	E->op=				opkvp+3;	*/
	byteinit			(E);
	E->show=			show_keymap;
	E->io.flag=			textmapunmap;
	E->textaddr=			v;
	E->textsize=			HUGE*0x10;
	v+=				HUGE*0x10;
	t->keyall=			E;

	VMETA		*F=
	var_new_sub			(".val.all",A);
/*	F->op=				opkvp+4;	*/
	byteinit			(F);
	F->show=			show_valmap;
	F->io.flag=			textmapunmap;
	F->textaddr=			v;
	F->textsize=			HUGE*0x10;
	t->valall=			F;
}
#endif
