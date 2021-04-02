/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"int.h"
#include	"a.h"

typedef	struct
{	VMETA		*amount,
			*origin,*originfrom,
			*target,*targetfrom;
}	CASTDATA;

CALIGN
static	CASTDATA	cd;

__attribute__((always_inline))
static	inline	void	want	(void)
{	int8want		(cd.targetfrom);
	int8want		(cd.originfrom);
	int8want		(cd.amount);
	return;
}

SCV	castconvey		(void)
{	want			();

	size_t		a=	cd.target->len;
	cd.target->len=		cd.targetfrom->value.i;
	size_t		d=	cd.amount->value.i;
	text_check		(cd.target,d);
	cd.target->len=		a;
	size_t		b=	cd.targetfrom->value.i;
	size_t		c=	cd.originfrom->value.i;

	memcpya			(cd.target->textaddr+b,
				 cd.origin->textaddr+c,d);

	*Gz.at=			castconvey;
	argot_next		();
}

SCV	castinsert		(void)
{	want			();

	size_t		d=	cd.amount->value.i;
	text_check		(cd.target,d);

	size_t		b=	cd.targetfrom->value.i;
	size_t		c=	cd.originfrom->value.i;

	memmove			(cd.target->textaddr+b+d,
				 cd.target->textaddr+b,
				 cd.target->textlen -b);
	cd.target->textlen+=	d;
	memcpya			(cd.target->textaddr+b,
				 cd.origin->textaddr+c,d);

	*Gz.at=		castinsert;
	argot_next		();
}

__attribute__((always_inline))
static	inline	void	single	(void (*A)(void),VMETA **B)
{	*B=		Gz.to[0];
	*Gz.at=	A;
	argot_next	();
}

SCV	casttarget	(void)	{single(casttarget,	&cd.target);}
SCV	castorigin	(void)	{single(castorigin,	&cd.origin);}
SCV	casttargetfrom	(void)	{single(casttargetfrom,	&cd.targetfrom);}
SCV	castoriginfrom	(void)	{single(castoriginfrom,	&cd.originfrom);}
SCV	castamount	(void)	{single(castamount,	&cd.amount);}

SCV	cast_			(void)
{	volatile
	CASTDATA	a=	cd;
	argot_next		();
	cd=			a;
}

SCV			cast	(void)
{	(*Gz.at=	cast_)	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200214",
	.official=	"20190214",
	.update=	"20200705"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(cast,		"cast");
	aa		(castamount,	"castamount");
	aa		(castorigin,	"castorigin");
	aa		(castoriginfrom,"castoriginfrom");
	aa		(casttarget,	"casttarget");
	aa		(casttargetfrom,"casttargetfrom");
	aa		(castconvey,	"castconvey");
	aa		(castinsert,	"castinsert");
	aa_fini		();
};

