/*	By Kyle Sallee from 2015 ... 2020 copyrighted.
	In the ascript manual page; the license is provided.
*/

#define		PROGRAM		1

#ifndef		_GNU_SOURCE
#define		_GNU_SOURCE
#endif
#define		_POSIX_SOURCE
#define		_POSIX_C_SOURCE		199309L	/* for siginfo_t in sigaction */
#define		_XOPEN_SOURCE		700
#define		_XOPEN_SOURCE_EXTENDED
#define		__USE_XOPEN

#define		PROGRAM		1
#include	"ascript.h"
#include	"parse.h"
#include	<dlfcn.h>

/*#include	<stddef.h>*/	/* for offsetof */

__attribute__((visibility("hidden")))
	CALIGN	uint8_t	main	(int argc,uint8_t *argv[])
{
/*
warnx	("Gz=	%p",&Gz);
warnx	("sizeof(VMETA)=%i",sizeof(VMETA));
warnx	("sizeof(IO)=%i",sizeof(IO));
warnx	("sizeof(OPERATOR)=%x",sizeof(OPERATOR));
warnx	("sizeof(VMETA)=%i",sizeof(VMETA));
warnx	("offsetof(VMETA,map)=%i",offsetof(VMETA,map));
warnx	("offsetof(VMETA,text)=%i",offsetof(VMETA,text));
warnx	("offsetof(VMETA,name)=%i",offsetof(VMETA,name));
warnx	("sizeof(HEAP)=%likB",sizeof(HEAP)/1024);
warnx	("sizeof(PIDS)=%likB",sizeof(PIDS)/1024);
warnx	("sizeof(DHTABLE)=%likB",sizeof(DHTABLE)/1024);
warnx	("sizeof(__time_t)=%i",sizeof(__time_t));
warnx	("sizeof(struct stat)=%i",sizeof(struct stat));
warnx	("sizeof(VLESS)=%i",sizeof(VLESS));
warnx	("&Gz.at=%p",&Gz.at);
warnx	("sizeof(Gz.op)=%i",sizeof(Gz.op));
warnx	("&Gz.out=%p",&Gz.out);
*/

	Gz.err=			&errno;
	Gz.arg.c=		argc;
	Gz.arg.v=		argv;
	ZYGOTE		*z=
	zygote_init		(argv[1]);	/* allowed */
	Gz.at=			z->head;
	(*Gz.at)		();
	return			0;
}

/*	Not only is Gz required,
	but transparent huge pages
	must be avoided.

	By constructor Gz must be madvise, because
	by constructor Gz data is set.
*/

GzT		Gz;

__attribute__((constructor(101)))
SCV	gz_init			(void)
{
#undef	madvise
	madvise			(&Gz,sizeof(Gz),MADV_NOHUGEPAGE);
	/*	In small scripts for huge pages zeroing
		too many opcodes execute
		IMHO available pages should already have 0 byte values!
	*/

	/* sigfillset is plt/got invocation and overfill, totally inane! */
/*	sigfillset		(&Gz.sa[0].sa_mask);	*/

	*(uint64_t *)
	&Gz.sa[0].sa_mask=	0xffffffffffffffff;
/*	mhub.a=			mhub.v;	*/
	Gz.next.pool.b=		POOL_MAX;
	Gz.next.pool.a=		Gz.heap.pool;
/*	Gz.prp.next=		Gz.prp.init;
	Gz.prp.full=		Gz.prp.init+PRP_INIT;
*/
	Gz.next.scratch=	Gz.heap.scratch;

/*	Gz.next.argot=		Gz.heap.argot;	*/
	Gz.next.data=		Gz.heap.data;
	Gz.next.vless=		Gz.heap.vless;
	Gz.next.pr=		Gz.heap.pr;
	Gz.next.part=		Gz.heap.func;
	Gz.next.vmeta=		Gz.heap.vmeta;
	Gz.next.zygote=		Gz.heap.zygote;
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	equalequal_	(void)
{	Gz.to[1]->op->equalequal	();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	notequal_	(void)
{	Gz.to[1]->op->notequal		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	less_		(void)
{	Gz.to[1]->op->less		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	lessequal_	(void)
{	Gz.to[1]->op->lessequal		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	more_		(void)
{	Gz.to[1]->op->more		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	moreequal_	(void)
{	Gz.to[1]->op->moreequal		();
}

__attribute__((noinline))
__attribute__((aligned(0x10)))
SCV	data_fix		(VMETA *A)
{	Gz.to[0]->op->fromtext	(A);
}

__attribute__((hot))
SCV	equalequal		(void)
{	Gz.to[1]->op->fromtext	(Gz.to[0]);
	(*Gz.at=equalequal_)	();
}

__attribute__((hot))
SCV	notequal		(void)
{	Gz.to[1]->op->fromtext	(Gz.to[0]);
	(*Gz.at=notequal_)	();
}

__attribute__((hot))
SCV	less			(void)
{	Gz.to[1]->op->fromtext	(Gz.to[0]);
	(*Gz.at=less_)		();
}

__attribute__((hot))
SCV	lessequal		(void)
{	Gz.to[1]->op->fromtext	(Gz.to[0]);
	(*Gz.at=lessequal_)	();
}

__attribute__((hot))
SCV	more			(void)
{	Gz.to[1]->op->fromtext	(Gz.to[0]);
	(*Gz.at=more_)		();
}

__attribute__((hot))
SCV	moreequal		(void)
{	Gz.to[1]->op->fromtext	(Gz.to[0]);
	(*Gz.at=moreequal_)	();
}

__attribute__((cold))
static	void	FINI	(void)
{	*Gz.at=	FINI;
	Gz.at--;
}

__attribute__((constructor(103)))
SCV	operator_init			(void)
{	opvalue[0].int_compat=		1;
	opconst[0].byte_compat=		1;

	opvalue[0].equalequal=
	opconst[0].equalequal=		equalequal;

	opvalue[0].notequal=
	opconst[0].notequal=		notequal;

	opvalue[0].less=
	opconst[0].less=		less;

	opvalue[0].lessequal=
	opconst[0].lessequal=		lessequal;

	opvalue[0].more=
	opconst[0].more=		more;

	opvalue[0].moreequal=
	opconst[0].moreequal=		moreequal;

	opvalue[0].data=
	opconst[0].data=		data_fix;

	aa_init				();
	aa_first			(FINI,"FINI");
	aa_fini				();
}

__attribute__((constructor(103)))
SCV	ap_init			(void)
{	void		*v=
	dlopen			("libascript.so." MM,RTLD_LOCAL|RTLD_LAZY);
	dlinfo			(v,RTLD_DI_ORIGIN,Gz.ap.p[0]);
	dlclose			(v);

	int		b=
	open			(Gz.ap.p[0],O_NONBLOCK|O_PATH|O_RDONLY);
	Gz.ap.d[0]=
	fcntl			(b,F_DUPFD_CLOEXEC,FDHIGH);
	__builtin_memcpy	(Gz.ap.p[0],LP,strlen(LP));
	__builtin_memcpy	(Gz.ap.p[1],LP,strlen(LP));
	__builtin_memcpy	(Gz.ap.p[0]+   strlen(LP),"req/",4);
	close			(b);
}

__attribute__((destructor(101)))
SCV	theend				(void)
{	ENDPART		*E;
	if			nay	(  Gz.endpart!=NULL)
	for				(E=Gz.endpart,
					   Gz.endpart= NULL;E;E=E->F)
	{	__builtin_memcpy	(Gz.to,E->to,sizeof(E->to));
		(*(Gz.at=E->L))		();
	}
}
