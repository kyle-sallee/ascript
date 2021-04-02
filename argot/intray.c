/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"

__attribute__((always_inline))
static	inline	 void	*intraydata	(VMETA *A)
{	return	(void *)		A->textaddr;
}

SCV	revise_ir		(VMETA *A)
{	A->textaddr=
	mremap			(A->textaddr
				,A->textsize
				,A->value.i,
				MREMAP_MAYMOVE);
	A->textsize=		A->value.i;
}

SCV	reval_ir		(VMETA *A)
{	A->value.i=		A->textsize;
}

__attribute__((always_inline))
static	inline	void	irinit	(VMETA *A)
{	int8init		(A);
	map_add			(A,PAGE,0);
	A->reval=		reval_ir;
	A->revise=		revise_ir;
}

SCV	intray			(void){tvarnewa(irinit);}

SCV	intrayindex		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];
	B->host=		A;
	*Gz.at=			intrayindex;
	argot_next		();
}

SCV	reval_irv4		(VMETA *A)
{	uint32_t	*a=	(uint32_t *)
				A->host->host->textaddr+
				A->host->value.i4.l;
	A->value.i4.l=		*a;
}

SCV	reval_irv8		(VMETA *A)
{	uint64_t	*a=	(uint64_t *)
				A->host->host->textaddr+
				A->host->value.i4.l;
	A->value.i=		*a;
}

SCV	revise_irv4		(VMETA *A)
{	uint32_t	*a=	(uint32_t *)
				A->host->host->textaddr+
				A->host->value.i4.l;
	*a=			A->value.i4.l;
}

SCV	revise_irv8		(VMETA *A)
{	uint64_t	*a=	(uint64_t *)
				A->host->host->textaddr+
				A->host->value.i4.l;
	*a=			A->value.i;
}

SCV	intrayvalue		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];
	B->host=		A;
	if			(B->op->int4_compat)
	{	B->reval=	reval_irv4;
		B->revise=	revise_irv4;
	}
	else
	{	B->reval=	reval_irv8;
		B->revise=	revise_irv8;
	}

	*Gz.at=			intrayindex;
	argot_next		();
}

SCV	intraybackorigin	(void)
{	VMETA		*A=	Gz.to[1];
	A->host->value.i--;
	*Gz.at=			intraybackorigin;
	argot_next		();
}

SCV	intraybacktarget	(void)
{	VMETA		*A=	Gz.to[0];
	A->host->value.i--;
	*Gz.at=			intraybackorigin;
	argot_next		();
}

SCV	intraynextorigin	(void)
{	VMETA		*A=	Gz.to[1];
	A->host->value.i++;
	*Gz.at=			intraynextorigin;
	argot_next		();
}

SCV	intraynexttarget	(void)
{	VMETA		*A=	Gz.to[0];
	A->host->value.i++;
	*Gz.at=			intraynextorigin;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190920",
	.official=	"20190920",
	.update=	"20200819"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(intray,		"intray");
	aa		(intrayindex,		"intrayindex");
	aa		(intrayvalue,		"intrayvalue");

	aa		(intraybackorigin,	"intraybackorigin");
	aa		(intraybacktarget,	"intraybacktarget");
	aa		(intraynextorigin,	"intraynextorigin");
	aa		(intraynexttarget,	"intraynexttarget");
	aa_fini		();
};
