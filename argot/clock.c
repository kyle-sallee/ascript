/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"int.h"
#include	"a.h"

#define	va(a)	{.name=(a),.len=strlen(a),.op=opint8,}
#define	vb(a)	{.name=(a),.len=strlen(a),.op=opint4,}

typedef	struct
{	VMETA			a[0xa];
	clockid_t		b[0xa];
	struct	timespec	c;
}	CLOCKVAR;

static	CLOCKVAR	c=
{	.a={	va		("real.sec"),
		vb		("real.nano"),
		va		("mono.sec"),
		vb		("mono.nano"),
		va		("boot.sec"),
		vb		("boot.nano"),
		va		("process.sec"),
		vb		("process.nano"),
		va		("thread.sec"),
		vb		("thread.nano"),
	},
	.b={	CLOCK_REALTIME,
		CLOCK_REALTIME,
		CLOCK_MONOTONIC,
		CLOCK_MONOTONIC,
		CLOCK_BOOTTIME,
		CLOCK_BOOTTIME,
		CLOCK_PROCESS_CPUTIME_ID,
		CLOCK_PROCESS_CPUTIME_ID,
		CLOCK_THREAD_CPUTIME_ID,
		CLOCK_THREAD_CPUTIME_ID,
	},
};

static		void	_clock	(void)
{	*Gz.at=		_clock;
	argot_next	();
}

__attribute__((noinline))
SCV	reval_sec	(VMETA *A)
{	clock_gettime	(c.b[A-c.a],&c.c);
	A[0].value.i=	c.c.tv_sec;
	A[1].value.i=	c.c.tv_nsec;
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20181016",
	.official=	"20181016",
	.update=	"20200923"
};

#define	vc(a)	map_init(A);A->show=Gz.out.den8;A->reval=reval_sec;vattach_faster(A,(a));A++
#define	vd(a)	map_init(A);A->show=Gz.out.nano;A->textlen=9   ;vattach_faster(A,(a));A++

__attribute__((always_inline))
static	inline	void	var_init	(void)
{	VMETA
	*A=	c.a;
	vc	("real.sec");
	vd	("real.nano");
	vc	("mono.sec");
	vd	("mono.nano");
	vc	("boot.sec");
	vd	("boot.nano");
	vc	("process.sec");
	vd	("process.nano");
	vc	("thread.sec");
	vd	("thread.nano");
}

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_clock,"clock");
	aa_fini		();
	var_init	();
};
