/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	<sys/utsname.h>

static		void	_uname	(void)
{	*Gz.at=		_uname;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180319",
	.official=	"20180319",
	.update=	"20200515"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_uname,	"uname");
	aa_fini		();
};

typedef	struct
{	VMETA		a[6];
	struct	utsname	b;
}	UTS_VMETA;

#define	vv(a)			\
	vattach_faster	(A,a);	\
	A++

#define	va(a)			\
{	.name=(a),		\
	.len=strlen((a)),	\
	.io.flag=textmapuse, 	\
	.op=opbyte		\
}

__attribute__((constructor))
static	CALIGN	void	init	(void)
{	static	VMETA		a[]=
	{	va		("uname.domainname"),
		va		("uname.machine"),
		va		("uname.nodename"),
		va		("uname.release"),
		va		("uname.sysname"),
		va		("uname.version"),
	};

	static
	struct	utsname	b;
	uname			(&b);

	VMETA		*A=	a;
	vv			("uname.domainname");
	vv			("uname.machine");
	vv			("uname.nodename");
	vv			("uname.release");
	vv			("uname.sysname");
	vv			("uname.version");

	a[0].textaddr=		b.domainname;
	a[1].textaddr=		b.machine;
	a[2].textaddr=		b.nodename;
	a[3].textaddr=		b.release;
	a[4].textaddr=		b.sysname;
	a[5].textaddr=		b.version;

	int		c;
	for			(c=0;6>c;c++)
	a[c].textlen=
	strlena			(a[c].textaddr);
}
