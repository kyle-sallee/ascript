/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"argot.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"ray.h"
#include	"sire.h"
#include	<stdio.h>
#include	<sys/ioctl.h>
#include	<sys/vt.h>
#include	<grp.h>
#include	<pwd.h>

#include	<stdlib.h>	/* for exit for random */

typedef	struct
{	struct	itimerspec	s[1];
	struct	sigevent	e;
	timer_t			t;
	void			(**a)	(void);	/* where to pin */
	uint8_t			c;		/* already configured == 1 */
	uint8_t			d;		/* elapsed */
}	TIMER_DATA;

typedef	struct
{	TIMER_DATA		due;
	TIMER_DATA		kill;
	struct	timespec	nap[2];
}	SD;

static	PALIGN	SD	sd;


__attribute__((always_inline))
static	inline	void	self_vattach	(VMETA *A,VAMFIT const *B)
{	A->vam=		&Gz.hash.var[bit128_to_bit16(B->name)];
	vattach_fast	(A);
}

#define		sv(a,b)	self_vattach	((a),&(VAMFIT const){.name=(b)})

#define		namelen(a)	.name=(a),	.len=strlen(a)

__attribute__((aligned(0x20)))
static		void	siginc	(int a)
{	VALUE 		*b=	(void *)	Gz.sig[a];
	b->i4.l++;
}

__attribute__((noinline))
SCV	rtreq		(void)
{	static	uint8_t		a;
	static	const	AFIT	A=	{.a="rt"};

	if	yay	(a!=0)	return;
	a=		1;
	ifaload		(A.a);
/*	ifaload		("rt\0\0\0\0\0\0\0\0\0\0\0\0\0");	*/
}

__attribute__((noinline))
SCV	sirereq		(void)
{	static	uint8_t		a;
	static	const	AFIT	A=	{.a="sire"};

	if	yay	(a!=0)	return;
	a=		1;
	ifaload		(A.a);
}

#ifdef		__GLIBC__
#ifdef		__linux__
SCV	selfcpuaffineset	(void)
{
/*	hexdenwant		(Gz.to[0]);	*/
	sched_setaffinity	(0,sizeof(VALUE),
				(cpu_set_t *)&Gz.to[0]->value.i);
	*Gz.at=			selfcpuaffineset;
	argot_next		();
}
#endif
#endif

__attribute__((noinline))
SCV	selfdirsetbyte	(void)
{	chdir		(Gz.to[0]->textaddr);
	argot_next	();
}

__attribute__((noinline))
SCV	selfdirsetint	(void)
{	fchdir		(Gz.to[0]->value.i);
	argot_next	();
}

SCV	selfdirset		(void)
{	if			(Gz.to[0]->op->int_compat==0)
	(*Gz.at=selfdirsetbyte)	();
	else
	(*Gz.at=selfdirsetint)	();
}

__attribute__((noinline))
SCV	selfrootsetbyte	(void)
{	chroot			(Gz.to[0]->textaddr);
	argot_next		();
}

__attribute__((noinline))
SCV	selfrootsetint	(void)
{	int		a=
	open			(".",O_CLOEXEC|O_DIRECTORY|O_PATH|O_RDONLY);
	fchdir			(Gz.to[0]->value.i);
	chroot			(".");
	fchdir			(a);
	close			(a);
	argot_next		();
}

SCV	selfrootset			(void)
{	if				(Gz.to[0]->op->int_compat==0)
	(*Gz.at=selfrootsetbyte)	();
	else
	(*Gz.at=selfrootsetint)	();
}

SCV	selfegidset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	gid_t		a=	 Gz.to[0]->value.i;
	setegid			(a);
	*Gz.at=			selfegidset;
	argot_next		();
}

SCV	selfeuidset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	uid_t		a=	 Gz.to[0]->value.i;
	seteuid			(a);
	*Gz.at=			selfeuidset;
	argot_next		();
}

SCV	selfgidset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	gid_t		a=	 Gz.to[0]->value.i;
	setgid			(a);
	*Gz.at=			selfgidset;
	argot_next		();
}

SCV	selfgroupsinit		(void)
{	struct	passwd	*P=
	getpwuid		(getuid());
	if		yay	(P!=NULL)
	initgroups		(P->pw_name,getgid());
	*Gz.at=			selfgroupsinit;
	argot_next		();
}

SCV	selfpgidset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	pid_t		a=	 Gz.to[0]->value.i;
	setpgid			(0,a);
	*Gz.at=			selfpgidset;
	argot_next		();
}

SCV	selfpgidtcset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	pid_t		a=	 Gz.to[0]->value.i;
	tcsetpgrp		(0,a);
	*Gz.at=			selfpgidtcset;
	argot_next		();
}

SCV	selfpidnew		(void)
{	sirereq			();
	pid_t		p=
	forkmust		();
	*Gz.at=			selfpidnew;
	argot_jump		(p>0);
}

SCV	selfsgidset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	gid_t		sgid=	 Gz.to[0]->value.i;
	setresgid		(getgid(),getegid(),sgid);
	*Gz.at=			selfsgidset;
	argot_next		();
}

SCV	selfsidnew		(void)
{	setsid			();
	*Gz.at=			selfsidnew;
	argot_next		();
}

SCV	selfsuidset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	uid_t		suid=	 Gz.to[0]->value.i;
	setresuid		(getuid(),geteuid(),suid);
	*Gz.at=			selfsuidset;
	argot_next		();
}

__attribute__((noinline))
SCV	selfttynew		(void)
{	int		a,b;
	a=
	open			("/dev/console",
				O_NONBLOCK|O_NOCTTY|O_RDONLY);

	ioctl			(a,VT_OPENQRY,&b);

	close			(a);
	close			(0);
	close			(1);
	close			(2);

	static	CALIGN
	uint8_t		c[0x40];
	sprintf			(c,"%s%i","/dev/tty",b);
	a=			(open(c,O_RDONLY)!=0);
	a|=			(open(c,O_WRONLY)!=1);
	a|=			(open(c,O_WRONLY)!=2);
	a|=			(ioctl(0,TIOCSCTTY,0)!=0);
	*Gz.at=			selfttynew;
	argot_next		();
}

SCV	selfttyvtset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	int		a=
	open			("/dev/console",
				O_NONBLOCK|O_NOCTTY|O_RDONLY);
	int		b=	 Gz.to[0]->value.i;
	ioctl			(a,VT_ACTIVATE,b);
	close			(a);

	*Gz.at=			selfttyvtset;
	argot_next		();
}

SCV	selfttyvtfree		(void)
{
/*	denwant			(Gz.to[0]);	*/

	int		a=
	open			("/dev/console",
				O_NONBLOCK|O_NOCTTY|O_RDONLY);

	int		b=	Gz.to[0]->value.i;
	ioctl			(a,VT_DISALLOCATE,b);
	close			(a);
	*Gz.at=			selfttyvtfree;
	argot_next		();
}

SCV	selfuidset		(void)
{
/*	denwant			(Gz.to[0]);	*/
	uid_t		a=	 Gz.to[0]->value.i;
	setreuid		(a,geteuid());
/*	setuid			(a);	*/
	*Gz.at=			selfuidset;
	argot_next		();
}

SCV	selfumaskset		(void)
{
/*	octwant			(Gz.to[0]);	*/
	mode_t		a=	 Gz.to[0]->value.i;
	umask			(a);
	*Gz.at=			selfumaskset;
	argot_next		();
}

/* would reading /proc/?/stat be better and parsing the tty_nr value? */

SCV	show_ttyname	(VMETA *A)
{	A->textlen=	0;
	int		a=
	ttyname_r	(0,A->textaddr,A->textsize);
	close		(a);

/*	ctermid		(A->textaddr);
*/
	A->textlen=
	strlenb		(A->textaddr);
}

SCV	reval_tty		(VMETA *A)
{	struct	stat	*s=	(struct stat *)	A->dataaddr;
	int		c=
	fstat			(0,s);

	if		yay	(c==0)
	if		yay	((s->st_mode&S_IFMT)==S_IFCHR)
	if		yay	(major(s->st_rdev)==4)
	{	A->value.i=
		minor		(s->st_rdev);
		return;
	}
	A->value.i=		-1;
}

SCV	reval_vt		(VMETA *A)
{	int		a=
	open			("/dev/console",
				O_NONBLOCK|O_NOCTTY|O_RDONLY);

	struct	vt_stat	*v=	(struct vt_stat *)	A->dataaddr;
	if		yay	(a>=0)
	{	ioctl		(a,VT_GETSTATE,v);
		close		(a);
		A->value.i=	v->v_active;
		return;
	}

	A->value.i=		-1;
}

SCV	reval_random_	(VMETA *A)
{	A->value.i=
	random		();
}

SCV	reval_random	(VMETA *A)
{	srandom		(time(NULL));
	A->show=	Gz.out.den8;
	A->reval=	reval_random_;
	A->value.i=
	random		();
}

static	void	reval_pid	(VMETA *A){A->value.i=getpid();}
static	void	reval_ppid	(VMETA *A){A->value.i=getppid();}
static	void	reval_uid	(VMETA *A){A->value.i=getuid();}
static	void	reval_euid	(VMETA *A){A->value.i=geteuid();}
static	void	reval_gid	(VMETA *A){A->value.i=getgid();}
static	void	reval_egid	(VMETA *A){A->value.i=getegid();}
static	void	reval_sid	(VMETA *A){A->value.i=getsid(0);}
static	void	reval_pgid	(VMETA *A){A->value.i=getpgrp();}
static	void	reval_tc	(VMETA *A){A->value.i=tcgetpgrp(0);}
static	void	reval_cpu	(VMETA *A){A->value.i=sched_getcpu();}
static	void	reval_time	(VMETA *A){A->value.i=time(NULL);}
static	void	reval_umask	(VMETA *A){mode_t a=A->value.i4.l=umask(0770);umask(a);}

SCV	reval_suid	(VMETA *A)
{	uid_t		ruid,euid,suid;
	getresuid	(&ruid,&euid,&suid);
	A->value.i=	suid;
}

SCV	reval_sgid	(VMETA *A)
{	gid_t		rgid,egid,sgid;
	getresgid	(&rgid,&egid,&sgid);
	A->value.i=	sgid;
}

__attribute__((noinline))
__attribute__((unused))
static	CALIGN	int	equal_groups_	(void)
{	errna=				0;
	VMETA		*B=		Gz.to[1];
	uint8_t		*b=		B->textaddr;
	uint8_t		*e=		B->textaddr+
					B->textlen;
	int		t;
	for				(t=0;e>b;b++)
	{	if		nay	(e[ 0]==0)
		if		yay	(e[-1]!=0)
		t++;
	}

	gid_t		G[t];
	b=				B->textaddr;
	e=				B->textaddr+
					B->textlen;
	int		a;
	int		s;
	struct	group	*g;
	for				(s=0;t>s;s++)
	{	g=
		getgrnam		(b);
		if			(g!=NULL)
		G[s]=			g->gr_gid;
		else
		{	t--;
			a=		1;
		}
		for			(;b[0]!=0;b++);
		for			(;b[0]==0;b++);
	}
	a|=
	setgroups			(t,G);
	return				a;
}

__attribute__((unused))
SCV	equal_groups		(void)
{	int		a=
	equal_groups_		();
	*Gz.at=			equal_groups;
	argot_jump		(a==0);
}


/*
__attribute__((unused))
SCV	not_dir_old	(void)
{	int		a=
	open			(".",O_CLOEXEC|O_DIRECTORY|O_PATH|O_RDONLY);
	a=
	highmake		(a);
	*Gz.at=			not_dir;
	argot_next		();
	fchdir			(a);
	close			(a);
}
*/

SCV	show_dir	(VMETA *A)
{	getcwd		(A->textaddr,PAGE);
	A->textlen=
	strlenb		(A->textaddr);
}

/*
__attribute__((aligned(0x20)))
static		void	reval_dir	(VMETA *A)
{	A->value.i=
	open			(".",O_CLOEXEC|O_DIRECTORY|O_PATH|O_RDONLY);
}
*/

/*
__attribute__((aligned(0x20)))
static	void	mapuse0_root	(VMETA *A)
{	A->textlen=		1;
	A->textaddr[0]=		'/';
	A->textaddr[1]=		0;
}
*/

#ifdef		__GLIBC__
#ifdef		__linux__
#include	<sched.h>
SCV	reval_cpu_total		(VMETA *A)
{	cpu_set_t	*a=	(cpu_set_t *)	&A->value;
	sched_getaffinity	(0,sizeof(VALUE),a);
	A->value.i=
	CPU_COUNT_S		(  sizeof(VALUE),a);
}


static	void	reval_cpu_affine(VMETA *A)
{	sched_getaffinity(0,sizeof(VALUE),(cpu_set_t *) &Gz.to[0]->value);
}
#endif
#endif

__attribute__((aligned(0x20)))
static		void	self	(void)
{	*Gz.at=		self;
	argot_next	();
}

__attribute__((noinline))
SCV	argvload			(VMETA *A)
{	raymaxaddr	(A)->i=		Gz.arg.c;

	VMETA		*a=
	Gz.arg.a=
	pps				(Gz.arg.c*
	sizeof				(VMETA))-1;

	VMETA		**d=
	raydataaddr			(A)-1;

	uint8_t		**c=		Gz.arg.v-1;
	do
	{	a++;
		c++;
		d++;
		*d=			a;
		map_init		(a);
		byteinit		(a);
		a->io.flag=		textmapuse;
		a->textaddr=		c[0];
		a->textlen=
		a->textsize=		c[1]-c[0]-1;
	}
	while				(c[1]!=NULL);

	a->textlen=
	a->textsize=
	strlenb				(a->textaddr);
}

SCV	selfargv		(void)
{	static	VMETA		a=
	{	namelen		("self.argv")
	};

	if		yay	(a.textaddr!=NULL)
	goto			done;

	map_init		(&a);
	raysubnew		(&a);
	sv			(&a,"self.argv");
	argvload		(&a);

	done:
	*Gz.at=			selfargv;
	argot_next		();
}

SCV	show_groups			(VMETA *A)
{	if				(A->textaddr==A->text)
	map_add				(A,PAGE*0x10,0);

	static	gid_t			G[0x1000];
	int		t=
	getgroups			(0x1000,G);

	struct	group	*g;
	uint8_t		*a=		A->textaddr;
	gid_t		*c=		G;
	gid_t		*e=		G+t;
	for				(;e>c;c++)
	{	g=
		getgrgid		(*c);
		if		yay	(g!=NULL)
		{	t=
			strlenb		(  g->gr_name);
			memcpyb		(a,g->gr_name,t);
			a+=		t+1;
		}
	}
	A->textlen=			a-A->textaddr;
}

SCV	show_home		(VMETA *A)
{	if			(A->dataaddr==NULL)
	map_add			(A,0,PAGE*2);

	struct	passwd	*a=	(struct passwd *)	A->dataaddr,
			*b;

	int		c=
	getpwuid_r		(getuid(),a,A->dataaddr+PAGE,PAGE,&b);

	if		yay	(c==0)
	{	A->textaddr=	 a->pw_dir;
		A->textlen=
		strlenb		(a->pw_dir);
	}
	else
	A->io.success=		errna;
}

SCV	selfpause	(void)
{	*Gz.at=		selfpause;
	pause		();
	argot_next	();
}

SCV	show_script		(VMETA *A)
{	A->textaddr=		 Gz.arg.v[1];
	A->textlen=	strlenb	(Gz.arg.v[1]);
}

SCV	show_shell		(VMETA *A)
{	if			(A->dataaddr==NULL)
	map_add			(A,0,PAGE*2);

	struct	passwd	*a=	(struct passwd *)	A->dataaddr,
			*b;

	int		c=
	getpwuid_r		(getuid(),a,A->dataaddr+PAGE,PAGE,&b);

	if		yay	(c==0)
	{	A->textaddr=	 a->pw_shell;
		A->textlen=
		strlenb		(a->pw_shell);
	}
	else
	A->io.success=		errna;
}

SCV	reval_ttin		(VMETA *A)
{	A->reval=		NULL;
	A->show=		Gz.out.den4;
	Gz.sig[SIGTTIN]=	&A->value;
	Gz.sa[0].sa_flags=	SA_RESTART;
	Gz.sa[0].sa_handler=	siginc;
	sigaction		(SIGTTIN,Gz.sa,NULL);
}

SCV	reval_ttou		(VMETA *A)
{	A->reval=		NULL;
	A->show=		Gz.out.den4;
	Gz.sig[SIGTTOU]=	&A->value;
	Gz.sa[0].sa_flags=	SA_RESTART;
	Gz.sa[0].sa_handler=	siginc;
	sigaction		(SIGTTOU,Gz.sa,NULL);
}

__attribute__((always_inline))
static	inline	 TIMER_DATA *	timer_data	(VMETA *A)
{	return	(TIMER_DATA *)	A->dataaddr;
}

noreturn
static		void	selfend	(void)
{	VMETA		*A;
	int		a=	0;
	if		yay	(arga(Gz.at)!=arga(Gz.at+1))
	{	A=	parapass(arga(Gz.at));
/*		denwant		(A);		*/
		a=		A->value.i;
	}
	exit			(a);
}

__attribute__((cold))
static		void	catch	(int a,siginfo_t *b,void *c)
{	sd.due.d=		1;
}

SCV	selfdueere		(void)
{	*Gz.at=			selfdueere;
	argot_jump		(sd.due.d==0);
}

SCV	selfduedone		(void)
{	TIMER_DATA	*t=	(TIMER_DATA *)	&sd.due;
	__builtin_memset	(t->s,0,sizeof(t->s[0]));
	timer_settime		(t->t,0,t->s,NULL);
	*Gz.at=			selfduedone;
	argot_next		();
}

static	inline	void	selfdue_init	(void)
{	TIMER_DATA	*t=	&sd.due;
	if			(t->c!=0)
	return;
	t->c=			1;

	rtreq			();
	int		s;
	for			(s=SIGRTMIN;Gz.sig[s];s++);
/*	Gz.sig[s]=		&sd.due;	*/
	Gz.sig[s]=		(void *)	1;
	t->e.sigev_signo=	s;
	t->e.sigev_notify=	SIGEV_SIGNAL;
	Gz.sa[0].sa_flags=	SA_SIGINFO;
	Gz.sa[0].sa_sigaction=	catch;
	sigaction		(s,Gz.sa,NULL);
	timer_create		(CLOCK_MONOTONIC,&t->e,&t->t);
}

SCV	selfdueset		(void)
{	selfdue_init		();

	VLESS		*P=
	arga			(NULL);

	VMETA		*A;
	A=
	parapass		(P),
/*	denwant			(A);		*/
	sd.due.s[0].it_value.tv_sec=
				A->value.i;

	A=
	parapass		(P+1);
/*	denwant			(A);		*/
	sd.due.s[0].it_value.tv_nsec=
				A->value.i;

	sd.due.d=		0;
	timer_settime		(sd.due.t,0,sd.due.s,NULL);
	*Gz.at=			selfdueset;
	argot_next		();
}

SCV	selfkill_init		(void)
{	rtreq			();
	sd.kill.e.sigev_notify=	SIGEV_SIGNAL;
	sd.kill.e.sigev_signo=	SIGTERM;
	timer_create		(CLOCK_MONOTONIC,&sd.kill.e,&sd.kill.t);
}

SCV	selfkillset		(void)
{	selfkill_init		();

	VLESS		*P=
	arga			(NULL);

	VMETA		*A;
	A=
	parapass		(P);
/*	denwant			(A);		*/
	sd.kill.s[0].it_value.tv_sec=
				A->value.i;

	A=
	parapass		(P+1);
/*	denwant			(A);		*/
	sd.kill.s[0].it_value.tv_nsec=
				A->value.i;

	timer_settime		(sd.kill.t,0,sd.kill.s,NULL);
	*Gz.at=			selfkillset;
	argot_next		();
}

SCV	selfnapset		(void)
{	VLESS		*P=
	arga			(NULL);

	VMETA		*A;

	A=
	parapass		(P);
/*	denwant			(A);		*/

	sd.nap[0].tv_sec=	A->value.i;

	A=
	parapass		(P+1);
/*	denwant			(A);		*/

	sd.nap[0].tv_nsec=	A->value.i;

	int		a=
	nanosleep		(sd.nap
				,sd.nap+1);
	if			(a==0)
	memset			(sd.nap+1,0,sizeof(sd.nap[0]));

	*Gz.at=			selfnapset;
	argot_next		();
}

SCV	selfnapfull		(void)
{	int			a;
	do
	{	sd.nap[0]=	sd.nap[1];
		a=
		nanosleep	(sd.nap
				,sd.nap+1);
	}
	while			(a!=0);
	memset			(sd.nap+1,0,sizeof(sd.nap[0]));

	*Gz.at=			selfnapfull;
	argot_next		();
}

static		void	selfyield	(void)
{
#ifdef	_POSIX_PRIORITY_SCHEDULING
	sched_yield	();
#else
#warning Function sched_yield is unavailable.
#endif
	*Gz.at=		selfyield;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190227",
	.official=	"20190227",
	.update=	"20200919"
};

#define	nlo(a,b)			\
{	.name=		(a),		\
	.len=	strlen	((a)),		\
	.op=		(b),		\
}

#define	iv(a)				\
	A++;				\
	map_init	(A);		\
	vattach_faster	(A,(a))

#define	r(a)	A->reval=	(a);
#define	s(a)	A->show=	(a);

SCV	varinit		(void)
{	static	VMETA	V[]=
{	nlo		("self.argc",		opint4),
/*	nlo		("self.argv",		opray),	*/
	nlo		("self.cpu",		opint8),
	nlo		("self.cpu.affine",	opint8),
	nlo		("self.cpu.total",	opint4),
	nlo		("self.dir",		opbyte),
	nlo		("self.egid",		opint8),
	nlo		("self.euid",		opint8),
	nlo		("self.gid",		opint8),
	nlo		("self.groups",		opbyte),
	nlo		("self.home",		opbyte),
	nlo		("self.pgid",		opint8),
	nlo		("self.pgid.tc",	opint4),
	nlo		("self.pid",		opint4),
	nlo		("self.ppid",		opint4),
	nlo		("self.script",		opbyte),
	nlo		("self.sgid",		opint8),
	nlo		("self.shell",		opbyte),
	nlo		("self.sid",		opint8),
	nlo		("self.sigttin",	opint4),
	nlo		("self.sigttou",	opint4),
	nlo		("self.random",		opint8),
	nlo		("self.suid",		opint8),
	nlo		("self.time",		opint8),
	nlo		("self.tty",		opint4),
	nlo		("self.tty.name",	opbyte),
	nlo		("self.tty.vt",		opint4),
	nlo		("self.uid",		opint8),
	nlo		("self.umask",		opint4),
};

	VMETA	*A=	V-1;
	iv		("self.argc");		A->value.i=	Gz.arg.c;
								s(Gz.out.den4);
/*	iv		("self.argv");					*/
	iv		("self.cpu");		r(reval_cpu);	s(Gz.out.dex8);
	iv		("self.cpu.affine");	r(reval_cpu_affine);
								s(Gz.out.dex8);
	iv		("self.cpu.total");	r(reval_cpu_total);
								s(Gz.out.dex8);
	iv		("self.dir");				s(show_dir);
	iv		("self.egid");		r(reval_egid);	s(Gz.out.den8);
	iv		("self.euid");		r(reval_euid);	s(Gz.out.den8);
	iv		("self.gid");		r(reval_gid);	s(Gz.out.den8);
	iv		("self.groups");			s(show_groups);
	iv		("self.home");				s(show_home);
	iv		("self.pgid");		r(reval_pgid);	s(Gz.out.den8);
	iv		("self.pgid.tc");	r(reval_tc);	s(Gz.out.den4);
	iv		("self.pid");		r(reval_pid);	s(Gz.out.den8);
	iv		("self.ppid");		r(reval_ppid);	s(Gz.out.den8);
	iv		("self.script");			s(show_script);
	iv		("self.sgid");		r(reval_sgid);	s(Gz.out.den8);
	iv		("self.shell");				s(show_shell);
	iv		("self.sid");		r(reval_sid);	s(Gz.out.den8);
	iv		("self.sigttin");	r(reval_ttin);
	iv		("self.sigttou");	r(reval_ttou);
	iv		("self.random");	r(reval_random);
	iv		("self.suid");		r(reval_suid);	s(Gz.out.den8);
	iv		("self.time");		r(reval_time);	s(Gz.out.den8);
	iv		("self.tty");		r(reval_tty);	s(Gz.out.den4);
	iv		("self.tty.name");			s(show_ttyname);
	iv		("self.tty.vt");	r(reval_vt);	s(Gz.out.den4);
	iv		("self.uid");		r(reval_uid);	s(Gz.out.den8);
	iv		("self.umask");		r(reval_umask);	s(Gz.out.oct4);
}


__attribute__((constructor))
SCV	aainit			(void)
{	aa_init		();
	aa		(self,			"self");

#ifdef		__GLIBC__
#ifdef		__linux__
	aa		(selfcpuaffineset,	"selfcpuaffineset");
#endif
#endif

	aa		(selfargv,		"selfargv");
	aa		(selfkillset,		"selfkillset");
	aa		(selfdueere,		"selfdueere");
	aa		(selfduedone,		"selfduedone");
	aa		(selfdueset,		"selfdueset");
	aa		(selfdirset,		"selfdirset");
	aa		(selfrootset,		"selfrootset");
	aa		(selfegidset,		"selfegidset");
	aa		(selfend,		"selfend");
	aa		(selfeuidset,		"selfeuidset");
	aa		(selfgidset,		"selfgidset");
	aa		(selfgroupsinit,	"selfgroupsinit");
	aa		(selfpause,		"selfpause");
	aa		(selfpgidset,		"selfpgidset");
	aa		(selfpgidtcset,		"selfpgidtcset");
	aa		(selfpidnew,		"selfpidnew");
	aa		(selfsgidset,		"selfsgidset");
	aa		(selfsidnew,		"selfsidnew");
	aa		(selfsuidset,		"selfsuidset");
	aa		(selfnapset,		"selfnapset");
	aa		(selfnapfull,		"selfnapfull");
	aa		(selfttynew,		"selfttynew");
	aa		(selfttyvtset,		"selfttyvtset");
	aa		(selfttyvtfree,		"selfttyvtfree");
	aa		(selfuidset,		"selfuidset");
	aa		(selfumaskset,		"selfumaskset");
	aa		(selfyield,		"selfyield");

	aa_fini		();
	varinit		();
};
