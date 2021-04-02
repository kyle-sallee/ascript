/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by io.c some functions are provided.
*/

#define		PROGRAM		1
#include	"ascript.h"

/*	Because pipe2 can return file descriptor value < 3
	to avoid bugs; open 0 1 2 file descriptors are required.
	If not open, as indicated by a dup2 error,
	then /dev/null is opened.
*/

#ifdef		__linux__
static		ssize_t	sendall_sendfile(int const,int const);
static		ssize_t	sendall_splice	(int const,int const);
#endif
static		ssize_t	sendall_slow	(int const,int const);

	CALIGN	size_t	sendall	(int const o,int const i)
{	posix_fadvise		(i,0,0,POSIX_FADV_WILLNEED);
	ssize_t		t;

#ifdef		__linux__
	t=
	sendall_sendfile	(o,i);
	if		yay	(t>=0)
	return			t;

	t=
	sendall_splice		(o,i);
	if		yay	(t>=0)
	return			t;
#endif
	return
	sendall_slow		(o,i);
}

#ifdef		__linux__
inline
static	CALIGN	ssize_t	sendall_sendfile	(int const o,int const i)
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

__attribute__((noinline))
static	CALIGN	ssize_t	sendall_splice	(int const o,int const i)
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

static		ssize_t	slowcopy		(int const,int const);

#ifdef		__linux__
__attribute__((noinline))
#else
inline
#endif
static	CALIGN	ssize_t	sendall_slow	(int const a,int const b)
{	ssize_t		c,d;
	for		(d=0;(c=slowcopy(a,b))>0;d+=c);
	if	yay	(c==0)
	return		d;
	else
	return		c;
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

	CALIGN	int	dupretry	(int const a)
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

__attribute__((noinline))
	CALIGN	int	dup2retry	(int const a,int const b)
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

	CALIGN	int	closeretry	(int const a)
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


	CALIGN	ssize_t	writeretry	(int const a,void const *b,size_t c,ssize_t d)
{	ssize_t		e;

	do
	{	switch		(errna)
		{	default:	return	d;
			case	EAGAIN:	errna=	0;
			case	0:	break;
		}

		e=
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

	CALIGN	ssize_t	readretry	(int const a,void *b,size_t c,ssize_t d)
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
