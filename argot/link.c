/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"

__attribute__((always_inline))
static	inline	void	link_head_set	(VMETA *H,VMETA *A)
{	VMETA		* const B=	A;
	do
	{	A->link_head=		H;
		A=			A->link_next;
	}	while			(A!=B);
}

__attribute__((always_inline))
static	inline	VMETA	*link_free_next	(VMETA *C)
{	VMETA		*A=		C->link_back,
			*B=		C->link_next;

	A->link_next=			B;
	B->link_back=			A;
	A=				C->link_head;
	C->link_back=
	C->link_next=
	C->link_head=			NULL;

	if			yay	(C!=A)
	return				A;
	link_head_set			(B,B);
	return				B;
}

__attribute__((always_inline))
static	inline	VMETA	*link_free_back	(VMETA *C)
{	VMETA		*A=		C->link_back,
			*B=		C->link_next;

	A->link_next=			B;
	B->link_back=			A;
	B=				C->link_head;
	C->link_back=
	C->link_next=
	C->link_head=			NULL;

	if			yay	(C!=B)
	return				B;
	link_head_set			(A,A);
	return				A;
}

__attribute__((always_inline))
static	inline	void	link_init	(VMETA *A)
{	if			nay	(A->link_head==NULL)
	A->link_head=
	A->link_back=
	A->link_next=			A;
}

__attribute__((noinline))
SCV	linkmake_		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];

	link_init		(A);
	if		nay	(B->link_head!=NULL)
	link_free_next		(B);

	B->link_head=		A->link_head;
	VMETA		*C=	A->link_next;
        C->link_back=		B;
	B->link_next=		C;
	A->link_next=		B;
	B->link_back=		A;

	argot_next		();
}

SCV		linkmake	(void)
{	(*Gz.at=linkmake_)	();
}

__attribute__((noinline))
SCV	linkjoin_		(void)
{	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];

	link_init		(A);
	link_init		(B);

	link_head_set		(A->link_head,B);

	VMETA		*C=	A->link_next;
	VMETA		*D=	B->link_back;
	D->link_next=		C;
	C->link_back=		D;
	A->link_next=		B;
	B->link_back=		A;
	argot_next		();
}

SCV		linkjoin	(void)
{	(*Gz.at=linkjoin_)	();
}

SCV	linkhead_		(void)
{	Gz.to[0]=		Gz.to[0]->link_head;
	argot_next		();
}

SCV		linkhead	(void)
{	(*Gz.at=linkhead_)	();
}

SCV	linktail_		(void)
{	Gz.to[0]=		Gz.to[0]->link_head->link_back;
	argot_next		();
}

SCV		linktail	(void)
{	(*Gz.at=linktail_)	();
}

__attribute__((noinline))
SCV		linkomit__	(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		*B=
	link_free_next		(A);
	argot_jump		(B!=B->link_next);
}

SCV		linkomit_	(void)
{	(*Gz.at=linkomit__)	();
}

__attribute__((noinline))
SCV	linkomitback_		(void)
{	VMETA		*A=	Gz.to[0];
	Gz.to[0]=		A->link_back;
	VMETA		*B=
	link_free_next		(A);
	argot_jump		(B!=B->link_next);
}

SCV		linkomitback	(void)
{	(*Gz.at=linkomitback_)	();
}

__attribute__((noinline))
SCV	linkomitnext_		(void)
{	VMETA		*A=	Gz.to[0];
	Gz.to[0]=		A->link_next;
	VMETA		*B=
	link_free_back		(A);
	argot_jump		(B!=B->link_next);
}

SCV		linkomitnext	(void)
{	(*Gz.at=linkomitnext_)	();
}

__attribute__((noinline))
SCV	linkback_		(void)
{	VMETA		*A=	Gz.to[0];
	Gz.to[0]=		A->link_back;
	argot_jump		(A!=A->link_head);
}

SCV		linkback	(void)
{	(*Gz.at=linkback_)	();
}

__attribute__((noinline))
SCV	linknext_		(void)
{	VMETA		*A=	Gz.to[0]->link_next;
	Gz.to[0]=		A;
	argot_jump		(A!=A->link_head);
}

SCV		 linknext	(void)
{	(*Gz.at=linknext_)	();
}

__attribute__((noinline))
SCV	linkwith_		(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	argot_jump		((A->link_head==B->link_head)&
				 (A->link_head!=NULL));
}

SCV		linkwith	(void)
{	(*Gz.at=linkwith_)	();
}

__attribute__((noinline))
SCV	linksans_		(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	argot_jump		((A->link_head!=B->link_head)|
				 (A->link_head==NULL));

}

SCV		linksans	(void)
{	(*Gz.at=linksans_)	();
}

__attribute__((noinline))
SCV		linkheadset_	(void)
{	VMETA		*A=	Gz.to[0];
	link_head_set		(A,A);
	argot_next		();
}

SCV		linkheadset	(void)
{	(*Gz.at=linkheadset_)	();
}

__attribute__((cold))
static	void		link_	(void)
{	*Gz.at=		link_;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200318",
	.official=	"20200318",
	.update=	"20200922"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(link_,		"link");
	aa		(linkmake,	"linkmake");
	aa		(linkjoin,	"linkjoin");
	aa		(linkomit_,	"linkomit");
	aa		(linkomitback,	"linkomitback");
	aa		(linkomitnext,	"linkomitnext");
	aa		(linkheadset,	"linkheadset");
	aa		(linkhead,	"linkhead");
	aa		(linktail,	"linktail");
	aa		(linkback,	"linkback");
	aa		(linknext,	"linknext");
	aa		(linksans,	"linksans");
	aa		(linkwith,	"linkwith");
	aa_fini		();
};
