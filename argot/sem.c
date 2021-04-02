/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	<semaphore.h>

typedef	struct
{	sem_t		*b;
	VMETA		*d;	/* var containing pathname */
	unsigned int	e;	/* initial value */
}	SEMDATA;

__attribute__((always_inline))
static	inline	 SEMDATA *	semdata	(VMETA *A)
{	return	(SEMDATA *)	A->dataaddr;
}

SCV	semfree			(VMETA *A)
{	SEMDATA		*a=
	semdata			(A);

	if		yay	(A->io.flag&datamapuse)
	sem_close		(a->b);
	var_free		(A);
}

__attribute__((noinline))
SCV	reval_sem		(VMETA *A)
{	SEMDATA		*a=
	semdata			(A);
	int		b;

	sem_getvalue		(a->b,&b);
	A->value.i=		b;
}

static	inline	void	semsubnew	(VMETA *A)
{	int4init	(A);
	A->reval=	reval_sem;
	A->free=	semfree;
	map_add		(A,0,sizeof(SEMDATA));
}

__attribute__((noinline))
SCV	semwith_		(void)
{	VMETA		*A=	Gz.active.sem;
	Gz.active.sem=		Gz.to[0];
	argot_next		();
	Gz.active.sem=		A;
}

SCV		semwith		(void)
{	(*Gz.at=semwith_)	();
}

SCV	semname			(void)
{	VMETA		*B=
	parapass		(arga(NULL));
	show			(B);
	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);
	a->d=			B;
	*Gz.at=			semname;
	argot_next		();
}

SCV	seminit			(void)
{	VMETA		*B=
	parapass		(arga(NULL));

/*	denwant			(B);		*/

	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);

	a->e=			B->value.i;

	*Gz.at=			seminit;
	argot_next		();
}

SCV	semopen			(void)
{	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);

	errna=			0;
	a->b=
	sem_open		(a->d->textaddr,A->value.i,0600,a->e);

	if		nay	(a->b==SEM_FAILED)
	{	argot_next	();
		return;
	}

	A->io.flag|=		datamapuse;
	if		nay	(errna!=0)
	A->io.success=		errna;
	*Gz.at=			semopen;
	argot_skip		();
}

__attribute__((noinline))
SCV	sempost_		(void)
{	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);
	errna=			0;
	sem_post		(a->b);
	if		nay	(errna!=0)
	A->io.success=		errna;
	argot_next		();
}

SCV		sempost		(void)
{	(*Gz.at=sempost_)	();
}

SCV	semwait			(void)
{	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);
	errna=			0;
	int		b=
	sem_wait		(a->b);
	if		nay	(errna!=0)
	A->io.success=		errna;
	*Gz.at=			semwait;
	argot_jump		(b==0);
}

SCV	semtry			(void)
{	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);
	errna=			0;
	int		b=
	sem_trywait		(a->b);
	if		nay	(errna!=0)
	A->io.success=		errna;
	*Gz.at=			semtry;
	argot_jump		(b==0);
}

SCV	semclose		(void)
{	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);
	errna=			0;
	sem_close		(a->b);
	*Gz.at=			semclose;
	if		nay	(errna!=0)
	A->io.success=		errna;
	argot_next		();
}

SCV	semunlink		(void)
{	VMETA		*A=	Gz.active.sem;
	SEMDATA		*a=
	semdata			(A);
	errna=			0;
	sem_unlink		(a->d->textaddr);
	if		nay	(errna!=0)
	A->io.success=		errna;
	*Gz.at=			semunlink;
	argot_next		();
}

SCV	sem	(void)	{tvarnewab(semsubnew,sem);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180705",
	.official=	"20180705",
	.update=	"20200808"
};

__attribute__((constructor))
SCV	aainit			(void)
{	aa_init			();
	aa			(sem,		"sem");
	aa			(semunlink,	"semunlink");
	aa			(semclose,	"semclose");
	aa			(semtry,	"semtry");
	aa			(semwait,	"semwait");
	aa			(semopen,	"semopen");
	aa			(seminit,	"seminit");
	aa			(semname,	"semname");
	aa			(semwith,	"semwith");
	aa			(sempost,	"sempost");
	aa_fini			();
};
