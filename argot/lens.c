/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"utf8.h"

#define	LENS	sizeof(int32_t)*0x110000
/*
static	PALIGN	int32_t		LB	[0x110000];
*/
static		int32_t		*L;

SCV	matrix_load	(VMETA *A,VMETA *B)
{	uint8_t		*a=		B->textaddr;
	uint8_t		*e=		B->textaddr+
					B->textlen;
	uint8_t		*b=		A->textaddr;
	int32_t		c;
	int32_t		d;
	while				(e>a)
	{	c=	utf8_in		(&a);
		d=	utf8_in		(&b);
		L[c]=		d-c;
	}
}

SCV	lensrender		(void)
{	show			(Gz.to[1]);
	text_check		(Gz.to[0],Gz.to[1]->textlen);

	uint8_t		*a,*e,*b;
	int32_t		c;
	for			(b=Gz.to[0]->textaddr+
				   Gz.to[0]->textlen,
				 a=Gz.to[1]->textaddr,
				 e=Gz.to[1]->textaddr+
				   Gz.to[1]->textlen;
				 e>a;)
	{	c=
		utf8_in		(&a);
		utf8_out	(&b,c+L[c]);
	}

	Gz.to[0]->textlen=	b-
	Gz.to[0]->textaddr;
	*Gz.at=		lensrender;
	argot_next		();
}

SCV	lensdata		(void)
{	matrix_load		(Gz.to[0],Gz.to[1]);
	*Gz.at=		lensdata;
	argot_next		();
}

SCV	lens_			(void)
{
/*	void	* volatile a=	L;	*/
	void	*a=		L;
	L=	pps		(  LENS);
	argot_next		();
	munmap			(L,LENS);
	L=			a;
}

SCV			lens	(void)
{	(*Gz.at=	lens_)	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180712",
	.official=	"20180712",
	.update=	"20200705",
};

__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(lens,		"lens");
	aa		(lensdata,	"lensdata");
	aa		(lensrender,	"lensrender");
	aa_fini		();
};
