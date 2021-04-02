/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_SIG_H
#define		_A_SIG_H
#include	"argot.h"
#include	"int.h"
#include	<signal.h>

/*
extern	OPERATOR	opsig[1];
*/

/*	map	1	SIGDATA
*/

typedef	struct
{
/*	VALUE			sig;	*/	/* now stored as ->value.i */
	VALUE			pid;
	VALUE			uid;
	VALUE			val;
	VALUE			sum;
	VALUE			flag;
/*	VMETA			*pin;	*/
	VMETA			*to[2];
	void			(**pin)	(void);
	void			*afore;
	struct	sigaction	sa[1];
	uint8_t			inuse;
}	SIGDATA;

__attribute__((always_inline))
static	inline	 SIGDATA *	sigdata	(VMETA *A)
{	return	(SIGDATA *)	A->dataaddr;
}

SCV	reval_pid	(VMETA *A){A->value.i4.l=sigdata(A->host)->pid.i;}
SCV	reval_uid	(VMETA *A){A->value.i=   sigdata(A->host)->uid.i;}
SCV	reval_sum	(VMETA *A){A->value.i=   sigdata(A->host)->sum.i;}
SCV	reval_val	(VMETA *A){A->value.i=   sigdata(A->host)->val.i;}

__attribute__((unused))
SCV	sigrelease		(VMETA *A)
{	SIGDATA		*a=
	sigdata			(A);
	int		b=	a->inuse;
	if			(a->inuse==0)
	return;
	a->inuse=		0;
	Gz.sig[b]=		a->afore;
/*	a->sig.i=		0;	*/
	A->value.i=		0;
	sigaction		(b,a->sa,NULL);
}

__attribute__((unused))
SCV	sigfree			(VMETA *A)
{	sigrelease		(A);
	cede			(A->dataaddr,A->datasize);
	vmeta_free		(A);
}

__attribute__((always_inline))
static	inline	void	sigsubnew	(VMETA *A)
{	A->free=	sigfree;
	A->op=		opsig;
	A->show=	Gz.out.den4;
	map_add		(A,0,sizeof(SIGDATA));
}

__attribute__((always_inline))
static	inline	void	sigpidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".pid",A);
	int4init		(B);
	B->reval=		reval_pid;
}

__attribute__((always_inline))
static	inline	void	siguidsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".uid",A);
	int8init		(B);
	B->reval=		reval_uid;
}

__attribute__((always_inline))
static	inline	void	sigvalsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".val",A);
	int8init		(B);
	B->reval=		reval_val;
}

__attribute__((always_inline))
static	inline	void	sigsumsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".sum",A);
	int4init		(B);
	B->reval=		reval_sum;
}
#endif
