/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"int.h"
#include	"a.h"
#include	"pts.h"
#include	<stdlib.h>	/* grantpt */

__attribute__((always_inline))
static	inline	int	high	(int a)
{	int		b=
	fcntl		(a,F_DUPFD_CLOEXEC,FDHIGH);
	close		(a);
	return		b;
}

SCV	action				(int,siginfo_t *,void *);
SCV	ptsinit				(void)
{	VMETA		*A=		Gz.to[0];
	PDATA		*P=
	pdata				(A);

	int		s;
	for				(s=SIGRTMIN;Gz.sig[s];s++);
	P->sig=				s;
	Gz.sig[s]=			A;

	Gz.sa[0].sa_flags=		SA_SIGINFO|SA_RESTART;
	Gz.sa[0].sa_sigaction=		action;
	sigaction			(s,Gz.sa,NULL);

	P->m[0]=	high		(open("/dev/ptmx",O_RDWR));
	grantpt				(P->m[0]);
	unlockpt			(P->m[0]);
	P->s[0]=	open		(ptsname(P->m[0]),O_RDONLY);
	P->s[1]=	open		(ptsname(P->m[0]),O_WRONLY);

	P->m[1]=	high		(open("/dev/ptmx",O_RDWR));
	grantpt				(P->m[1]);
	unlockpt			(P->m[1]);
	P->s[2]=	open		(ptsname(P->m[1]),O_WRONLY);

	PSAVE		*e=		P->save;
	e->d[0]=			P->host0->i;
	e->d[1]=	fcntl		(e->d[0],F_DUPFD_CLOEXEC,FDHIGH);

	e->f=		fcntl		(e->d[0],F_GETFL);
	tcgetattr			(e->d[0],e->T);
	e->T[1]=			 e->T[0];
	close				(e->d[0]);

	PSAVE		*f=		P->save+1;
	f->d[0]=			P->host1->i;
	f->d[1]=	fcntl		(f->d[0],F_DUPFD_CLOEXEC,FDHIGH);
	f->f=		fcntl		(f->d[0],F_GETFL);
	tcgetattr			(f->d[0],f->T);
	f->T[1]=			 f->T[0];
	close				(f->d[0]);

	PSAVE		*g=		P->save+2;
	g->d[0]=			P->host2->i;
	g->d[1]=	fcntl		(g->d[0],F_DUPFD_CLOEXEC,FDHIGH);
	g->f=		fcntl		(g->d[0],F_GETFL);
	tcgetattr			(g->d[0],g->T);
	g->T[1]=			 g->T[0];
	close				(g->d[0]);

	cfmakeraw			(e->T+1);
	tcsetattr			(e->d[1],TCSANOW,e->T+1);

	cfmakeraw			(f->T+1);
	tcsetattr			(f->d[1],TCSANOW,f->T+1);

	cfmakeraw			(g->T+1);
	tcsetattr			(g->d[1],TCSANOW,g->T+1);

	PSAVE		*k=		P->save+3;
	k->d[0]=			P->fake0->i;
	k->d[1]=	dup2		(P->s[0],k->d[0]);
	close				(P->s[0]);

	PSAVE		*l=		P->save+4;
	l->d[0]=			P->fake1->i;
	l->d[1]=	dup2		(P->s[1],l->d[0]);
	close				(P->s[1]);

	PSAVE		*m=		P->save+5;
	m->d[0]=			P->fake2->i;
	m->d[1]=	dup2		(P->s[2],m->d[0]);
	close				(P->s[2]);

/*	From p[0][0]  pseudo   terminal host input when available signal
        From p[1][0]  pseudo   terminal host input when available signal
	from e->d[1]  pipe,    terminal        input when avaialble signal
*/

	pid_t		p=
	getpid				();

	fcntl				(P->m[0],F_SETOWN,p);
	fcntl				(P->m[1],F_SETOWN,p);
	fcntl				(e->d[1],F_SETOWN,p);

	fcntl				(P->m[0],F_SETFL,O_ASYNC|O_NONBLOCK);
	fcntl				(P->m[1],F_SETFL,O_ASYNC|O_NONBLOCK);
	fcntl				(e->d[1],F_SETFL,O_ASYNC|O_NONBLOCK);

	fcntl				(P->m[0],F_SETSIG,s);
	fcntl				(P->m[1],F_SETSIG,s);
	fcntl				(e->d[1],F_SETSIG,s);

/*
dprintf	(P->save[1].d[1],"init completed\n\r");
dprintf	(P->save[1].d[1],"P->m[0]=%i\n\r",P->m[0]);
dprintf	(P->save[1].d[1],"P->m[1]=%i\n\r",P->m[1]);
dprintf	(P->save[1].d[1],"e->d[1]=%i\n\r",e->d[1]);
dprintf	(P->save[1].d[1],"P->sig=%i s=%i\n\r",P->sig,s);
dprintf	(P->save[1].d[1],"errna=%i\n\r",errna);
*/

	*Gz.at=				ptsinit;
	argot_next			();
}

__attribute__((noinline))
SCV	action					(int s,siginfo_t *i,void *v)
{	int		d,z=			errna;
		VMETA		*A=		Gz.sig[s];
	if				nay	(A==NULL)
	return;

	do
	{	d=				0;
		PDATA		*P=
		pdata				(A);
		uint8_t		*a=		P->io;
		ssize_t		b;

		b=	read			(P->m[0],a,sizeof(P->io));
		if			nay	(b>0)
		{	PSAVE	*f=		P->save+1;
			write			(f->d[1],a,b);
			write			(P->host1log->i,a,b);
			d=			1;
		}

		b=	read			(P->m[1],a,HUGE);
		if			nay	(b>0)
		{	PSAVE	*g=		P->save+2;
			write			(g->d[1],a,b);
			write			(P->host2log->i,a,b);
			d=			1;
		}

		PSAVE		*e=		P->save;
		b=	read			(e->d[1],a,HUGE);
		if			nay	(b>0)
		{	write			(P->m[0],a,b);
			write			(P->host0log->i,a,b);
			d=			1;
		}
	}
	while					(d!=0);

	errna=					z;
}

__attribute__((noinline))
SCV	ptsfini_		(VMETA *A)
{	sched_yield		();
	PDATA		*P=
	pdata			(A);
	siginfo_t	i;
	action			(P->sig,&i,A);

	Gz.sig[P->sig]=		NULL;
	signal			(P->sig,SIG_IGN);

	close			(P->m[0]);
	close			(P->m[1]);

	dup2			(P->save[0].d[1],
				 P->save[0].d[0]);

	dup2			(P->save[1].d[1],
				 P->save[1].d[0]);

	dup2			(P->save[2].d[1],
				 P->save[2].d[0]);

	fcntl			(P->save[0].d[0],F_SETFL,
				 P->save[0].f);

	fcntl			(P->save[1].d[0],F_SETFL,
				 P->save[1].f);

	fcntl			(P->save[2].d[0],F_SETFL,
				 P->save[2].f);

	tcsetattr		(P->save[0].d[0],TCSANOW,
				 P->save[0].T);

	tcsetattr		(P->save[1].d[0],TCSANOW,
				 P->save[1].T);

	tcsetattr		(P->save[2].d[0],TCSANOW,
				 P->save[2].T);

	close			(P->save[0].d[1]);
	close			(P->save[1].d[1]);
	close			(P->save[2].d[1]);
	close			(P->save[3].d[1]);
	close			(P->save[4].d[1]);
	close			(P->save[5].d[1]);
}

__attribute__((noinline))
SCV	ptsfix		(void)
{	static
	struct	termios	T=
	{	.c_iflag=			0x6504,
		.c_oflag=			5,
		.c_cflag=			0xbf,
		.c_lflag=			0x8a3b,
		.c_cc=
		{	0x3,	0x1c,	0x7f,	0x15,
			0x4,	0x0,	0x1,	0x0,
			0x11,	0x13,	0x1a,	0x0,
			0x12,	0xf,	0x17,	0x16,
		},
	};

	fcntl		(0,F_SETFL,0);
	tcsetattr	(0,TCSANOW,&T);
}

SCV	ptsfini			(void)
{	VMETA		*A=	Gz.to[0];
	PDATA		*P=
	pdata			(A);
	if		yay	(P->sig==0)	return;
	ptsfini_		(A);
	*Gz.at=			ptsfini;
	argot_next		();
}

SCV	ptsfree			(VMETA *A)
{	PDATA		*P=
	pdata			(A);
	if		yay	(P->sig==0)	return;
	ptsfini_		(A);
	var_free		(A);
/*	vmeta_free		(A);
*/
}
__attribute__((always_inline))
static	inline	void	ptssubnew	(VMETA *A)
{	int4init			(A);
	A->free=			ptsfree;
	map_add				(A,0,sizeof(PDATA));

	PDATA		*P=
	pdata				(A);

	P->host1->i=	P->fake1->i=	1;
	P->host2->i=	P->fake2->i=	2;

	P->host0log->i=
	P->host1log->i=
	P->host2log->i=			-1;

	VMETA		*B;

	B=	var_new_sub		(".host.0",A);
	int4init			(B);
	P->host0=			&B->value;

	B=	var_new_sub		(".host.1",A);
	int4init			(B);
	P->host1=			&B->value;

	B=	var_new_sub		(".host.2",A);
	int4init			(B);
	P->host2=			&B->value;

	B=	var_new_sub		(".host.0.log",A);
	int4init			(B);
	P->host0log=			&B->value;

	B=	var_new_sub		(".host.1.log",A);
	int4init			(B);
	P->host1log=			&B->value;

	B=	var_new_sub		(".host.2.log",A);
	int4init			(B);
	P->host2log=			&B->value;

	B=	var_new_sub		(".fake.0",A);
	int4init			(B);
	P->fake0=			&B->value;

	B=	var_new_sub		(".fake.1",A);
	int4init			(B);
	P->fake1=			&B->value;

	B=	var_new_sub		(".fake.2",A);
	int4init			(B);
	P->fake2=			&B->value;
}

SCV	pts		(void)	{tvarnewab(ptssubnew,pts);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180529",
	.official=	"20180529",
	.update=	"20200811"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(pts,		"pts");
	aa		(ptsfix,	"ptsfix");
	aa		(ptsfini,	"ptsfini");
	aa		(ptsinit,	"ptsinit");
	aa_fini		();
};

