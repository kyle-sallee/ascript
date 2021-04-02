/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by io.h some functions are provided.
*/

#ifdef		__linux__
#include	<sys/sendfile.h>
#endif


/*	Because pipe2 can return file descriptor value < 3
	to avoid bugs; open 0 1 2 file descriptors are required.
	If not open, as indicated by a dup2 error,
	then /dev/null is opened.
*/

#include	<poll.h>

/* For gcc by calling readpoll a sibling jump will be precluded */

__attribute__((unused))
static	CALIGN	ssize_t	readpoll	(int a, void *b, size_t c)
{	struct	pollfd	d=
	{	.fd=		a,
		.events=	POLLIN
	};
	poll			(&d,1,-1);
	return	read		(a,b,c);
}

__attribute__((unused))
static	CALIGN	ssize_t	writepoll (int a,const void *b,size_t c)
{	struct	pollfd	d=
	{	.fd=		a,
		.events=	POLLOUT
	};
	poll			(&d,1,-1);
	return	write		(a,b,c);
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	int32_t	writeretry	(int const a,void const *b,uint32_t c,ssize_t d)
{	do
	{	switch		(errna)
		{	default:	return	d;
			case	EAGAIN:	errna=	0;
			case	0:	break;
		}

		int	e=
		writepoll	(a,b,c);
		if	yay	(e>0)
		{	b+=	e;
			c-=	e;
			d+=	e;
		}
	}
	while			(c>0);
	return			d;
}

/* This can not be used with O_DIRECT because the c will seldom be page aligned */

__attribute__((unused))
__attribute__((always_inline))
CALIGN
static	inline	ssize_t	writeall_aide	(int const a,void const *b,uint32_t c)
{	ssize_t		e,d=	0;
	do
	{	e=
		write		(a,b,c);
		if	yay	(e>0)
		{	b+=	e;
			c-=	e;
			d+=	e;
		}
		else
		return
		writeretry	(a,b,c,d);
	}
	while			(c>0);
	return			d;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	ssize_t	sendretry	(int const a,void const *b,size_t c,int d,ssize_t f)
{	ssize_t		e;

	do
	{	switch		(errna)
		{	default:	return	f;
			case	EAGAIN:	errna=	0;
			case	0:	break;
		}

		e=
		send		(a,b,c,d);
		if	yay	(e>0)
		{	b+=	e;
			c-=	e;
			f+=	e;
		}
	}
	while			(c>0);
	return			f;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	ssize_t	sendall_aide	(int const a,void const *b,size_t c,int d)
{	ssize_t		e=	0,
			f=	0;
	do
	{	e=
		send		(a,b,c,d);
		if	yay	(e>0)
		{	b+=	e;
			c-=	e;
			f+=	e;
		}
		else
		return
		sendretry	(a,b,c,d,f);
	}
	while			(c>0);
	return			f;
}

inline
static	CALIGN	ssize_t	slowcopy		(int const a,int const b)
{	PALIGN	uint8_t	buf	[0x10000];
	ssize_t		c=
	readpoll				(b,buf,0x10000);
	if				yay	(c>0)
	return		writeall		(a,buf,c);
	else
	return					c;
}

#ifdef		__linux__
inline
static	CALIGN	ssize_t	copyall_sendfile	(int const o,int const i)
{
/*	errna=		0;
*/
	ssize_t		r,t;
	for		(t=0;(r=sendfile(o,i,NULL,0x10000000))>0;t+=r);
	if	yay	(r==0)
	return		t;
	else
	return		r;
}

static	CALIGN	ssize_t	splicepoll	(int a, loff_t *b,
					 int c, loff_t *d, size_t e, int f)
{	struct	pollfd	g[]=
	{	{	.fd=	a,	.events=	POLLIN	},
		{	.fd=	c,	.events=	POLLOUT	}
	};

	poll		(g  ,1,-1);
	poll		(g+1,1,-1);
	return
	splice		(a,b,c,d,e,f);
}

__attribute__((noinline))
static	CALIGN	ssize_t	copyall_splice	(int const o,int const i)
{
/*	errna=		0;
*/
	ssize_t		r,t;
	for		(t=0;(r=splicepoll(i,NULL,o,NULL,0x10000000,0))>0;t+=r);
	if	yay	(r==0)
	return		t;
	else
	return		r;
}
#endif		/*	__linux__	*/

#ifdef		__linux__
__attribute__((noinline))
#else
inline
#endif
static	CALIGN	ssize_t	copyall_slow	(int const a,int const b)
{	ssize_t		c,d;
	for		(d=0;(c=slowcopy(a,b))>0;d+=c);
	if	yay	(c==0)
	return		d;
	else
	return		c;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	size_t	copyall	(int const o,int const i)
{	posix_fadvise		(i,0,0,POSIX_FADV_WILLNEED);
	ssize_t		t;

#ifdef		__linux__
	t=
	copyall_sendfile	(o,i);
	if		yay	(t>=0)
	return			t;

	t=
	copyall_splice		(o,i);
	if		yay	(t>=0)
	return			t;
#endif
	return
	copyall_slow		(o,i);
}


__attribute__((unused))
__attribute__((noinline))
static	CALIGN	int	dupretry	(int const a)
{	while				(1)
	{	switch			(errna)
		{	default:	err	(errna,"%s %i","dup",a);
			case	EINTR:
			case	EBUSY:	errna=	0;
		}
		int	c=
		dup			(a);
		if		yay	(c>=0)
		return			c;
	}
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	int	dup2retry	(int const a,int const b)
{	while				(1)
	{	switch			(errna)
		{	default:	err	(errna,"%s %i %i","dup2",a,b);
			case	EINTR:
			case	EBUSY:	errna=	0;
		}
		int	c=
		dup2			(a,b);
		if		yay	(c>=0)
		return			c;
	}
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	int	closeretry	(int const a)
{	while				(1)
	{	switch			(errna)
		{	default:	return	-1;
			case	EINTR:	errna=	0;
		}
		int	c=
		close			(a);
		if		yay	(c==0)
		return			c;
	}
}


__attribute__((unused))
__attribute__((noinline))
static	CALIGN	ssize_t	readretry	(int const a,void *b,size_t c,ssize_t d)
{	ssize_t		e;
	do
	{	switch		(errna)
		{	default:	return	d;
			case	EAGAIN:	errna=	0;
			case	0:	break;
		}

		e=
		readpoll	(a,b,c);
		if	yay	(e>0)
		{	b+=	e;
			c-=	e;
			d+=	e;
		}
	}
	while			(c>0);
	return			d;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	ssize_t	readsome	(int const a,uint8_t *b,size_t c)
{	ssize_t		e,d=	0;
	do
	{	e=
		read		(a,b,c);

		if	yay	(e>0)
		{	b+=	e;
			c-=	e;
			d+=	e;
		}
		else
		if	yay	(e==0)
		return		d;
		else
		return
		readretry	(a,b,c,d);
	}
	while			(c>0);
	return			d;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	ssize_t	bufcopy	(int const o,int const i,size_t a)
{	PALIGN	uint8_t	b[HUGE];
	ssize_t		t;

	for			(;a>HUGE;a-=t)
	{	t=
		readsome	(i,b,HUGE);
		if	yay	(t>0)
		writeall	(o,b,t);
		else		break;
	}

	for			(;a;a-=t)
	{	t=
		readsome	(i,b,a);
		if	yay	(t>0)
		writeall	(o,b,t);
		else
		break;
	}

	madvise			(b,HUGE,MADV_DONTNEED);
	return			t;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	size_t	sendsome	(int const o,int const i,size_t const A)
{	size_t
	t=			0,
	a=			A;

#ifndef		__linux__
	ssize_t	r;
	for			(;(r=sendfile(o,i,NULL,a))>0;t+=r,a-=r);

	if		yay	(a==0)
	return			t;

	for			(;(r=splicepoll(i,NULL,o,NULL,a,0))>0;t+=r,a-=r);
	if		yay	(a==0)
	return			t;
#endif

	return
	bufcopy			(o,i,a)+t;
}

__attribute__((unused))
static	CALIGN	ssize_t	write_direct	(int const a,void const *b,size_t c)
{	size_t		d=	c&~(PAGE-1);
	if		yay	(d!=c)
	d+=			PAGE;

	ssize_t		e=
	write			(a,b,d);

	if			(d==e)
	return			c;
	else
	return			e;
}

__attribute__((unused))
static	CALIGN	ssize_t	copy_direct	(int const a,int const b)
{	static	HALIGN	uint8_t	buf	[HUGE];
/*	PALIGN	uint8_t	buf	[0x10000];
*/
	ssize_t		c,d,e=		0;
	while				(1)
	{	c=
		read			(b,buf,HUGE);
		if		nay	(0>c)
		goto			fail;
		d=
		write_direct		(a,buf,c);
		if		nay	(0>d)
		fail:
		return			-1;
		e+=			d;
		if		nay	(c!=HUGE)
		break;
	}
	ftruncate			(a,e);
	return				e;
}
