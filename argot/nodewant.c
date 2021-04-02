/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	"sire.h"

typedef	struct
{	VMETA	*dub, *name, *amount, *offset;
	int	advice;
}	NWV;

typedef	struct
{	VLESS	z;
	NWV	v;
}	NWD;

static	NWD	nwd;

__attribute__((noinline))
SCV	give_dub		(void)
{	posix_fadvise		(nwd.v.dub   ->value.i4.l
				,nwd.v.offset->value.i4.l
				,nwd.v.amount->value.i4.l
				,nwd.v.advice);
	argot_next		();
}

__attribute__((noinline))
SCV	give_pathname		(void)
{	int		a=
	open			(nwd.v.name->textaddr,O_RDONLY|O_NOATIME);

	posix_fadvise		(a
				,nwd.v.offset->value.i4.l
				,nwd.v.amount->value.i4.l
				,nwd.v.advice);
	close			(a);
	argot_next		();
}

SCV	give			(void)
{	if			(nwd.v.name!=NULL)
	(*Gz.at=give_pathname)	();
	else
	(*Gz.at=give_dub)	();
}

SCV	drop			(void)
{	sync			();
	int
	a=	open		("/proc/sys/vm/drop_caches",	O_WRONLY);
	write			(a,"3\n",2);
	close			(a);
	a=	open		("/proc/sys/vm/compact_memory",	O_WRONLY);
	write			(a,"1\n",2);
	close			(a);
	*Gz.at=			drop;
	argot_next		();
}

__attribute__((noinline))
SCV	cac_dub			(void)
{	int		b=	nwd.v.dub->value.i;
	off_t		f=
	lseek			(b,0,SEEK_CUR);
	off_t		c=
	lseek			(b,0,SEEK_END);
	lseek			(b,nwd.v.offset->value.i,SEEK_SET);
	size_t		d=	nwd.v.amount->value.i;
	if		yay	(d==0)
	d=			c-nwd.v.offset->value.i;
	void		*e=
	mmap			(NULL,d,PROT_READ|PROT_WRITE,
				 MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
	read			(b,e,d);
	munmap			(e,d);
	lseek			(b,f,SEEK_SET);
	close			(b);
}

__attribute__((noinline))
SCV	cac_path		(void)
{	int		b=
	open			(nwd.v.name->textaddr,O_RDONLY|O_NOATIME);
	off_t		c=
	lseek			(b,0,SEEK_END);
	lseek			(b,nwd.v.offset->value.i,SEEK_SET);
	size_t		d=	   nwd.v.amount->value.i;
	if		yay	(d==0)
	d=			c- nwd.v.offset->value.i;
	void		*e=
	mmap			(NULL,d,PROT_READ|PROT_WRITE,
				 MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
	read			(b,e,d);
	munmap			(e,d);
	close			(b);
}

SCV	cache			(void)
{	if			(nwd.v.name!=NULL)
	cac_path		();
	else
	cac_dub			();
	*Gz.at=			cache;
	argot_next		();
}

__attribute__((always_inline))
static	inline	void	advice		(int a,void (*b)(void))
{	nwd.v.advice=	a;
	*Gz.at=		b;
	argot_next	();
}

SCV	dontneed	(void)	{advice(POSIX_FADV_DONTNEED,	dontneed);}
SCV	noreuse		(void)	{advice(POSIX_FADV_NOREUSE,	noreuse);}
SCV	normal		(void)	{advice(POSIX_FADV_NORMAL,	normal);}
SCV	randy		(void)	{advice(POSIX_FADV_RANDOM,	randy);}
SCV	sequent		(void)	{advice(POSIX_FADV_SEQUENTIAL,	sequent);}
SCV	willneed	(void)	{advice(POSIX_FADV_WILLNEED,	willneed);}

SCV	nodewant	(void)
{	NWV	v=	nwd.v;
	*Gz.at=		nodewant;
	nwd.v.amount=
	nwd.v.offset=	(VMETA *)	&nwd.z;
	argot_next	();
	nwd.v=		v;
}

SCV	nodewantamount	(void)
{	nwd.v.amount=	Gz.to[0];
	*Gz.at=		nodewantamount;
	argot_next	();
}

SCV	nodewantoffset	(void)
{	nwd.v.offset=	Gz.to[0];
	*Gz.at=		nodewantoffset;
	argot_next	();
}

SCV	nodewantname	(void)
{	nwd.v.name=	Gz.to[0];
	nwd.v.dub=	NULL;
	*Gz.at=		nodewantname;
	argot_next	();
}

SCV	nodewantdub	(void)
{	nwd.v.dub=	Gz.to[0];
	nwd.v.name=	NULL;
	*Gz.at=		nodewantdub;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190225",
	.official=	"20190225",
	.update=	"20200922"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(nodewant,		"nodewant");
	aa		(drop,			"nodewantdrop");

	aa		(dontneed,		"nodewantdontneed");
	aa		(noreuse,		"nodewantnoreuse");
	aa		(normal,		"nodewantnormal");
	aa		(randy,			"nodewantrandom");
	aa		(sequent,		"nodewantsequent");
	aa		(willneed,		"nodewantwillneed");

	aa		(nodewantamount,	"nodewantamount");
	aa		(nodewantoffset,	"nodewantoffset");
	aa		(nodewantdub,		"nodewantdub");
	aa		(nodewantname,		"nodewantname");

	aa		(give,			"nodewantgive");
	aa		(cache,			"nodewantread");
	aa_fini		();
};
