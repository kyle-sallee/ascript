/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	"net.h"
#include	<sys/socket.h>
#include	<netdb.h>

/* 4 bytes per address */
/*
#define		IPABYTE		4
#define		IFA_FAMILY	AF_INET
#define		FULL_PREFIX	32
#define		SOCKADDR_IN	struct	sockaddr_in
#define		SIN_ADDR(a)	((SOCKADDR_IN *)(a))->sin_addr
#define		SIN_PORT(a)	((SOCKADDR_IN *)(a))->sin_port
#define		SIN_FAMILY(a)	((SOCKADDR_IN *)(a))->sin_family
*/

#define		IPABYTE		0x10
#define		IFA_FAMILY	AF_INET6
#define		FULL_PREFIX	128
#define		SOCKADDR_IN	struct	sockaddr_in6
#define		SIN_ADDR(a)	((SOCKADDR_IN *)(a))->sin6_addr
#define		SIN_PORT(a)	((SOCKADDR_IN *)(a))->sin6_port
#define		SIN_FAMILY(a)	((SOCKADDR_IN *)(a))->sin6_family


#define	at4	__attribute__((aligned(4)))

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	rtmsg		b;
	at4	struct	rtattr		c;
	at4	uint8_t			d[0x10];
	at4	struct	rtattr		e;
	at4	uint32_t		f[0x10];
}	RAA;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	rtmsg		b;
	at4	struct	rtattr		c;
	at4	uint8_t			d[0x10];
	at4	struct	rtattr		e;
	at4	uint32_t		f;
}	RAD;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	rtmsg		b;
	at4	struct	rtattr		c;
	at4	uint8_t			d[0x10];
}	GA;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	rtmsg		b;
	at4	struct	rtattr		c;
	at4	uint8_t			d[0x10];
}	IFRD;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	ifaddrmsg	b;
}	IFAINFO;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	ifaddrmsg	b;
	at4	struct	rtattr		c;
	at4	uint8_t			d[0x10];
}	IFA;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	ifinfomsg	b;
	at4	struct	rtattr		c;
	at4	uint8_t			d[0x10];
}	IFI;

typedef	struct
{	ssize_t			a;
	ssize_t			b;
	struct	nlmsghdr	*c;
	struct	ifaddrmsg	*d;
	struct	rtattr		*e;
	uint8_t			*f;
}	REPLY;

typedef	struct
{	SOCKADDR_IN	sockaddr;	/* also includes port */
	VMETA		*sockvar;
	uint32_t	ifa_index;
	uint8_t		prefixlen;
/*	uint8_t		ifname[0x10];	*/
}	SALIENT_DATA;

static	CALIGN	SALIENT_DATA	SD;

static	CALIGN	IFAINFO	ifainfo=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_DUMP,
	.a.nlmsg_type=		RTM_GETADDR,
	.a.nlmsg_len=		sizeof(IFAINFO),
	.b.ifa_family=		IFA_FAMILY,
};

static	CALIGN	IFA	ifaadd=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(IFA),
	.a.nlmsg_type=		RTM_NEWADDR,

	.b.ifa_family=		IFA_FAMILY,

	.c.rta_len=		RTA_LENGTH(0x10),
/*	.c.rta_type=	*/	/* when used set */
};

static	CALIGN	IFA	ifasub=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(IFA),
	.a.nlmsg_type=		RTM_DELADDR,

	.b.ifa_family=		IFA_FAMILY,

	.c.rta_len=		RTA_LENGTH(0x10),
/*	.c.rta_type=	*/	/* when used set */
};

static	RAA		raa=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_CREATE|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(RAA),
	.a.nlmsg_type=		RTM_NEWROUTE,

	.b.rtm_family=		IFA_FAMILY,
	.b.rtm_table=		RT_TABLE_MAIN,
	.b.rtm_protocol=	RTPROT_BOOT,
	.b.rtm_scope=		RT_SCOPE_UNIVERSE,
	.b.rtm_type=		RTN_UNICAST,
	.b.rtm_dst_len=		8*IPABYTE,

	.c.rta_type=		RTA_DST,
	.c.rta_len=		RTA_LENGTH(0x10),

	.e.rta_type=		RTA_GATEWAY,		/* ifindex give */
	.e.rta_len=		RTA_LENGTH(4),
};

static	RAD		rad=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_CREATE|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(RAD),
	.a.nlmsg_type=		RTM_NEWROUTE,

	.b.rtm_family=		IFA_FAMILY,
	.b.rtm_table=		RT_TABLE_MAIN,
	.b.rtm_protocol=	RTPROT_BOOT,
	.b.rtm_scope=		RT_SCOPE_LINK,
	.b.rtm_type=		RTN_UNICAST,
	.b.rtm_dst_len=		8*IPABYTE,

	.c.rta_type=		RTA_DST,
	.c.rta_len=		RTA_LENGTH(0x10),

	.e.rta_type=		RTA_OIF,		/* ifindex */
	.e.rta_len=		RTA_LENGTH(4),
};

static	GA		ga=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_CREATE|NLM_F_REPLACE|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(GA),
	.a.nlmsg_type=		RTM_NEWROUTE,

	.b.rtm_family=		IFA_FAMILY,
	.b.rtm_table=		RT_TABLE_MAIN,
	.b.rtm_scope=		RT_SCOPE_NOWHERE,
	.b.rtm_protocol=	RTPROT_BOOT,
	.b.rtm_scope=		RT_SCOPE_UNIVERSE,
	.b.rtm_type=		RTN_UNICAST,
/*	.b.rtm_dst_len=		0,	*/	/* must be 0 */

	.c.rta_len=		RTA_LENGTH(0x10),
	.c.rta_type=		RTA_GATEWAY,
};

static	IFRD		rd=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(IFRD),
	.a.nlmsg_type=		RTM_DELROUTE,

	.b.rtm_family=		IFA_FAMILY,
	.b.rtm_table=		RT_TABLE_MAIN,
	.b.rtm_scope=		RT_SCOPE_NOWHERE,
	.b.rtm_scope=		RT_SCOPE_NOWHERE,
	.b.rtm_dst_len=		8*IPABYTE,		/* later changed */

	.c.rta_len=		RTA_LENGTH(0x10),
	.c.rta_type=		RTA_DST,
};

#define	subnet(a,b,c)	memcpy((a),(c),	(b)=sizeof(c));

SCV	ipv6facewith		(void)
{	errna=			0;
	int		a=
	SD.ifa_index=
	ifindex			(Gz.to[0]->textaddr);
	*Gz.at=			ipv6facewith;
	argot_jump		(a>=0);
}

SCV	ipv6namewith		(void)
{	static	struct	addrinfo	H=	{.ai_family=	IFA_FAMILY};
		struct	addrinfo	*i;

	errna=			0;
	int		e=
	getaddrinfo		(Gz.to[0]->textaddr,NULL,&H,&i);

	if		nay	(e!=0)
	goto			fail;

	uint16_t	p=
	SIN_PORT		(&SD.sockaddr);
	__builtin_memcpy	(&SD.sockaddr
				,i->ai_addr
				,sizeof(SOCKADDR_IN));
	SIN_PORT		(&SD.sockaddr)=
				p;
	freeaddrinfo		(i);

	*Gz.at=			ipv6namewith;
	argot_skip		();
	return;

	fail:
	*Gz.at=			ipv6namewith;
	argot_next		();
}

SCV	ipv6addrwith		(void)
{	SD.prefixlen=
	ipv6a			(Gz.to[0]->textaddr,&SIN_ADDR(&SD.sockaddr));
	*Gz.at=			ipv6addrwith;
	argot_skip		();
}

SCV	ipv6portwith		(void)
{	in_port_t	p;
	if			(Gz.to[0]->op->int_compat)
	p=			 Gz.to[0]->value.i4.l;
	else
	{	struct	servent	*s=
		getservbyname	(Gz.to[0]->textaddr,NULL);
		if	nay	(s==NULL)
		goto		fail;
		p=		s->s_port;
	}

	SIN_PORT		(&SD.sockaddr)=
	htobe16			(p);

	*Gz.at=			ipv6portwith;
	argot_skip		();
	return;

	fail:
	*Gz.at=			ipv6portwith;
	argot_next		();
}

SCV	ipv6sockwith		(void)
{	SD.sockvar=		Gz.to[0];
	*Gz.at=			ipv6sockwith;
	argot_skip		();
}


SCV	address_output			(VMETA *A,REPLY *R)
{
/*	inet_ntop			(IFA_FAMILY,R->f,
					 A->textaddr+
					 A->textlen,
					 A->textsize-
					 A->textlen);
	A->textlen+=
	strlenb				(A->textaddr
					+A->textlen);
*/
	ipv6a_ascii			(A,R->f);

	slash_net_prefix		(A,R->d->ifa_prefixlen);

/*
	A->textaddr[
	A->textlen++]=		'/';
	uint8_t	d,c=			R->d->ifa_prefixlen;
	if				(c>100)
	{	d=			c/100;
		c=			c%100;
		A->textaddr[
		A->textlen++]=	d+'0';
	}
	if				(c>10)
	{	d=			c/10;
		c=			c%10;
		A->textaddr[
		A->textlen++]=	d+'0';
	}
	A->textaddr[
	A->textlen++]=		c+'0';
*/

	A->textaddr[
	A->textlen++]=		0;
}

__attribute__((always_inline))
static	inline	void	parse		(int		sd,
					 uint32_t	ifa_index,
					 unsigned short	rta_type)
{	uint8_t		a[PAGE];
	REPLY		R;
	VMETA		*A=			Gz.to[0];
	A->textlen=				0;

	while					((R.a=recv(sd,a,PAGE,
						 MSG_DONTWAIT))>0)
	{	R.c=	(struct nlmsghdr *)	a;
	for					(   ;NLMSG_OK	(R.c,R.a);
						 R.c=NLMSG_NEXT	(R.c,R.a))
	{
		R.b=				IFA_PAYLOAD	(R.c);
		R.d=	(struct ifaddrmsg *)	NLMSG_DATA	(R.c);
		R.e=	(struct rtattr *)	IFA_RTA		(R.d);
		R.f=	(uint8_t *)		RTA_DATA	(R.e);

		for				(   ;RTA_OK	(R.e,R.b);
						 R.e=RTA_NEXT	(R.e,R.b))
		if			nay	(R.d->ifa_index	==ifa_index)
		if			nay	(R.e->rta_type	==rta_type)
		address_output			(A,&R);
	}
	}
}

SCV	generic_get			(unsigned short rta_type)
{	int		a=	socket	(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&ifainfo,sizeof(ifainfo),0);

	int		b=		SD.ifa_index;
	parse				(a,b,rta_type);
	close				(a);
	argot_next			();
}

/*
SCV	generic_get			(unsigned short rta_type)
{	int		a=	socket	(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&ifainfo,sizeof(ifainfo),0);

	int		b=
	ifindex				(Gz.to[0]->textaddr);
	parse				(a,b,rta_type);
	close				(a);
	argot_next			();
}
*/

/*
SCV	generic_get			(unsigned short rta_type)
{	int		a=	socket	(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&ifainfo,sizeof(ifainfo),0);

	int		b=
	ifindex				(Gz.to[0]->textaddr);
	parse				(a,b,rta_type);
	close				(a);
	argot_next			();
}
*/

__attribute__((unused))
static	CALIGN	uint8_t	ifa_prefixlen	(uint8_t *a)
{	uint8_t		b=		0;
	uint8_t		c=		a[0]-'0';
	if				(9>=c)
	{	b=			c;
		c=			a[1]-'0';
		if			(9>=c)
		b=			b*10+c;
	}
	return				b;
}

SCV	generic_set			(unsigned short rta_type)
{	ifaadd.b.ifa_index=		SD.ifa_index;
	ifaadd.c.rta_type=		rta_type;
	ifaadd.b.ifa_prefixlen=		SD.prefixlen;
	__builtin_memcpy		(ifaadd.d
					,&SIN_ADDR(&SD.sockaddr)
					,IPABYTE);
	errna=				0;

	int		a=
	socket				(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&ifaadd,sizeof(ifaadd),0);
	nlreply				(a);
	close				(a);
	argot_jump			(errna==0);
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6anycastset	(void)
{	*Gz.at=		ipv6anycastset;
	generic_set	(IFA_ANYCAST);
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6broadcastset	(void)
{	*Gz.at=		ipv6broadcastset;
	generic_set	(IFA_BROADCAST);
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6localset	(void)
{	*Gz.at=		ipv6localset;
#if	IFA_FAMILY	==	AF_INET
	generic_set	(IFA_LOCAL);
#else
	generic_set	(IFA_ADDRESS);
#endif
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6multicastset	(void)
{	*Gz.at=		ipv6multicastset;
	generic_set	(IFA_MULTICAST);
}

SCV	generic_del			(unsigned short rta_type)
{	ifasub.b.ifa_index=		SD.ifa_index;
	ifasub.c.rta_type=		rta_type;
	ifasub.b.ifa_prefixlen=		SD.prefixlen;
	__builtin_memcpy		(ifasub.d
					,&SIN_ADDR(&SD.sockaddr)
					,IPABYTE);
	errna=				0;
	int		a=
	socket				(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&ifasub,sizeof(ifasub),0);
	nlreply				(a);
	close				(a);
	argot_jump			(errna==0);
}

/*
SCV	generic_del			(unsigned short rta_type)
{	ifasub.b.ifa_index=
	ifindex				(Gz.to[0]->textaddr);
	ifasub.c.rta_type=		rta_type;
	ifasub.b.ifa_prefixlen=
	ipv6a				(Gz.to[1]->textaddr,ifasub.d);
	int		a=
	socket				(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&ifasub,sizeof(ifasub),0);
	nlreply				(a);
	close				(a);
	argot_jump			(errna==0);
}
*/

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6anycastdel	(void)
{	*Gz.at=		ipv6anycastdel;
	generic_del	(IFA_ANYCAST);
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6broadcastdel	(void)
{	*Gz.at=		ipv6broadcastdel;
	generic_del	(IFA_BROADCAST);
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6localdel	(void)
{	*Gz.at=		ipv6localdel;
#if	IFA_FAMILY	==	AF_INET
	generic_del	(IFA_LOCAL);
#else
	generic_del	(IFA_ADDRESS);
#endif
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6multicastdel	(void)
{	*Gz.at=		ipv6multicastdel;
	generic_del	(IFA_MULTICAST);
}


__attribute__((noinline))
__attribute__((unused))
SCV			ipv6anycastget	(void)
{	*Gz.at=		ipv6anycastget;
	generic_get	(IFA_ANYCAST);
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6broadcastget	(void)
{	*Gz.at=		ipv6broadcastget;
	generic_get	(IFA_BROADCAST);
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6localget	(void)
{	*Gz.at=		ipv6localget;
#if	IFA_FAMILY	==	AF_INET
	generic_get	(IFA_LOCAL);
#else
	generic_get	(IFA_ADDRESS);
#endif
}

__attribute__((noinline))
__attribute__((unused))
SCV			ipv6multicastget	(void)
{	*Gz.at=		ipv6multicastget;
	generic_get	(IFA_MULTICAST);
}


SCV		ipv6routedel	(void)
{
/*	rd.b.rtm_dst_len=	FULL_PREFIX-SD.prefixlen;
	__builtin_memcpy	(rd.d,SIN_ADDR(&SD.sockaddr),IPABYTE);
*/

	rd.b.rtm_dst_len=	FULL_PREFIX-
	ipv6a			(Gz.to[0]->textaddr,rd.d);
	int		a=
	socket			(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send			(a,&rd,sizeof(rd),0);
	nlreply			(a);
	close			(a);
	*Gz.at=			ipv6routedel;
	argot_jump		(errna==0);
}

static		void	ipv6routeset	(void);

__attribute__((always_inline))
static	inline	void	radset	(uint32_t b)
{	rad.f=			b;

	rad.b.rtm_dst_len=	FULL_PREFIX-
	ipv6a			(Gz.to[0]->textaddr,rad.d);

	int		a=
	socket			(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);

	send			(a,&rad,sizeof(rad),0);
	nlreply			(a);
	close			(a);
	argot_jump		(errna==0);
}

__attribute__((always_inline))
static	inline	void	raaset	(void)
{	ipv6a			(Gz.to[1]->textaddr,raa.f);

	raa.b.rtm_dst_len=	FULL_PREFIX-
	ipv6a			(Gz.to[0]->textaddr,raa.d);

	int		a=
	socket			(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);

	send			(a,&raa,sizeof(raa),0);
	nlreply			(a);
	close			(a);
	argot_jump		(errna==0);
}

SCV		ipv6routeset	(void)
{	*Gz.at=			ipv6routeset;
	int32_t		b=
	ifindex			(Gz.to[1]->textaddr);
	if			(b>=0)
	radset			(b);
	else
	raaset			();
}

SCV				ipv6routedefault	(void)
{
/*	ga.b.rtm_dst_len must be 0	*/
/*	ga.b.rtm_dst_len=	FULL_PREFIX-	*/
/*	__builtin_memcpy	(ga.d,SIN_ADDR(&SD.sockaddr),IPABYTE);	*/
	ipv6a			(Gz.to[0]->textaddr,ga.d);
	int		a=
	socket			(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send			(a,&ga,sizeof(ga),0);
	nlreply			(a);
	close			(a);
	*Gz.at=			ipv6routedefault;
	argot_jump		(errna==0);
}

__attribute__((unused))
SCV				ipv6routedefault_old	(void)
{
/*	ga.b.rtm_dst_len must be 0	*/
/*	ga.b.rtm_dst_len=	FULL_PREFIX-	*/
	ipv6a			(Gz.to[0]->textaddr,ga.d);
	int		a=
	socket			(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send			(a,&ga,sizeof(ga),0);
	nlreply			(a);
	close			(a);
	*Gz.at=			ipv6routedefault;
	argot_jump		(errna==0);
}

SCV			yayipv6address	(void)
{	*Gz.at=		yayipv6address;
	argot_jump	(is_ipv6a(Gz.to[0]->textaddr));
}

SCV	sockfree	(VMETA *A)
{	if		(A->value.i4.l>0)
	close		(A->value.i4.l);
	var_free	(A);
}

ALIVE	ipv6tcpsockinit			(VMETA *A)
{	A->free=			sockfree;
	int4init			(A);
	errna=				0;
	A->value.i4.l=
	socket				(IFA_FAMILY,SOCK_STREAM|SOCK_CLOEXEC,0);
	A->io.success=			errna;
	map_add				(A,0,PAGE);
	SIN_FAMILY(A->dataaddr)=	IFA_FAMILY;
}

ALIVE	ipv6udpsockinit			(VMETA *A)
{	A->free=			sockfree;
	int4init			(A);
	errna=				0;
	A->value.i4.l=
	socket				(IFA_FAMILY,SOCK_DGRAM|SOCK_CLOEXEC,0);
	A->io.success=			errna;
	map_add				(A,0,PAGE);
	SIN_FAMILY(A->dataaddr)=	IFA_FAMILY;
}

SCV		ipv6tcpsock		(void)	{tvarnewa(ipv6tcpsockinit);}
SCV		ipv6udpsock		(void)	{tvarnewa(ipv6udpsockinit);}

SCV		ipv6addrfromname	(void)
{	*Gz.at=	ipv6addrfromname;
	static	struct	addrinfo	H={.ai_family=	IFA_FAMILY};
		struct	addrinfo	*i;
	int		a=
	getaddrinfo			(Gz.to[1]->textaddr,NULL,&H,&i);

	Gz.to[0]->io.success=		a;
	if			nay	(a!=0)
	{	char const	*b=
		gai_strerror		(a);
		uint32_t	c=
		strlenb			(b);
		Gz.to[0]->textlen=	0;
		text_check		(Gz.to[0],c);
		Gz.to[0]->textlen=	c;
		memcpy			(Gz.to[0]->textaddr,b,c);
		argot_next		();
		return;
	}

	Gz.to[0]->textlen=		0;
	ipv6a_ascii			(Gz.to[0],&SIN_ADDR(i->ai_addr));
	freeaddrinfo			(i);
	argot_skip			();
}

SCV	ipv6bind		(void)
{	errna=			0;
	int		a=
	bind			(SD.sockvar->value.i4.l
				,(struct sockaddr *)
				&SD.sockaddr
				,sizeof(SOCKADDR_IN));
	SD.sockvar->io.success=	errna;
	*Gz.at=			ipv6bind;
	argot_jump		(a==0);
}

SCV	ipv6connect		(void)
{	errna=			0;
	int		a=
	connect			(SD.sockvar->value.i4.l
				,(struct sockaddr *)
				&SD.sockaddr
				,sizeof(SOCKADDR_IN));
	SD.sockvar->io.success=	errna;
	*Gz.at=			ipv6connect;
	argot_jump		(a==0);
}

SCV	ipv6listen		(void)
{	errna=			0;
	int		a=
	listen			(SD.sockvar->value.i4.l
				,Gz.to[0]->value.i4.l);
	SD.sockvar->io.success=	errna;
	*Gz.at=			ipv6listen;
	argot_jump		(a==0);
}

ALIVE	ipv6acceptinit		(VMETA *A)
{	A->free=		sockfree;
	errna=			0;
	map_add			(A,0,PAGE);
	socklen_t	a=
	sizeof			(SOCKADDR_IN);
	A->value.i4.l=
	accept4			(SD.sockvar->value.i4.l,(struct sockaddr *)
				 SD.sockvar->dataaddr,&a,SOCK_CLOEXEC);
	A->io.success=		errna;
}

SCV	ipv6accept		(void)
{	tvarnewa			(ipv6acceptinit);
}

/*
SCV	ipv6bind				(void)
{	*Gz.at=					ipv6bind;
	errna=					0;
	VLESS		*L=			arga(NULL);
	VMETA		*A=	parapass	(L+0);
	VMETA		*B=	parapass	(L+1);
	VMETA		*C=	parapass	(L+2);

	{
		static	struct	addrinfo	H={.ai_family=	IFA_FAMILY};
			struct	addrinfo	*i;
		int		e=
		getaddrinfo			(B->textaddr,NULL,&H,&i);
		if			nay	(e!=0)
		goto				fail;

		__builtin_memcpy		(A->dataaddr,i->ai_addr
						,sizeof(SOCKADDR_IN));
		freeaddrinfo			(i);
	}

	{	in_port_t	p;
		if				(C->op==opvalue)
		p=				C->value.i4.l;
		else
		{	struct	servent	*s=
			getservbyname		(C->textaddr,NULL);
			if		nay	(s==NULL)
			goto			fail;
			p=			s->s_port;
		}

		SIN_PORT(A->dataaddr)=
		htobe16				(p);
	}

	int		a=
	bind					(A->value.i4.l
						,(struct sockaddr *)A->dataaddr
						,sizeof(SOCKADDR_IN));
	A->io.success=				errna;
	if				nay	(a!=0)
	goto					fail;
	argot_skip				();
	return;

	fail:
	A->io.success=				errna;
	argot_next				();
}

SCV	ipv6connect				(void)
{	*Gz.at=					ipv6connect;
	errna=					0;
	VLESS		*L=			arga(NULL);
	VMETA		*A=	parapass	(L+0);
	VMETA		*B=	parapass	(L+1);
	VMETA		*C=	parapass	(L+2);

	{
		static	struct	addrinfo	H={.ai_family=	IFA_FAMILY};
			struct	addrinfo	*i;
		int		e=
		getaddrinfo			(B->textaddr,NULL,&H,&i);
		if			nay	(e!=0)
		goto				fail;

		__builtin_memcpy		(A->dataaddr,i->ai_addr
						,sizeof(SOCKADDR_IN));
		freeaddrinfo			(i);
	}

	{	in_port_t	p;
		if				(C->op==opvalue)
		p=				C->value.i4.l;
		else
		{	struct	servent	*s=
			getservbyname		(C->textaddr,NULL);
			if		nay	(s==NULL)
			goto			fail;
			p=			s->s_port;
		}

		SIN_PORT(A->dataaddr)=
		htobe16				(p);
	}

	int		a=
	connect					(A->value.i4.l
						,(struct sockaddr *)A->dataaddr
						,sizeof(SOCKADDR_IN));
	A->io.success=				errna;
	if				nay	(a!=0)
	goto					fail;
	argot_skip				();
	return;

	fail:
	A->io.success=				errna;
	argot_next				();
}
*/

static		void	ipv6	(void)
{	SALIENT_DATA	sd;
	sd=		SD;
	*Gz.at=		ipv6;
	argot_next	();
	SD=		sd;
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200523",
	.official=	"20200523",
	.update=	"20200901"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(ipv6,			"ipv6");
	aa		(yayipv6address,	"yayipv6address");

	aa		(ipv6routedefault,	"ipv6routedefault");
	aa		(ipv6routedel,		"ipv6routedel");
	aa		(ipv6routeset,		"ipv6routeset");

	aa		(ipv6anycastdel,	"ipv6anycastdel");
	aa		(ipv6broadcastdel,	"ipv6broadcastdel");
	aa		(ipv6localdel,		"ipv6localdel");
	aa		(ipv6multicastdel,	"ipv6multicastdel");

	aa		(ipv6anycastget,	"ipv6anycastget");
	aa		(ipv6broadcastget,	"ipv6broadcastget");
	aa		(ipv6localget,		"ipv6localget");
	aa		(ipv6multicastget,	"ipv6multicastget");

	aa		(ipv6anycastset,	"ipv6anycastset");
	aa		(ipv6broadcastset,	"ipv6broadcastset");
	aa		(ipv6localset,		"ipv6localset");
	aa		(ipv6multicastset,	"ipv6multicastset");

	aa		(ipv6addrfromname,	"ipv6addrfromname");
	aa		(ipv6listen,		"ipv6listen");
	aa		(ipv6udpsock,		"ipv6udpsock");
	aa		(ipv6bind,		"ipv6bind");
	aa		(ipv6connect,		"ipv6connect");
	aa		(ipv6accept,		"ipv6accept");
	aa		(ipv6tcpsock,		"ipv6tcpsock");

	aa		(ipv6addrwith,		"ipv6addrwith");
	aa		(ipv6facewith,		"ipv6facewith");
	aa		(ipv6namewith,		"ipv6namewith");
	aa		(ipv6portwith,		"ipv6portwith");
	aa		(ipv6sockwith,		"ipv6sockwith");
	aa_fini		();
}
