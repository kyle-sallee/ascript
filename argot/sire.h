/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_SIRE_H
#define		_A_SIRE_H
#include	"int.h"
#include	<sys/wait.h>

/*
static	void	inline	forkclose	(void)
{	FORK	*a,*b;
	for	(a=Gz.fork;a;b=a->fore,a->func(a->v),a=b);
}
*/

static	void	reval_done	(VMETA *A){A->value.i=	pids.done[A->host->value.i];}
static	void	reval_exit	(VMETA *A){A->value.i=	pids.exit[A->host->value.i];}
static	void	reval_stop	(VMETA *A){A->value.i=	pids.stop[A->host->value.i];}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	donesubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".done",A);
	int4init		(B);
	B->reval=		reval_done;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	exitsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".exit",A);
	int4init		(B);
	B->reval=		reval_exit;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	stopsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".stop",A);
	int4init		(B);
	B->reval=		reval_stop;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	siresubnew	(VMETA *A)
{	int4init			(A);
	A->value.i=			pids.last;
	donesubnew			(A);
	exitsubnew			(A);
	stopsubnew			(A);
}

__attribute__((unused))
static	inline	pid_t	forkmust	(void)
{	pids.miss=			0;
	pids.skip=			1;
	pid_t
	p=	fork			();

	if			yay	(p> 0)
	{	self:
		pids.now++;
		pids.done[p]=
		pids.exit[p]=
		pids.stop[p]=		0;
		pids.pin[p]=		NULL;
/*		pids.cfg[p]=		NULL;	*/
		pids.target[p]=		NULL;
		pids.origin[p]=		NULL;
		pids.last=		p;
		pids.skip=		0;
		if		nay	(pids.miss)
		sigqueue		(0,SIGCHLD,(union sigval){ .sival_int=0});
		return			p;
	}
	if			yay	(p==0)
	{	progeny:
		pids.exit[0]=		0;
		pids.skip=		0;
		pids.now=		0;
		pids.last=		0;
/*		forkclose		();	*/
		return			0;
	}

	sleep				(1);
	p=	fork			();
	if				(p >0)	goto	self;
	if				(p==0)	goto	progeny;
	err				(errna,"fork");
}

__attribute__((unused))
__attribute__((noinline))
SCV	waitall			(int opt)
{	siginfo_t		si;
	do
	{	errna=		0;
		waitid		(P_ALL,0,&si,opt|WNOWAIT);
	}
	while			(errna!=ECHILD);
	errna=			0;
}

__attribute__((noinline))
__attribute__((unused))
static	CALIGN	void	waitthis_	(pid_t const p,int const opt)
{	siginfo_t	si;
	int		e=	errna;
	do
	{	errna=		0;
		waitid		(P_PID,p,&si,opt|WNOWAIT);
	}
	while			(errna==EINTR);
	errna=			e;
}

__attribute__((always_inline))
__attribute__((unused))
static	inline	void	waitthis	(pid_t const p,int const opt)
{	if			yay	(pids.done[p]==0)
	waitthis_			(p,opt);
}
#endif
