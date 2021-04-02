/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
/*
#include	"io.h"
*/
#include	"a.h"
#include	<termios.h>	/* for tcgetattr */

/*
typedef	struct
{	PALIGN
	uint8_t		b	[0x20]	[PAGE];
	VMETA		a	[3];*/	/* var sip out err */
/*
}	IOV;
*/

static	VMETA	iov[3]=
{	[0].name="sip",[0].len=3,[0].op=opbyte,[0].textsize=0x10000,[0].io.flag=textmapuse|textmapunmap,
	[1].name="out",[1].len=3,[1].op=opbyte,[1].textsize=0x10000,[1].io.flag=textmapuse|textmapunmap,[1].io.log=1,
	[2].name="err",[2].len=3,[2].op=opbyte,[2].io.log=2
};

__attribute__((cold))
__attribute__((noinline))
static	void	io_	(void)	{argot_next	();}
static	void	io	(void)	{(*Gz.at=io_)	();}

SCV	reval_seek	(VMETA *A)
{	A->value.i=
	lseek		(A->host->value.i4.l,0,SEEK_CUR);
}

SCV	revise_seek	(VMETA *A)
{	errna=		0;
	lseek		(A->host->value.i4.l,A->value.i,SEEK_SET);
	A->io.success=	errna;
}

SCV	revise_log		(VMETA *B)
{	VMETA		*A=	B->host;

	if		nay	(A->io.log>0)
	{	writeall	(A->io.log,A->textaddr,A->textlen);
		close		(A->io.log);
		A->io.log=	0;
		A->textlen=	0;
	}

	errna=			0;
	int		a=
	highwant		(B->value.i4.l);
	A->io.success=		errna;
	if		yay	(a>0)
	{	A->io.log=
		B->value.i=	a;
	}
	else
	{	A->io.log=
		B->value.i=	0;
	}
/*
	if			(a>0)
	B->io.flag|=		datamapuse;
	else
	B->io.flag&=		~datamapuse;
*/
}

static	CALIGN	int	prot_acquire	(int d)
{
/*	int		e=	errna;	*/
	int		r=	0;
	if		yay	(read (d,NULL,0)==0)	r|=	PROT_READ;
	if		yay	(write(d,NULL,0)==0)	r|=	PROT_WRITE;
/*	errna=			e;	*/
	return			r;
}

SCV	revise_map			(VMETA *B)
{	VMETA		*A=		B->host;

	if			nay	(A->io.map!=0)
	close				(A->io.map);

	if			nay	(A->io.flag&textmapunmap)
	munmap				(A->textaddr,A->textsize);
	A->io.flag|=			textmapunmap;


/*	B->io.flag|=			datamapuse;
*/

	errna=				0;
	int		b=
	B->value.i4.l=
	highwant			(Gz.to[1]->value.i4.l);

	if			nay	(0>b)
	{	A->io.success=		errna;
		return;
	}

	A->io.map=			b;

	struct	stat	s;
	s.st_size=			0;
	fstat				(b,&s);

	size_t		S=
	A->textlen=			s.st_size;
	if				(S==0)
	ftruncate			(b,S=0x1000);

	A->textsize=			S;

	int		p=
	prot_acquire			(b);

	errna=				0;
	A->textaddr=
	mmap				(NULL,S,p,MAP_SHARED,b,0);
	A->io.success=			errna;

	if			nay	(A->textaddr==(void *) -1)
	{	close			(A->io.map);
		A->io.map=		0;
		B->value.i=		0;
		A->textaddr=		NULL;
		A->textlen=
		A->textsize=		0;
		A->io.flag&=		~textmapunmap;
	}
}

SCV	revise_sip		(VMETA *B)
{	VMETA		*A=	B->host;

	errna=			0;
	int		a=
	highwant		(Gz.to[1]->value.i4.l);
	A->io.success=		errna;
	if			(a>0)
	{	A->io.sip=
		B->value.i=	a;
	}

/*	if			(a>=0)
	{	A->io.flag&=	~textmapuse;
		B->io.flag|=	datamapuse;
	}
	else	B->io.flag&=	~datamapuse;
*/
}

__attribute__((noinline))
SCV	show_sip		(VMETA *A)
{	size_t		a=	A->textsize-
				A->textlen;

	if		nay	(a==0)
	return;

	int		e=	errna;


	ssize_t		b=
	read			(A->io.sip,
				 A->textaddr+
				 A->textlen,a);

	if			(b>0)
	A->textlen+=		b;
	else
	{	int	c=	errna;
		if		(c!=0)
		A->io.success=	c;
	}

	errna=			e;
}

__attribute__((unused))
SCV	ffree			(VMETA *B)
{	VMETA		*A=	B->host;
	if		yay	(A->textlen)
	{	writeall	(A->io.log,
				 A->textaddr,
				 A->textlen);
	}
/*	if		yay	(B->io.flag&datamapuse)	*/
	if			(B->value.i4.l>0)
	close			(B->value.i4.l);
	var_free		(B);
}

__attribute__((always_inline))
static	inline	void	iologsubnew	(VMETA *A)
{	A->io.log=		1;
	VMETA		*B=
	var_new_sub		(".log",A);
	int4init		(B);
	B->revise=		revise_log;
	B->free=		ffree;
	B->value.i=		1;
}

__attribute__((unused))
SCV	sfree			(VMETA *B)
{	if		yay	(B->io.flag&datamapuse)
	close			(B->value.i4.l);
	var_free		(B);
}

__attribute__((always_inline))
static	inline	void	iosipsubnew	(VMETA *A)
{	A->io.flag&=		~textmapuse;
	A->show=		show_sip;
	VMETA		*B=
	var_new_sub		(".sip",A);
	int4init		(B);
	B->revise=		revise_sip;
	B->io.flag|=		datamapuse;
	B->free=		sfree;
	B->show=		show_sip;
}

__attribute__((unused))
SCV	bfree			(VMETA *B)
{	VMETA		*A=	B->host;
	/*	For the Linux kernel the msync invocation is not required */

	msync			(A->textaddr,
				 A->textlen,
				 MS_ASYNC|MS_INVALIDATE);

	int		b=	B->value.i4.l;
	if			(b>0)
	{	ftruncate	(b,A->textlen);
		close		(b);
	}

	var_free		(B);
}

__attribute__((always_inline))
static	inline	void	iomapsubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".map",A);
	int4init		(B);
	B->revise=		revise_map;
	B->free=		bfree;
	B->io.flag&=		~datamapuse;
}

__attribute__((always_inline))
static	inline	void	ioseeksubnew	(VMETA *A)
{	VMETA		*B=
	var_new_sub		(".seek",A);
	int8init		(B);
/*	B->op=			varintop;	*/
	B->reval=		reval_seek;
	B->revise=		revise_seek;
/*	B->show=		show_seek;	*/
}


__attribute__((always_inline))
inline
SCV	common1			(void)
{	VMETA		*B=
	parapass		(arga(NULL));
	show			(B);

	size_t		b=	B->textlen;

	if		nay	((iov[1].textlen+b+0x10)>
				  iov[1].textsize)
	text_flush		( iov+1,b);

	uint8_t		*c=	iov[1].textaddr+
				iov[1].textlen;

	iov[1].textlen+=	b;
	memcpye			(c,B->textaddr,B->textlen);
}

__attribute__((always_inline))
inline
SCV	common2			(void)
{	VLESS		*A=
	arga			(NULL);

	VMETA		*B[2];
	B[0]=	parapass	(A  );	show	(B[0]);
	B[1]=	parapass	(A+1);	show	(B[1]);

	size_t		b=	B[0]->textlen+
				B[1]->textlen;

	if		nay	((iov[1].textlen+b+0x10)>
				  iov[1].textsize)
	text_flush		( iov+1,b);

	uint8_t		*c=	iov[1].textaddr+
				iov[1].textlen;

	iov[1].textlen+=	b;
	memcpye			(c,B[0]->textaddr,B[0]->textlen);
	c+=			B[0]->textlen;
	memcpye			(c,B[1]->textaddr,B[1]->textlen);
}

__attribute__((always_inline))
inline
SCV	common3			(void)
{	VLESS		*A=
	arga			(NULL);

	VMETA		*B[3];
	B[0]=	parapass	(A  );
	B[1]=	parapass	(A+1);
	B[2]=	parapass	(A+2);

	show			(B[0]);
	show			(B[1]);
	show			(B[2]);

	size_t		b=	B[0]->textlen+
				B[1]->textlen+
				B[2]->textlen;

	if		nay	((iov[1].textlen+b+0x10)>
				  iov[1].textsize)
	text_flush		( iov+1,b);

	uint8_t		*c=	iov[1].textaddr+
				iov[1].textlen;

	iov[1].textlen+=	b;
	memcpye			(c,B[0]->textaddr,B[0]->textlen);
	c+=			B[0]->textlen;
	memcpye			(c,B[1]->textaddr,B[1]->textlen);
	c+=			B[1]->textlen;
	memcpye			(c,B[2]->textaddr,B[2]->textlen);
}

__attribute__((always_inline))
inline
SCV	common4			(void)
{	VLESS		*A=
	arga			(NULL);
	VMETA		*B[4];
	B[0]=	parapass	(A  );
	B[1]=	parapass	(A+1);
	B[2]=	parapass	(A+2);
	B[3]=	parapass	(A+3);

	show			(B[0]);
	show			(B[1]);
	show			(B[2]);
	show			(B[3]);

	size_t		b=	B[0]->textlen+
				B[1]->textlen+
				B[2]->textlen+
				B[3]->textlen;

	if		nay	((iov[1].textlen+b+0x10)>
				  iov[1].textsize)
	text_flush		( iov+1,b);

	uint8_t		*c=	iov[1].textaddr+
				iov[1].textlen;

	iov[1].textlen+=	b;
	memcpye			(c,B[0]->textaddr,B[0]->textlen);
	c+=			B[0]->textlen;
	memcpye			(c,B[1]->textaddr,B[1]->textlen);
	c+=			B[1]->textlen;
	memcpye			(c,B[2]->textaddr,B[2]->textlen);
	c+=			B[2]->textlen;
	memcpye			(c,B[3]->textaddr,B[3]->textlen);
}

/*
On gcc
the function commonx
when inlined
the stack
afore clearing
the next argot
is called.
Naughty compiler!
*/

__attribute__((noinline))
SCV	commonx				(void)
{	VLESS		*a,*b;
	argarange			(NULL,&a,&b);
	VMETA		*A;
	do
	{	A=
		parapass		(a);
		show			(A);
		text_check		(iov+1,A->textlen);
		memcpye			(iov[1].textaddr
					+iov[1].textlen
					,A->textaddr
					,A->textlen);
		iov[1].textlen+=	 A->textlen;
	}
	while				(b>++a);
}

__attribute__((noinline))
SCV	add1_		(void)
{	common1		();
	argot_next	();
}

__attribute__((noinline))
SCV	add2_		(void)
{	common2		();
	argot_next	();
}

__attribute__((noinline))
SCV	add3_		(void)
{	common3		();
	argot_next	();
}

__attribute__((noinline))
SCV	add4_		(void)
{	common4		();
	argot_next	();
}

__attribute__((noinline))
SCV	addx_		(void)
{	commonx		();
	argot_next	();
}

__attribute__((noinline))
static	void	add1	(void)	{(*Gz.at=add1_)	();}
__attribute__((noinline))
static	void	add2	(void)	{(*Gz.at=add2_)	();}
__attribute__((noinline))
static	void	add3	(void)	{(*Gz.at=add3_)	();}
__attribute__((noinline))
static	void	add4	(void)	{(*Gz.at=add4_)	();}
__attribute__((noinline))
static	void	addx	(void)	{(*Gz.at=addx_)	();}

SCV	out				(void)
{	void		(*A)		(void);
	VLESS		*a,*b;
	argarange			(NULL,&a,&b);
	switch				(b-a)
	{	case	0:	A=	io_;	break;
		case	1:	A=	add1;	break;
		case	2:	A=	add2;	break;
		case	3:	A=	add3;	break;
		case	4:	A=	add4;	break;
		default:	A=	addx;
	}
	(*Gz.at=		A)	();
}

__attribute__((noinline))
SCV	not0			(void)
{	writeall		(1,iov[1].textaddr,iov[1].textlen);
	iov[1].textlen=	0;
	argot_next		();
}

__attribute__((noinline))
SCV	not1			(void)
{	common1			();
	writeall		(1,iov[1].textaddr,iov[1].textlen);
	iov[1].textlen=	0;
	argot_next		();
}

__attribute__((noinline))
SCV	not2			(void)
{	common2			();
	writeall		(1,iov[1].textaddr,iov[1].textlen);
	iov[1].textlen=	0;
	argot_next		();
}

__attribute__((noinline))
SCV	not3			(void)
{	common3			();
	writeall		(1,iov[1].textaddr,iov[1].textlen);
	iov[1].textlen=	0;
	argot_next		();
}

__attribute__((noinline))
SCV	not4			(void)
{	common4			();
	writeall		(1,iov[1].textaddr,iov[1].textlen);
	iov[1].textlen=	0;
	argot_next		();
}

__attribute__((noinline))
SCV	notx			(void)
{	commonx			();
	writeall		(1,iov[1].textaddr,iov[1].textlen);
	iov[1].textlen=	0;
	argot_next		();
}

SCV	outnow				(void)
{	void			(*A)	(void);
	switch				(argaamount(NULL))
	{	case	0:	A=	not0;	break;
		case	1:	A=	not1;	break;
		case	2:	A=	not2;	break;
		case	3:	A=	not3;	break;
		case	4:	A=	not4;	break;
		default:	A=	notx;
	}
	(*Gz.at=		A)	();
}

static		void	errnow		(void)
{	int		c=		iov[2].io.log;

	if			nay	(  iov[2].len!=0)
	{	writeall		(c,iov[2].textaddr,
					   iov[2].textlen);
		iov[2].textlen=		0;
	}

	VLESS		*a,*b;
	argarange			(NULL,&a,&b);

	VMETA		*A;
	for				(;b>a;a++)
	{	A=	parapass	(a);
		show			(A);
		writeall		(c,A->textaddr,A->textlen);
	}
	*Gz.at=				errnow;
	argot_next			();
}


static	CALIGN size_t	data_save	(int a,uint8_t *A,ssize_t b)
{	ssize_t		c,d=		0;
	while				(b!=d)
	{	c=
		writepoll		(a,A+d,b-d);
		if		yay	(c>0)
		d+=			c;
		else
		return			d;
	}
	return				b;
}

inline
SCV	saveto			(int *c,int *d)
{	if			(Gz.to[0]->op->int_compat)
	{/*	denwant		(Gz.to[0]);	*/
		*d=		 Gz.to[0]->value.i4.l;
		*c=		-1;
	}
	else
	{	show		(Gz.to[0]);
		*c=	*d=
		open		(Gz.to[0]->textaddr,
				 O_APPEND|O_CREAT|O_WRONLY,0666);
	}
}

static	inline	size_t	saveamount		(void)
{	VLESS		*a,*b;
	argarange		(NULL,&a,&b);

	if			(a==b)
	return			Gz.to[1]->textlen;

	VMETA		*A=
	parapass		(a);
/*	denwant			(A);	*/
	return			A->value.i;
}


/* must be no inline for jump to next argot rather than a call */
__attribute__((noinline))
SCV	saver					(void)
{	show					(Gz.to[1]);
	int		c,d;	saveto		(&c,&d);
	size_t		e=	saveamount	();
	size_t		a=	data_save	(d,Gz.to[1]->textaddr,e);
	if	nay	(c>=0)	close		(c);
	argot_jump	(a==e);
}

SCV	iosave		(void)
{	saver		();
	*Gz.at=		iosave;
	argot_next	();
}

__attribute__((always_inline))
static	inline	int	sendflag	(void)
{	VLESS		*a,*b;
	argarange			(NULL,&a,&b);

	int		c;
	for				(c=0;b>a;a++)
	switch				(a->textlen)
	{	case	7:
		if			(a->textaddr[4]=='E')
		c|=			MSG_EOR;
		else
		c|=			MSG_OOB;	break;
		case	8:	c|=	MSG_MORE;	break;
		case	11:	c|=	MSG_CONFIRM;	break;
		case	12:
		if			(a->textaddr[4]=='D')
		c|=			MSG_DONTWAIT;
		else
		c|=			MSG_NOSIGNAL;	break;
		case	13:	c|=	MSG_DONTROUTE;	break;
	}
	return				c;
}

SCV	iosend_			(void)
{	ssize_t		b=
	sendall			(Gz.to[0]->value.i4.l
				,Gz.to[1]->textaddr
				,Gz.to[1]->textlen
				,partsave(NULL)->i4.l);
	argot_jump		(Gz.to[1]->textlen==b);
}

SCV	iosend			(void)
{	int		a=
	partsave(NULL)->i4.l=
	sendflag		();

	ssize_t		b=
	sendall			(Gz.to[0]->value.i4.l
				,Gz.to[1]->textaddr
				,Gz.to[1]->textlen
				,a);
	*Gz.at=			iosend_;
	argot_jump		(Gz.to[1]->textlen==b);
}


__attribute__((always_inline))
static	inline	int	recvflag	(void)
{	VLESS		*a,*b;
	argarange			(NULL,&a,&b);
	int		c;
	for				(c=0;b>a;a++)
	switch				(a->textlen)
	{	case	7:	c|=	MSG_OOB;		break;
		case	8:	c|=	MSG_PEEK;		break;
		case	9:	c|=	MSG_TRUNC;		break;
		case	11:	c|=	MSG_WAITALL;		break;
		case	12:	c|=	MSG_ERRQUEUE;		break;
		case	16:	c|=	MSG_CMSG_CLOEXEC;	break;
	}
	return				c;
}

SCV	iorecv_			(void)
{	ssize_t		b=
	recv			(Gz.to[1]->value.i4.l
				,Gz.to[0]->textaddr
				+Gz.to[0]->textlen
				,Gz.to[0]->textsize
				-Gz.to[0]->textlen
				,partsave(NULL)->i4.l);
	if			(b>0)
	Gz.to[0]->textlen+=	b;
	argot_jump		(b>0);
}

SCV	iorecv			(void)
{	partsave(NULL)->i4.l=
	recvflag		();
	(*Gz.at=iorecv_)	();
}

static	inline	size_t	loadamount	(void)
{	VLESS		*a,*b;
	argarange		(NULL,&a,&b);

	if		yay	(a==b)
	return			0x7fffffff;

	VMETA	*A=
	parapass		(a);
/*	parapass		(arga(Gz.at));	*/
/*	denwant			(A);	*/
	return			A->value.i;
}

static	CALIGN ssize_t	data_append	(int a,VMETA *A,ssize_t b)
{	ssize_t		c;
	while				(b>0)
	{	if			(b>=HUGE)
		c=			HUGE;
		else
		c=			b;

		text_check		(A,c);

		c=
		read			(a
					,A->textaddr
					+A->textlen
					,c);
		if		yay	(c>0)
		{	A->textlen+=	c;
			b-=		c;
		}
		if			(c!=HUGE)
		return			c;
	}
	return				0;
}

inline
static	void	loadfrom	(int *c,int*d)
{	if			(Gz.to[1]->op->int_compat)
	{	*d=		Gz.to[1]->value.i4.l;
		*c=		-1;
	}
	else
	{	show		(Gz.to[1]);
		*c=	*d=
		open		(Gz.to[1]->textaddr,O_RDONLY);
	}
}


/* must be no inline for jump to next argot rather than a call */
__attribute__((noinline))
static	CALIGN	ssize_t	loader	(void)
{	int		c,d;	loadfrom	(&c,&d);
	size_t		a=	loadamount	();
	ssize_t		b=	data_append	(d,Gz.to[0],a);
	if	nay	(c>=0)	close		(c);
	return			b;
}

SCV	ioload		(void)
{	ssize_t		a=
	loader		();
	*Gz.at=		ioload;
	argot_jump	(a==0);
}

__attribute__((always_inline))
static	inline	void	seek1		(void (*F)(void),int w)
{	VMETA		*A=		Gz.to[0];
	VMETA		*B=		A->host;
	int		d=		B->value.i;
	d=		lseek		(d,0,w);
	*Gz.at=				F;
	argot_jump			(d!=-1);
}

__attribute__((always_inline))
static	inline	void	seek2		(void (*F)(void),int w,int n)
{	VMETA		*A=		Gz.to[0];
	VMETA		*B=		A->host;
	int		d=		B->value.i4.l;

	B=				Gz.to[1];
/*	denwant				(B);	*/
	off_t		t=		B->value.i;

	if			nay	(n)
	t=				-t;

	d=		lseek		(d,t,w);
	*Gz.at=				F;
	argot_jump			(d!=-1);
}

SCV	ioseekend		(void)
{	off_t		a=
	lseek			((int)*(int64_t *)Gz.to[0],0,SEEK_END);
	*Gz.at=			ioseekend;
	argot_jump		(a>=0);
}

SCV	termnoecho		(void)
{	VMETA		*A=	Gz.to[0];
/*	denwant			(A);	*/
	int		d=	A->value.i;
	struct termios	t[2];
	if		nay	(tcgetattr(d,&t[0]))
	{	*Gz.at=		termnoecho;
		argot_next	();
		return;
	}
	t[1]=			t[0];
	t[1].c_lflag&=		~ECHO;
	tcsetattr		(d,TCSANOW,&t[1]);
	*Gz.at=			termnoecho;
	argot_skip		();
	tcsetattr		(d,TCSANOW,&t[0]);
}

SCV	termnocanon		(void)
{	VMETA		*A=	Gz.to[0];
/*	denwant			(A);	*/
	int		d=	A->value.i;
	struct termios	t[2];
	if		nay	(tcgetattr(d,&t[0]))
	{	*Gz.at=		termnocanon;
		argot_next	();
		return;
	}

	t[1]=			t[0];
	t[1].c_lflag&=		~ICANON;
	tcsetattr		(d,TCSANOW,&t[1]);
	*Gz.at=			termnocanon;
	argot_skip		();
	tcsetattr		(d,TCSANOW,&t[0]);
}

SCV	iomap	(void)	{tsubab	(iomapsubnew,	iomap);}
SCV	iolog	(void)	{tsubab	(iologsubnew,	iolog);}
SCV	ioseek	(void)	{tsubab	(ioseeksubnew,	ioseek);}
SCV	iosip	(void)	{tsubab	(iosipsubnew,	iosip);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190516",
	.official=	"20190516",
	.update=	"20200921"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(io,		"io");
	aa		(termnocanon,	"termnocanon");
	aa		(termnoecho,	"termnoecho");
	aa		(iomap,		"iomap");
	aa		(ioseekend,	"ioseekend");
	aa		(ioseek,	"ioseek");
	aa		(iosip,		"iosip");
	aa		(iolog,		"iolog");
	aa		(ioload,	"ioload");
	aa		(iosave,	"iosave");
	aa		(iosend,	"iosend");
	aa		(iorecv,	"iorecv");
	aa		(errnow,	"errnow");
	aa		(out,		"out");
	aa		(outnow,	"outnow");
	aa_fini		();

	Gz.iov=		iov;
	map_init	(iov+0);
	map_init	(iov+1);
	map_init	(iov+2);

	vattach_faster	(iov+0,"sip");
	vattach_faster	(iov+1,"out");
	vattach_faster	(iov+2,"err");

	iov[0].show=	show_sip;

/*	static	uint8_t	b[0x20]	[PAGE];

	iov[0].textaddr=b[0];
	iov[1].textaddr=b[0x10];
*/
	void		*v=
	pps				(0x20000);
	iov[0].textaddr=		v;
	iov[1].textaddr=		v+0x10000;
};

__attribute__((destructor))
SCV	fini			(void)
{	VMETA		*A=	iov+1;
	if		yay	(A->textlen)
	writeall		(A->io.log,
				 A->textaddr,
				 A->textlen);
	A++;
	if		yay	(A->textlen)
	writeall		(A->io.log,
				 A->textaddr,
				 A->textlen);
}
