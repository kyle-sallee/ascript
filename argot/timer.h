/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_TIMER_H
#define		_A_TIMER_H
#include	"int.h"
#include	"sig.h"

#include	<signal.h>
/*
#include	<sys/time.h>
*/
#include	<time.h>

/*
extern	OPERATOR	vartimerop[1];
*/

/*	-lrt
	textTDATA
*/

/*	host	type sig variable address */

typedef	struct
{	timer_t			t;	/* the timerid used for release */
	struct	itimerspec	i;
	struct	sigevent	s;

/*	VALUE	it_value_tv_sec;
	VALUE	it_value_tv_nsec;
	VALUE	it_interval_tv_sec;
	VALUE	it_interval_tv_nsec;
*/
	VALUE	clockid;
/*	VALUE	overrun;	*/
	VALUE	flags;
	VMETA	*sig;
}	TDATA;

__attribute__((always_inline))
static	inline	 TDATA *	tdata	(VMETA *A)
{	return	(TDATA *)	A->dataaddr;
}

__attribute__((unused))
SCV	timerrelease	(VMETA *A)
{	TDATA		*a=
	tdata				(A);
	timer_t		b=		a->t;
	if				(b=0)
	{	a->t=			0;
		timer_delete		(b);
	}
}

__attribute__((unused))
SCV	timerfree	(VMETA *A)
{	timerrelease	(A);
	cede		(A->dataaddr,A->datasize);
	vmeta_free	(A);
}

SCV	reval_overrun		(VMETA *B)
{	B->value.i=
	timer_getoverrun	(tdata(B->host)->t);
}

SCV	reval_1n(VMETA *A){A->value.i=tdata(A->host)->i.it_value.tv_nsec;}
SCV	reval_1s(VMETA *A){A->value.i=tdata(A->host)->i.it_value.tv_sec;}
SCV	reval_in(VMETA *A){A->value.i=tdata(A->host)->i.it_interval.tv_nsec;}
SCV	reval_is(VMETA *A){A->value.i=tdata(A->host)->i.it_interval.tv_sec;}

SCV	revise_1n(VMETA *A){tdata(A->host)->i.it_value.tv_nsec=A->value.i;}
SCV	revise_1s(VMETA *A){tdata(A->host)->i.it_value.tv_sec=A->value.i;}
SCV	revise_in(VMETA *A){tdata(A->host)->i.it_interval.tv_nsec=A->value.i;}
SCV	revise_is(VMETA *A){tdata(A->host)->i.it_interval.tv_sec=A->value.i;}

__attribute__((unused))
static	inline	void	timersubnew	(VMETA *A)
{	int8init		(A);
	A->free=		timerfree;
	map_add			(A,0,sizeof(TDATA));
	TDATA		*a=
	tdata			(A);
	a->s.sigev_notify=	SIGEV_SIGNAL;
	a->clockid.i=		CLOCK_MONOTONIC;

	VMETA		*B;

	B=	var_new_sub	(".once.nano",A);
	int4init		(B);
	B->show=		Gz.out.nano;
	B->reval=		reval_1n;
	B->revise=		revise_1n;
/*	B->val=			(void *)	&a->it_value_tv_nsec;	*/


	B=	var_new_sub	(".once.sec",A);
	int8init		(B);
	B->reval=		reval_1s;
	B->revise=		revise_1s;
/*	B->val=			(void *)	&a->it_value_tv_sec;	*/

	B=	var_new_sub	(".lull.nano",A);
	int4init		(B);
	B->show=		Gz.out.nano;
	B->reval=		reval_in;
	B->revise=		revise_in;
/*	B->val=			(void *)	&a->it_interval_tv_nsec;*/

	B=	var_new_sub	(".lull.sec",A);
	int8init		(B);
	B->reval=		reval_is;
	B->revise=		revise_is;
/*	B->val=			(void *)	&a->it_interval_tv_sec;*/

	B=	var_new_sub	(".overrun",A);
	int4init		(B);
	B->reval=		reval_overrun;

	B=	var_new_sub	(".sig",A);
	sigsubnew		(B);
	a->sig=			B;
}
#endif
