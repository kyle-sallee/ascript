/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_TOP_H
#define		_A_TOP_H
#include	"ambit.h"
#include	"byte.h"

/*	map 0
	ordered output same size as pair->textsize

	map 1
	sizeof(TSC *)	* 0x10000 +
	sizeof(ELEMENT)	* 2*pair count+
	sizeof(TSC)	* 3*pair count

	The final map 1 portion holds both TSC and WANT,
	which works since WANT is smaller than TSC.
*/

typedef	struct	TSC_S
{	uint8_t		*a;		/* the element name */
	uint32_t	b;		/* the element size */
	uint8_t		sent;		/* sent to buffer */
	uint8_t		seen;		/* being processed */
	struct	TSC_S	*tsm;		/* next in the tsn if it exists */
	void		*want;		/* TSM must output before this */
}	TSC;

typedef	struct
{	uint8_t		*a;		/* start address */
	uint32_t	b;		/* byte  amount */
	TSC		*c;		/* tsc pointer */
}	ELEMENT;

typedef	struct	WANT_S
{	ELEMENT		*e;		/* Pointer to the what comes before */
	struct	WANT_S	*next;		/* Another requirement if it exists */
}	WANT;

typedef	struct
{	VMETA	*host,*ambit,*part,*fail;
}	TSV;


__attribute__((always_inline))
static	inline	 TSC ** tscm	(VMETA *A)
{	return	(TSC **)	A->dataaddr;
}

__attribute__((always_inline))
static	inline	 ELEMENT * ele	(VMETA *A)
{	return	(ELEMENT *)	(tscm	(A)+0x10000);
}

__attribute__((always_inline))
static	inline	 TSC * tsc	(VMETA *A)
{	return	(TSC *)	(ele	(A)+A->value.i*2);
}

SCV	show_top			(VMETA *);

__attribute__((always_inline))
static	inline	void	topsubnew	(VMETA *A)
{	VMETA		*B;
	B=	var_new_sub		(".top",A);
	byteinit			(B);
	B->show=			show_top;

	TSV		*a=		(TSV *)	B->text;
	a->host=			A;

	VMETA		*C;

	C=	var_new_sub		(".ambit",B);
	a->ambit=			C;
	ambitsubnew			(C);
	C->textaddr[0]=
	C->textaddr['\t']=
	C->textaddr['\n']=		1;

	C=	var_new_sub		(".fail",B);
	a->fail=			C;
	byteinit			(C);

	C=	var_new_sub		(".part",B);
	a->part=			C;
	byteinit			(C);
	C->textaddr[0]=			'\n';
	C->textlen=			1;
}
#endif
