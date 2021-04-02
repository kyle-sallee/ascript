/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

/*
To self note.
The memcpyt invocations
to  memcpya invocations
do not change.
the bytes aft copying
by memcpyt
16 value 0 bytes
are written.
memcpyt solves problems.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"ko.h"
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

#define		MODULE_INIT_IGNORE_MODVERSIONS	1
#define		MODULE_INIT_IGNORE_VERMAGIC	2

static		uint8_t	KOBYTE[0x100]=
{	0x00,	0x01,	0x02,	0x03,	0x04,	0x05,	0x06,	0x07,
	0x08,	0x09,	0x0a,	0x0b,	0x0c,	0x0d,	0x0e,	0x0f,
	0x10,	0x11,	0x12,	0x13,	0x14,	0x15,	0x16,	0x17,
	0x18,	0x19,	0x1a,	0x1b,	0x1c,	0x1d,	0x1e,	0x1f,
	0x20,	0x21,	0x22,	0x23,	0x24,	0x25,	0x26,	0x27,
	0x28,	0x29,	0x2a,	0x2b,	0x2c,	0x5f,	0x2e,	0x2f,
	0x30,	0x31,	0x32,	0x33,	0x34,	0x35,	0x36,	0x37,
	0x38,	0x39,	0x3a,	0x3b,	0x3c,	0x3d,	0x3e,	0x3f,
	0x40,	0x41,	0x42,	0x43,	0x44,	0x45,	0x46,	0x47,
	0x48,	0x49,	0x4a,	0x4b,	0x4c,	0x4d,	0x4e,	0x4f,
	0x50,	0x51,	0x52,	0x53,	0x54,	0x55,	0x56,	0x57,
	0x58,	0x59,	0x5a,	0x5b,	0x5c,	0x5d,	0x5e,	0x5f,
	0x60,	0x61,	0x62,	0x63,	0x64,	0x65,	0x66,	0x67,
	0x68,	0x69,	0x6a,	0x6b,	0x6c,	0x6d,	0x6e,	0x6f,
	0x70,	0x71,	0x72,	0x73,	0x74,	0x75,	0x76,	0x77,
	0x78,	0x79,	0x7a,	0x7b,	0x7c,	0x7d,	0x7e,	0x7f,
	0x80,	0x81,	0x82,	0x83,	0x84,	0x85,	0x86,	0x87,
	0x88,	0x89,	0x8a,	0x8b,	0x8c,	0x8d,	0x8e,	0x8f,
	0x90,	0x91,	0x92,	0x93,	0x94,	0x95,	0x96,	0x97,
	0x98,	0x99,	0x9a,	0x9b,	0x9c,	0x9d,	0x9e,	0x9f,
	0xa0,	0xa1,	0xa2,	0xa3,	0xa4,	0xa5,	0xa6,	0xa7,
	0xa8,	0xa9,	0xaa,	0xab,	0xac,	0xad,	0xae,	0xaf,
	0xb0,	0xb1,	0xb2,	0xb3,	0xb4,	0xb5,	0xb6,	0xb7,
	0xb8,	0xb9,	0xba,	0xbb,	0xbc,	0xbd,	0xbe,	0xbf,
	0xc0,	0xc1,	0xc2,	0xc3,	0xc4,	0xc5,	0xc6,	0xc7,
	0xc8,	0xc9,	0xca,	0xcb,	0xcc,	0xcd,	0xce,	0xcf,
	0xd0,	0xd1,	0xd2,	0xd3,	0xd4,	0xd5,	0xd6,	0xd7,
	0xd8,	0xd9,	0xda,	0xdb,	0xdc,	0xdd,	0xde,	0xdf,
	0xe0,	0xe1,	0xe2,	0xe3,	0xe4,	0xe5,	0xe6,	0xe7,
	0xe8,	0xe9,	0xea,	0xeb,	0xec,	0xed,	0xee,	0xef,
	0xf0,	0xf1,	0xf2,	0xf3,	0xf4,	0xf5,	0xf6,	0xf7,
	0xf8,	0xf9,	0xfa,	0xfb,	0xfc,	0xfd,	0xfe,	0xff,
};

static	HALIGN	MEMORY		memory;

/*
typedef	struct
{	uint8_t	a[0x20];
}	FIT;

__attribute__((always_inline))
static	inline	void	vd	(VMETA *A,FIT const *B)
{	map_init		(A);
	A->vam=			&Gz.hash.var[bit128_to_bit16(B->a)];
	vattach_fast		(A);
}
*/

#define	va(a,b)	{.name=(a),.len=strlen((a)),.io.flag=textmapuse,.op=opbyte\
		,.text=b,.textlen=strlen(b)}

#define	vb(a)	{.name=(a),.len=strlen((a)),.io.flag=textmapuse,.op=opbyte}
#define	vc(a)	{.name=(a),.len=strlen((a)),.io.flag=datamapuse,.op=opint4}

/*
#define	vc(z)	vd(A,&(FIT const){.a=z});A++
*/
#define	vd(z)	map_init(A);vattach_faster(A,z);A->show=Gz.out.den4;A++
#define	ve(z)	map_init(A);vattach_faster(A,z);A++

static	VMETA	kov[]=
{	vc("ko.defy.modver"),
	vc("ko.defy.omit"),
	vc("ko.defy.vermagic"),
	vc("ko.uevent.major"),
	vc("ko.uevent.minor"),
	vc("ko.uevent.pid"),

	vb("ko.alias"),
	vb("ko.name"),
	vb("ko.info"),
	vb("ko.pathname"),
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
	vd("ko.defy.modver");
	vd("ko.defy.omit");
	vd("ko.defy.vermagic");
	vd("ko.uevent.major");
	vd("ko.uevent.minor");
	vd("ko.uevent.pid");

	ve("ko.alias");
	ve("ko.name");
	ve("ko.info");
	ve("ko.pathname");
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
	A=				kov+ko_pathname;
	A->textaddr=			memory.kovp+PAGE*2;
	A->textsize=			PAGE;
	A=				kov+ko_uevent_alias;
	A->textaddr=			memory.kovp+PAGE*3;
	A->textsize=			PAGE;
	A=				kov+ko_uevent_syspath;
	A->textaddr=			memory.kovp+PAGE*4;
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
/*
static		VMETA		*koa;
*/

static		void	*datastore	(size_t);
static		void	*stringstore	(size_t,uint8_t *);
static		void	delay		(void);
static		void	kobyte		(uint8_t *);
static		void	omattach	(OBJECT *);
static		void	amattach	(ALIAS *);
static		void	kocache		(void);
static		int	object_find	(void);
static		int	object_pathname	(uint8_t *,OBJECT *);
static		OBJECT	*name_to_object	(uint8_t *,int);
static		int	koload_		(void);
static		int	kooust_		(void);
static		OBJECT	*alias_to_object(uint8_t *);

static		void	ko_	(void)
{	*Gz.at=		ko_;
	argot_next	();
}

static	CALIGN	void	kocram	(void)
{	madvise			(memory.avail=memory.data,
				sizeof(memory.data),MADV_DONTNEED);
	kocache			();
	*Gz.at=			kocram;
	argot_next		();
}

static	CALIGN	void	koinfo	(void)
{	object_find		();
	*Gz.at=			koinfo;
	argot_next		();
}

static		void	syswalk	(void);

static	inline	void	syscheck(void)
{	if	yay	(access("/sys/devices",F_OK)==0)
	return;
	mkdir		("/sys",0755);
	mount		(NULL,"/sys","sysfs", MS_NOATIME|MS_NODEV|MS_NOEXEC,"");
}

static	inline	void	syswalk	(void);

static	CALIGN	void	kocold	(void)
{	syswalk			();
	*Gz.at=			kocold;
	argot_next		();
}

__attribute__((noinline))
static	CALIGN	void	syswalk_r	(int a,uint8_t *b)
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
/*
static	void	line_init	(void);
*/
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
{	/* For the daemon start a sec wait */
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

static		void	nasty			(void);
static		int	parse_clone		(void *);
static		void	parse_clone_init	(void);

__attribute__((noinline))
static	CALIGN	int	progeny			(void)
{	nasty					();
	chdir					("/");
	newname					();
/*	line_init				();	*/
/*	parse_clone_init			();	*/
	socketup				();
	memory.uevent.data[0]=			0;	/* huge page fault */
	memory.uevent.futex.use=		0;
	syscall					(SYS_futex,
						 &memory.uevent.futex,
						 FUTEX_WAKE,
						 INT_MAX,NULL,NULL,0);
	parse_clone				(NULL);
}


static	inline	void	nasty		(void)
{	nice				(-20);
/*
	struct	sched_attr	a;
	a.sched_policy=			 SCHED_FIFO;
	a.sched_priority=
	sched_get_priority_max		(SCHED_FIFO);
	a.size=
	sizeof				(struct sched_attr);
	syscall				(SYS_sched_setattr,0,a,0);
*/
}

__attribute__((unused))
SCV	parse_clone_init	(void)
{	uint8_t		*v=
	mmap					(NULL,
						 HUGE*4,
						 PROT_READ|PROT_WRITE,
						 MAP_ANONYMOUS|
						 MAP_PRIVATE|
						 MAP_STACK,
						 -1,0);

/*	clone					(parse_clone,
						 v+HUGE*4,
						 CLONE_FILES|
						 CLONE_FS|
						 CLONE_PARENT|
						 CLONE_PTRACE|
						 CLONE_SYSVSEM|
						 CLONE_VM|
						 SIGCHLD,
						 NULL);
*/

	clone					(parse_clone,
						 v+HUGE*4,
						 CLONE_FILES|
						 CLONE_FS|
						 CLONE_PARENT|
						 CLONE_PTRACE|
						 CLONE_SIGHAND|
						 CLONE_SYSVSEM|
						 CLONE_THREAD|
						 CLONE_VM,
						 NULL);
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

static	inline	void	zeroout		(uint8_t *);
static	inline	void	newname		(void)
{	uint8_t		*p,**v=		Gz.arg.v;
	prctl				(PR_SET_NAME,"kod");
	if			yay	(v[0][0]!=0)
	if			yay	(v[0][1]!=0)
	if			yay	(v[0][2]!=0)
	{	memcpy			(v[0],"kod",4);
		zeroout			(v[0]+4);
	}
	while				(p=*++v)
	zeroout				(p);
}

static	inline	void	zeroout		(uint8_t *a)
{	for		(;*a;*a++=0);
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

static	CALIGN	void	usr1	(int x,siginfo_t *i,void *v)
{	VMETA		*G=	kov+ko_defy_omit;	/* ko.defy.omit */
	G->value.i=		i->si_value.sival_int;
}

SCV	usr2			(int x,siginfo_t *i,void *v)
{	int	e=		errna;
	madvise			(memory.avail=memory.data,
				sizeof(memory.data),MADV_DONTNEED);
	kocache			();
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
/*	int const	b=		0x400;
*/

	VMETA		*K=		kov+ko_path_log;	/* ko.path.log*/

	mkdirr				(K->textaddr,0700);
	logmsg				(K->textaddr,a,b);

	VMETA		*B=		kov+ko_alias;	/* ko.alias */
	VMETA		*C=		kov+ko_name;	/* ko.name  */
	VMETA		*E=		kov+ko_pathname;	/* ko.pathname */
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
	C->textlen=
	E->textlen=			0;

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
	object_find			();

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

static	CALIGN	void	koauto	(void)
{	tacit			();
	*Gz.at=			koauto;
	argot_next		();
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
/*	delay				();	*/

	VMETA		*C=		kov+ko_name;	/* ko.name  */
	if				(C->textlen==0)
	return				0;

	int		a;
	while				(1)
	{	errna=			0;
		a=
		syscall			(__NR_delete_module,
					 C->textaddr,
					 O_NONBLOCK);

		if			(a==0)			break;
		if			(errna==EINTR)		continue;
		if			(errna==ERESTART)	continue;
		break;
	}

	warn				("%-19s %-19s %i",
					 "__NR_delete_module",C->textaddr,errna);
	return				a;
}

__attribute__((unused))
static	inline	uint8_t	tacit_change	(void)
{	return	0;
}

__attribute__((unused))
static	inline	uint8_t	tacit_move	(void)
{	return	0;
}

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
static	inline	uint8_t	ischar		(int a)
{	struct	stat	b;
	int		c=
	fstat			(a,&b);
	if			(0>c)
	return			0;
	return			((b.st_mode&S_IFMT)==S_IFCHR);
}


static		uint8_t	loaded		(uint8_t *);

static	CALIGN	void	kolive		(void)
{	object_find			();
	int		r=
	loaded				(kov[ko_name].textaddr);
	*Gz.at=				kolive;
	argot_jump			(r==0);
}

static	CALIGN	void	kodead		(void)
{	object_find			();
	int		r=
	loaded				(kov[ko_name].textaddr);
	*Gz.at=				kodead;
	argot_jump			(r!=0);
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
{	VMETA		*I=	kov+ko_path_config;	/* ko.path.config */

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

static	inline	uint8_t	kopara	(uint8_t *a,uint8_t *b)
{	VMETA		*I=	kov+ko_path_config;	/* ko.path.config */

	b[0]=			0;
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
	read			(e,b,PAGE);
	close			(e);
	if		nay	(0>t)
	return			t;

	b[t]=			0;
	return			0;
}

static	CALIGN	void	koload		(void)
{	object_find			();
	int		r=
	koload_				();
	*Gz.at=				koload;
	argot_jump			(r==0);
}

static	CALIGN	void	kooust		(void)
{	object_find			();
	int		r=
	kooust_				();
	*Gz.at=				kooust;
	argot_jump			(r==0);
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

static		int	koload_r	(KOLOAD *);

__attribute__((noinline))
static	CALIGN	int	koload_		(void)
{
/*	VMETA		*A=		koa;	*/
	VMETA		*B=		kov+ko_alias;	/* ko.alias */
	VMETA		*C=		kov+ko_name;	/* ko.name  */
	VMETA		*F=		kov+ko_defy_modver;	/* ko.defy.modver */
	VMETA		*G=		kov+ko_defy_omit;	/* ko.defy.omit */
	VMETA		*H=		kov+ko_defy_vermagic;	/* ko.defy.vermagic */

	KOLOAD		K;
/*	memset				(K.name,0,0x10);
*/

	if				(B->textlen>0)
	{	B->textaddr[
		B->textlen]=		0;
		K.object=
		alias_to_object		(B->textaddr);
		if		nay	(K.object==NULL)
		return			1;

		K.name_len=		 K.object->name_len;
		memcpyt			(K.name,
					 K.object->name,
					 K.name_len);
	}
	else
	if				(C->textlen>0)
	{	C->textaddr[
		C->textlen]=		0;
		K.name_len=		 C->textlen;
		memcpyt			(K.name,C->textaddr,K.name_len);

		K.object=
		name_to_object		(K.name,K.name_len);
		if		nay	(K.object==NULL)
{
/*	warnx	("by name object not discovered: %s",K.name);
*/
		return			1;
}
	}
	else
	{	errna=			EINVAL;
		return			1;
	}

	K.flag=				(F->value.i!=0)*
					MODULE_INIT_IGNORE_MODVERSIONS;
	K.flag|=			(H->value.i!=0)*
					MODULE_INIT_IGNORE_VERMAGIC;

	K.omit=				G->value.i;
	return
	koload_r			(&K);
}

static		int	kodep		(KOLOAD *);
__attribute__((noinline))
static	CALIGN	int	koload_r	(KOLOAD *K)
{	if			yay	(loaded(K->name)==0)
	return				0;

	if			nay	(K->omit==0)
	if			nay	(koomit(K->name)==0)
	return				0;

	int		e=
	kodep				(K);
	kopara				(K->name,K->para);

	object_pathname			(K->pathname,K->object);
	int		d=
	open				(K->pathname,O_RDONLY);
	if			nay	(0>d)
	return				d;

/*	delay				();	*/

	int		f;
	while				(1)
	{	errna=			0;
		f=
		syscall			(__NR_finit_module,d,K->para,K->flag);

/*		warn			("__NR_finit_module for f=%i %s",f,K->pathname);
*/
		if			(f==0)			break;
		if			(errna==EINTR)		continue;
		if			(errna==ERESTART)	continue;
		break;
	}

/*	warn				("%-19s %-19s %-39s %i",
					 "__NR_finit_module",
					 K->name,K->pathname,errna);
*/
	e|=				f;
	close				(d);
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

__attribute__((noinline))
static	CALIGN	int	kodep		(KOLOAD *K)
{	if			nay	(K->object==NULL)
	return				1;

	uint8_t		*a=
	memmema				(K->object->modinfo,
					 K->object->modinfo_len,
					 "depends=",8);

	if			nay	(a==NULL)	return	0;
	if			yay	(a[9]==0)	return	0;

	KOLOAD		k;
	k.flag=				K->flag;
	k.omit=				K->omit;

	uint8_t		*b,c;

	for				(a+=8,b=a;c=*b,1;b++)
	if			nay	((c==',')||(c==0))
	{	k.name_len=		b-a;
		if		nay	(k.name_len==0)
		if		nay	(c==',')
		continue;
		else
		return			0;

		memcpyt			(k.name,a,
					 k.name_len);
/*		k.name[
		k.name_len]=		0;
*/
		kobyte			(k.name);
		k.object=
		name_to_object		(k.name,k.name_len);
		koload_r		(&k);
		if		nay	(c==0)
		return			0;
		a=			b+1;
	}
}

static		OBJECT	*alias_to_name		(void);
static		int	pathname_to_name	(void);
static		int	name_to_pathname	(void);

/* keep revising this */
__attribute__((noinline))
static	CALIGN	int	object_find	(void)
{
/*	VMETA		*A=		koa;	*/
	VMETA		*B=		kov+ko_alias;	/* ko.alias */
	VMETA		*C=		kov+ko_name;	/* ko.name */
	VMETA		*D=		kov+ko_info;	/* ko.info */
	VMETA		*E=		kov+ko_pathname;	/* ko.pathname */

	OBJECT		*O=		NULL;

	if			nay	(B->textlen>0)
	{	B->textaddr[
		B->textlen]=		0;
		O=
		alias_to_name		();
	}

	if			yay	(O==NULL)
	if			yay	(C->textlen>0)
	{	C->textaddr[
		C->textlen]=		0;
		O=
		name_to_object		(C->textaddr,C->textlen);
	}

	if			nay	(O==NULL)
	return				1;

	E->textlen=
	object_pathname			(E->textaddr,O);

	D->textaddr=			O->modinfo;
	D->textlen=			O->modinfo_len;
	return				0;
}

static		uint8_t	amatch		(uint8_t *,uint8_t *);
static	inline	OBJECT	*alias_to_name	(void)
{	VMETA		*B=		kov+ko_alias;	/* ko.alias */
	VMETA		*C=		kov+ko_name;	/* ko.name */
	uint8_t		*b=		B->textaddr;

	OBJECT		*O=
	alias_to_object			(b);
	if			yay	(O!=NULL)
	{	C->textlen=		 O->name_len;
		memcpyt			(C->textaddr,O->name,
					 C->textlen);
		return			O;
	}
	return				O;
}


static	CALIGN	OBJECT	*alias_to_object	(uint8_t *b)
{	ALIAS		*S;
	S=				memory.alias[b[0]];
	for				(;S;S=S->next)
	if			nay	(amatch(S->alias,b))
	return				S->object;
	return				NULL;
}


static		int	kopathnamefind		(void);
__attribute__((unused))
static	CALIGN	int	name_to_pathname	(void)
{	VMETA		*C=		kov+ko_name;	/* ko.name */
	kobyte				(C->textaddr);
	kopathnamefind			();
}

__attribute__((unused))
static	CALIGN	int	pathname_to_name	(void)
{	VMETA		*C=		kov+ko_name;	/* ko.name */
	VMETA		*E=		kov+ko_pathname;	/* ko.pathname */

	uint8_t		*c=		C->textaddr,
			*e=		E->textaddr;
	uint8_t		a;

	for				(;a=*e;*c++=KOBYTE[a],e++)
	if			nay	(a=='/')
	c=				C->textaddr;

	size_t		t=		c-C->textaddr;
	if			yay	(t>4)
	if				(c[-1]=='o')
	if			yay	(c[-2]=='k')
	if			yay	(c[-3]=='.')
	t-=				3;
	c[t]=				0;
	C->textlen=			t;
	return				0;
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

static	CALIGN	uint8_t		amatch		(uint8_t *a,uint8_t *b)
{	if			nay	(*a==0)		return	0;

	while				(1)
	{	if		nay	(*a==0)		return	1;
		if		nay	(*a=='*')	break;
		if		nay	(*b==0)		return	0;
		if		yay	(*a!=*b)	return	0;
		a++;
		b++;
	}

	while				(1)
	{	uint8_t		*A=	++a;
		while			(1)
		{	if	nay	(*a==0)		return	1;
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

static		void		dircacheinit	(DIRCACHE *);
static		PATHABOVE	*dircachenext	(DIRCACHE *);

static		void	align0x10	(void **);

static		void	modaliascache	(OBJECT *);


static		void	alsocache	(void);

__attribute__((noinline))
SCV	kocache				(void)
{	sigset_t			s[2];
	*(uint64_t *)	s=		0xffffffffffffffff;
	sigprocmask			(SIG_SETMASK,s,s+1);

	DIRCACHE	dc;
	dircacheinit			(&dc);

	PATHABOVE	*p;
	OBJECT		*o;
	uint8_t		*m;

	if				(dc.D[0].dir!=NULL)
	while				(p=dircachenext(&dc))
	{	m=
		datastore		(0);
		int		r=
		modinfoat		(m,dc.d->des,p->name);

		if		nay	(0>=r)
		continue;

		datastore		(r+1);
		o=
		datastore		(sizeof(OBJECT));

		o->modinfo=		m;
		o->modinfo_len=		r;
		o->pathabove=		p;
		o->name_len=		p->len-3;
		o->name=
		stringstore		(o->name_len,p->name);
		kobyte			(o->name);

		omattach		(o);
		modaliascache		(o);
	}

	alsocache			();
	sigprocmask			(SIG_SETMASK,s+1,NULL);
}

static		void	alias_custom	(OBJECT *,uint8_t *,int);
static	CALIGN	void	alsocache	(void)
{	VMETA		*I=		kov+ko_path_config;	/* ko.path.config */
	int		a=
	open				(I->textaddr,O_RDONLY);
	if			nay	(0>a)	return;

	int		b=
	openat				(a,"also",O_RDONLY);
	close				(a);

	if			nay	(0>b)	return;

	DIR		*c=
	fdopendir			(b);

	struct	dirent	*d;
	struct	stat	e;
	int		f;
	uint8_t		g;
	uint8_t		*h;
	OBJECT		*i;
	uint8_t		*j;
	int		k;
	int		z;

	while				(d=readdir(c))
	{	z=			d->d_name[0];
		if			(z=='.')		continue;
		z=	fstatat		(b,d->d_name,&e,0);
		if			(0>z)			continue;
		f=	openat		(b,d->d_name,O_RDONLY);
		if			(0>f)			continue;

		g=	strlenb		(d->d_name);
		h=	datastore	(0);
		memcpyt			(h,d->d_name,g);

		i=	name_to_object	(h,g);

		if		nay	(i==NULL)		continue;

		j=	datastore	(0);
		k=	read		(f,j,PAGE);
		close			(f);

		if			(0>k)			continue;
		datastore		(k+1);
		alias_custom		(i,j,k);
	}
	closedir			(c);
}

static	CALIGN	void	alias_custom	(OBJECT *O,uint8_t *a,int b)
{	uint8_t		*c,*e;
	int		d;
	ALIAS		*A;

	for				(e=a+b,c=a;e>c;c++)
	if			nay	(*c=='\n')
	{	d=			c-a;
		if		nay	(d==0)		continue;
		missing_lf:
		*c=			0;
		a=
		stringstore		(d,a);
		A=
		datastore		(sizeof(ALIAS));
		A->alias=		a;
		A->object=		O;
		a=			c+1;
		amattach		(A);
	}
	if			nay	(a!=c)
	goto				missing_lf;
}

SCV	dircacheinit			(DIRCACHE *D)
{	/* ko.path.object */
	uint8_t		*n=		kov[ko_path_object].textaddr;
	int		L=
	strlenb				(n);
	uint8_t		*a=
	stringstore			(L,n);

	D->D[0].pa=
	datastore			(sizeof(PATHABOVE));

	D->D[0].pa->name=		a;
	D->D[0].pa->len=		L;
	D->d=				D->D;

	int		d=
	D->D[0].des=
	open				(n,O_DIRECTORY);
	if			yay	(d>=0)
	D->D[0].dir=
	fdopendir			(d);
	else
	D->D[0].dir=			NULL;
}

static	CALIGN	PATHABOVE	*dircachenext	(DIRCACHE *D)
{	struct	dirent	*E;
	PATHABOVE	*pa;

	while				(1)
	if			nay	((E=readdir(D->d->dir))==NULL)
	{	closedir		(D->d->dir);
		D->d--;
		if		nay	(D->D>D->d)
		return			NULL;
	}
	else
	if				(E->d_type==DT_REG)
	{	pa=
		datastore		(sizeof(PATHABOVE));

		pa->above=		D->d->pa;
		pa->len=
		strlenb			(E->d_name);
		pa->name=
		stringstore		(pa->len,E->d_name);
		return			pa;
	}
	else
	if			yay	(E->d_type==DT_DIR)
	{	if			(E->d_name[0]=='.')
		if			(E->d_name[1]=='.')	continue;
		else	if		(E->d_name[1]==0  )	continue;

		int	d=
		openat			(D->d->des,E->d_name,O_DIRECTORY);
		if		nay	(0>d)			continue;

		pa=
		datastore		(sizeof(PATHABOVE));
		pa->above=		D->d->pa;
		pa->len=
		strlenb			(E->d_name);
		pa->name=
		stringstore		(pa->len,E->d_name);

		D->d++;
		D->d->des=		d;
		D->d->pa=		pa;
		D->d->dir=
		fdopendir		(d);
	}
}

static	CALIGN	void	modaliascache	(OBJECT *o)
{	ALIAS		*A;
	uint8_t		*a=		o->modinfo,
			*e=		o->modinfo+
					o->modinfo_len;

	while				(a=memmema(a,e-a,"alias=",6))
	{	A=
		datastore		(sizeof(ALIAS));
		A->object=		o;
		A->alias=
		a+=			6;
		amattach		(A);
		for			(;*a;a++);
	}
}

static	CALIGN	int	kopathnamefind	(void)
{
/*	VMETA		*A=		koa;	*/
	VMETA		*C=		kov+ko_name;	/* ko.name */

	uint8_t		*a=		C->textaddr;
	int		b=		C->textlen;

	OBJECT		*o=
	name_to_object			(a,b);
	if			nay	(o==NULL)
	return				1;

	VMETA		*E=		kov+ko_pathname;	/* ko.pathname */
	E->textlen=
	object_pathname			(E->textaddr,o);
	return				0;
}


static	inline	void	pad0x10		(uint8_t *,int);

__attribute__((noinline))
static	CALIGN	OBJECT	*name_to_object	(uint8_t *a,int b)
{	pad0x10				(a,b);
	OBJECT		*O=		memory.object[b&7][bit128_to_bit16(a)];
	for				(;O;O=O->next)
	if			yay	(O->name_len==b)
	if			yay	(O->name[0]==a[0])
	if			yay	(memcmpa(O->name,a,b)==0)
	return				O;
	return				NULL;
}

static	inline	void	pad0x10		(uint8_t *a,int b)
{	if	yay	(b>=0x10);
	else
	memset		(a+b,0,0x10);
}

__attribute__((always_inline))
static	inline	void	*datastore	(size_t t)
{	void		*v=	memory.avail;
	memory.avail+=		t;
	align0x10		(&memory.avail);
	return			v;
}

__attribute__((always_inline))
static	inline	void	*stringstore	(size_t t,uint8_t *a)
{	if		nay	(t==0)
	t=	strlenb		(a);
	void		*v=	memory.avail;
	memory.avail+=		t+1;
	align0x10		(&memory.avail);
/*	memset			(v,0,0x10);	*/
	memcpyt			(v,a,t);
	((uint8_t *)v)[t]=	0;	/* does this hide an error? */
	return			v;
}

static		void	object_pathname_r(uint8_t **,PATHABOVE *);
static	CALIGN	int	object_pathname	(uint8_t *a,OBJECT *o)
{	uint8_t		*b=		a;
	object_pathname_r		(&b,o->pathabove);
	return				b-a;
}

__attribute__((noinline))
static	CALIGN	void	object_pathname_r(uint8_t **a,PATHABOVE *p)
{	PATHABOVE	*o=		p->above;
	if			yay	(o!=NULL)
	{	object_pathname_r	(a,o);
		**a=			'/';
		(*a)++;
	}

	/* uncertain if memcpyt suitable */
/*	memcpy				(*a,p->name,p->len+1);	*/
	memcpyt				(*a,p->name,p->len);
	*a+=				p->len;
}

__attribute__((always_inline))
static	inline	void	kobyte		(uint8_t *a)
{	uint8_t	c;
	for		(;c=*a;*a++=KOBYTE[c]);
}

__attribute__((always_inline))
static	inline	void	omattach	(OBJECT *o)
{	OBJECT		**O=		&memory.object
					[o->name_len&7]
					[bit128_to_bit16(o->name)];
	o->next=			*O;
	*O=				o;
}

__attribute__((always_inline))
static	inline	void	amattach	(ALIAS *a)
{	ALIAS		**A=		&memory.alias[a->alias[0]];
	a->next=			*A;
	*A=				a;
}

__attribute__((always_inline))
static	inline	void	align0x10	(void **v)
{	uintptr_t
	p=		(uintptr_t)	*v;
	p+=		 0xf;
	p&=		~0xf;
	*v=		(void *)	p;
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
	warnx	("ko_pathname %s",	kov[ko_pathname].name);
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
	aa	(ko_,		"ko");
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
{	memory.avail=	memory.data;
	kocache		();
	errna=		0;
}
