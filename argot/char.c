/*	By Kyle Sallee in 2020 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"char.h"
#include	"utf8.h"

/* From type byte the other string comparison variables can be acquired. */

/*
OPERATOR	opchar[1];
*/

SCV	charsave			(void)
{	VMETA		*A=		Gz.to[0];
	CHARD		*a=
	chard				(A);
	uint64_t	from=		a->from->value.i;
	uint64_t	len=		A->textlen;
	*Gz.at=				charsave;
	argot_next			();
	a->from->value.i=		from;
	A->textlen=			len;
	argot_next			();
}

SCV	charfull			(void)
{	VMETA		*A=		Gz.to[0];
	CHARD		*a=
	chard				(A);
	a->from->value.i=		0;
	A->textlen=			a->host->textlen;
	*Gz.at=				charfull;
	argot_next			();
}

SCV	addadd_				(void)
{	VMETA		*A=		Gz.to[0];
	CHARD		*a=
	chard				(A);
	uint8_t		*b=		a->host->textaddr;
	uint64_t	c=		a->from->value.i;
	uint8_t		*d=		b+c;
	uint8_t		e=
	utf8_size			(d);
	c+=				e;

	if				(a->host->textlen >c)
	{
/*		A->textaddr=		d+e;	*/
		a->from->value.i=	c;
		A->textlen=		e;
		argot_skip		();
	}
	else	argot_next		();
}

SCV	subsub_				(void)
{	VMETA		*A=		Gz.to[0];
	CHARD		*a=
	chard				(A);
	int64_t		b=		a->from->value.i;
	if			nay	(0>=b)
	{	argot_next		();
		return;
	}

	uint8_t		*c=		    a->host->textaddr+b;
	utf8_back			(&c);
/*	A->textaddr=			  c;	*/
	a->from->value.i=		  c-a->host->textaddr;

	A->textlen=
	utf8_size			(c);
	argot_skip			();
}

/*
__attribute__((hot))
__attribute__((noinline))
SCV	equalequal_		(void)
{	VMETA		*A=	Gz.to[0];	show	(A);
	VMETA		*B=	Gz.to[1];

	if			((memcmpa	(A->textaddr,
						 B->textaddr,
						 B->textlen)==0))
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	notequal_		(void)
{	VMETA		*A=	Gz.to[0];	show	(A);
	VMETA		*B=	Gz.to[1];
	if			((memcmpa	(A->textaddr,
						 B->textaddr,
						 B->textlen)))
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	less_			(void)
{	VMETA		*A=	Gz.to[0];	show	(A);
	VMETA		*B=	Gz.to[1];

	int64_t		d=
	memcmpa			(A->textaddr,
				 B->textaddr,
				 B->textlen);
	if			(d<0)
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	lessequal_		(void)
{	VMETA		*A=	Gz.to[0];	show	(A);
	VMETA		*B=	Gz.to[1];
	int64_t		d=
	memcmpa			(A->textaddr,
				 B->textaddr,
				 B->textlen);

	if			(d<=0)
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	more_			(void)
{	VMETA		*A=	Gz.to[0];	show	(A);
	VMETA		*B=	Gz.to[1];
	int64_t		d=
	memcmpa			(A->textaddr,
				 B->textaddr,
				 B->textlen);
	if			(d>0)
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	moreequal_		(void)
{	VMETA		*A=	Gz.to[0];	show	(A);
	VMETA		*B=	Gz.to[1];
	int64_t		d=
	memcmpa			(A->textaddr,
				 B->textaddr,
				 B->textlen);
	if			(d>=0)
	argot_skip		();
	else
	argot_next		();
}

SCV	equalequal	(void){(*Gz.at=equalequal_)	();}
SCV	notequal	(void){(*Gz.at=notequal_)	();}
SCV	less		(void){(*Gz.at=less_)		();}
SCV	lessequal	(void){(*Gz.at=lessequal_)	();}
SCV	more		(void){(*Gz.at=more_)		();}
SCV	moreequal	(void){(*Gz.at=moreequal_)	();}
*/
SCV	addadd		(void){(*Gz.at=addadd_)		();}
SCV	subsub		(void){(*Gz.at=subsub_)		();}
SCV	_char		(void){tsubab(charsubnew,_char);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200607",
	.official=	"20200607",
	.update=	"20200808"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_char,		"char");
	aa		(charsave,	"charsave");
	aa		(charfull,	"charfull");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	opchar[0]=			opbyte[0];
/*	opchar[0].equalequal=		equalequal;
	opchar[0].less=			less;
	opchar[0].lessequal=		lessequal;
	opchar[0].more=			more;
	opchar[0].moreequal=		moreequal;
	opchar[0].notequal=		notequal;
*/
	opchar[0].addadd=		addadd;
	opchar[0].subsub=		subsub;
}
