/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"cap.h"
#include	"int.h"
#include	<sys/prctl.h>

OPERATOR	varcapop[1];

static	int64_t					*cap_pid;
static	struct	__user_cap_data_struct		cap_data[2];
static	struct	__user_cap_header_struct	cap_head=
{	.version=	_LINUX_CAPABILITY_VERSION_3	};

static		void	_cap	(void)
{	argot_next		();
}

__attribute__((always_inline))
static	inline	int	common		(int (*a)(long))
{	VMETA		*A;
	VLESS		*B=	arga	(Gz.at+0),
			*C=	arga	(Gz.at+1);

	int		b=		0;
	for				(;C>B;B++)
	{	A=	parapass	(B);
		b|=	a		((long) A->value.i);
	}
	return				b;
}

__attribute__((always_inline))
static	inline	int	common1		(int (*a)(long))
{	return		a	((long)	parapass(arga(NULL))->value.i);
}

static		int	car_		(long L)
{	return	prctl	(PR_CAP_AMBIENT,PR_CAP_AMBIENT_RAISE,L,0,0);
}

static		int	cal_		(long L)
{	return	prctl	(PR_CAP_AMBIENT,PR_CAP_AMBIENT_LOWER,L,0,0);
}

static		int	cac_		(long L)
{	return	(prctl(PR_CAP_AMBIENT,PR_CAP_AMBIENT_IS_SET,L,0,0)==1);
}


SCV	capambientadd	(void)
{	int		a=
	common		(car_);
	*Gz.at=		capambientadd;
	argot_jump	(a==0);
}

SCV	capambientsub	(void)
{	int		a=
	common		(cal_);
	*Gz.at=		capambientsub;
	argot_jump	(a==0);
}

SCV	capambientyay	(void)
{	int		a=
	common1		(cac_);
	*Gz.at=		capambientyay;
	argot_jump	(a);
}

SCV	capambientnay	(void)
{	int		a=
	common1		(cac_);
	*Gz.at=		capambientnay;
	argot_jump	(a==0);
}

static		int	cer_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	cap_data[L/0x20].effective|=	1<<(L&0x1f);
	return	capset			(&cap_head,cap_data);
}

static		int	cel_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	cap_data[L/0x20].effective&=	~(1<<(L&0x1f));
	return	capset			(&cap_head,cap_data);
}

static		int	cec_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	int32_t		e=		cap_data[L/0x20].effective;
	return				((e&(1<<(L&0x1f)))!=0);
}

SCV	capeffectadd	(void)
{	int		a=
	common		(cer_);
	*Gz.at=		capeffectadd;
	argot_jump	(a==0);
}

SCV	capeffectsub	(void)
{	int		a=
	common		(cel_);
	*Gz.at=		capeffectsub;
	argot_jump	(a==0);
}

SCV	capeffectyay	(void)
{	int		a=
	common1		(cec_);
	*Gz.at=		capeffectyay;
	argot_jump	(a);
}

SCV	capeffectnay	(void)
{	int		a=
	common1		(cec_);
	*Gz.at=		capeffectnay;
	argot_jump	(a==0);
}


static		int	cir_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	cap_data[L/0x20].inheritable|=	1<<(L&0x1f);
	return	capset			(&cap_head,cap_data);
}

static		int	cil_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	cap_data[L/0x20].inheritable&=	~(1<<(L&0x1f));
	return	capset			(&cap_head,cap_data);
}

static		int	cic_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	int32_t		e=		cap_data[L/0x20].inheritable;
	return				((e&(1<<(L&0x1f)))!=0);
}

SCV	capinheritadd	(void)
{	int		a=
	common		(cir_);
	*Gz.at=		capinheritadd;
	argot_jump	(a==0);
}

SCV	capinheritsub	(void)
{	int		a=
	common		(cil_);
	*Gz.at=		capinheritsub;
	argot_jump	(a==0);
}

SCV	capinherityay	(void)
{	int		a=
	common1		(cic_);
	*Gz.at=		capinherityay;
	argot_jump	(a);
}

SCV	capinheritnay	(void)
{	int		a=
	common1		(cic_);
	*Gz.at=		capinheritnay;
	argot_jump	(a==0);
}

static		int	cpr_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	cap_data[L/0x20].permitted|=	1<<(L&0x1f);
	return	capset			(&cap_head,cap_data);
}

static		int	cpl_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	cap_data[L/0x20].permitted&=	~(1<<(L&0x1f));
	return	capset			(&cap_head,cap_data);
}

static		int	cpc_		(long L)
{	cap_head.pid=			*cap_pid;
	capget				(&cap_head,cap_data);
	int32_t		e=		cap_data[L/0x20].permitted;
	return				((e&(1<<(L&0x1f)))!=0);
}

SCV	cappermitadd	(void)
{	int		a=
	common		(cpr_);
	*Gz.at=		cappermitadd;
	argot_jump	(a==0);
}

SCV	cappermitsub	(void)
{	int		a=
	common		(cpl_);
	*Gz.at=		cappermitsub;
	argot_jump	(a==0);
}

SCV	cappermityay	(void)
{	int		a=
	common1		(cpc_);
	*Gz.at=		cappermityay;
	argot_jump	(a);
}

SCV	cappermitnay	(void)
{	int		a=
	common1		(cpc_);
	*Gz.at=		cappermitnay;
	argot_jump	(a==0);
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180328",
	.official=	"20180328",
	.update=	"20200809"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_cap,		"cap");
	aa		(capambientadd,	"capambientadd");
	aa		(capambientnay,	"capambientnay");
	aa		(capambientsub,	"capambientsub");
	aa		(capambientyay,	"capambientyay");

	aa		(capinheritadd,	"capinheritadd");
	aa		(capinheritnay,	"capinheritnay");
	aa		(capinheritsub,	"capinheritsub");
	aa		(capinherityay,	"capinherityay");

	aa		(capeffectadd,	"capeffectadd");
	aa		(capeffectnay,	"capeffectnay");
	aa		(capeffectsub,	"capeffectsub");
	aa		(capeffectyay,	"capeffectyay");

	aa		(cappermitadd,	"cappermitadd");
	aa		(cappermitnay,	"cappermitnay");
	aa		(cappermitsub,	"cappermitsub");
	aa		(cappermityay,	"cappermityay");
	aa_fini		();
};


#define	vmac(a)				\
{	.name=		#a,		\
	.value.i=	(a),		\
	.len=	strlen	(#a),		\
	.op=		opint8,		\
	.textlen=	0x10,		\
},

__attribute__((constructor))
SCV	init	(void)
{	static	VMETA	a[]=
	{	vmac	(CAP_AUDIT_CONTROL)
		vmac	(CAP_AUDIT_READ)
		vmac	(CAP_AUDIT_WRITE)
		vmac	(CAP_BLOCK_SUSPEND)
		vmac	(CAP_CHOWN)
		vmac	(CAP_DAC_OVERRIDE)
		vmac	(CAP_DAC_READ_SEARCH)
		vmac	(CAP_FOWNER)
		vmac	(CAP_FSETID)
		vmac	(CAP_IPC_LOCK)
		vmac	(CAP_IPC_OWNER)
		vmac	(CAP_KILL)
		vmac	(CAP_LEASE)
		vmac	(CAP_LINUX_IMMUTABLE)
		vmac	(CAP_MAC_ADMIN)
		vmac	(CAP_MAC_OVERRIDE)
		vmac	(CAP_MKNOD)
		vmac	(CAP_NET_ADMIN)
		vmac	(CAP_NET_BIND_SERVICE)
		vmac	(CAP_NET_BROADCAST)
		vmac	(CAP_NET_RAW)
		vmac	(CAP_SETGID)
		vmac	(CAP_SETFCAP)
		vmac	(CAP_SETPCAP)
		vmac	(CAP_SETUID)
		vmac	(CAP_SYS_ADMIN)
		vmac	(CAP_SYS_BOOT)
		vmac	(CAP_SYS_CHROOT)
		vmac	(CAP_SYS_MODULE)
		vmac	(CAP_SYS_NICE)
		vmac	(CAP_SYS_PACCT)
		vmac	(CAP_SYS_PTRACE)
		vmac	(CAP_SYS_RAWIO)
		vmac	(CAP_SYS_RESOURCE)
		vmac	(CAP_SYS_TIME)
		vmac	(CAP_SYS_TTY_CONFIG)
		vmac	(CAP_SYSLOG)
		vmac	(CAP_WAKE_ALARM)
	};

	int	const	c=
	sizeof			(a)/
	sizeof			(a[0]);

	int		b;
	for			(b=0;c>b;b++)
	{	map_init	(a+b);
		vattach		(a+b);
		a[b].show=	Gz.out.dex8;
	}

	static	VMETA	A[1]=
	{	{	.name=		"cap.pid",
			.len=		7,
			.op=		opint4,
		}
	};

	map_init		(A);
/*	A[0].val=		(void *)	&cap_pid;	*/
	A[0].show=		Gz.out.den4;
	vattach			(A);

	cap_pid=		&A[0].value.i;
}
