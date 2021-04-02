/*	By Kyle Sallee in 2020 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_NET_H
#define		_A_NET_H
#include	<arpa/inet.h>	/* for htons */
#include	<linux/netlink.h>
#include	<linux/rtnetlink.h>
#include	<net/if.h>
#include	<linux/if.h>
#include	<sys/ioctl.h>
#include	<sys/socket.h>

__attribute__((always_inline))
static	inline	int	is_ipv4a	(uint8_t *a)
{	if	nay	(a[1]=='.')	return	1;
	if	nay	(a[2]=='.')	return	1;
	if	nay	(a[3]=='.')	return	1;
					return	0;
}

__attribute__((always_inline))
static	inline	int	is_ipv6a	(uint8_t *a)
{	if	nay	(a[0]==':')	return	1;
	if	nay	(a[1]==':')	return	1;
	if	nay	(a[2]==':')	return	1;
	if	nay	(a[3]==':')	return	1;
	if	nay	(a[4]==':')	return	1;
					return	0;
}

__attribute__((always_inline))
static	inline	uint8_t	ipv4b	(uint8_t **a)
{	uint8_t		b,c;
	c=		*(*a)  -'0';
	b=		*(++*a)-'0';
	if	nay	(b>9)
	goto		done;
	c=		c*10+b;
	b=		*(++*a)-'0';
	if	nay	(b>9)
	goto		done;
	c=		c*10+b;
	++*a;

	done:
	if	yay	(**a=='.')
	(*a)++;
	return		c;
}

__attribute__((always_inline))
static	inline	uint8_t	ipp	(uint8_t *a)
{	uint8_t		b,c;
	b=		*(++a)-'0';	if	nay	(b>9)	return	0;
	c=		b;
	b=		*(++a)-'0';	if	nay	(b>9)	return	c;
	c=		c*10+b;
	b=		*(++a)-'0';	if	nay	(b>9)	return	c;
								return	c*10+b;
}

static	inline	uint8_t	ipv4a	(uint8_t *a,void *b)
{	*(uint8_t *)(b+0)=	ipv4b	(&a);
	*(uint8_t *)(b+1)=	ipv4b	(&a);
	*(uint8_t *)(b+2)=	ipv4b	(&a);
	*(uint8_t *)(b+3)=	ipv4b	(&a);

	if			nay	(*a=='/')
	return	ipp			(a);
	return				0;
}

__attribute__((always_inline))
static	inline	int32_t	ipv6b	(uint8_t **a)
{	int8_t		b;
	uint16_t	c;

	if		nay	(**a==':')
	return			-1;

	b=		Gz.dh.xX[*   *a ];	if nay	(0>b)	goto	done;
	c=		b;
	b=		Gz.dh.xX[*(++*a)];	if nay	(0>b)	goto	done;
	c=		c*0x10+b;
	b=		Gz.dh.xX[*(++*a)];	if nay	(0>b)	goto	done;
	c=		c*0x10+b;
	b=		Gz.dh.xX[*(++*a)];	if nay	(0>b)	goto	done;
	c=		c*0x10+b;
	++*a;

	done:
	if			(**a==':')
	++*a;
	return		htons	(c);
}

__attribute__((always_inline))
static	inline	int32_t	ipv6c	(uint8_t **a)
{	int8_t		b;
	uint16_t	c;

	b=		Gz.dh.xX[*   *a ];	if nay	(0>b)	return	-1;
	c=		b;
	b=		Gz.dh.xX[*(++*a)];	if nay	(0>b)	goto	done;
	c=		c*0x10+b;
	b=		Gz.dh.xX[*(++*a)];	if nay	(0>b)	goto	done;
	c=		c*0x10+b;
	b=		Gz.dh.xX[*(++*a)];	if nay	(0>b)	goto	done;
	c=		c*0x10+b;
	++*a;

	done:
	if		yay	(**a==':')
	++*a;
	return		htons	(c);
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint8_t	ipv6a		(uint8_t *a,void *b)
{	uint16_t 	* const	c=	b;
	int32_t		d;
	uint8_t		e;
	for				(e=0;8>e;e++)
	{	d=	ipv6b		(&a);
		if		yay	(d>=0)
		c[e]=			d;
		else
		goto			skip;
	}
	goto				prefix;

	skip:
	a++;
	if			nay	(*a==':');
	a++;

	CALIGN
	uint16_t	g[0x10];
	__builtin_memcpy		(g,  c,0x10);
	__builtin_memset		(g+e,0,0x10);
	__builtin_memset		(g+8,0,0x10);

	uint8_t		f;
	for				(f=0;7>e;e++,f++)
	{	d=	ipv6c		(&a);
		if		yay	(d>=0)
		g[8+f]=			d;
		else
		break;
	}

	memmove				(g+8-f,g+8,0x10);
	memcpy				(c,    g,  0x10);

	prefix:
	if			nay	(*a=='/')
	return			ipp	(a);
	return				0;
}

/*
static	inline	uint8_t	ipv6a_old	(uint8_t *a,void *b)
{	((uint16_t *)(b))[0]=	ipv6b	(&a);	if nay (*a==':') goto skip;
	((uint16_t *)(b))[1]=	ipv6b	(&a);	if nay (*a==':') goto skip;
	((uint16_t *)(b))[2]=	ipv6b	(&a);	if nay (*a==':') goto skip;
	((uint16_t *)(b))[3]=	ipv6b	(&a);	if nay (*a==':') goto skip;
	((uint16_t *)(b))[4]=	ipv6b	(&a);	if nay (*a==':') goto skip;
	((uint16_t *)(b))[5]=	ipv6b	(&a);	if nay (*a==':') goto skip;
	((uint16_t *)(b))[6]=	ipv6b	(&a);	if nay (*a==':') goto skip;
	((uint16_t *)(b))[7]=	ipv6b	(&a);

	goto				prefix;

	skip:;
	CALIGN
	uint16_t	c[0x10];
	uint8_t		d=		0;
	a++;
	if			nay	(*a==':');
	a++;

	c[8]=			ipv6c	(&a,&d);
	c[9]=			ipv6c	(&a,&d);
	c[0xa]=			ipv6c	(&a,&d);
	c[0xb]=			ipv6c	(&a,&d);
	c[0xc]=			ipv6c	(&a,&d);
	c[0xd]=			ipv6c	(&a,&d);
	c[0xe]=			ipv6c	(&a,&d);

	__builtin_memcpy		(c,b,0x10);
	memmove				(((void *)c)+0x10-d,
					 ((void *)c)+0x10,0x10);
	memcpy				(b,c,0x10);

	prefix:
	if			nay	(*a=='/')
	return			ipp	(a);
	return				0;
}
*/

__attribute__((unused))
static	CALIGN	int	ifindex		(uint8_t *a)
{	struct	ifreq	b;
	__builtin_memcpy		(b.ifr_name,a,IFNAMSIZ);

	int		c=
	socket				(PF_INET,SOCK_DGRAM,0);
	int		d=
	ioctl				(c,SIOCGIFINDEX,&b);
	close				(c);
	if				(d==0)
	return				b.ifr_ifindex;
	else
	return				-1;
}

__attribute__((unused))
static	CALIGN	void	nlreply		(int a)
{	PALIGN
	uint8_t			b[PAGE];
	ssize_t			d,e;

	for				(d=0;1;)
	{	e=	recv		(a,b+d,PAGE-d,MSG_DONTWAIT);
		if			(0>=e)
		break;
		e=	NLMSG_ALIGN	(e);
		d+=			e;
		a+=			e;
	}

	struct	nlmsghdr	*f=	(void *)	b;
	struct	nlmsgerr	*g;

	for				( ;NLMSG_OK	(f,d);
					 f=NLMSG_NEXT	(f,d))
	if				(f->nlmsg_type==NLMSG_ERROR)
	{	g=			(struct nlmsgerr *)	NLMSG_DATA(f);
		errna=			-g->error;
	}
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	slash_net_prefix	(VMETA *A,uint8_t a)
{	A->textaddr[
	A->textlen++]=	'/';
	*(uint32_t *)
	(A->textaddr
	+A->textlen)=		Gz.dh.den.left.w[a];
	A->textlen+=		Gz.dh.den.next	[a];
}

__attribute__((unused))
static	inline	void	ipv4a_ascii	(VMETA *A,void *a)
{	uint8_t		b;
	int		c;
	for				(c=4;c;c--)
	{	b=			*(uint8_t *)a++;
		*(uint32_t *)
		(A->textaddr
		+A->textlen)=		Gz.dh.den.left.w[b];
		A->textlen+=		Gz.dh.den.next	[b];
		A->textaddr[
		A->textlen++]=		'.';
	}
	A->textlen--;
	A->textaddr[
	A->textlen]=			0;
}

__attribute__((unused))
static	inline	void	ipv6a_ascii	(VMETA *A,void *a)
{	uint16_t		b;
	int		c;
	for				(c=8;c;c--)
	{	b=	ntohs		(*(uint16_t *)a);
		a+=			2;
		*(uint32_t *)
		(A->textaddr
		+A->textlen)=		Gz.dh.hex.Left[b];
		A->textlen+=		Gz.dh.hex.next[b];
		A->textaddr[
		A->textlen++]=		':';
	}
	A->textlen--;
	A->textaddr[
	A->textlen]=			0;
}
#endif
