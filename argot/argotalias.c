/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"

/*
static	inline	ARGOT	**aam		(uint8_t const *);
*/

static	inline	void	argot_old	(void (*f)(void),uint8_t const *n)
{	ARGOT		*A=
	pool		(PAGE);
	A->at=		f;
	memcpy		(A->name,n,0x10);

	ARGOT		**M=
	aam		(n);
	A->fore=	*M;
	*M=		A;
}

__attribute__((noinline))
SCV	wrap			(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];

	show			(A);
	show			(B);

	uint8_t		n	[2][ARGOT_NAME_SIZE];

	memset			(n,0,sizeof(n));
	memcpy			(n[0],A->textaddr,A->textlen);
	memcpy			(n[1],B->textaddr,B->textlen);

	ARGOT		**MB=
	aam			(n[1]);

	uint64_t	a0,a1,
			b0=	*(uint64_t *)	 n[1],
			b1=	*(uint64_t *)	(n[1]+8);

	ARGOT	*C=		*MB;
	while			(1)
	{	a0=		*(uint64_t *)	 C->name;
		a1=		*(uint64_t *)	(C->name+8);
		if	yay	(((a0^b0)|(a1^b1))==0)
		break;
		C=		C->fore;
	}

	argot_old		(C->at,n[0]);
}

SCV	argotalias	(void)
{	wrap		();
	*Gz.at=		argotalias;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190302",
	.official=	"20190302",
	.update=	"20200622"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(argotalias,	"argotalias");
	aa_fini		();
};

