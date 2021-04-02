/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	<stddef.h>
#include	<sys/resource.h>
#include	<sys/time.h>
#include	<time.h>

CALIGN
static	struct	rusage	R;

SCV	reval_self	(VMETA *A)
{	getrusage	(RUSAGE_SELF,&R);
	A->value.i=	*(long *)(((void *)&R)+A->datalen);
}

SCV	reval_kids	(VMETA *A)
{	getrusage	(RUSAGE_CHILDREN,&R);
	A->value.i=	*(long *)(((void *)&R)+A->datalen);
}

SCV	reval_nano	(VMETA *A)
{	A->value.i=	*(long *)(((void *)&R)+A->datalen);
}

SCV	rusage		(void)
{	*Gz.at=		rusage;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180525",
	.official=	"20180525",
	.update=	"20200823"
};

#define	va(a,b)		map_init	(A);			\
			A->reval=	reval_self;		\
			A->show=	Gz.out.den8;		\
			vattach_faster	(A,a);			\
			A++

#define	vb(a,b)		map_init	(A);			\
			A->reval=	reval_kids;		\
			A->show=	Gz.out.den8;		\
			vattach_faster	(A,a);			\
			A++

#define	vc(a,b)		map_init	(A);			\
			A->reval=	reval_nano;		\
			A->show=	Gz.out.nano;		\
			vattach_faster	(A,a);			\
			A++

#define	vv(a,b)						\
{	.name=		(a),				\
	.len=	strlen	(a),				\
	.datalen=	offsetof(struct rusage,b),	\
	.op=		opint8,				\
}

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(rusage,"rusage");
	aa_fini		();
}

__attribute__((constructor))
SCV	init				(void)
{	static	VMETA	a[]={
	vv	("self.utime.tv_sec",	ru_utime.tv_sec),
	vv	("self.utime.tv_usec",	ru_utime.tv_usec),
	vv	("self.stime.tv_sec",	ru_stime.tv_sec),
	vv	("self.stime.tv_usec",	ru_stime.tv_usec),
	vv	("self.maxrss",		ru_maxrss),
	vv	("self.minflt",		ru_minflt),
	vv	("self.majflt",		ru_majflt),
	vv	("self.inblock",	ru_inblock),
	vv	("self.outblock",	ru_oublock),
	vv	("self.nvcsw",		ru_nvcsw),
	vv	("self.nivcsw",		ru_nivcsw),
#ifndef	__linux__
	vv	("self.ixrss",		ru_ixrss),
	vv	("self.idrss",		ru_idrss),
	vv	("self.isrss",		ru_isrss),
	vv	("self.nswap",		ru_nswap),
	vv	("self.msgsnd",		ru_msgsnd),
	vv	("self.msgrcv",		ru_msgrcv),
	vv	("self.nsignals",	ru_nsignals),
#endif
	vv	("kids.utime.tv_sec",	ru_utime.tv_sec),
	vv	("kids.utime.tv_usec",	ru_utime.tv_usec),
	vv	("kids.stime.tv_sec",	ru_stime.tv_sec),
	vv	("kids.stime.tv_usec",	ru_stime.tv_usec),
	vv	("kids.maxrss",		ru_maxrss),
	vv	("kids.minflt",		ru_minflt),
	vv	("kids.majflt",		ru_majflt),
	vv	("kids.inblock",	ru_inblock),
	vv	("kids.outblock",	ru_oublock),
	vv	("kids.nvcsw",		ru_nvcsw),
	vv	("kids.nivcsw",		ru_nivcsw),
#ifndef	__linux__
	vv	("kids.ixrss",		ru_ixrss),
	vv	("kids.idrss",		ru_idrss),
	vv	("kids.isrss",		ru_isrss),
	vv	("kids.nswap",		ru_nswap),
	vv	("kids.msgsnd",		ru_msgsnd),
	vv	("kids.msgrcv",		ru_msgrcv),
	vv	("kids.nsignals",	ru_nsignals),
#endif
	};

	VMETA		*A=		a;
	va	("self.utime.tv_sec",	ru_utime.tv_sec);
	vc	("self.utime.tv_usec",	ru_utime.tv_usec);
	va	("self.stime.tv_sec",	ru_stime.tv_sec);
	vc	("self.stime.tv_usec",	ru_stime.tv_usec);
	va	("self.maxrss",		ru_maxrss);
	va	("self.minflt",		ru_minflt);
	va	("self.majflt",		ru_majflt);
	va	("self.inblock",	ru_inblock);
	va	("self.outblock",	ru_oublock);
	va	("self.nvcsw",		ru_nvcsw);
	va	("self.nivcsw",		ru_nivcsw);
#ifndef	__linux__
	va	("self.ixrss",		ru_ixrss);
	va	("self.idrss",		ru_idrss);
	va	("self.isrss",		ru_isrss);
	va	("self.nswap",		ru_nswap);
	va	("self.msgsnd",		ru_msgsnd);
	va	("self.msgrcv",		ru_msgrcv);
	va	("self.nsignals",	ru_nsignals);
#endif
	vb	("kids.utime.tv_sec",	ru_utime.tv_sec);
	vc	("kids.utime.tv_usec",	ru_utime.tv_usec);
	vb	("kids.stime.tv_sec",	ru_stime.tv_sec);
	vc	("kids.stime.tv_usec",	ru_stime.tv_usec);
	vb	("kids.maxrss",		ru_maxrss);
	vb	("kids.minflt",		ru_minflt);
	vb	("kids.majflt",		ru_majflt);
	vb	("kids.inblock",	ru_inblock);
	vb	("kids.outblock",	ru_oublock);
	vb	("kids.nvcsw",		ru_nvcsw);
	vb	("kids.nivcsw",		ru_nivcsw);
#ifndef	__linux__
	vb	("kids.ixrss",		ru_ixrss);
	vb	("kids.idrss",		ru_idrss);
	vb	("kids.isrss",		ru_isrss);
	vb	("kids.nswap",		ru_nswap);
	vb	("kids.msgsnd",		ru_msgsnd);
	vb	("kids.msgrcv",		ru_msgrcv);
	vb	("kids.nsignals",	ru_nsignals);
#endif
}
