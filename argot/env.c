/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"env.h"

extern	char	**environ;

typedef	struct
{	uint8_t		a[ENV_BYTE_MAX];
}	ENVDATA;

typedef	struct
{	VMETA		env	[ENV_MAX];
	PALIGN
	uint8_t		p	[PAGE];
	ENVDATA		data	[ENV_MAX];
}	ENVPORT;

PALIGN	ENVPORT	ep;

static	void	add		(void);
static	void	equalequal	(void);
static	void	notequal	(void);
static	void	sub		(void);

__attribute__((always_inline))
static	inline	void	namevar		(VMETA *A,uint8_t *a)
{	__builtin_memcpy		(A->name,"env.",4);
	size_t		b=
	bytelen				(a,'=');
	A->len=				4+b;
	memcpya				(A->name+4,a,b);
	__builtin_memset		(A->name+A->len,0,0x10);
	vattach				(A);
}

__attribute__((constructor))
SCV			init		(void)
{	openv[0].add=			add;
	openv[0].equalequal=		equalequal;
	openv[0].notequal=		notequal;
	openv[0].sub=			sub;

	Gz.env=				ep.env;

	ep.env[0].op=			openv;
	map_init			(ep.env);
	ep.env[0].dataaddr=		ep.p;
	ep.env[0].datasize=		PAGE;

	uint8_t		**a=		(uint8_t **)
					ep.p;

	__builtin_memcpy		(ep.env[0].name,"env",4);
	ep.env[0].len=			3;
	ep.env[0].show=			show_env;
	vattach_faster			(ep.env,"env");

	VMETA		*A;
	uint8_t		**e=		(uint8_t **)	environ;

	if			nay	(e[0]==NULL)
	goto				empty;

	ENVDATA		*D=		ep.data;
	A=				ep.env+1;
	while				(1)
	{	map_init		(A);
		A->op=			opbyte;
		A->io.flag=		textmapuse|textmapunmap;
		*a++=
/*		A->textaddr=		e[0];	*/
		A->textaddr=		D[0].a;
		D++;
		A->textsize=		ENV_BYTE_MAX;

		namevar			(A,e[0]);
		A[0].link_head=		ep.env;
		A[0].link_back=		A-1;
		A[-1].link_next=	A;

		if		nay	(e[1]==NULL)
		break;
/*		A->textsize=		*/
		A->textlen=		e[1]-e[0]-1;
		memcpya			(A->textaddr,e[0],A->textlen);
		e++;
		A++;
	}

/*	A->textsize=			*/
	A->textlen=
	strlena				(e[0]);
	memcpya				(A->textaddr,e[0],A->textlen);

	A[0].link_next=
	ep.env[0].link_head=		ep.env;
	ep.env[0].link_back=		A;
	ep.env[0].link_next=		ep.env+1;

	empty:
	ep.env[0].datalen=		(uint8_t *) a-	ep.p;
}

__attribute__((always_inline))
static	inline	uint8_t **envfind	(void)
{	uint8_t		**a=		(uint8_t **)	Gz.to[0]->dataaddr;
	uint8_t		*b=		(uint8_t *)	Gz.to[1]->textaddr;
	while				(1)
	{	if		nay	(*a==b)		return	a;
		if		nay	(*a==NULL)	return	0;
		a++;
	}
}

__attribute__((noinline))
SCV			equalequal_	(void)	{argot_jump(envfind()!=NULL);}
__attribute__((noinline))
SCV			notequal_	(void)	{argot_jump(envfind()==NULL);}

__attribute__((noinline))
SCV			add_		(void)
{	VMETA		*A=		Gz.to[0];
	VMETA		*B=		Gz.to[1];
	void		*v=		A->dataaddr+
					A->datalen;
	uint8_t		**a=		(uint8_t **)	v;
	*a=				B->textaddr;
	A->datalen+=
	sizeof				(void *);
	argot_next			();
}

__attribute__((noinline))
SCV			sub_	(void)
{	uint8_t		**a=
	envfind			();

	if		nay	(a==NULL)
	{	argot_next	();
		return;
	}

	Gz.to[0]->datalen-=
	sizeof			(void *);

	void		*v=	Gz.to[0]->dataaddr+
				Gz.to[0]->datalen;

	uint8_t		**c=	v;
	*a=			*c;
	*c=			NULL;
	argot_skip		();
}

SCV	_env		(void)	{tvarnewab(envinit,_env);}
SCV	_envbyte	(void)	{tvarnewab(envbyteinit,_env);}

#define	SHV	__attribute__((aligned(0x20)))	static	void

SHV		notequal	(void){(*Gz.at=notequal_)	();}
SHV		equalequal	(void){(*Gz.at=equalequal_)	();}
SHV		add		(void){(*Gz.at=add_)		();}
SHV		sub		(void){(*Gz.at=sub_)		();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180228",
	.official=	"20180228",
	.update=	"20200920"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_env,		"env");
	aa		(_envbyte,	"envbyte");
	aa_fini		();
};
