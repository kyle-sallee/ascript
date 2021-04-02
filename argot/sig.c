/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"ray.h"
#include	"sig.h"
#include	"trek.h"

/* for sigwinchkey */
#ifdef		__linux__
#include	<sys/ioctl.h>
#include	<sys/kd.h>
#include	<linux/keyboard.h>
#endif

/*
OPERATOR	opsig[1];
*/

/*
PALIGN
static	int8_t	sam	[0x10000];
*/

/*
__attribute__((always_inline))
static	inline	int8_t	sigint	(uint8_t *a)
{	return	sam[bit128_to_bit16	(a)];
}
*/

static	inline	int8_t	sigint	(uint8_t *a)
{	return	0;
}

SCV	equal			(void)
{
/*	toint			(Gz.to[1],Gz.to[0]);	*/
	VMETA		*A=	Gz.to[0];
	A->value.i=		Gz.to[1]->value.i;
	*Gz.at=			equal;
	argot_next		();
}

static		void	action		(int,siginfo_t *,void *);

SCV	siginit				(void)
{	VMETA		*A=		Gz.to[0];
	SIGDATA		*a=
	sigdata				(A);
	sigrelease			(A);

/*	int		b=		a->sig.i;	*/
	int		b=		A->value.i;
	if			nay	(0>=b)
	{	for			(b=SIGRTMIN;Gz.sig[b];b++);
/*		a->sig.i=		b;	*/
		A->value.i=		b;
	}

	a->inuse=			b;
	a->afore=			Gz.sig[b];
	Gz.sig[b]=			A;

	Gz.sa[0].sa_sigaction=		action;
	Gz.sa[0].sa_flags=		a->flag.i|SA_SIGINFO;

	sigaction			(b,Gz.sa,a->sa);
	*Gz.at=				siginit;
	argot_next			();
}

SCV	action				(int n,siginfo_t *i,void *v)
{	VMETA		*A=		Gz.sig[n];
	if			nay	(A==NULL)	return;
	int		b=		errna;
	SIGDATA		*a=
	sigdata				(A);
	a->pid.i=					i->si_pid;
	a->uid.i=					i->si_uid;
	a->val.i=			(uintptr_t)	i->si_ptr;
	a->sum.i++;
	target_object_to_stack		();
	__builtin_memcpy		(Gz.to,a->to,sizeof(Gz.to));
	void		(**B)	(void)=	Gz.at;
	(*(Gz.at=	a->pin))	();
	Gz.at=			B;
	target_object_from_stack	();
	errna=				b;
}

SCV	sigfini				(void)
{	VMETA		*A=		Gz.to[0];
/*	SIGDATA		*a=
	sigdata				(A);
*/
	sigrelease			(A);
	*Gz.at=				sigfini;
	argot_next			();
}

SCV	queue					(void)
{	VMETA		*A=	parapass	(arga(NULL)+0);
	VMETA		*B=	parapass	(arga(NULL)+1);
	VMETA		*C=	parapass	(arga(NULL)+2);
/*	denwant					(A);
	denwant					(B);
	denwant					(C);
*/
	pid_t		a=			A->value.i;
	int		b=			B->value.i;
	union sigval	c=	{.sival_int=	C->value.i};

	int		d=
	sigqueue				(a,b,c);

	*Gz.at=					queue;
	argot_jump				(d==0);
}

SCV	block			(void)
{
/*	denwant			(   Gz.to[0]);	*/
	sigset_t		b;
	sigemptyset		(&b);
	sigaddset		(&b,Gz.to[0]->value.i);
	sigprocmask		(SIG_BLOCK,&b,NULL);
	argot_next		();
}

SCV	unblock			(void)
{
/*	denwant			(   Gz.to[0]);	*/
	sigset_t		b;
	sigemptyset		(&b);
	sigaddset		(&b,Gz.to[0]->value.i);
	sigprocmask		(SIG_UNBLOCK,&b,NULL);
	argot_next		();
}

SCV	sigrestart		(void)
{	VMETA		*A=	Gz.to[0];
	SIGDATA		*a=
	sigdata			(A);
	a->flag.i|=		SA_RESTART;
	*Gz.at=			sigrestart;
	argot_next		();
}

SCV	signodefer		(void)
{	VMETA		*A=	Gz.to[0];
	SIGDATA		*a=
	sigdata			(A);
	a->flag.i|=		SA_NODEFER;
	*Gz.at=			sigrestart;
	argot_next		();
}

SCV	sigtarget			(void)
{	sigdata(Gz.to[0])->to[0]=	Gz.to[1];
	*Gz.at=				sigtarget;
	argot_next			();
}

SCV	sigorigin			(void)
{	sigdata(Gz.to[0])->to[1]=	Gz.to[1];
	*Gz.at=				sigorigin;
	argot_next			();
}

#ifdef	__linux__
SCV	_sigwinchkey			(void)
{	errna=				0;
	int		a=
	open				("/dev/console",O_RDONLY);
	if			nay	(0>a)
	{	argot_next		();
		return;
	}

	ioctl				(a,KDSIGACCEPT,SIGWINCH);

	struct	kbentry	b;
	b.kb_value=			K_SPAWNCONSOLE;

/*	denwant				(Gz.to[0]);		*/
	uint64_t	c=		 Gz.to[0]->value.i;
	b.kb_index=			c;
	b.kb_table=			c >> 8;
	ioctl				(c,KDSKBENT,&b);
	close				(a);
	argot_skip			();
}
#endif

SCV	sigpin			(void)
{	void		(**P)	(void);
	if			(Gz.to[1]->value.i=='\'')
	P=	nearfind_fast	(Gz.to[1]->textaddr,partfar(NULL));
	else
	P=	farfind_fast	(Gz.to[1]->textaddr);

	sigdata(Gz.to[0])->pin=	P;
	*Gz.at=			sigpin;
	argot_next		();
}


SCV	sigpid	(void)	{tsubab(sigpidsubnew,sigpid);}
SCV	sigsum	(void)	{tsubab(sigsumsubnew,sigsum);}
SCV	siguid	(void)	{tsubab(siguidsubnew,siguid);}
SCV	sigval	(void)	{tsubab(sigvalsubnew,sigval);}
SCV	sig_	(void)	{tvarnewa (sigsubnew);}

SCV	sig			(void)
{	*Gz.at=		sig;
	tvarnewab		(sigsubnew,sig_);
}

SCV	sigyay			(void)
{
/*	denwant			(Gz.to[0]);	*/
	*Gz.at=			sigyay;
	int8_t		a=	Gz.to[0]->value.i;
	argot_jump		(Gz.sig[a]!=NULL);
}

SCV	signay			(void)
{
/*	denwant			(Gz.to[0]);	*/
	*Gz.at=			signay;
	int8_t		a=	Gz.to[0]->value.i;
	argot_jump		(Gz.sig[a]==NULL);
}
/*
typedef	struct
{	uint8_t		a[0x10];
	uint8_t		b;
	int8_t		c;
}	SAMC;
*/

#define	va(a)		{.name=#a		\
			,.len=strlen(#a)	\
			,.value.i=a		\
			,.io.flag=datamapuse	\
			,.op=opint4}

#define	vb(a,b)		{.name=a		\
			,.len=strlen(a)		\
			,.value.i=b		\
			,.io.flag=datamapuse	\
			,.op=opint4}

#define	vc(b) map_init(A);A->show=Gz.out.den4;vattach_faster(A,#b);A++
#define	vd(b) map_init(A);A->show=Gz.out.den4;vattach_faster(A, b);A++

static	void		signame_	(void)	{argot_next	();}

SCV			signame	(void)
{	static
	VMETA		a[]=
{

#ifdef	SIGHUP
va	(SIGHUP),
#endif

#ifdef	SIGINT
va	(SIGINT),
#endif

#ifdef	SIGQUIT
va	(SIGQUIT),
#endif

#ifdef	SIGILL
va	(SIGILL),
#endif

#ifdef	SIGTRAP
va	(SIGTRAP),
#endif

#ifdef	SIGABRT
va	(SIGABRT),
#endif

#ifdef	SIGIOT
va	(SIGIOT),
#endif

#ifdef	SIGBUS
va	(SIGBUS),
#endif

#ifdef	SIGFPE
va	(SIGFPE),
#endif

#ifdef	SIGKILL
va	(SIGKILL),
#endif

#ifdef	SIGUSR1
va	(SIGUSR1),
#endif

#ifdef	SIGSEGV
va	(SIGSEGV),
#endif

#ifdef	SIGUSR2
va	(SIGUSR2),
#endif

#ifdef	SIGPIPE
va	(SIGPIPE),
#endif

#ifdef	SIGALRM
va	(SIGALRM),
#endif

#ifdef	SIGTERM
va	(SIGTERM),
#endif

#ifdef	SIGSTKFLT
va	(SIGSTKFLT),
#endif

#ifdef	SIGCLD
va	(SIGCLD),
#endif

#ifdef	SIGCHLD
va	(SIGCHLD),
#endif

#ifdef	SIGCONT
va	(SIGCONT),
#endif

#ifdef	SIGSTOP
va	(SIGSTOP),
#endif

#ifdef	SIGTSTP
va	(SIGTSTP),
#endif

#ifdef	SIGTTIN
va	(SIGTTIN),
#endif

#ifdef	SIGTTOU
va	(SIGTTOU),
#endif

#ifdef	SIGURG
va	(SIGURG),
#endif

#ifdef	SIGXCPU
va	(SIGXCPU),
#endif

#ifdef	SIGXFSZ
va	(SIGXFSZ),
#endif

#ifdef	SIGVTALRM
va	(SIGVTALRM),
#endif

#ifdef	SIGPROF
va	(SIGPROF),
#endif

#ifdef	SIGWINCH
va	(SIGWINCH),
#endif

#ifdef	SIGIO
va	(SIGIO),
#endif

#ifdef	SIGPOLL
va	(SIGPOLL),
#endif

#ifdef	SIGPWR
va	(SIGPWR),
#endif

#ifdef	SIGSYS
va	(SIGSYS),
#endif

#ifdef	SIGUNUSED
va	(SIGUNUSED),
#endif

vb	("RT32",32),
vb	("RT33",33),
vb	("RT34",34),
vb	("RT35",35),
vb	("RT36",36),
vb	("RT37",37),
vb	("RT38",38),
vb	("RT39",39),

vb	("RT40",40),
vb	("RT41",41),
vb	("RT42",42),
vb	("RT43",43),
vb	("RT44",44),
vb	("RT45",45),
vb	("RT46",46),
vb	("RT47",47),
vb	("RT48",48),
vb	("RT49",49),

vb	("RT50",50),
vb	("RT51",51),
vb	("RT52",52),
vb	("RT53",53),
vb	("RT54",54),
vb	("RT55",55),
vb	("RT56",56),
vb	("RT57",57),
vb	("RT58",58),
vb	("RT59",59),

vb	("RT60",60),
vb	("RT61",61),
vb	("RT62",62),
vb	("RT63",63),
vb	("RT64",64),
};

	VMETA		*A=	a;

#ifdef	SIGHUP
vc	(SIGHUP);
#endif

#ifdef	SIGINT
vc	(SIGINT);
#endif

#ifdef	SIGQUIT
vc	(SIGQUIT);
#endif

#ifdef	SIGILL
vc	(SIGILL);
#endif

#ifdef	SIGTRAP
vc	(SIGTRAP);
#endif

#ifdef	SIGABRT
vc	(SIGABRT);
#endif

#ifdef	SIGIOT
vc	(SIGIOT);
#endif

#ifdef	SIGBUS
vc	(SIGBUS);
#endif

#ifdef	SIGFPE
vc	(SIGFPE);
#endif

#ifdef	SIGKILL
vc	(SIGKILL);
#endif

#ifdef	SIGUSR1
vc	(SIGUSR1);
#endif

#ifdef	SIGSEGV
vc	(SIGSEGV);
#endif

#ifdef	SIGUSR2
vc	(SIGUSR2);
#endif

#ifdef	SIGPIPE
vc	(SIGPIPE);
#endif

#ifdef	SIGALRM
vc	(SIGALRM);
#endif

#ifdef	SIGTERM
vc	(SIGTERM);
#endif

#ifdef	SIGSTKFLT
vc	(SIGSTKFLT);
#endif

#ifdef	SIGCLD
vc	(SIGCLD);
#endif

#ifdef	SIGCHLD
vc	(SIGCHLD);
#endif

#ifdef	SIGCONT
vc	(SIGCONT);
#endif

#ifdef	SIGSTOP
vc	(SIGSTOP);
#endif

#ifdef	SIGTSTP
vc	(SIGTSTP);
#endif

#ifdef	SIGTTIN
vc	(SIGTTIN);
#endif

#ifdef	SIGTTOU
vc	(SIGTTOU);
#endif

#ifdef	SIGURG
vc	(SIGURG);
#endif

#ifdef	SIGXCPU
vc	(SIGXCPU);
#endif

#ifdef	SIGXFSZ
vc	(SIGXFSZ);
#endif

#ifdef	SIGVTALRM
vc	(SIGVTALRM);
#endif

#ifdef	SIGPROF
vc	(SIGPROF);
#endif

#ifdef	SIGWINCH
vc	(SIGWINCH);
#endif

#ifdef	SIGIO
vc	(SIGIO);
#endif

#ifdef	SIGPOLL
vc	(SIGPOLL);
#endif

#ifdef	SIGPWR
vc	(SIGPWR);
#endif

#ifdef	SIGSYS
vc	(SIGSYS);
#endif

#ifdef	SIGUNUSED
vc	(SIGUNUSED);
#endif

vd	("RT32");
vd	("RT33");
vd	("RT34");
vd	("RT35");
vd	("RT36");
vd	("RT37");
vd	("RT38");
vd	("RT39");

vd	("RT40");
vd	("RT41");
vd	("RT42");
vd	("RT43");
vd	("RT44");
vd	("RT45");
vd	("RT46");
vd	("RT47");
vd	("RT48");
vd	("RT49");

vd	("RT50");
vd	("RT51");
vd	("RT52");
vd	("RT53");
vd	("RT54");
vd	("RT55");
vd	("RT56");
vd	("RT57");
vd	("RT58");
vd	("RT59");

vd	("RT60");
vd	("RT61");
vd	("RT62");
vd	("RT63");
vd	("RT64");

	*Gz.at=			signame_;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180328",
	.official=	"20180328",
	.update=	"20200923",
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(sig,		"sig");
#ifdef	__linux__
	aa		(_sigwinchkey,	"sigwinchkey");
#endif
	aa		(signame,	"signame");
	aa		(sigfini,	"sigfini");
	aa		(siginit,	"siginit");
	aa		(sigyay,	"sigyay");
	aa		(signay,	"signay");
	aa		(sigsum,	"sigsum");
	aa		(siguid,	"siguid");
	aa		(sigpid,	"sigpid");
	aa		(sigval,	"sigval");
	aa		(sigrestart,	"sigrestart");
	aa		(signodefer,	"signodefer");
	aa		(queue,		"sigqueue");
	aa		(block,		"sigblock");
	aa		(unblock,	"sigunblock");
	aa		(sigorigin,	"sigorigin");
	aa		(sigtarget,	"sigtarget");
	aa		(sigpin,	"sigpin");
	aa_fini		();

	opsig[0]=		opint8[0];
	opsig[0].equal=		equal;
};
