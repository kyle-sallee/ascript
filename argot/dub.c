/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"
#include	"dub.h"
#include	"int.h"
#ifdef		__linux__
#include	<linux/memfd.h>
#endif
#include	<sys/file.h>	/* for flock */

/*
OPERATOR	opdub[4];
*/

static	struct	flock	f[2]=
{	{.l_type=	F_WRLCK},
	{.l_type=	F_UNLCK},
};

SCV	at_file			(void)
{	VMETA		*B=	Gz.to[0];
	VMETA		*C=	Gz.to[1];

	B->io.flag|=		datamapuse;
	B->dataaddr=		C->textaddr;

	char		*a=	B->dataaddr;
	int		b=	B->value.i4.l;
	int		c=
	open			(a,b,0666);

	if		yay	(c>=0)
	{	B->value.i=	c;
		B->io.flag|=	datamapuse;
		*Gz.at=		at_file;
		argot_skip	();
	}
	else	argot_next	();
}

/*
SCV	dubend				(void)
{	VMETA		*B=		Gz.to[0];
	if			yay	(B->io.flag&datamapuse)
	{	B->io.flag&=		~datamapuse;
		int	a=		B->value.i4.l;
		B->value.i=		0;
		close			(a);
	}
	*Gz.at=			dubend;
	argot_next			();
}
*/

/* struct stat a; precludes tail jump with gcc */
__attribute__((noinline))
SCV	query_mem_			(void)
{	struct stat	a;
	a.st_size=			-1;

	VMETA		*A=		Gz.to[0];
	fstat				(A->value.i4.l,&a);

	uint8_t			b=	A->host->io.flag&textmapunmap;
	A->host->io.flag|=			textmapunmap;
	A->host->io.map=		A->value.i;

	if			nay	(b)
	munmap				(A->host->textaddr,
					 A->host->textsize);

	off_t		c=		a.st_size;

	if			nay	(0>c)
	ftruncate			(A->value.i4.l,c=PAGE);

	A->host->textsize=		c;
	A->host->textaddr=
	mmap				(NULL,c,
					 PROT_READ|PROT_WRITE,
					 MAP_SHARED,A->value.i4.l,0);
}

SCV	query_mem	(void)
{	query_mem_	();
	*Gz.at=		query_mem;
	argot_next	();
}

SCV	dubunlink		(void)
{	VMETA		*B=	Gz.to[0];
	VMETA		*A=	B->host;
	if		yay	(A->io.flag&datamapuse)
	unlink			(A->dataaddr);
	*Gz.at=			dubunlink;
	argot_next		();
}

SCV	at_shm				(void)
{
/*	ifaload				("rt\0\0\0\0\0\0\0\0\0\0\0\0\0");
*/

	VMETA		*B=		Gz.to[0];
	VMETA		*C=		Gz.to[1];

	B->io.flag|=			datamapuse;
	__builtin_memcpy		(B->dataaddr,"/dev/shm",8);
	memcpya				(B->dataaddr+8,
					 C->textaddr,
					 C->textlen);

	B->datalen= 			8+C->textlen;
	B->dataaddr[
	B->datalen]=			0;

	char		*a=		B->dataaddr;
	int		b=		B->value.i4.l;
	int		c=
	open				(a,b,0666);

	if			yay	(c>=0)
	{	*(int64_t *)
		B->dataaddr=		c;
		B->io.flag|=		datamapuse;
		*Gz.at=			at_shm;
		argot_skip		();
	}
	else	argot_next		();
}

SCV	at_tmp				(void)
{	VMETA		*C=		Gz.to[1];
	int		a=
	open				(C->textaddr,O_DIRECTORY|O_PATH);

	uint8_t		b[4];
	b[3]=				0;

	int		c;

	for				(b[0]='a';'z'>=b[0];b[0]++)
	for				(b[1]='a';'z'>=b[1];b[1]++)
	for				(b[2]='a';'z'>=b[2];b[2]++)
	{	c=	openat		(a,b,O_CREAT|O_EXCL|O_NOATIME|O_RDWR,0600);
		if		yay	(c>=0)		goto	ready;
		if		nay	(errna!=EEXIST)	goto	fail;
	}

	ready:;
	VMETA		*B=		Gz.to[0];
	B->value.i=			c;
	B->io.flag|=			datamapuse;
	unlinkat			(a,b,0);
	close				(a);
	*Gz.at=				at_tmp;
	argot_skip			();
	return;

	fail:
	close				(a);
	argot_next			();
}

SCV	dubonexegive		(void)
{	int		a,b,c;
	VMETA		*A=	Gz.to[0];
	a=			A->value.i4.l;
	b=	fcntl		(a,F_GETFD);
	c|=	fcntl		(a,F_SETFD,b&~O_CLOEXEC);
	*Gz.at=			dubonexegive;
	argot_jump		(c==0);
}

SCV	dubonexekeep		(void)
{	int		a,b,c;
	VMETA		*A=	Gz.to[0];
	a=			A->value.i4.l;
	b=	fcntl		(a,F_GETFD);
	c|=	fcntl		(a,F_SETFD,b|O_CLOEXEC);
	*Gz.at=			dubonexekeep;
	argot_jump		(c==0);
}

SCV	dubonuserush		(void)
{	int		a,b,c;
	VMETA		*A=	Gz.to[0];
	a=			A->value.i4.l;
	b=	fcntl		(a,F_GETFL);
	c|=	fcntl		(a,F_SETFL,b|O_NONBLOCK);
	*Gz.at=			dubonuserush;
	argot_jump		(c==0);
}

SCV	dubonusewait		(void)
{	int		a,b,c;
	VMETA		*A=	Gz.to[0];
	a=			A->value.i4.l;
	b=	fcntl		(a,F_GETFL);
	c|=	fcntl		(a,F_SETFL,b&~O_NONBLOCK);
	*Gz.at=			dubonusewait;
	argot_jump		(c==0);
}

SCV	dubsig			(void)
{	int		b=	Gz.to[0]->value.i4.l;
	int		c=	Gz.to[1]->value.i4.l;
	fcntl			(b,F_SETSIG,c);

	pid_t		a=
	gettid_			();
	fcntl			(b,F_SETOWN,a);

	c=
	fcntl			(b,F_GETFL);
	fcntl			(b,F_SETFL,c|O_ASYNC|O_NONBLOCK);
	*Gz.at=			dubsig;
	argot_next		();
}

SCV	dubpoll				(void)
{	struct	pollfd	p[1];
	p[0].fd=			Gz.to[0]->value.i4.l;
	VLESS		*a=	arga	(Gz.at+0);
	VLESS		*b=	arga	(Gz.at+1);

	int		t=	parapass(a)->value.i4.l;
	short		c;
	for				(c=0,a++;b>a;a++)
	switch				(a->textaddr[4])
	{	case	'I':	c|=	POLLIN;		break;
		case	'P':	c|=	POLLPRI;	break;
		case	'O':	c|=	POLLOUT;	break;
		case	'R':	c|=	POLLRDHUP;	break;
		case	'E':	c|=	POLLERR;	break;
		case	'H':	c|=	POLLHUP;	break;
		case	'N':	c|=	POLLNVAL;	break;
	}
	p[0].events=			c;
	int		d=
	poll				(p,1,t);
	*Gz.at=				dubpoll;
	argot_jump			(d>0);
}

SCV	dubend			(void)
{	reval			(Gz.to[0]);
	close			(Gz.to[0]->value.i4.l);
	Gz.to[0]->value.i=	0;
	*Gz.at=			dubend;
	argot_next		();
}

SCV	dubendlate		(void)
{	reval			(Gz.to[0]);
	VMETA		*A=	 Gz.to[0];
	*Gz.at=			dubendlate;
	argot_next		();
	close			(A->value.i4.l);
	A->value.i=		0;
}

SCV	dubuse			(void)
{	reval			(Gz.to[0]);
	int		a=	Gz.to[0]->value.i4.l;

	a=
	fcntl			(a,F_GETFL);

	*Gz.at=			dubuse;
	argot_jump		(a!=-1);
}

SCV	dubflock		(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i4.l;

	a=
	flock			(a,LOCK_EX);
	*Gz.at=			dubflock;
	argot_jump		(a==0);
}

SCV	dubflocknow		(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i4.l;
	a=
	flock			(a,LOCK_EX|LOCK_NB);
	*Gz.at=			dubflocknow;
	argot_jump		(a==0);
}

SCV	dubflockfree		(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i4.l;
	flock			(a,LOCK_UN);
	*Gz.at=			dubflockfree;
	argot_next		();
}

SCV	dubflockfreelate	(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i4.l;
	*Gz.at=			dubflockfreelate;
	argot_next		();
	int		b=	errna;
	flock			(a,LOCK_UN);
	errna=			b;
}

SCV	dublock			(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i4.l;
	a=
	fcntl			(a,F_SETLKW,f);
	*Gz.at=			dublock;
	argot_jump		(a==0);
}

SCV	dublocknow		(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i4.l;
	a=
	fcntl			(a,F_SETLK,f);
	*Gz.at=			dublocknow;
	argot_jump		(a==0);
}

SCV	dublockfree		(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i4.l;
	fcntl			(a,F_SETLKW,f+1);
	*Gz.at=			dublockfree;
	argot_next		();
}

SCV	dublockfreelate		(void)
{	reval			(Gz.to[0]);
	int		a=	 Gz.to[0]->value.i;
	*Gz.at=			dublockfreelate;
	argot_next		();
	int		b=	errna;
	fcntl			(a,F_SETLKW,f+1);
	errna=			b;
}


__attribute__((always_inline))
static	inline	void	flagor	(void (*A) (void),int a)
{	Gz.to[0]->value.i|=	a;
	*Gz.at=			A;
	argot_next		();
}

SCV	O_APPEND_	(void)	{flagor	(O_APPEND_,	O_APPEND	);}
SCV	O_ASYNC_	(void)	{flagor	(O_ASYNC_,	O_ASYNC		);}
SCV	O_CLOEXEC_	(void)	{flagor	(O_CLOEXEC_,	O_CLOEXEC	);}
SCV	O_CREAT_	(void)	{flagor	(O_CREAT_,	O_CREAT		);}
SCV	O_DIRECT_	(void)	{flagor	(O_DIRECT_,	O_DIRECT	);}
SCV	O_DIRECTORY_	(void)	{flagor	(O_DIRECTORY_,	O_DIRECTORY	);}
SCV	O_DSYNC_	(void)	{flagor	(O_DSYNC_,	O_DSYNC		);}
SCV	O_EXCL_		(void)	{flagor	(O_EXCL_,	O_EXCL		);}
SCV	O_NOATIME_	(void)	{flagor	(O_NOATIME_,	O_NOATIME	);}
SCV	O_NOCTTY_	(void)	{flagor	(O_NOCTTY_,	O_NOCTTY	);}
SCV	O_NOFOLLOW_	(void)	{flagor	(O_NOFOLLOW_,	O_NOFOLLOW	);}
SCV	O_NONBLOCK_	(void)	{flagor	(O_NONBLOCK_,	O_NONBLOCK	);}
SCV	O_PATH_		(void)	{flagor	(O_PATH_,	O_PATH		);}
SCV	O_RDONLY_	(void)	{flagor	(O_RDONLY_,	O_RDONLY	);}
SCV	O_RDWR_		(void)	{flagor	(O_RDWR_,	O_RDWR		);}
SCV	O_SYNC_		(void)	{flagor	(O_SYNC_,	O_SYNC		);}
SCV	O_TMPFILE_	(void)	{flagor	(O_TMPFILE_,	O_TMPFILE	);}
SCV	O_TRUNC_	(void)	{flagor	(O_TRUNC_,	O_TRUNC		);}
SCV	O_WRONLY_	(void)	{flagor	(O_WRONLY_,	O_WRONLY	);}

SCV	dubfile		(void)	{tsubab(dubfilesubnew,	dubfile);}
SCV	dubmem		(void)	{tsubab(dubmemsubnew,		dubmem);}
SCV	dubname		(void)	{tsubab(dubnamesubnew,	dubname);}
SCV	dubshm		(void)	{tsubab(dubshmsubnew,		dubshm);}
SCV	dubtmp		(void)	{tsubab(dubtmpsubnew,		dubtmp);}

__attribute__((aligned(0x20)))
static		void	dub	(void)
{	*Gz.at=		dub;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180516",
	.official=	"20180516",
	.update=	"20200821"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(dubsig,		"dubsig");
	aa		(dubend,		"dubend");
	aa		(dubunlink,		"dubunlink");
	aa		(dubuse,		"dubuse");

	aa		(dubpoll,		"dubpoll");
	aa		(dublock,		"dublock");
	aa		(dublocknow,		"dublocknow");
	aa		(dublockfree,		"dublockfree");
	aa		(dublockfreelate,	"dublockfreelate");

	aa		(dubflock,		"dubflock");
	aa		(dubflocknow,		"dubflocknow");
	aa		(dubflockfree,		"dubflockfree");
	aa		(dubflockfreelate,	"dubflockfreelate");

	aa		(dubend,		"dubend");
	aa		(dubendlate,		"dubendlate");

	aa		(dubonexegive,		"dubonexegive");
	aa		(dubonexekeep,		"dubonexekeep");
	aa		(dubonuserush,		"dubonuserush");
	aa		(dubonusewait,		"dubonusewait");

	aa		(O_APPEND_,		"O_APPEND");
	aa		(O_ASYNC_,		"O_ASYNC");
	aa		(O_CLOEXEC_,		"O_CLOEXEC");
	aa		(O_CREAT_,		"O_CREAT");
	aa		(O_DIRECT_,		"O_DIRECT");
	aa		(O_DIRECTORY_,		"O_DIRECTORY");
	aa		(O_DSYNC_,		"O_DSYNC");
	aa		(O_EXCL_,		"O_EXCL");
	aa		(O_NOATIME_,		"O_NOATIME");
	aa		(O_NOCTTY_,		"O_NOCTTY");
	aa		(O_NOFOLLOW_,		"O_NOFOLLOW");
	aa		(O_NONBLOCK_,		"O_NONBLOCK");
	aa		(O_PATH_,		"O_PATH");
	aa		(O_RDONLY_,		"O_RDONLY");
	aa		(O_RDWR_,		"O_RDWR");
	aa		(O_SYNC_,		"O_SYNC");
	aa		(O_TMPFILE_,		"O_TMPFILE");
	aa		(O_TRUNC_,		"O_TRUNC");
	aa		(O_WRONLY_,		"O_WRONLY");

	aa		(dubname,		"dubname");
	aa		(dubshm,		"dubshm");
	aa		(dub,			"dub");
	aa		(dubtmp,		"dubtmp");
	aa		(dubmem,		"dubmem");
	aa		(dubfile,		"dubfile");
	aa_fini		();
};


__attribute__((constructor))
SCV	init			(void)
{	opdub[0]=
	opdub[1]=
	opdub[2]=
	opdub[3]=		opint4[0];

	opdub[0].at=		at_file;
	opdub[1].at=		at_tmp;
	opdub[3].at=		at_shm;

/*	the sub var when created the memory dub value is acquired */
	opdub[2].query=		query_mem;
}
