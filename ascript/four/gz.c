/*	By Kyle Sallee 2019 copyrighted.
	Used by ascript.c and argots
*/

/*	Not only is Gz required,
	but transparent huge pages
	must be avoided.

	By constructor Gz must be madvise, because
	by constructor Gz data is set.
*/

#define		PROGRAM		1
#include	"ascript.h"
GzT		Gz;
__attribute__((aligned(0x20)))
__attribute__((constructor(102)))
static		void	gz_init	(void)
{	madvise		(&Gz,sizeof(Gz),MADV_NOHUGEPAGE);
	sigfillset	(&Gz.sa[0].sa_mask);
}

#define	mhub	Gz.mhub

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	equalequal_	(void)
{	mhub.v[1]->op->equalequal	();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	notequal_	(void)
{	mhub.v[1]->op->notequal		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	less_		(void)
{	mhub.v[1]->op->less		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	lessequal_	(void)
{	mhub.v[1]->op->lessequal	();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	more_		(void)
{	mhub.v[1]->op->more		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	moreequal_	(void)
{	mhub.v[1]->op->moreequal	();
}

__attribute__((noinline))
__attribute__((aligned(0x10)))
static	CALIGN	void	mapuse1		(VMETA *A)
{	mhub.v[0]->op->fromtext		(A);
}

__attribute__((constructor(104)))
__attribute__((aligned(0x10)))
static		void	mhub_init	(void)
{	mhub.a=		mhub.v;
}

__attribute__((hot))
static	CALIGN	void	equalequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	equalequal_)	();
}

__attribute__((hot))
static	CALIGN	void	notequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	notequal_)	();
}

__attribute__((hot))
static	CALIGN	void	less		(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	less_)		();
}

__attribute__((hot))
static	CALIGN	void	lessequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	lessequal_)	();
}

__attribute__((hot))
static	CALIGN	void	more		(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	more_)		();
}

__attribute__((hot))
static	CALIGN	void	moreequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	moreequal_)	();
}

__attribute__((constructor(104)))
static	CALIGN	void	operator_init	(void)
{	varfixop[0].equalequal=
	varconstop[0].equalequal=	equalequal;

	varfixop[0].notequal=
	varconstop[0].notequal=		notequal;

	varfixop[0].less=
	varconstop[0].less=		less;

	varfixop[0].lessequal=
	varconstop[0].lessequal=	lessequal;

	varfixop[0].more=
	varconstop[0].more=		more;

	varfixop[0].moreequal=
	varconstop[0].moreequal=	moreequal;

	varfixop[0].mapuse[1]=
	varconstop[0].mapuse[1]=	mapuse1;
}
