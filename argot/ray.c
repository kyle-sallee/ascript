/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"ray.h"

/*
OPERATOR	opray[1];
*/

SCV	raysave_		(void)
{	VMETA		*A=	Gz.active.ray;
	argot_next		();
	Gz.active.ray=		A;
}

SCV	raywith_		(void)
{	Gz.active.ray=		Gz.to[0];
	argot_next		();
}

SCV	set				(void)
{	VLESS		*a=	arga	(Gz.at),
			*b=	arga	(Gz.at+1);

	VMETA		*A=		Gz.to[0];
	VMETA		**C=
	raydataaddr			(A)+
	raymaxaddr			(A)->i;

	raymaxaddr	(A)->i+=	b-a;

	while				(b>a)
	*C++=	parapass		(a++);

	*Gz.at=				set;
	argot_next			();
}

SCV	rayadd_			(void)
{	VMETA		*A=	Gz.active.ray;
	VMETA		**B=	raydataaddr(A)+
				raymaxaddr (A)->i++;
	*B=			Gz.to[0];
	argot_next		();
}

SCV	add_			(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		**B=	raydataaddr(A)+
				raymaxaddr (A)->i++;
	*B=			Gz.to[1];
	argot_next		();
}

SCV			rayequal_	(void)
{	VMETA		*A=	Gz.active.ray;
	VMETA		**B=	raydataaddr(A)+
				raynowaddr (A)->i;
	*B=			Gz.to[0];
	argot_next		();
}

SCV			equal_	(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		**B=	raydataaddr(A)+
				raynowaddr (A)->i;
	*B=			Gz.to[1];
	argot_next		();
}

SCV	addadd_				(void)
{	VMETA		*A=		Gz.to[0];

	if				(raymaxaddr(A)->i>++
					(raynowaddr(A)->i))
	argot_skip			();
	else
	{	raynowaddr(A)->i=	0;
		argot_next		();
	}
}

SCV	raynext_			(void)
{	VMETA		*A=		Gz.active.ray;

	if				(raymaxaddr(A)->i>++
					(raynowaddr(A)->i))
	argot_skip			();
	else
	{	raynowaddr(A)->i=	0;
		argot_next		();
	}
}

__attribute__((always_inline))
static	inline	void	sub_generic	(VMETA *A)
{	if			nay	(0>=raymaxaddr(A)->i)
	{	argot_next		();
		return;
	}

	raymaxaddr			(A)->i--;
	raydataaddr			(A)
	[raynowaddr			(A)->i]=
	raydataaddr			(A)
	[raymaxaddr			(A)->i];
	raydataaddr			(A)
	[raymaxaddr			(A)->i]=
					NULL;

	if				(raynowaddr(A)->i==raymaxaddr(A)->i)
	raynowaddr			(A)->i--;
	argot_skip			();
}

SCV	sub_			(void)
{	sub_generic		(Gz.to[0]);
}

SCV	raysub_			(void)
{	sub_generic		(Gz.active.ray);
}

SCV	subsub_				(void)
{	VMETA		*A=		Gz.to[0];

	if				(--(raynowaddr(A)->i)>=0)
	argot_skip			();
	else
	{	raynowaddr		(A)->i=
		raymaxaddr		(A)->i-1;
		argot_next		();
	}
}

SCV	rayback_			(void)
{	VMETA		*A=		Gz.active.ray;

	if				(--(raynowaddr(A)->i)>=0)
	argot_skip			();
	else
	{	raynowaddr		(A)->i=
		raymaxaddr		(A)->i-1;
		argot_next		();
	}
}

SCV	raycat			(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];

	memcpya			(raydataaddr	(A)+
				 raymaxaddr	(A)->i,
				 raydataaddr	(B),
				 raymaxaddr	(B)->i*sizeof(VMETA *));

	raymaxaddr		(A)->i+=
	raymaxaddr		(B)->i;

	*Gz.at=			raycat;
	argot_next		();
}

SCV	rayorigin_		(void)
{	Gz.to[1]=		*rayrefaddr	(Gz.active.ray);
	argot_next				();
}

SCV	raytarget_		(void)
{	Gz.to[0]=		*rayrefaddr	(Gz.active.ray);
	argot_next				();
}

__attribute__((noinline))
SCV	raytellorigin_			(void)
{	Gz.to[1]=	*rayrefaddr	(Gz.to[1]);
	argot_next			();
}

__attribute__((noinline))
SCV	raytelltarget_			(void)
{	Gz.to[0]=	*rayrefaddr	(Gz.to[0]);
	argot_next			();
}

/*
SCV	tell	(VMETA **A)	{*A=	*rayrefaddr	(*A);}
*/

#define	NISCV	__attribute__((noinline))	static	void
NISCV	rayyay_	(void)	{argot_jump(Gz.to[0]->op==opray);}
NISCV	raynay_	(void)	{argot_jump(Gz.to[0]->op!=opray);}

__attribute__((aligned(0x20)))
static	void	rayyay	(void)	{(*Gz.at=rayyay_)	();}
static	void	raynay	(void)	{(*Gz.at=raynay_)	();}

SCV	rayadd		(void)	{(*Gz.at=rayadd_)		();}
SCV	rayback		(void)	{(*Gz.at=rayback_)		();}
SCV	rayequal	(void)	{(*Gz.at=rayequal_)		();}
SCV	raynext		(void)	{(*Gz.at=raynext_)		();}
SCV	rayorigin	(void)	{(*Gz.at=rayorigin_)		();}
SCV	raysave		(void)	{(*Gz.at=raysave_)		();}
SCV	raysub		(void)	{(*Gz.at=raysub_)		();}
SCV	raytarget	(void)	{(*Gz.at=raytarget_)		();}
SCV	raytelltarget	(void)	{(*Gz.at=raytelltarget_)	();}
SCV	raytellorigin	(void)	{(*Gz.at=raytellorigin_)	();}
SCV	raywith		(void)	{(*Gz.at=raywith_)		();}

SCV	add		(void)	{(*Gz.at=add_)			();}
SCV	addadd		(void)	{(*Gz.at=addadd_)		();}
SCV	equal		(void)	{(*Gz.at=equal_)		();}
SCV	sub		(void)	{(*Gz.at=sub_)			();}
SCV	subsub		(void)	{(*Gz.at=subsub_)		();}

SCV	ray		(void)	{tvarnewab(raysubnew,	ray);}
SCV	raymax		(void)	{tsubab(raymaxsubnew,	raymax);}
SCV	raynow		(void)	{tsubab(raynowsubnew,	raynow);}
SCV	rayname		(void)	{tsubab(raynamesubnew,rayname);}


const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(ray,		"ray");

	aa		(rayyay,	"rayyay");
	aa		(raynay,	"raynay");

	aa		(rayname,	"rayname");
	aa		(raynow,	"raynow");
	aa		(raymax,	"raymax");

	aa		(raycat,	"raycat");

	aa		(rayback,	"rayback");
	aa		(raynext,	"raynext");

	aa		(raytellorigin,	"raytellorigin"); /*use not intended*/
	aa		(raytelltarget,	"raytelltarget"); /*use not intended*/

	aa		(raysub,	"raysub");
	aa		(raywith,	"raywith");
	aa		(raysave,	"raysave");
	aa		(rayequal,	"rayequal");
	aa		(rayadd,	"rayadd");
	aa		(rayorigin,	"rayorigin");
	aa		(raytarget,	"raytarget");

	aa_fini		();
};

__attribute__((constructor))
SCV	init			(void)
{	opray[0].add=		add;
	opray[0].addadd=	addadd;
	opray[0].equal=		equal;
	opray[0].sub=		sub;
	opray[0].subsub=	subsub;
	opray[0].set=		set;
/*	opray[0].tell=		tell;	*/
}
