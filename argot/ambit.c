/*	By Kyle Sallee in 2015 and 2016 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"ambit.h"
#include	"a.h"

SCV	add_				(void)
{	show				(Gz.to[1]);
	VMETA		*B=		 Gz.to[1];

	VMETA		*A=		Gz.to[0];
	A->io.flag|=			textmapuse;
	uint8_t		*M=		(uint8_t *) A->textaddr;

	uint32_t	b;
	uint8_t		*a=		B->textaddr;
	uint8_t		*e=		B->textaddr+
					B->textlen;
	while				(e>a)
	{	b=	utf8_in		(&a);
		M[b]=			1;
	}
	argot_next			();
}

SCV	sub_				(void)
{	show				(Gz.to[1]);
	VMETA		*B=		 Gz.to[1];

	VMETA		*A=		Gz.to[0];
	A->io.flag|=			textmapuse;
	uint8_t		*M=		(uint8_t *) A->textaddr;

	uint32_t	b;
	uint8_t		*a=		B->textaddr;
	uint8_t		*e=		B->textaddr+
					B->textlen;
	while				(e>a)
	{	b=	utf8_in		(&a);
		M[b]=			0;
	}
	argot_next			();
}

SCV	set_				(void)
{	VMETA		*B=
	parapass			(arga(NULL));
	show				(B);

	VMETA		*A=		Gz.to[0];
	A->io.flag|=			textmapuse;
	uint8_t		*M=		(uint8_t *) A->textaddr;

	uint32_t	b;
	uint8_t		*a=		B->textaddr;
	uint8_t		*e=		B->textaddr+
					B->textlen;
	while				(e>a)
	{	b=	utf8_in		(&a);
		M[b]=			1;
	}
	argot_next			();
}

SCV	equal_			(void)
{	VMETA		*A=	Gz.to[0];
	madvise			(A->textaddr,A->textsize,MADV_DONTNEED);
	add_			();
}

static	void	equal	(void){(*Gz.at=equal_)	();}
static	void	add	(void){(*Gz.at=	add_)	();}
static	void	sub	(void){(*Gz.at=	sub_)	();}
static	void	set	(void){(*Gz.at=	set_)	();}

SCV		ambit	(void){tvarnewab(ambitsubnew,ambit);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit			(void)
{	aa_init			();
	aa			(ambit,	"ambit");
	aa_fini			();

	opambit[0].add=		add;
	opambit[0].equal=	equal;
	opambit[0].set=		set;
	opambit[0].sub=		sub;
};
