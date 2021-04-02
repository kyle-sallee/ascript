/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	<time.h>

#define	vaa(a)	{.name=a,.len=strlen(a),.op=opint8,}
#define	va(a)	{.name=a,.len=strlen(a),.op=opint4,}
#define	vb(a)	{.name=a,.len=strlen(a),.op=opbyte,}

enum	tmv_idx
{	tm_epoch,
	tm_hour,
	tm_hours,
	tm_isdst,
	tm_mday,
	tm_min,
	tm_mon,
	tm_mons,
	tm_sec,
	tm_utc,
	tm_wday,
	tm_yday,
	tm_year,
	tm_years,
	tm_ampm,
	tm_form
};

VMETA	tmv	[]=
{	vaa	("tm"),
	va	("tm.hour"),
	va	("tm.hours"),
	va	("tm.isdst"),
	va	("tm.mday"),
	va	("tm.min"),
	va	("tm.mon"),
	va	("tm.mons"),
	va	("tm.sec"),
	va	("tm.utc"),
	va	("tm.wday"),
	va	("tm.yday"),
	va	("tm.year"),
	va	("tm.years"),
	vb	("tm.ampm"),
	vb	("tm.form")
};

__attribute__((always_inline))
static	inline	struct tm	*structtm(void)
{	return	(struct tm *)	tmv[0].dataaddr;
}

SCV	tm_copy				(void)
{	struct tm	*a=
	structtm			();

	tmv[tm_isdst].value.i=		a->tm_isdst;
	tmv[tm_mday].value.i=		a->tm_mday;
	tmv[tm_min].value.i=		a->tm_min;
	tmv[tm_sec].value.i=		a->tm_sec;
	tmv[tm_wday].value.i=		a->tm_wday;
	tmv[tm_yday].value.i=		a->tm_yday;
	tmv[tm_hour].value.i=		a->tm_hour;

	int64_t		b=		a->tm_hour;
	int8_t		c=		0;

	switch				(b)
	{	case	0:	b=	0xc;
		case	1:
		case	2:
		case	3:
		case	4:
		case	5:
		case	6:
		case	7:
		case	8:
		case	9:
		case	10:
		case	11:	break;
		default:	b-=	0xc;
				c=	1;
	}
	tmv[tm_hours].value.i=		b;

	if				(c==0)
	__builtin_memcpy		(tmv[tm_ampm].textaddr,"AM",2);
	else
	__builtin_memcpy		(tmv[tm_ampm].textaddr,"PM",2);

	tmv[tm_mon].value.i=		a->tm_mon;
	tmv[tm_mons].value.i=		a->tm_mon+1;

	tmv[tm_year].value.i=		a->tm_year;
	tmv[tm_years].value.i=		a->tm_year+1900;
}

__attribute__((noinline))
SCV	revise_tm			(VMETA *A)
{	struct tm	*a=
	structtm			();


	time_t		*b=		(time_t *)	&tmv[0].value.i;

	if				(tmv[tm_utc].value.i==1)
	gmtime_r			(b,a);
	else
	localtime_r			(b,a);

	tm_copy				();
}

SCV	show_tm			(VMETA *A)
{	uint8_t		*b=	tmv[tm_form].textaddr;
	size_t		c=	tmv[tm_form].textlen;

	if			(c!=0)
	{	A->textlen=
		strftime	((char *)	tmv[0].textaddr,
				 (size_t)	tmv[0].textsize,
				 (char *)	b,structtm());
	}
	else
	Gz.out.den8		(A);
}

SCV	tmconvert		(void)
{	struct tm	*a=
	structtm		();

	a->tm_hour=		tmv[tm_hour].value.i;
	a->tm_min=		tmv[tm_min].value.i;
	a->tm_mon=		tmv[tm_mon].value.i;
	a->tm_mday=		tmv[tm_mday].value.i;
	a->tm_sec=		tmv[tm_sec].value.i;
	a->tm_year=		tmv[tm_year].value.i;
	a->tm_isdst=		-1;

	tmv[0].value.i=
	mktime			(a);

	*Gz.at=			tmconvert;
	argot_next		();
}

SCV			tm_	(void)
{	*Gz.at=		tm_;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190328",
	.official=	"20190328",
	.update=	"20200810"
};

#define	vc(z)	map_init(A);vattach_faster(A,z);A->show=Gz.out.time,A++
#define	vd(z)	map_init(A);vattach_faster(A,z);A++

__attribute__((always_inline))
static	inline	void	tmv_init	(void)
{	VMETA		*A=	tmv;

	vc	("tm"),
	vc	("tm.hour"),
	vc	("tm.hours"),
	vc	("tm.isdst"),
	vc	("tm.mday"),
	vc	("tm.min"),
	vc	("tm.mon"),
	vc	("tm.mons"),
	vc	("tm.sec"),
	vc	("tm.utc"),
	vc	("tm.wday"),
	vc	("tm.yday"),
	vc	("tm.year"),
	vc	("tm.years"),
	vd	("tm.ampm"),
	vd	("tm.form"),

	tmv[0].show=			show_tm;
	tmv[0].revise=
	tmv[tm_utc].revise=		revise_tm;
	tmv[tm_ampm].textlen=		2;
	map_add				(tmv+0,PAGE,PAGE);
}

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(tm_,		"tm");
	aa		(tmconvert,	"tmconvert");
	aa_fini		();
	tmv_init	();
};
