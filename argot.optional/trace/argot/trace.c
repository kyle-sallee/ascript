/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
/*	from sire sigchld is being annexed */
#include	"sire.h"
#include	"trace.h"
#include	<sched.h>
#include	<signal.h>
#include	<stdio.h>	/* for snprintf */
#include	<sys/ptrace.h>
#include	<sys/syscall.h>
#include	<sys/time.h>

static	TRACEDATA	td;

/*
#define	BM		__builtin_memcmp
*/

__attribute__((always_inline))
static	inline	int	same	(uint8_t const *a,uint8_t const *b)
{	return	*(uint32_t *)a==*(uint32_t *)b;
}

__attribute__((always_inline))
static	inline	int	tval	(VLESS *A)
{	uint8_t		*a=	A->textaddr;
	if		nay	(same(a,"file"))	return	TRACE_FILE;
	else	if	nay	(same(a,"line"))	return	TRACE_LINE;
	else	if	nay	(same(a,"name"))	return	TRACE_NAME;
	else	if	nay	(same(a,"orig"))	return	TRACE_ORIGIN;
	else	if	nay	(same(a,"para"))	return	TRACE_PARA;
/*	else	if	nay	(same(a,"part"))	return	TRACE_PART;*/
	else	if	nay	(same(a,"skip"))	return	TRACE_SKIP;
	else	if	nay	(same(a,"targ"))	return	TRACE_TARGET;
	else	if	nay	(same(a,"time"))	return	TRACE_TIME;
	else	if	nay	(same(a,"toll"))	return	TRACE_TOLL;
}

SCV	trace				(void)
{	VLESS		*A=	arga	(Gz.at+0),
			*B=	arga	(Gz.at+1);

	int		a=		0;

	for				(;B>A;A++)
	a|=	tval			(A);

	td.i=				a;
	td.d=				1;
	*Gz.at=				trace;
	argot_next			();
}

SCV	trace_end	(int a,siginfo_t *b,void *c)
{	ptrace		(PTRACE_DETACH,b->si_pid,0,0);
}

static	CALIGN	int	tracer		(void *V)
{	Gz.sa[0].sa_flags=		SA_RESTART|SA_SIGINFO;
	Gz.sa[0].sa_sigaction=		trace_end;
	sigaction			(SIGUSR1,Gz.sa,NULL);

	td.L=				Gz.at;
	pid_t		p=		td.p[0];	/* progenitor process */
	ptrace				(PTRACE_ATTACH,p,0,0);
	while				(1)
	pause				();
/*	sleep				(3600);	*/
}

SCV	trace_file		(void)
{	td.len+=
	snprintf		(td.text
				+td.len
				,HUGE
				-td.len
				,"%-10s%-10s%s\n","trace","file"
				,script_name());
}

SCV	trace_name		(void)
{	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%s\n","trace","argot",
				 script_argot());
}

SCV	trace_line		(void)
{	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%i\n","trace","line",
				 script_line_number());
}

/*
SCV	trace_part		(void)
{	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%i\n","trace","part",
				 Gz.aat->from&0xff);
}
*/

SCV	trace_skip		(void)
{	if		nay	(Gz.at!=(td.L+1))
	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%i\n","trace","skip",td.L-Gz.at);
}

SCV	to			(VMETA *A,uint8_t *b)
{	if			(A==NULL);
	return;

	uint8_t		av	[0x20];
	uint8_t		*c,*d;

	sprintf			(av,b);

	if			(A->len==0)
	{	c=		"self ref";
		d=		A->textaddr;
	}
	else
	{	c=		"variable";
		d=		A->name;
	}

	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%-10s%s\n",
				 "trace",av,c,d);
}

SCV	trace_target		(void)
{	to			(Gz.to[0],"target");
}

SCV	trace_origin		(void)
{	to			(Gz.to[1],"origin");
}


SCV	trace_para		(void)
{	if		yay	(arga(Gz.at)==arga(Gz.at+1))
	return;

	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%i\n",
				 "trace","c",arga(Gz.at+1)-arga(Gz.at));

	uint8_t		av	[0x20];
	uint8_t		*b;
	int		c;
	VLESS		*B,*E;

	for				(c=0
					,B=arga(Gz.at  )
					,E=arga(Gz.at+1);E>B;B++)
	{	snprintf		(av,0x20,"v[%i]",c++);

		if			((B->vam==NULL)||((VMETA *)B!=*B->vam))
		b=			"variable";
		else
		b=			"self ref";

		td.len+=
		snprintf		(td.text+
					 td.len,
					 HUGE-
					 td.len,
					 "%-10s%-10s%-10s%s\n",
					 "trace",av,b,B->textaddr);
	}
}

SCV	trace_time			(void)
{	clock_gettime			(CLOCK_PROCESS_CPUTIME_ID,td.T+1);

	td.T[1].tv_sec-=		td.T[0].tv_sec;
	td.T[1].tv_nsec-=		td.T[0].tv_nsec;
	if			nay	(0>td.T[1].tv_nsec)
	{	td.T[1].tv_nsec+=	0x3b9aca00;
		td.T[1].tv_sec-=	1;
	}

	td.len+=
	snprintf			(td.text+
					 td.len,
					 HUGE-
					 td.len,
					 "%-10s%-10s%li.%09li\n",
					 "trace","time",
					td.T[1].tv_sec,td.T[1].tv_nsec);
	clock_gettime			(CLOCK_PROCESS_CPUTIME_ID,td.T);
}

SCV	trace_toll		(void)
{	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%li\n",
				 "trace","toll",td.t);
}

SCV	troff			(void)
{	if			(td.p[1])
	{	sigqueue	(td.p[1],SIGUSR1,
				(union sigval){.sival_ptr=NULL});
		td.p[1]=	0;
	}
	*Gz.at=			troff;
	argot_next		();
}

__attribute__((noinline))
SCV	trace_parse		(void)
{	int		i=	td.i;
	td.len=		0;
	if			(i&TRACE_TIME)	trace_time	();
	if			(i&TRACE_TOLL)	trace_toll	();

	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s\n\n","trace","fini");

/*
	td.len+=
	snprintf		(td.text+
				 td.len,
				 HUGE-
				 td.len,
				 "%-10s%-10s%-10i%i\n\n","trace","fini",
				 td.L->from>>0x20,td.L->from&0xff);
*/

	if			(i&TRACE_FILE)	trace_file	();
	if			(i&TRACE_LINE)	trace_line	();
	if			(i&TRACE_SKIP)	trace_skip	();
/*	if			(i&TRACE_PART)	trace_part	();	*/
	if			(i&TRACE_NAME)	trace_name	();
	if			(i&TRACE_PARA)	trace_para	();
	if			(i&TRACE_TARGET)trace_target	();
	if			(i&TRACE_ORIGIN)trace_origin	();

	writeall		(td.d,td.text,td.len);
}

SCV	trap				(int a,siginfo_t *b,void *c)
{	if			yay	(b->si_signo==SIGCHLD)
	td.sa[0].sa_sigaction		(a,b,c);

	switch				(b->si_code)
	{	case	CLD_EXITED:
		case	CLD_KILLED:
		case	CLD_DUMPED:	_exit	(0);
		default:		return;
		case	CLD_TRAPPED:	break;
	}

	td.t++;
	if			nay	(Gz.at!=td.L)
	{	trace_parse		();
		td.L=			Gz.at;
		td.t=			0;
	}

	pid_t		p=		b->si_pid;
	if			nay	(ptrace(PTRACE_SINGLESTEP,p,0,0)!=0)
	_exit				(0);
}

static	inline	void	action_init	(void)
{	if			nay	(Gz.sig[SIGTRAP]!=NULL)
	return;
	Gz.sig[SIGTRAP]=		(void *)	-1;
	Gz.sa[0].sa_flags=		SA_RESTART|SA_SIGINFO;
	Gz.sa[0].sa_sigaction=		trap;
	sigaction			(SIGTRAP,Gz.sa,NULL);
	sigaction			(SIGCHLD,Gz.sa,td.sa);
}

static	CALIGN	int	tracer		(void *);
SCV	tron				(void)
{	action_init			();

	*Gz.at=				tron;

	if			yay	(td.p[1]==0)
	{	td.p[0]=
		getpid			();
		pids.last=
		td.p[1]=
		clone			(tracer,td.stack+
					 sizeof(td.stack),
					 CLONE_VM|SIGCHLD,NULL);
		sleep			(1);
	}
	argot_next			();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180913",
	.official=	"20180913",
	.update=	"20200707"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(trace,		"trace");
	aa		(tron,		"tron");
	aa		(troff,		"troff");
	aa_fini		();
};
