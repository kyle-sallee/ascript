/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

/*	Network interfaces
	to      configure
	the     ioctl   use
	the     netlink use
	is      inane.
	A file  within /sys/ would be clever.
	A syscall            would be tolerable.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	"net.h"
#include	<linux/veth.h>
#include	<stddef.h>		/* for offsetof */
#include	<sys/mount.h>
#include	<sys/wait.h>

/*
static	PALIGN	VMETA	NIC		[0x1000];
*/

/*
static	OPERATOR	varnetupop	[1];
*/

#define	at4	__attribute__((aligned(4)))

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	ifinfomsg	b;
/*	at4	struct	rtattr		c;
	at4	uint32_t		d;
*/
}	LINKINFO;

typedef	struct
{	int		a;
	struct	ifreq	b;
}	IFR;

typedef	struct
{	int				a[2];
	ssize_t				b;
	struct	nlmsghdr		*c;
	struct	ifaddrmsg		*d;
	struct	ifreq			e;
}	LINKREPLY;

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
{	at4	struct	nlmsghdr	a;
	at4	struct	ifinfomsg	b;
	at4	struct	rtattr		c;		/* IFLA_IFNAME    */
	at4	uint8_t			d[0x10];	/* veth name */
	at4	struct	rtattr		e;		/* IFLA_LINKINFO  */
	at4	struct	rtattr		f;		/* IFLA_INFO_KIND */
	at4	uint8_t			g[4];		/* veth */
	at4	struct	rtattr		h;		/* IFLA_INFO_DATA */
	at4	struct	rtattr		i;		/* IFLA_INFO_PEER */
	at4	struct	ifinfomsg	j;
	at4	struct	rtattr		k;		/* IFLA_IFNAME */
	at4	uint8_t			l[0x10];	/* peer name */
}	VETHREQ;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	ifinfomsg	b;
	at4	struct	rtattr		c;		/* IFLA_NET_NS_FD  */
	at4	uint32_t		d;		/* dub */
}	NETNSREQ;

typedef	struct
{	at4	struct	nlmsghdr	a;
	at4	struct	rtmsg		b;
	at4	struct	rtattr		c;
	at4	uint32_t		d;
}	GD;

__attribute__((unused))
static	LINKINFO	linkinfo=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_DUMP,
	.a.nlmsg_type=		RTM_GETLINK,
	.a.nlmsg_len=		sizeof(LINKINFO),
	.b.ifi_family=		AF_PACKET,
/*	.c.rta_type=		IFLA_EXT_MASK,
	.c.rta_len=		RTA_LENGTH(4),
	.d=			RTEXT_FILTER_VF,
*/
};

static	VETHREQ	v=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(VETHREQ),
	.a.nlmsg_type=		RTM_NEWLINK,

	.c.rta_len=		RTA_LENGTH(0x10),
	.c.rta_type=		IFLA_IFNAME,

	.e.rta_len=		sizeof(VETHREQ)-offsetof(VETHREQ,e),
	.e.rta_type=		IFLA_LINKINFO,

	.f.rta_len=		RTA_LENGTH(4),
	.f.rta_type=		IFLA_INFO_KIND,
	.g=			"veth",

	.h.rta_len=		sizeof(VETHREQ)-offsetof(VETHREQ,h),
	.h.rta_type=		IFLA_INFO_DATA,

	.i.rta_len=		sizeof(VETHREQ)-offsetof(VETHREQ,i),
	.i.rta_type=		VETH_INFO_PEER,

	.k.rta_len=		RTA_LENGTH(0x10),
	.k.rta_type=		IFLA_IFNAME,
};

static	NETNSREQ	n=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(NETNSREQ),
	.a.nlmsg_type=		RTM_NEWLINK,

	.c.rta_len=		RTA_LENGTH(4),
	.c.rta_type=		IFLA_NET_NS_FD,
};

/*
static	IFA		c=
{	.a.nlmsg_flags=		NLM_F_REQUEST,
	.a.nlmsg_len=		sizeof(IFA),
	.a.nlmsg_type=		RTM_NEWADDR,

	.b.ifa_family=		AF_INET,

	.c.rta_len=		RTA_LENGTH(0x10),
	.c.rta_type=		IFA_LABEL
};
*/

static	GD		gd=
{	.a.nlmsg_flags=		NLM_F_REQUEST|NLM_F_CREATE|NLM_F_REPLACE|NLM_F_ACK,
	.a.nlmsg_len=		sizeof(GD),
	.a.nlmsg_type=		RTM_NEWROUTE,

	.b.rtm_family=		PF_INET,
	.b.rtm_table=		RT_TABLE_MAIN,
	.b.rtm_protocol=	RTPROT_BOOT,
	.b.rtm_scope=		RT_SCOPE_LINK,
	.b.rtm_type=		RTN_UNICAST,
/*	.b.rtm_dst_len=		0,		*/	/* must be 0 */

	.c.rta_len=		RTA_LENGTH(4),
	.c.rta_type=		RTA_OIF,
};



#define	va(a,b)	{	.name=(a),	.len=		strlen(a),	\
			.text=(b),	.textlen=	strlen(b),	\
					.io.flag=		textmapuse	}

static	VMETA		nv[]=
	{	va		("net.hub","/var/run/netns/hub"),
	};


#define	rta_add(a,b)	(a)->nlmsg_len=			\
			NLMSG_ALIGN((a)->nlmsg_len) +	\
			RTA_ALIGN((b))

#define	rta_new(a)	(void *)(((void *)(a))+(a)->nlmsg_len)

static	CALIGN	void	netveth		(void)
{	__builtin_memcpy		(v.d,Gz.to[0]->textaddr,0x10);
	__builtin_memcpy		(v.l,Gz.to[1]->textaddr,0x10);
	int		a=	socket	(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&v,sizeof(v),0);
	nlreply				(a);
	close				(a);
	*Gz.at=			netveth;
	argot_jump			(errna==0);
}

static	CALIGN	void	nethubmove	(void)
{	n.b.ifi_index=
	ifindex				(Gz.to[0]->textaddr);
	n.d=			open	(nv[0].textaddr,O_RDONLY);
	int		a=	socket	(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&n,sizeof(n),0);
	nlreply				(a);
	close				(a);
	close				(n.d);
	*Gz.at=			nethubmove;
	argot_jump			(errna==0);
}

static	CALIGN	void	netnsmove	(void)
{	n.b.ifi_index=
	ifindex				(Gz.to[1]->textaddr);
	n.d=			open	(Gz.to[0]->textaddr,O_RDONLY);
	int		a=	socket	(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,&n,sizeof(n),0);
	nlreply				(a);
	close				(a);
	close				(n.d);
	*Gz.at=				netnsmove;
	argot_jump			(errna==0);
}

__attribute__((unused))
static		void	netvethold	(void)
{	*Gz.at=	netvethold;

	PALIGN
	char		v[0x100];
	memset				(v,0,0x100);


	struct nlmsghdr	*b=		(struct nlmsghdr *)	v;

	b->nlmsg_flags=			NLM_F_REQUEST|NLM_F_CREATE|NLM_F_EXCL;
	b->nlmsg_type=			RTM_NEWLINK;

	__attribute__((unused))
	struct ifinfomsg *c=
	NLMSG_DATA			(b);
	b->nlmsg_len=
	NLMSG_LENGTH			(sizeof(struct ifinfomsg));

/*	c->ifi_family=			AF_UNSPEC;
	c->ifi_index=			-1;
	c->ifi_change=			-1;
*/

	struct	rtattr	*d=
	rta_new				(b);
	d->rta_type=			IFLA_IFNAME;
	d->rta_len=
	RTA_LENGTH			(Gz.to[0]->textlen);
	rta_add				(b,d->rta_len);
	memcpy				(RTA_DATA(d),
					 Gz.to[0]->textaddr,
					 Gz.to[0]->textlen);

	d=
	rta_new				(b);
	rta_add				(b,RTA_LENGTH(0));
	d->rta_type=			IFLA_LINKINFO;

	struct	rtattr	*e=
	rta_new				(b);
	e->rta_type=			IFLA_INFO_KIND;
	e->rta_len=
	RTA_LENGTH			(4);
	rta_add				(b,e->rta_len);
	__builtin_memcpy		(RTA_DATA(e),"veth",4);

	e=
	rta_new				(b);
	rta_add				(b,RTA_LENGTH(0));
	e->rta_type=			IFLA_INFO_DATA;

	struct	rtattr	*f=
	rta_new				(b);
	rta_add				(b,RTA_LENGTH(0));
	f->rta_type=			VETH_INFO_PEER;

	__attribute__((unused))
	struct ifinfomsg *g=
	rta_new				(b);
	rta_add				(b,sizeof(struct ifinfomsg));

	struct	rtattr	*h=
	rta_new				(b);
	h->rta_type=			IFLA_IFNAME;
	h->rta_len=
	RTA_LENGTH			(Gz.to[1]->textlen);
	rta_add				(b,h->rta_len);
	memcpy				(RTA_DATA(h),
					 Gz.to[1]->textaddr,
					 Gz.to[1]->textlen);

	void		*i=
	rta_new				(b);

	/* VETH_INFO_PEER nest end */
	f->rta_len=			i-(void *)f;

	/* IFLA_INFO_KIND nest end */
	e->rta_len=			i-(void *)e;


	/* IFLA_LINKINFO nest end */
	d->rta_len=			i-(void *)d;

	int		a=
	socket				(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send				(a,b,b->nlmsg_len,0);
	close				(a);

	argot_next			();
}

SCV	netraise		(void)
{	int		a=
	socket			(PF_INET,SOCK_DGRAM,0);
	struct	ifreq	b;
	__builtin_memcpy	(b.ifr_name,Gz.to[0]->textaddr,IFNAMSIZ);
	ioctl			(a,SIOCGIFFLAGS,&b);
	b.ifr_flags|=		IFF_UP;
	int		c=
	ioctl			(a,SIOCSIFFLAGS,&b);
	close			(a);
	*Gz.at=			netraise;
	argot_jump		(c==0);
}

SCV	netlower		(void)
{	int		a=
	socket			(PF_INET,SOCK_DGRAM,0);
	struct	ifreq	b;
	__builtin_memcpy	(b.ifr_name,Gz.to[0]->textaddr,IFNAMSIZ);
	ioctl			(a,SIOCGIFFLAGS,&b);
	b.ifr_flags&=		~IFF_UP;
	int		c=
	ioctl			(a,SIOCSIFFLAGS,&b);
	close			(a);
	*Gz.at=			netlower;
	argot_jump		(c==0);
}

static		void	net	(void)
{	*Gz.at=		net;
	argot_next	();
}

__attribute__((always_inline))
static	inline	void	vini	(VMETA *A,VMETA const *B)
{	map_init		(A);
	A->op=			opbyte;
	A->vam=			&Gz.hash.var[bit128_to_bit16(B->name)];
	vattach_fast		(A);
}

#define	vc(a)		vini		(A,&(VMETA const)	\
			{.name=		(a)});			\
			A++

__attribute__((noinline))
SCV		varinit		(void)
{	VMETA		*A=	nv;
	vc			("net.hub");
}

__attribute__((always_inline))
static	inline	uint8_t		iflen	(uint8_t *a)
{	if	nay	(a[1]==0)	return	1;
	if	nay	(a[2]==0)	return	2;
	if	nay	(a[3]==0)	return	3;
	if	nay	(a[4]==0)	return	4;
	if	nay	(a[5]==0)	return	5;
	if	nay	(a[6]==0)	return	6;
	if	nay	(a[7]==0)	return	7;
	if	nay	(a[8]==0)	return	8;
	if	nay	(a[9]==0)	return	9;
	if	nay	(a[0xa]==0)	return	0xa;
	if	nay	(a[0xb]==0)	return	0xb;
	if	nay	(a[0xc]==0)	return	0xc;
	if	nay	(a[0xd]==0)	return	0xd;
	if	nay	(a[0xe]==0)	return	0xe;
					return	0xf;
}

__attribute__((noinline))
SCV			netinterface		(void)
{	PALIGN	static	uint8_t	b[0x10000];

	text_check				(Gz.to[0],0x10000);

	static	CALIGN	LINKREPLY	R;

	R.a[0]=				socket	(AF_NETLINK,SOCK_RAW,
						 NETLINK_ROUTE);
	R.a[1]=				socket	(PF_INET,SOCK_DGRAM,0);

	send					(R.a[0],
						&linkinfo,
	sizeof					(linkinfo),0);

	VMETA		*A=			 Gz.to[0];
	A->textlen=				0;

	while					((R.b=recv(R.a[0],b,PAGE,
						 MSG_DONTWAIT))>0)
	{	R.c=				(struct nlmsghdr *)	b;
		for				(    ;NLMSG_OK	(R.c,R.b);
						 R.c=NLMSG_NEXT	(R.c,R.b))
		{	R.d=			(struct ifaddrmsg *)
			NLMSG_DATA		(R.c);

			if		nay	(b[PAGE+R.d->ifa_index]!=0)
			continue;
			b[PAGE+R.d->ifa_index]=	1;

			__builtin_memset	(&R.e,0,
			sizeof			( R.e));

			R.e.ifr_ifindex=	R.d->ifa_index;
			ioctl			(R.a[1],SIOCGIFNAME,&R.e);

			__builtin_memcpy	(A->textaddr+
						 A->textlen,
						 R.e.ifr_ifrn.ifrn_name,
			sizeof			(R.e.ifr_ifrn));
			for			(;A->textaddr
						 [A->textlen]!=0;
						  A->textlen++);
			A->textlen++;
		}
	}
	close					(R.a[0]);
	close					(R.a[1]);
	madvise					(b,sizeof(b),MADV_DONTNEED);
	*Gz.at=					netinterface;
	argot_next				();
}

static	inline	void	mkdirp		(uint8_t *a)
{	uint8_t		*b;
	if			yay	(*a!=0)
	for				(b=a+1;*b!=0;b++)
	if			nay	(*b=='/')
	{	*b=			0;
		mkdir			(a,0755);
		*b=			'/';
	}
}

__attribute__((always_inline))
static	inline	void	loraise		(void)
{	static	struct	ifreq	lo=
	{	.ifr_name="lo",
	};

	int		a=
	socket			(PF_INET,SOCK_DGRAM,0);
	ioctl			(a,SIOCGIFFLAGS,&lo);
	lo.ifr_flags|=		IFF_UP;
	ioctl			(a,SIOCSIFFLAGS,&lo);
	close			(a);
}

__attribute__((always_inline))
static	inline	void	hubmake		(void)
{	uint8_t		*a=		nv[0].textaddr;
	int		b;
	int		c;

	b=
	open				(a,O_RDONLY);
	if			nay	(b>=0)
	{	c=
		setns			(b,CLONE_NEWNET);
		close			(b);
		if		nay	(c==0)
		{	errna=		EEXIST;
			return;
		};
	}

	mkdirp				(a);
	mknod				(a,0666|S_IFREG,0);
	errna=				0;
	unshare				(CLONE_NEWNET);
	mount				("/proc/self/ns/net",a,"",MS_BIND,"");
	if			yay	(errna==0)
	loraise				();
}

SCV			nethubmake	(void)
{	int		a=
	open				("/proc/self/ns/net",O_RDONLY);
	hubmake				();
	setns				(a,0);
	close				(a);
	*Gz.at=				nethubmake;
	argot_jump			(errna==0);
}

SCV	netroutedefault		(void)
{	gd.d=
	ifindex			(Gz.to[0]->textaddr);
	int		a=
	socket			(AF_NETLINK,SOCK_RAW,NETLINK_ROUTE);
	send			(a,&gd,sizeof(gd),0);
	nlreply			(a);
	close			(a);
	argot_jump		(errna==0);
	*Gz.at=			netroutedefault;
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200525",
	.official=	"20200525",
	.update=	"20200915"
};

__attribute__((constructor))
static	CALIGN	void	aainit	(void)
{	aa_init			();
	aa			(net,			"net");
	aa			(netinterface,		"netinterface");
	aa			(nethubmake,		"nethubmake");
	aa			(netnsmove,		"netnsmove");
	aa			(nethubmove,		"nethubmove");
	aa			(netveth,		"netveth");
	aa			(netlower,		"netlower");
	aa			(netroutedefault,	"netroutedefault");
	aa			(netraise,		"netraise");
	aa_fini			();
	varinit			();
}
