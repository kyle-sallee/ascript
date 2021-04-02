/*	By Kyle Sallee in 2015, 2016, 2017, 2018, 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"trek.h"
#include	"a.h"

__attribute__((cold))
static		void	trek	(void)
{	*Gz.at=		trek;
	argot_next	();
}

SCV	golatenearfast	(void);
SCV	golatenear	(uint16_t a)
{	void		(**L)	(void)=	Gz.at;
	void		(**S)	(void)=
	partsave(NULL)->p=
	nearfind_faster			(arga(NULL)->textaddr,partfar(NULL),a);

	*L=				golatenearfast;
	argot_next			();
	(*(L=S))			();
}

SCV	golatenearfast			(void)
{	void		(**S)	(void)=	partsave(NULL)->p;
	argot_next			();
	(*(Gz.at=S))			();
}

SCV	gofarnearfast			(void)
{	VLESS		*a,*b;
	argarange			(NULL,&a,&b);
	PART_REFER	**c=	partsave(NULL)->p;

	void		(**d)	(void)=
	farmfind_fast			(a->textaddr,c);
	d=
	nearfind_fast			(b->textaddr,partfar(d));
	(*(Gz.at=d))			();
}

SCV	pinfarnearfast			(void)
{	void		(**L)	(void)=	Gz.at;
	VLESS		*a,*b;
	argarange			(NULL,&a,&b);
	PART_REFER	**c=	partsave(NULL)->p;

	void		(**d)	(void)=
	farmfind_fast			(a->textaddr,c);
	d=
	nearfind_fast			(b->textaddr,partfar(d));
	(*(Gz.at=d))			();
	(*(Gz.at=L+1))			();
}

SCV	golatefarfast		(void)
{	void		(**L)	(void)=	Gz.at;
	argot_next		();

	Gz.at=
	farmfind_fast		(arga(L)->textaddr,partsave(L)->p);
	(*Gz.at)		();
}

SCV	golatefarfast			(void);
SCV	golatefar			(uint16_t a)
{	void		(**L)	(void)=	Gz.at;
	*L=				golatefarfast;

	partsave(L)->p=			&Gz.hash.far[a];
	argot_next			();

	Gz.at=
	farmfind_fast			(arga(L)->textaddr,partsave(L)->p);
	(*Gz.at)			();
}

SCV	goend				(void)
{	ENDPART		*E=	pp	();

	void		(**L)	(void)=
	farfind_fast			(arga(NULL)->textaddr);

	E->F=				Gz.endpart;
	Gz.endpart=			E;
	E->L=				L;
	__builtin_memcpy		(E->to,Gz.to,sizeof(Gz.to));

	*Gz.at=				goend;
	argot_next			();
}

SCV	gofarnear			(void)
{	PART_REFER	**F=
	farm				(arga(NULL)->textaddr);
	partsave(NULL)->p=		F;

	void		(**N)	(void)=
	farmfind_fast			(arga(NULL)->textaddr,F);
	N=
	nearfind_fast			(arga(NULL)[1].textaddr,partfar(N));

	*Gz.at=				gofarnearfast;
	(*(Gz.at=N))			();
}

SCV	pinfarnear			(void)
{	void		(**L)	(void)=	Gz.at;

	PART_REFER	**F=
	farm				(arga(NULL)->textaddr);
	partsave(NULL)->p=		F;

	void		(**N)	(void)=
	farmfind_fast			(arga(NULL)->textaddr,F);
	N=
	nearfind_fast			(arga(NULL)[1].textaddr,partfar(N));

	*Gz.at=				pinfarnearfast;
	(*(Gz.at=N  ))			();
	(*(Gz.at=L+1))			();
}

SCV	go2		(void)
{	gofarnear	();
}

SCV	pin2		(void)
{	pinfarnear	();
}

SCV	golate				(void)
{	uint16_t	a=
	jidx				(arga(NULL)[0].textaddr);
/*	if			yay	(arga(NULL)[0].value.b=='\'')	*/
	if			yay	(arga(NULL)[0].op==opnear)
	golatenear			(a);
	else
	golatefar			(a);
}

static	intptr_t	weir_skip;

__attribute__((hot))
SCV	weirnearfast			(void)
{	intptr_t	S=		weir_skip;
	weir_skip=		sizeof	(void *);
	void		(**L)	(void)=	Gz.at;
	(*(Gz.at=partsave(NULL)->p))	();
	void		*v=		L+1;
	v+=				weir_skip;
	weir_skip=			S;
	(*(Gz.at=v))			();
}

__attribute__((hot))
SCV	weirfarfast			(void)
{	intptr_t	S=		weir_skip;
	weir_skip=		sizeof	(void *);
	void		(**L)	(void)=	Gz.at;
	Gz.at=
	farmfind_fast			(arga(NULL)->textaddr
					,partsave(NULL)->p);
	(*Gz.at)			();
	void		*v=		L+1;
	v+=				weir_skip;
	weir_skip=			S;
	(*(Gz.at=v))			();
}

SCV	weirnear			(uint16_t a)
{	partsave(NULL)->p=
	nearfind_faster			(arga(NULL)->textaddr,partfar(NULL),a);
	(*Gz.at=weirnearfast)		();
}

SCV	weirfar				(uint16_t a)
{	partsave(NULL)->p=		&Gz.hash.far[a];
	(*Gz.at=weirfarfast)		();
}

SCV	weirnext_	(void)	{weir_skip=	0;		argot_next();}
SCV	weirnextret_	(void)	{weir_skip=	0;}
SCV	weirskip_	(void)	{weir_skip=	sizeof(void *);	argot_next();}
SCV	weirskipret_	(void)	{weir_skip=	sizeof(void *);}

SCV	weirnext	(void)	{(*Gz.at=weirnext_)	();}
SCV	weirnextret	(void)	{(*Gz.at=weirnextret_)	();}
SCV	weirskip	(void)	{(*Gz.at=weirskip_)	();}
SCV	weirskipret	(void)	{(*Gz.at=weirskipret_)	();}

SCV	weir			(void)
{	uint16_t	a=
	jidx			(arga(NULL)[0].textaddr);
	if			(arga(NULL)[0].op==opnear)
	weirnear		(a);
	else
	weirfar			(a);
}

SCV	farequal			(void)
{	VMETA		*A=		Gz.to[0],
			*B=		Gz.to[1];
	uint8_t		*a=		B->textaddr;

	PART_REFER	**F,*G,*H;
	uint16_t	c=
	bit128_to_bit16			(a);
	F=				&Gz.hash.far[c];
	G=
	H=				*F;

	if			nay	(G->fore==NULL)
	{	vector8x16	d,e;
		d=			*(vector8x16 *)	a;

		while			(1)
		{	e=		*(vector8x16 *)	G->name;
			e^=		d;
			if	yay	((e[0]|e[1])==0)
			break;
			H=		G;
			G=		G->fore;
		}
	}

	if				(G==H)
	*F=				G->fore;
	else
	H->fore=			G->fore;

	memcpy				(G->name,A->textaddr,LABEL_SIZE);
	c=
	bit128_to_bit16			(G->name);

	PART_REFER	**LL=		&Gz.hash.far[c];
	G->fore=			*LL;
	*LL=				G;
	*Gz.at=				farequal;
	argot_next			();
}
#ifdef		__linux__
#include	<ucontext.h>

struct		USAVE_T;
typedef	struct	USAVE_T	USAVE;

typedef	struct	USAVE_T
{	ucontext_t	a;
	void		(**b)	(void);
	uint8_t		c;
	USAVE		*d;
}	USAVE;

static	USAVE	*U;

SCV	contextfree		(void)
{	USAVE		*a=	U;
	U=			a->d;
	munmap			(a,PAGE);
	*Gz.at=			contextfree;
	argot_next		();
}

SCV	contextget		(void)
{
/*	if		nay	(*Gz.at==contextget)
	{	argot_skip	();
		return;
	}
*/

	*Gz.at=			contextget;

	USAVE		*a=
	pp			();
	a->d=			U;
	U=			a;
	U->b=			Gz.at;

	/*	getcontext
		aft invocation
		Gz.at
		can differ.
	*/

	getcontext		(&a->a);

	if		yay	(U->c==0)
	(*(Gz.at=U->b+2))	();
	else
	(*(Gz.at=U->b+1))	();
}

SCV	contextset		(void)
{	VMETA		*A=
	parapass		(arga(NULL));
/*	denwant			(A);	*/
	USAVE		*a=	U;
	int		b=	A->value.i;
	for			(;b;b--)
	a=			a->d;

	a->c=			1;
	*Gz.at=			contextset;
	setcontext		(&a->a);
}
#endif	/* __linux__ */

__attribute__((cold))
		void	segv	(void)
{	int		c=
	arga			(Gz.at+1)-
	arga			(Gz.at);

	if	yay		(c>0)
	{	uint8_t	*a=	arga(NULL)[0].textaddr;
		int	e=
		errna=		EADDRNOTAVAIL;
		err		(e,"The target 	\"%s\"" " is required.\n",a);
	}
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200922",
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
#ifdef	__linux__
	aa		(contextget,	"contextget");
	aa		(contextset,	"contextset");
	aa		(contextfree,	"contextfree");
#endif
	aa		(trek,		"trek");
	aa		(go2,		"go2");
	aa		(pin2,		"pin2");
	aa		(goend,		"goend");
/*	aa		(late,		"late");	*/
	aa		(farequal,	"farequal");
	aa		(weirnext,	"weirnext");
	aa		(weirskip,	"weirskip");
	aa		(weirnextret,	"weirnextret");
	aa		(weirskipret,	"weirskipret");
	aa		(weir,		"weir");
	aa		(golate,	"golate");
/*	aa		(skip,		"skip");	*/
	aa_fini		();
};

