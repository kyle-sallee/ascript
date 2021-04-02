/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_EXE_H
#define		_A_EXE_H
#include	"byte.h"
#include	"env.h"
#include	"int.h"
#include	"para.h"
#include	"sire.h"

typedef	struct
{	VALUE			pid;
	void			(**pin)	(void);
	VMETA			*name,*para,*env,*out,*err,*origin,*target;
}	EXEDATA;


SCV	pidclr			(VMETA *A)
{	pid_t		p=	A->value.i;
	pids.origin[p]=		NULL;
	pids.target[p]=		NULL;
	pids.pin[p]=		NULL;
	var_free		(A);
}

__attribute__((always_inline))
static	inline	 EXEDATA *	exedata	(VMETA *A)
{	return	(EXEDATA *)	A->dataaddr;
}

SCV	execlose		(VMETA *A)
{	if		nay	(A->io.map>0)
	close			(A->io.map);
	var_free		(A);
}

__attribute__((always_inline))
static	inline	void	exeinit	(VMETA *A)
{	int4init		(A);
/*	A->ready=		ready_int;	*/
	map_add			(A,0,sizeof(EXEDATA));
	A->value.i=		-1;
	A->free=		pidclr;
}

__attribute__((always_inline))
static	inline	void	exeenvinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".env",A);
	envinit		(B);
	exedata	(A)->env=	B;
}

__attribute__((always_inline))
static	inline	void	exeparainit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".para",A);
	parainit		(B);
	exedata	(A)->para=	B;
}

__attribute__((always_inline))
static	inline	void	exenameinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".name",A);
	byteinit		(B);
	exedata	(A)->name=	B;
}

__attribute__((always_inline))
static	inline	void	exeoutinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".out",A);
	byteinit		(B);
	B->free=		execlose;
	exedata	(A)->out=	B;
}

__attribute__((always_inline))
static	inline	void	exeerrinit	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".err",A);
	byteinit		(B);
	B->free=		execlose;
	exedata	(A)->err=	B;
}
#endif
