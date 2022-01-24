/*	By Kyle Sallee in 2017 copyrighted.
	By Kyle Sallee in 2022 revised.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"komap.h"
#include	"sire.h"
#include	"trek.h"
/*
#include	"way.h"
*/
#include	<elf.h>
#include	<linux/netlink.h>
#include	<linux/types.h>
#include	<sched.h>
#include	<stdlib.h>
#include	<stdnoreturn.h>
#include	<string.h>
#include	<syslog.h>
#include	<sys/mount.h>
#include	<sys/prctl.h>
#include	<sys/socket.h>
#include	<time.h>			/*	clock_gettime	*/

OPERATOR	varkoop[1];

static	PALIGN	KODATA		kodata;
static	HALIGN	MEMORY		memory;

#define	va(a,b)	{.name=(a),.len=strlen((a)),.io.flag=textmapuse,.op=opbyte\
		,.text=b,.textlen=strlen(b)}

#define	vb(a)	{.name=(a),.len=strlen((a)),.io.flag=textmapuse,.op=opbyte}
#define	vc(a)	{.name=(a),.len=strlen((a)),.io.flag=datamapuse,.op=opint4}
#define	vd(z)	map_init(A);vattach_faster(A,z);A->show=Gz.out.den4;A++
#define	ve(z)	map_init(A);vattach_faster(A,z);A++

static	VMETA	kov[]=
{	vc("ko.defy.omit"),
	vc("ko.uevent.major"),
	vc("ko.uevent.minor"),
	vc("ko.uevent.pid"),

	vb("ko.alias"),
	vb("ko.name"),
	vb("ko.info"),
	va("ko.path.config",	"/etc/ko"),
	va("ko.path.dev",	"/dev"),
	va("ko.path.log",	"/var/log/ko"),
	va("ko.path.object",	"/lib/modules/"),
	vb("ko.uevent.action"),
	vb("ko.uevent.alias"),
	vb("ko.uevent.devname"),
	vb("ko.uevent.raw"),
	vb("ko.uevent.syspath"),
	vb("ko.uevent.subsys"),
};

__attribute__((constructor))
SCV		kov_init	(void)
{	uname			(&memory.uts);

	VMETA		*A=	kov;
	vd("ko.defy.omit");
	vd("ko.uevent.major");
	vd("ko.uevent.minor");
	vd("ko.uevent.pid");

	ve("ko.alias");
	ve("ko.name");
	ve("ko.info");
	ve("ko.path.config");
	ve("ko.path.dev");
	ve("ko.path.log");
	ve("ko.path.object");
	ve("ko.uevent.action");
	ve("ko.uevent.alias");
	ve("ko.uevent.devname");
	ve("ko.uevent.raw");
	ve("ko.uevent.syspath");
	ve("ko.uevent.subsys");

	kov[ko_uevent_major].io.flag|=	textmapuse;
	kov[ko_uevent_minor].io.flag|=	textmapuse;

	A=				kov+ko_alias;
	A->textaddr=			memory.kovp;
	A->textsize=			PAGE;
	A=				kov+ko_name;
	A->textaddr=			memory.kovp+PAGE;
	A->textsize=			PAGE;
	A=				kov+ko_uevent_alias;
	A->textaddr=			memory.kovp+PAGE*2;
	A->textsize=			PAGE;
	A=				kov+ko_uevent_syspath;
	A->textaddr=			memory.kovp+PAGE*3;
	A->textsize=			PAGE;

	A=				kov+ko_path_object;
	size_t		a=
	strlenb				(memory.uts.release);
	A->textlen=			0xd+a;
	__builtin_memcpy		(A->text+0xd
					,memory.uts.release
					,sizeof(A->text)
					-sizeof("/lib/modules/"));
/* not using _UTSNAME_LENGTH */
}

static	void	delay		(void);
static	void	index_find	(void);
static	int	koload_		(void);
static	int	kooust_		(void);
static	uint8_t	amatch		(uint8_t const *,uint8_t const *);

SCV	komap_		(void)
{	*Gz.at=		komap_;
	argot_next	();
}

SCV	koinfo		(void)
{	index_find	();
	*Gz.at=		koinfo;
	argot_jump	(memory.index!=0xFFFFFFFF);
	argot_next	();
}

static	inline	void	syscheck	(void)
{	if	yay	(access("/sys/devices",F_OK)==0)	return;
	mkdir		("/sys",0755);
	mount		(NULL,"/sys","sysfs", MS_NOATIME|MS_NODEV|MS_NOEXEC,"");
}

static	inline	void	syswalk	(void);

SCV	kocold		(void)
{	syswalk		();
	*Gz.at=		kocold;
	argot_next	();
}

__attribute__((noinline))
SCV	syswalk_r			(int a,uint8_t *b)
{	struct	dirent	*E;
	int		t,d=
	openat				(a,b,O_DIRECTORY|O_RDONLY);
	if			nay	(0>d)			return;

	DIR		*D=
	fdopendir			(d);

	while				(E=readdir(D))
	if				(E->d_type==DT_REG)
	{	if		yay	(E->d_name[0]!='u')	continue;
		t=	strlenb		(E->d_name);
		if		yay	(t!=6)			continue;
		t=	memcmpa		(E->d_name,"uevent",6);
		if		nay	(t!=0)			continue;
		t=	openat		(d,E->d_name,O_WRONLY);
		write			(t,"add",3);
		close			(t);
		sched_yield		();
	}
	else
	if				(E->d_type==DT_DIR)
	{	if		yay	(E->d_name[0]=='.')	continue;
		syswalk_r		(d,E->d_name);
	}
	closedir			(D);
}

static	inline	void	syswalk	(void)
{	syscheck	();
	syswalk_r	(AT_FDCWD,"/sys/devices");
}

static		void	usr1	(int,siginfo_t *,void *);
static		void	usr2	(int,siginfo_t *,void *);
static		void	event	(int,siginfo_t *,void *);
static		void	socketup(void);

static		int	kod_init(void);

SCV	kohark			(void)
{	int		a=
	kod_init		();
/*	*Gz.at=			kohark;	*/
	argot_jump		(a==0);
}

static	int	progenitor	(void);
static	int	progeny		(void);

static	void	parse		(void);
static	void	newname		(void);

__attribute__((noinline))
static	CALIGN	int	kod_init	(void)
{	mmap			(&memory.uevent.futex,
				 PAGE,
				 PROT_READ|PROT_WRITE,
				 MAP_ANONYMOUS|MAP_FIXED|MAP_SHARED,
				 -1,0);
	memory.uevent.futex.use=1;

	pid_t		p=
	kov[ko_uevent_pid].value.i=
	fork			();

	if		yay	(p==0)	return	progeny		();
	if		yay	(p>0)
	{	pids.last=	p;	return	progenitor	();	}
					return	1;
}

__attribute__((noinline))
static	CALIGN	int	progenitor	(void)
{	/* For the daemon start no more than a second wait */
	struct	timespec	t;
	t.tv_sec=		1;
	t.tv_nsec=		0;

	int		a=
	syscall			(SYS_futex,
				 &memory.uevent.futex,
				 FUTEX_WAIT,1,&t,NULL,0);
	if		yay	(a==0)			return	0;
	if		nay	(errna==ETIMEDOUT)	return	1;
	errna=			0;			return	0;
}

static	void	nasty		(void);
static	int	parse_clone	(void *);

__attribute__((noinline))
static	CALIGN	int	progeny		(void)
{	nasty				();
	chdir				("/");
	newname				();
	socketup			();
	madvise				(memory.uevent.data,sizeof
					(memory.uevent.data)
					,MADV_NOHUGEPAGE);
/*	memory.uevent.data[0]=		0;*/	/* page fault */
	memory.uevent.futex.use=	0;
	syscall				(SYS_futex,
					 &memory.uevent.futex,
					 FUTEX_WAKE,
					 INT_MAX,NULL,NULL,0);
	parse_clone			(NULL);
}


static	inline	void	nasty	(void)
{	nice			(-20);
/*
	struct	sched_attr	a;
	a.sched_policy=		 SCHED_FIFO;
	a.sched_priority=
	sched_get_priority_max	(SCHED_FIFO);
	a.size=
	sizeof			(struct sched_attr);
	syscall			(SYS_sched_setattr,0,a,0);
*/
}

__attribute__((noinline))
static	CALIGN	int	parse_clone	(void *z)
{	while				(1)
	{	for			(;memory.uevent.next_write>
					  memory.uevent.next_read;)
		parse			();
		syscall			(SYS_futex,
					 &memory.uevent.futex,
					 FUTEX_WAIT,0,NULL,NULL,0);
		memory.uevent.futex.use=0;
	}
}

static	inline	void	socketup	(void)
{	Gz.sig[SIGUSR1]=
	Gz.sig[SIGUSR2]=
	Gz.sig[SIGRTMIN]=		kov;

	Gz.sa[0].sa_flags=		SA_RESTART|SA_SIGINFO;
	Gz.sa[0].sa_sigaction=usr1;	sigaction	(SIGUSR1 ,Gz.sa,NULL);
	Gz.sa[0].sa_sigaction=usr2;	sigaction	(SIGUSR2 ,Gz.sa,NULL);
	Gz.sa[0].sa_sigaction=event;	sigaction	(SIGRTMIN,Gz.sa,NULL);

	pid_t		p=
	getpid				();
	int		s=
	socket				(PF_NETLINK,
					 SOCK_CLOEXEC|SOCK_DGRAM|SOCK_NONBLOCK,
					 NETLINK_KOBJECT_UEVENT);
	memory.uevent.socket=
	s=
	highmake			(s);

	fcntl				(s,F_SETFD,FD_CLOEXEC);
	fcntl				(s,F_SETOWN,p);
	fcntl				(s,F_SETSIG,SIGRTMIN);
	fcntl				(s,F_SETFL,O_ASYNC|O_NONBLOCK);

	struct	sockaddr_nl	aa;
	memset				(&aa,0,sizeof(aa));
	aa.nl_family=			AF_NETLINK;
	aa.nl_groups=			-1;

	aa.nl_pid=			p;
	bind				(s,(struct sockaddr *)&aa
					,sizeof(struct sockaddr_nl));

	openlog				(NULL,LOG_CONS|LOG_PID,LOG_DAEMON|LOG_ERR);
	syslog				(LOG_DAEMON|LOG_ERR,"kod start");
	closelog			();

/**/
	close				(0);
	close				(1);
	close				(2);
	setsid				();
	open				("/dev/console",O_WRONLY);
	dup2				(0,1);
	dup2				(0,2);
	close				(0);
/**/
}

static	inline	void	zeroout		(uint8_t *a)
{	for		(;*a;*a++=0);
}

static	inline	void	newname		(void)
{	uint8_t		*p,**v=		Gz.arg.v;
	prctl				(PR_SET_NAME,"ko hark");
	if			yay	(v[0][0]!=0)
	if			yay	(v[0][1]!=0)
	if			yay	(v[0][2]!=0)
	{	memcpy			(v[0],"ko hark",7);
		zeroout			(v[0]+7);
	}
	while				(p=*++v)
	zeroout				(p);
}

static	inline	void	mkdirr	(uint8_t *a,mode_t m)
{	uint8_t		*b,c;
	for			(b=a+1;c=*b,1;b++)
	if			((c=='/')||(c==0))
	{	*b=		0;
		if		(access(a,F_OK))
		mkdir		(a,m);
		*b=		c;
		if		(c==0)
		return;
	}
}

SCV	usr1			(int x,siginfo_t *i,void *v)
{	VMETA
	*G=	kov+ko_defy_omit;	/* ko.defy.omit */
	 G->value.i=		i->si_value.sival_int;
}

SCV	cram			(void);
SCV	usr2			(int x,siginfo_t *i,void *v)
{	int	e=		errna;

	sigset_t		s[2];
	*(uint64_t *)	s=	0xffffffffffffffff;
	sigprocmask		(SIG_SETMASK,s,s+1);

	cram			();

	sigprocmask		(SIG_SETMASK,s+1,NULL);
	errna=			e;
}

SCV	event				(int x,siginfo_t *i,void *v)
{	uint8_t		*a=		 memory.uevent.next_write;
	if			yay	(memory.uevent.next_read==a)
	memory.uevent.next_write=
	memory.uevent.next_read=
	a=			 	memory.uevent.data;

	int		c,b=		errna;

	errna=				0;
	*(int *)
	a=
	c=
	read				(memory.uevent.socket,
					 a    +sizeof(int),
					 0x400-sizeof(int));
	if				(c>0)
	{	memory.uevent.next_write=a+0x400;
		memory.uevent.futex.use=1;
	}

	clock_gettime			(CLOCK_MONOTONIC,memory.uevent.last);
	errna=				b;
}

static		int	tacit		(void);
static		void	logmsg		(uint8_t *,uint8_t *,ssize_t const);
static		void	mkdirr		(uint8_t *,mode_t);

__attribute__((noinline))
SCV	parse				(void)
{	delay				();

	uint8_t		*a=		memory.uevent.next_read;
	int		b=		*(int *)	a;
	a+=
	sizeof				(int);

	VMETA		*K=		kov+ko_path_log;	/* ko.path.log*/

	mkdirr				(K->textaddr,0700);
	logmsg				(K->textaddr,a,b);

	VMETA		*B=		kov+ko_alias;	/* ko.alias */
	VMETA		*C=		kov+ko_name;	/* ko.name  */
	VMETA		*N=		kov+ko_uevent_action;	/* ko.uevent.action */
	VMETA		*O=		kov+ko_uevent_alias;	/* ko.uevent.alias  */
	VMETA		*P=		kov+ko_uevent_devname;	/* ko.uevent.devname*/
/*	VMETA		*Q=		kov+ko_uevent_pin;*/	/* ko.uevent.pin    */
	VMETA		*R=		kov+ko_uevent_major;	/* ko.uevent.major  */
	VMETA		*S=		kov+ko_uevent_minor;	/* ko.uevent.minor  */
	VMETA		*U=		kov+ko_uevent_raw;	/* ko.uevent.raw    */
	VMETA		*V=		kov+ko_uevent_syspath;	/* ko.uevent.syspath */
	VMETA		*W=		kov+ko_uevent_subsys;	/* ko.uevent.subsys */
/*	VMETA		*X=		kov+ko_uevent_cfg;*/	/* ko.uevent.cfg */

	U->textaddr=			a;
	U->textlen=			b;

	B->textlen=
	C->textlen=			0;
/*	E->textlen=			0; */

	O->textlen=
	P->textlen=
/*	Q->textlen=	*/
	R->textlen=
	S->textlen=
	V->textlen=
	W->textlen=			0;

	uint8_t		*c;
	int		d;

	c=		memmema		(a,b,"ACTION=",7);
	c+=				7;
	d=		strlenb		(c);
	N->textlen=			d;
	memcpy				(N->textaddr,c,8);

	c=		memmema		(a,b,"MODALIAS=",9);
	if			nay	(c!=NULL)
	{	c+=			9;
		d=	strlenb		(c);
		O->textlen=		d;
		memcpyt			(O->textaddr,c,d);
		B->textlen=		d;
		memcpyt			(B->textaddr,c,d);
	}

	c=		memmema		(a,b,"DEVNAME=",8);
	if			nay	(c!=NULL)
	{	c+=			8;
		d=	strlenb		(c);
		P->textlen=		d;
		memcpyt			(P->textaddr,c,d);
	}

	c=		memmema		(a,b,"MAJOR=",6);
	if			nay	(c!=NULL)
	{	c+=			6;
		d=	strlenb		(c);
		R->textlen=		d;
		memcpy			(R->textaddr,c,8);
		Gz.out.asden		(R->textaddr,&R->value.i);
	}

	c=		memmema		(a,b,"MINOR=",6);
	if			nay	(c!=NULL)
	{	c+=			6;
		d=	strlenb		(c);
		S->textlen=		d;
		memcpy			(S->textaddr,c,8);
		Gz.out.asden		(S->textaddr,&S->value.i);
	}

	c=		memmema		(a,b,"DEVPATH=",8);
	if			nay	(c!=NULL)
	{	c+=			8;
		d=	strlenb		(c);
		V->textlen=		d;
		memcpyt			(V->textaddr,c,d);
	}

	c=		memmema		(a,b,"SUBSYSTEM=",0xa);
	if			nay	(c!=NULL)
	{	c+=			0xa;
		d=	strlenb		(c);
		W->textlen=		d;
		memcpyt			(W->textaddr,c,d);
	}

	if				(B->textlen>0)
	index_find			();

	void		(**n)	(void)=	memory.pin;

	if				(n!=NULL)
	{	void	(**L)	(void)=	Gz.at;
		(*(Gz.at=n))		();
		Gz.at=			L;
	}
	else
	tacit				();
	memory.uevent.next_read+=	0x400;
}

static	inline	void	logmsg	(uint8_t *a,uint8_t *b,ssize_t const c)
{	int		d=
	open			(a,O_DIRECTORY|O_NOATIME|O_RDONLY);
	int		e=
	openat			(d,memmema(b,c,"SEQNUM=",7)+7,
				 O_CREAT|O_SYNC|O_WRONLY,0600);
	close			(d);
	write			(e,b,c);
	close			(e);
}

SCV	koauto		(void)
{	tacit		();
	*Gz.at=		koauto;
	argot_next	();
}

static		uint8_t	tacit_add	(void);
static		uint8_t	tacit_change	(void);
static		uint8_t	tacit_move	(void);
static		uint8_t	tacit_remove	(void);

__attribute__((noinline))
static	CALIGN	int	tacit		(void)
{	switch				(kov[ko_uevent_action].textaddr[0])
	{	case	'a':		return	tacit_add	();
		case	'r':		return	tacit_remove	();
		case	'c':		return	tacit_change	();
		case	'm':		return	tacit_move	();
	}
}

__attribute__((noinline))
static	CALIGN	uint8_t	tacit_remove	(void)
{
/*	delay			();	*/

	VMETA		*C=	kov+ko_name;	/* ko.name  */
	if			(C->textlen==0)
	return			0;

	int		a;
	while			(1)
	{	errna=		0;
		a=
		syscall		(__NR_delete_module,
				 C->textaddr,
				 O_NONBLOCK);

		if		(a==0)			break;
		if		(errna==EINTR)		continue;
		if		(errna==ERESTART)	continue;
		break;
	}

	warn			("%-19s %-19s %i",
				 "__NR_delete_module",C->textaddr,errna);
	return			a;
}

static	inline	uint8_t	tacit_change	(void)	{return	0;}
static	inline	uint8_t	tacit_move	(void)	{return	0;}

static		uint8_t	ischar		(int);

__attribute__((noinline))
static	CALIGN	uint8_t	tacit_add	(void)
{	VMETA		*B=		kov+ko_alias;	/* ko.alias */

	if				(B->textlen>0)
	koload_				();

	VMETA		*P=		kov+ko_uevent_devname;	/* ko.uevent.devname*/

	if				(P->textlen==0)
	return				0;

	VMETA		*R=		kov+ko_uevent_major;
/* ko.uevent.major */
	int		maj=		R->value.i;

	VMETA		*S=		kov+ko_uevent_minor;
/* ko.uevent.minor */
	int		min=		S->value.i;

	VMETA		*J=		kov+ko_path_dev;	/* ko.path.dev */

	int		d=
	open				(J->textaddr,
					 O_DIRECTORY|O_RDONLY);
	int		f=
	openat				(d,P->textaddr,
					 O_NOCTTY|O_RDONLY);
	close				(d);
	fchown				(f,-1,(gid_t)maj);
	mode_t		m=		0660;

	struct	stat	s;
	fstat				(f,&s);
	if				(maj==1)
	switch				(min)
	{	case	3:		/* null */
		case	5:		/* zero */
		case	8:		/* random */
		case	9:		/* urandom */
/*		if		yay	(ischar(f))	*/
/* With tmpfs; why use ramdisks?			*/
		m=			0666;
	}
	else
	if			nay	((maj==5)&&(min==0))	/* tty */
	m=				0666;

	fchmod				(f,m);
	close				(f);
	return				0;
}

__attribute__((unused))
static	inline	uint8_t	ischar	(int a)
{	struct	stat	b;
	int		c=
	fstat			(a,&b);
	if			(0>c)
	return			0;
	return			((b.st_mode&S_IFMT)==S_IFCHR);
}


static		uint8_t	loaded		(uint8_t *);

SCV	kolive			(void)
{	index_find		();
	int		r=
	loaded			(kov[ko_name].textaddr);
	*Gz.at=			kolive;
	argot_jump		(r==0);
}

SCV	kodead			(void)
{	index_find		();
	int		r=
	loaded			(kov[ko_name].textaddr);
	*Gz.at=			kodead;
	argot_jump		(r!=0);
}

/*	loaded
	return	0 	    found
	return	1	not found
*/

__attribute__((noinline))
static	CALIGN	uint8_t	loaded	(uint8_t *a)
{	int		b=
	open			("/sys/module",O_DIRECTORY|O_RDONLY);
	if		nay	(0>b)
	return			(0>b);

	int		c=
	faccessat		(b,a,F_OK,0);
	close			(b);
	return			c;
}

static	inline	uint8_t	koomit	(uint8_t *a)
{	VMETA		*G=	kov+ko_defy_omit;	/* ko.defy.omit */

	if			(G->value.i==0)
	return			1;

	VMETA		*I=	kov+ko_path_config;	/* ko.path.config */

	int		b=
	open			(I->textaddr,O_RDONLY);
	if		nay	(0>b)
	return			b;

	int		c=
	openat			(b,"omit",O_RDONLY);
	close			(b);
	if		nay	(0>c)
	return			c;

	int		d=
	faccessat		(c,a,F_OK,0);
	close			(c);
	return			d;
}

static	inline	uint8_t	kopara	(uint8_t *a)
{	VMETA		*I=	kov+ko_path_config;	/* ko.path.config */

	memory.para[0]=		0;
	int		c=
	open			(I->textaddr,O_RDONLY);
	if		nay	(0>c)
	return			c;

	int		d=
	openat			(c,"para",O_RDONLY);
	close			(c);
	if		nay	(0>d)
	return			d;

	int		e=
	openat			(d,a,O_RDONLY);
	close			(d);
	if		nay	(0>e)
	return			e;

	ssize_t		t=
	read			(e,memory.para,PAGE);
	close			(e);
	if		nay	(0>t)
	return			t;

	memory.para[t]=		0;
	return			0;
}

SCV	koload			(void)
{	index_find		();
	int		r=
	koload_			();
	*Gz.at=			koload;
	argot_jump		(r==0);
}

SCV	kooust			(void)
{	index_find		();
	int		r=
	kooust_			();
	*Gz.at=			kooust;
	argot_jump		(r==0);
}

__attribute__((noinline))
static	CALIGN	int	kooust_	(void)
{	VMETA		*C=	kov+ko_name;	/* ko.name */
	errna=			0;
	C->textaddr[
	C->textlen]=		0;
	return
	syscall			(__NR_delete_module,
				 C->textaddr,O_NONBLOCK);
}

static	int	koload_r	(uint32_t);
static	void	name_to_index	(void);
static	void	alias_to_index	(void);

__attribute__((noinline))
static	CALIGN	int	koload_	(void)
{
/*	VMETA		*A=	koa;	*/
	VMETA		*B=	kov+ko_alias;	/* ko.alias */
	VMETA		*C=	kov+ko_name;	/* ko.name  */
/*	VMETA		*F=	kov+ko_defy_modver;*/	/* ko.defy.modver */
/*	VMETA		*H=	kov+ko_defy_vermagic;*/	/* ko.defy.vermagic */

	if			(B->textlen>0)	alias_to_index	();
	else	if		(C->textlen>0)	name_to_index	();

	if		nay	(memory.index==0xFFFFFFFF)
	{	errna=		EINVAL;
		return		1;
	}

	return
	koload_r		(memory.index);
}

static		int	kodep		(uint32_t);
__attribute__((noinline))
static	CALIGN	int	koload_r	(uint32_t i)
{	char		*n=		kodata.name[i];
	if			nay	(loaded(n)==0)	return	0;
	if			nay	(koomit(n)==0)	return	0;

	int		e=
	kodep				(i);
	kopara				(n);

	int		f;
	while				(1)
	{	errna=			0;
		f=
		syscall			(__NR_init_module
					,kodata.addr[i]
					,kodata.size[i]
					,memory.para);

/*		warn			("__NR_init_module for f=%i %s",f,n);
*/
		if			(f==0)			break;
		if			(errna==EINTR)		continue;
		if			(errna==ERESTART)	continue;
		break;
	}

	e|=				f;
	return				e;
}

/*
A kernel module
during load
during unload
The /sys/ contained uevent files
if written
all the triggered events
might not be received
might not be parsed.
The log numbers will have gaps
important modules will not have loaded.
Looks like a kernel bug.
On single CPU single core computers
the bug probably does not even manifest.
A module when loading when unloading
all processes should probably be suspended.
Argot ko can not possess that ability.
The uevent
for receiving
for parsing
separate threads
when used
the problem
is not precluded.
An unpalatable solution follows.
From the most recent uevent received
a reasonable duration
until elapsed
a the uevent processing
is delayed.
Yes slower       kernel object  loading becomes.
But then   again kernel objects seldom  load.
*/

__attribute__((noinline))
SCV	delay					(void)
{	struct	timespec
	*t=					memory.uevent.last;
	int		a;

	do
	{		t[1].tv_sec=		t[0].tv_sec;
			t[1].tv_nsec=		t[0].tv_nsec;
/* At 800 MHz  100000 seems  reliable */
/* At 100 MHz 1000000 should work */

			t[1].tv_nsec+=		1000000;
		if			nay	(t[1].tv_nsec>=
						0x3b9aca00)
		{	t[1].tv_nsec-=		0x3b9aca00;
			t[1].tv_sec++;
		}
		a=
		clock_nanosleep			(CLOCK_MONOTONIC,
						 TIMER_ABSTIME,
						 t+1,NULL);
	}
	while					(a!=0);
}

static	uint32_t	name_to_index_	(uint8_t *,uint32_t);
static	uint32_t	alias_to_index_	(uint8_t *,uint32_t);

__attribute__((noinline))
static	CALIGN	int	kodep		(uint32_t mi)
{	char		*ma=		kodata.modinfo_addr[mi];
	uint32_t	 ms=		kodata.modinfo_size[mi];

	uint8_t		*a=
	memmema				(ma,ms,"depends=",8);

	if			nay	(a==NULL)	return	0;
	if			yay	(a[9]==0)	return	0;

	uint8_t		*b,c;
	char		req[0x100];
	uint32_t	req_len;
	uint32_t	i;

	for				(a+=8,b=a;c=*b,1;b++)
	if			nay	((c==',')||(c==0))
	{	req_len=		b-a;
		if		nay	(req_len==0)
		if		nay	(c==',')
		continue;
		else
		return			0;

		memcpyt			(req,a,req_len);

		i=
		name_to_index_		(req,req_len);
		if		nay	(i==0xFFFFFFFF)
		i=
		alias_to_index_		(req,req_len);

		if			(i!=0xFFFFFFFF)
		koload_r		(i);
		if		nay	(c==0)
		return			0;
		a=			b+1;
	}
}

SCV	index_to_name		(void)
{	VMETA		*C=	kov+ko_name;	/* ko.name */
	char		*s;
	uint32_t	a;

	s=			kodata.name[memory.index];
	if			(s)
	{	C->textlen=
		a=
		strlen		(s);
		ascript_memcpy	(C->textaddr,s,a);
		C->textaddr[a]=	0;
	}
	else	C->textlen=	0;
}


SCV	index_to_modinfo	(void)
{	VMETA		*D=	kov+ko_info;	/* ko.info */
	uint32_t	i=	memory.index;
	if			(i!=0xFFFFFFFF)
	{	D->textaddr=	kodata.modinfo_addr[i];
		D->textlen=	kodata.modinfo_size[i];
	}
}

__attribute__((noinline))
SCV	index_find	(void)
{	VMETA		*B=	kov+ko_alias;	/* ko.alias */
	VMETA		*C=	kov+ko_name;	/* ko.name */
	memory.index	=	0xFFFFFFFF;

	if		yay	(C->textlen>0)
	name_to_index		();

	if		nay	(B->textlen>0)
	{	alias_to_index	();
		index_to_name	();
	}

	index_to_modinfo	();
}

static	CALIGN	uint32_t	name_to_index_	(uint8_t *,uint32_t);

static	CALIGN	uint32_t	alias_file	(uint8_t *a,struct dirent *b,int c)
{	uint8_t		*d=		b->d_name;
	int		e;
	ssize_t		f;
	uint8_t		t[0x100];

	if			nay	(amatch(d,a))
	{	e=	openat		(c,d,O_RDONLY);
		if		nay	(0>e)		return	0xFFFFFFFF;
		f=	read		(e,t,0xff);
		close			(e);
		if		nay	(0>=f)		return	0xFFFFFFFF;
		if		yay	(t[f-1]=='\n')
		t[--f]=			0;
		return	name_to_index_	(t,f);
	}						return	0xFFFFFFFF;
}

__attribute__((noinline))
static	CALIGN	uint32_t	alias_from_fs	(uint8_t *a)
{	VMETA		*I=	kov+ko_path_config;	/* ko.path.config */

	int	b=	open		(I->textaddr,O_DIRECTORY|O_RDONLY);
	if			nay	(0>b)	return		0xFFFFFFFF;

	int	c=	openat		(b,"alias",O_DIRECTORY|O_RDONLY);
	close				(b);
	if			nay	(0>c)	return		0xFFFFFFFF;

	DIR	*d=	fdopendir	(c);
	if			nay	(d==NULL)
	{	close			(c);	return		0xFFFFFFFF;}

	struct dirent	*e;
	uint32_t	f=					0xFFFFFFFF;
	while				(e=readdir(d))
	if			yay	(e->d_type==DT_REG)
	if			nay	((f=alias_file(a,e,c))!=0xFFFFFFFF)
	break;

	closedir			(d);
	close				(c);
	return				f;
}


static	CALIGN	uint32_t	alias_to_index_	(uint8_t *a, uint32_t b)
{	KOALIAS		*A=	kodata.alias;
	a[b]=			0;
	for			(;A->addr;A++);
	if		nay	(amatch(A->addr,a))
	return			A->from;
	return	alias_from_fs	(a);
}

SCV	alias_to_index		(void)
{	VMETA		*B=	kov+ko_alias;	/* ko.alias */
	memory.index=
	alias_to_index_		(B->textaddr,B->textlen);
}


static		int	modinfod	(uint8_t *i,int d);
static	inline	int	modinfoat	(uint8_t *i,int a,uint8_t *n)
{	int		d=
	openat				(a,n,O_RDONLY);
	if			nay	(0>d)
	return				d;
	int		r=
	modinfod			(i,d);
	close				(d);
	return				r;
}

__attribute__((unused))
static	inline	int	modinfoname	(uint8_t *i,uint8_t *n)
{	int	d=
	open				(n,O_RDONLY);
	if			nay	(0>d)
	return				d;
	int	r=
	modinfod			(i,d);
	close				(d);
	return				r;
}

static		int	modinfod32	(uint8_t *,int,Elf32_Ehdr *);
static		int	modinfod64	(uint8_t *,int,Elf64_Ehdr *);

static	CALIGN	int	modinfod	(uint8_t *i,int d)
{	Elf64_Ehdr			e;

	read				(d,&e,sizeof(Elf64_Ehdr));
	if			nay	(memcmp(e.e_ident,ELFMAG,SELFMAG)!=0)
	goto				invalid;

	switch				(e.e_ident[EI_CLASS])
	{	case	ELFCLASS64:
		return	modinfod64	(i,d,(Elf64_Ehdr *)	&e);
		case	ELFCLASS32:
		return	modinfod32	(i,d,(Elf32_Ehdr *)	&e);
		default:
		invalid:
		errna=			EINVAL;
		return			-1;
	}
}

static	CALIGN	int	modinfod64	(uint8_t *i,int d,Elf64_Ehdr *e)
{	Elf64_Shdr	S[0x40];
	Elf64_Shdr	*s=		S;

	lseek				(d,  e->e_shoff,SEEK_SET);
	read				(d,s,e->e_shnum*
					     e->e_shentsize);

	int	sh_offset=		s[e->e_shstrndx].sh_offset;
	int	sh_size=		s[e->e_shstrndx].sh_size;

	lseek				(d,  sh_offset,SEEK_SET);
	read				(d,i,sh_size);

	uint8_t		*a=
	memmem				(i,sh_size,"\0.modinfo",0xa);
	if			nay	(a==NULL)
	goto				not_found;

	int		b=		a-i+1;

	for				(;s->sh_name!=b;s++);

	int		x=		s->sh_size;
	lseek				(d,s->sh_offset,SEEK_SET);
	read				(d,i,x);
	return				x;

	not_found:
	errna=				EINVAL;
	return				-1;
}

static	CALIGN	int	modinfod32	(uint8_t *i,int d,Elf32_Ehdr *e)
{	Elf32_Shdr	S[0x40];
	Elf32_Shdr	*s=		S;

	lseek				(d,  e->e_shoff,SEEK_SET);
	read				(d,s,e->e_shnum*
					     e->e_shentsize);

	int	sh_offset=		s[e->e_shstrndx].sh_offset;
	int	sh_size=		s[e->e_shstrndx].sh_size;

	lseek				(d,  sh_offset,SEEK_SET);
	read				(d,i,sh_size);

	uint8_t		*a=
	memmem				(i,sh_size,"\0.modinfo",0xa);
	if			nay	(a==NULL)
	goto				not_found;

	int		b=		a-i+1;

	for				(;s->sh_name!=b;s++);

	int		x=		s->sh_size;
	lseek				(d,s->sh_offset,SEEK_SET);
	read				(d,i,x);
	return				x;

	not_found:
	errna=				EINVAL;
	return				-1;
}

/*	if found 1 is returned.
	first  parameter is the modalias string from the kernel   module
	second parameter is the modalias string from the modalias file
	Only in the first parameter * exists.
	* indicates one or more bytes where a match is not required.
	Thus the bytes between * must match.
	Unless the modalias ends with * then all the bytes
	from the second parameter must be used.
*/

__attribute__((pure))
static	CALIGN	uint8_t		amatch		(uint8_t const *a
						,uint8_t const *b)
{	if			nay	(*a==0)		return	0;
	if			nay	(*a==',')	return	0;

	while				(1)
	{	if		nay	(*a==0)
		if		nay	(*b==0)		return	1;

		if		nay	(*a==',')
		if		nay	(*b==0)		return	1;

		if		nay	(*a=='*')	break;
		if		nay	(*b==0)		return	0;
		if		yay	(*a!=*b)	return	0;
		a++;
		b++;
	}

	while				(1)
	{	uint8_t	const	*A=	++a;
		while			(1)
		{	if	nay	(*a==0)
			if		(*b==0)		return	1;

			if	nay	(*a==',')
			if		(*b==0)		return	1;

			if	nay	(*a=='*')	break;
			if	nay	(*b==0)		return	0;
			if	nay	(*a==*b)
			{	a++;
				b++;			continue;
			}
			if		(a==A)
			b++;
			else
			a=		A;
		}
	}
}

SCV	inline	koaddrfind64		(uint32_t i,void *v)
{	Elf64_Ehdr	*e=		v;
	Elf64_Shdr	*s=		v+e->e_shoff;
	Elf64_Shdr	*m=		s+e->e_shnum;
	void		*t=		v+s[e->e_shstrndx].sh_offset;
	uint8_t		*c;

	for				(;m>s;s++)
	{	c=			t+s->sh_name;
/* .modinfo */
		if		nay	(c[8]==0)
		if		yay	(c[4]=='i')
		goto			next_name;


/* .gnu.linkonce.this_module */
		if		nay	(c[25]==0)
		if		yay	(c[19]=='m')
		goto			next_info;
	}
	return;

	next_name:
	kodata.modinfo_addr[i]= 	v+s->sh_offset;
	kodata.modinfo_size[i]= 	  s->sh_size;
	for				(s++;m>s;s++)
	{	c=			t+s->sh_name;
		if		yay	(c[25]!=0)	continue;
		if		nay	(c[19]!='m')	continue;
		kodata.name[i]=		v+s->sh_offset+24;
		return;
	}
	return;

	next_info:
	kodata.name[i]=			v+s->sh_offset+24;
	for				(s++;m>s;s++)
	{	c=			t+s->sh_name;
		if		yay	(c[8]!=0)	continue;
		if		nay	(c[4]!='i')	continue;
		kodata.modinfo_addr[i]= v+s->sh_offset;
		kodata.modinfo_size[i]=   s->sh_size;
		return;
	}
}

SCV	inline	koaddrfind32		(uint32_t i,void *v)
{	Elf32_Ehdr	*e=		v;
	Elf32_Shdr	*s=		v+e->e_shoff;
	Elf32_Shdr	*m=		s+e->e_shnum;
	void		*t=		v+s[e->e_shstrndx].sh_offset;
	uint8_t		*c;

	for				(;m>s;s++)
	{	c=			t+s->sh_name;
/* .modinfo */
		if		nay	(c[8]==0)
		if		yay	(c[4]=='i')
		goto			next_name;


/* .gnu.linkonce.this_module */
		if		nay	(c[25]==0)
		if		yay	(c[19]=='m')
		goto			next_info;
	}
	return;

	next_name:
	kodata.modinfo_addr[i]= 	v+s->sh_offset;
	kodata.modinfo_size[i]= 	  s->sh_size;
	for				(s++;m>s;s++)
	{	c=			t+s->sh_name;
		if		yay	(c[25]!=0)	continue;
		if		nay	(c[19]!='m')	continue;
		kodata.name[i]=		v+s->sh_offset+12;
		return;
	}
	return;

	next_info:
	kodata.name[i]=			v+s->sh_offset+12;
	for				(s++;m>s;s++)
	{	c=			t+s->sh_name;
		if		yay	(c[8]!=0)	continue;
		if		nay	(c[4]!='i')	continue;
		kodata.modinfo_addr[i]= v+s->sh_offset;
		kodata.modinfo_size[i]=   s->sh_size;
		return;
	}
}

SCV	inline	koaddrfind	(uint32_t i)
{	Elf64_Ehdr	*e=	kodata.addr[i];
	switch			(e->e_ident[EI_CLASS])
	{	case	ELFCLASS64:	koaddrfind64	(i,e);	return;
		case	ELFCLASS32:	koaddrfind32	(i,e);	return;
	}
}

SCV	kodir		(int, struct dirent *, int *);
SCV	kofile		(int, struct dirent *, int *);

__attribute__((noinline))
SCV	komapinit		(int d, uint8_t *n, int *i)
{	DIR		*s;
	struct dirent	*e;

	d=	openat		(d,n,O_DIRECTORY);
	if		nay	(0>d)	 {warn("%s %s","openat"   ,n);return;}
	s=	fdopendir	(d);
	if		nay	(s==NULL){warn("%s %s","fdopendir",n);return;}

	errna=			0;
	while			(e=readdir(s))
	{	if	yay	(e->d_type==DT_REG)	kofile	(d,e,i);else
		if	yay	(e->d_type==DT_DIR)	kodir	(d,e,i);
	}

	if		yay	(s!=NULL)		closedir(s);
	if		yay	(d>=0)			close	(d);
}

SCV	kofile		(int d, struct dirent *e, int *i)
{	d=	openat	(d,e->d_name,O_RDONLY);
	if	nay	(0>d)	{warn("%s %s","openat",e->d_name);return;}

	off_t	s=
	lseek		(d,0,SEEK_END);

	void	*v=
	mmap		(NULL,s,PROT_READ,MAP_SHARED,d,0);
	close		(d);
	if	nay	(v==(void *)-1)
	{	if	(s!=0)
		warn	("%s %s","mmap",e->d_name);
		return;
	}

	Elf64_Ehdr	*h=	v;
	if		yay	(memcmp(h->e_ident,ELFMAG,SELFMAG)==0)
	{	kodata.addr[*i]=v;
		kodata.size[*i]=s;
		(*i)++;
	}
	else	munmap		(v,s);
}

SCV	kodir		(int d, struct dirent *e, int *i)
{	if	nay	(e->d_name[0]!='.')	komapinit	(d,e->d_name,i);
}

__attribute__((noinline))
SCV	koaddrinit		(void)
{	uint32_t	i=	0;
	do
	{	koaddrfind	(i);
	}	while		(kodata.addr[++i]!=NULL);
}


/*
For multiple aliases alias= for each is often specified.
But in some modinfo multiple alias are comma separated.
*/

SCV	inline	koaliasfind	(uint32_t i, uint32_t *a, uint8_t *c,uint32_t s)
{	uint8_t		*m;
	for					(m=c+s;m>c;c++)
	if				nay	(c[0]=='a')
	if				nay	(c[1]=='l')
	if				yay	(c[2]=='i')
	if				yay	(c[3]=='a')
	if				yay	(c[4]=='s')
	if				yay	(c[5]=='=')
	{	kodata.alias[*a].addr=		c+6;
		kodata.alias[*a].from=		i;
		(*a)++;
		for				(c+=6;*c;c++)
		if			nay	(*c==',')
		{	kodata.alias[*a].addr=	c+1;
			kodata.alias[*a].from=	i;
			(*a)++;
		}
	}
}

__attribute__((noinline))
SCV	koaliasinit		(void)
{	uint32_t		a,i;
	for			(i= a=0;kodata.modinfo_addr[i];i++)
	koaliasfind		(i,&a,  kodata.modinfo_addr[i],
				        kodata.modinfo_size[i]);
}


__attribute__((unused))
__attribute__((noinline))
SCV	kodatashow		(void)
{	uint32_t	i;
	for		(i=0;kodata.addr[i];i++)
	warnx		("%i	%s	%p	%i	%p	%i",
			i,
			kodata.name[i],
			kodata.addr[i],
			kodata.size[i],
			kodata.modinfo_addr[i],
			kodata.modinfo_size[i]);
}

__attribute__((unused))
__attribute__((noinline))
SCV	koaliasshow	(void)
{	uint32_t	i;
	for		(i=0;kodata.alias[i].addr;i++)
	warnx		("%i	%i	%s	%s"
			,i
			,kodata.alias[i].from
			,kodata.alias[i].addr
			,kodata.name[kodata.alias[i].from]);
}

__attribute__((unused))
__attribute__((noinline))
SCV	komodinfoshow	(void)
{	uint32_t	i;
	for		(i=0;kodata.addr[i];i++)
	{	warnx	("%i	%s	%p	%i	%p	%i\n",
			i,
			kodata.name[i],
			kodata.addr[i],
			kodata.size[i],
			kodata.modinfo_addr[i],
			kodata.modinfo_size[i]);
		write	(2,kodata.modinfo_addr[i],kodata.modinfo_size[i]);
		write	(2,"\n\n",2);
	}
}

__attribute__((noinline))
SCV	kodatainit		(void)
{	madvise			(&kodata,sizeof(kodata),MADV_NOHUGEPAGE);
	uint32_t	i=	0;
	uint8_t		*n=	kov[ko_path_object].textaddr;
	komapinit		(AT_FDCWD,n,&i);
	koaddrinit		();
	koaliasinit		();
/*	kodatashow		();	*/
/*	komodinfoshow		();	*/
/*	koaliasshow		();	*/
}

__attribute__((noinline))
SCV	cram		(void)
{	void		**v=kodata.addr;
	uint32_t	*s=kodata.size;
	for		(;*v;v++,s++)
	munmap		(*v,*s);
	madvise		(&kodata,sizeof(kodata),MADV_DONTNEED);
	kodatainit	();
}

SCV	kocram		(void)
{	cram		();
	*Gz.at=		kocram;
	argot_next	();
}

static	CALIGN	uint32_t	name_to_index_	(uint8_t *a,uint32_t b)
{
/*	memset			(a+b,0,8);		*/
	uint32_t	h=	*(uint32_t *)a;
	uint32_t	i;
	char		*c;
	for			(i=0;c=kodata.name[i],c!=NULL;i++);
	if			(*(uint32_t *)c==h)
	if			(c[b]==0)
	if			(ascript_memcmp(a,c,b)==0)
	return			i;
	return			0xFFFFFFFF;
}

SCV	name_to_index		(void)
{	VMETA		*C=	kov+ko_name;	/* ko.name */
	memory.index=
	name_to_index_		(C->textaddr,C->textlen);
}

SCV	kopin		(void)
{	void		(**P)	(void);
	if		(Gz.to[0]->value.i=='\'')
	P=
	nearfind_fast	(Gz.to[0]->textaddr,partfar(NULL));
	else
	P=
	farfind_fast	(Gz.to[0]->textaddr);

	memory.pin=	P;
	*Gz.at=		kopin;
	argot_next	();
}

/*
SCV	koharktest	(void)	{progeny();};
SCV	kovartest	(void)
{	warnx	("ko_defy_modver %s",	kov[ko_defy_modver].name);
	warnx	("ko_defy_omit %s",	kov[ko_defy_omit].name);
	warnx	("ko_defy_vermagic %s",	kov[ko_defy_vermagic].name);
	warnx	("ko_uevent_major %s",	kov[ko_uevent_major].name);
	warnx	("ko_uevent_minor %s",	kov[ko_uevent_minor].name);
	warnx	("ko_uevent_pid %s",	kov[ko_uevent_pid].name);
	warnx	("ko_alias %s",	kov[ko_alias].name);
	warnx	("ko_name %s",	kov[ko_name].name);
	warnx	("ko_info %s",	kov[ko_info].name);
	warnx	("ko_path_config %s",	kov[ko_path_config].name);
	warnx	("ko_path_dev %s",	kov[ko_path_dev].name);
	warnx	("ko_path_log %s",	kov[ko_path_log].name);
	warnx	("ko_path_object %s",	kov[ko_path_object].name);
	warnx	("ko_uevent_action %s",	kov[ko_uevent_action].name);
	warnx	("ko_uevent_alias %s",	kov[ko_uevent_alias].name);
	warnx	("ko_uevent_devname %s",	kov[ko_uevent_devname].name);
	warnx	("ko_uevent_raw %s",	kov[ko_uevent_raw].name);
	warnx	("ko_uevent_syspath %s",	kov[ko_uevent_syspath].name);
	warnx	("ko_uevent_subsys %s",	kov[ko_uevent_subsys].name);
	argot_next	();
}
*/

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180401",
	.official=	"20180401",
	.update=	"20200809",
};

__attribute__((constructor))
SCV	aainit	(void)
{	aa_init	();
	aa	(komap_,	"komap");
	aa	(kopin,		"kopin");
	aa	(kohark,	"kohark");
	aa	(kocold,	"kocold");
	aa	(kocram,	"kocram");
	aa	(koinfo,	"koinfo");
	aa	(kodead,	"kodead");
	aa	(kolive,	"kolive");
	aa	(kooust,	"kooust");
	aa	(koload,	"koload");
	aa	(koauto,	"koauto");

/*
	aa	(koharktest,	"koharktest");
	aa	(kovartest,	"kovartest");
*/
	aa_fini	();
};


__attribute__((constructor))
SCV	init		(void)
{	kodatainit	();
	errna=		0;
}
