/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"int.h"
#include	"a.h"
#include	<sys/resource.h>
#include	<sys/time.h>

typedef	struct
{	int		a;
	struct	rlimit	b;
}	RLD;

SCV	rlimit		(void)
{	*Gz.at=		rlimit;
	argot_next	();
}

__attribute__((always_inline))
static	inline	RLD	*rld	(VMETA *A)
{	return		(RLD *)	A->dataaddr;
}

__attribute__((always_inline))
static	inline	void	set	(VMETA *A)
{	setrlimit		(rld(A)->a,&rld(A)->b);
}

__attribute__((always_inline))
static	inline	void	get	(VMETA *A)
{	getrlimit		(rld(A)->a,&rld(A)->b);
}

SCV	reval_rlimit		(VMETA *A)
{	errna=			0;
	get			(A);
	A->io.success=		errna;

	RLD		*r=
	rld			(A);

	rlim_t		b;
	if			(A->host==NULL)
	b=			r->b.rlim_max;
	else
	b=			r->b.rlim_cur;
	A->value.i=		b;
}

SCV	revise_rlimit		(VMETA *A)
{	get			(A);
	RLD		*r=
	rld			(A);

	if			(A->host==NULL)
	r->b.rlim_max=		A->value.i;
	else
	r->b.rlim_cur=		A->value.i;

	errna=			0;
	set			(A);
	A->io.success=		errna;
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20181014",
	.official=	"20181014",
	.update=	"20200923"
};

#define	va(y,z)				\
	map_init	(A);		\
	vattach_faster	(A,y);		\
	rld(A)->a=	z;		\
	A->reval=	reval_rlimit;	\
	A->revise=	revise_rlimit;	\
	A->show=	Gz.out.den8;	\
	A++

#define	vc(a,b)		{.name=(a),.op=opint8,.len=strlen(a)}

__attribute__((always_inline))
static	inline	void	ram_init	(void)
{
	static	VMETA	a[]=
	{	vc	("max.as",		RLIMIT_AS),
		vc	("now.as",		RLIMIT_AS),
		vc	("max.core",		RLIMIT_CORE),
		vc	("now.core",		RLIMIT_CORE),
		vc	("max.cpu",		RLIMIT_CPU),
		vc	("now.cpu",		RLIMIT_CPU),
		vc	("max.data",		RLIMIT_DATA),
		vc	("now.data",		RLIMIT_DATA),
		vc	("max.fsize",		RLIMIT_FSIZE),
		vc	("now.fsize",		RLIMIT_FSIZE),
		vc	("max.locks",		RLIMIT_LOCKS),
		vc	("now.locks",		RLIMIT_LOCKS),
		vc	("max.memlock",		RLIMIT_MEMLOCK),
		vc	("now.memlock",		RLIMIT_MEMLOCK),
		vc	("max.msgqueue",	RLIMIT_MSGQUEUE),
		vc	("now.msgqueue",	RLIMIT_MSGQUEUE),
		vc	("max.nice",		RLIMIT_NICE),
		vc	("now.nice",		RLIMIT_NICE),
		vc	("max.nofile",		RLIMIT_NOFILE),
		vc	("now.nofile",		RLIMIT_NOFILE),
		vc	("max.nproc",		RLIMIT_NPROC),
		vc	("now.nproc",		RLIMIT_NPROC),
		vc	("max.rss",		RLIMIT_RSS),
		vc	("now.rss",		RLIMIT_RSS),
		vc	("max.rtprio",		RLIMIT_RTPRIO),
		vc	("now.rtprio",		RLIMIT_RTPRIO),
		vc	("max.rttime",		RLIMIT_RTTIME),
		vc	("now.rttime",		RLIMIT_RTTIME),
		vc	("max.sigpending",	RLIMIT_SIGPENDING),
		vc	("now.sigpending",	RLIMIT_SIGPENDING),
		vc	("max.stack",		RLIMIT_STACK),
		vc	("now.stack",		RLIMIT_STACK),
	};

	RLD		*b=
	pps				(sizeof(RLD)*0x10);

	uint8_t		c;
	for				(c=0;0x10>c;c++)
	{	a[c*2+0].textaddr=	a[c*2+0].text;
		a[c*2+1].textaddr=	a[c*2+1].text;
		a[c*2+0].dataaddr=
		a[c*2+1].dataaddr=	(void *)(b+c);
		a[c*2+1].host=		a+c*2;
	}

	VMETA		*A=	a;

	va	("max.as",		RLIMIT_AS);
	va	("now.as",		RLIMIT_AS);
	va	("max.core",		RLIMIT_CORE);
	va	("now.core",		RLIMIT_CORE);
	va	("max.cpu",		RLIMIT_CPU);
	va	("now.cpu",		RLIMIT_CPU);
	va	("max.data",		RLIMIT_DATA);
	va	("now.data",		RLIMIT_DATA);
	va	("max.fsize",		RLIMIT_FSIZE);
	va	("now.fsize",		RLIMIT_FSIZE);
	va	("max.locks",		RLIMIT_LOCKS);
	va	("now.locks",		RLIMIT_LOCKS);
	va	("max.memlock",		RLIMIT_MEMLOCK);
	va	("now.memlock",		RLIMIT_MEMLOCK);
	va	("max.msgqueue",	RLIMIT_MSGQUEUE);
	va	("now.msgqueue",	RLIMIT_MSGQUEUE);
	va	("max.nice",		RLIMIT_NICE);
	va	("now.nice",		RLIMIT_NICE);
	va	("max.nofile",		RLIMIT_NOFILE);
	va	("now.nofile",		RLIMIT_NOFILE);
	va	("max.nproc",		RLIMIT_NPROC);
	va	("now.nproc",		RLIMIT_NPROC);
	va	("max.rss",		RLIMIT_RSS);
	va	("now.rss",		RLIMIT_RSS);
	va	("max.rtprio",		RLIMIT_RTPRIO);
	va	("now.rtprio",		RLIMIT_RTPRIO);
	va	("max.rttime",		RLIMIT_RTTIME);
	va	("now.rttime",		RLIMIT_RTTIME);
	va	("max.sigpending",	RLIMIT_SIGPENDING);
	va	("now.sigpending",	RLIMIT_SIGPENDING);
	va	("max.stack",		RLIMIT_STACK);
	va	("now.stack",		RLIMIT_STACK);
}

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(rlimit,"rlimit");
	aa_fini		();
	ram_init	();
};
