/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"a.h"
#include	"glob.h"

OPERATOR	opglob[1];
VMETA		*G;

SCV	globnext_	(void)
{	GLOBDATA	*a=
	globdata			(G);
	if			nay	(a->t.gl_pathv==NULL)
	{	a->c=			0;
		glob			(G->host->textaddr,
					 a->flag,NULL,
					&a->t);
		a=	globdata	(G);
	}

	if			yay	(a->t.gl_pathc>a->c)
	{	G->textlen=
		strlena			(a->t.gl_pathv[a->c]);
		memcpyb			(G->textaddr,
					 a->t.gl_pathv[a->c],
					 G->textlen);
		G->textaddr[
		G->textlen]=		0;
		a->c++;
		argot_skip		();
	}
	else
	argot_next			();
}

__attribute__((noinline))
SCV			globnext	(void)
{	(*Gz.at=	globnext_)	();
}

SCV	globreset	(void)
{	globfree_	(G);
	*Gz.at=		globreset;
	argot_next	();
}

static	inline	void	c1	(int a,void (*F)(void))
{	GLOBDATA	*b=
	globdata		(G);
	b->flag|=		a;
	*Gz.at=			F;
	argot_next		();
}

static	inline	void	c0	(int a,void (*F)(void))
{	GLOBDATA	*b=
	globdata		(G);
	b->flag&=		~a;
	*Gz.at=			F;
	argot_next		();
}

SCV	globwith	(void)
{	G=		Gz.to[0];
	*Gz.at=		globwith;
	argot_next	();
}

SCV	globpush	(void)
{	VMETA	*g=	G;
	*Gz.at=		globpush;
	argot_next	();
	G=		g;
}

SCV	globbrace	(void){c1(GLOB_BRACE,globbrace);}
SCV	globdironly	(void){c1(GLOB_ONLYDIR,globdironly);}
SCV	globdotmatch	(void){c1(GLOB_PERIOD,globdotmatch);}
SCV	globnoescape	(void){c1(GLOB_NOESCAPE,globnoescape);}
SCV	globslash	(void){c1(GLOB_MARK,globslash);}
SCV	globsort	(void){c0(GLOB_NOSORT,globsort);}
SCV	globtilde	(void){c1(GLOB_TILDE_CHECK,globtilde);}
SCV	_glob		(void){tsubab(globsubnew,_glob);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180412",
	.official=	"20180412",
	.update=	"20200924"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_glob,		"glob");
	aa		(globreset,	"globreset");
	aa		(globdironly,	"globdironly");
	aa		(globbrace,	"globbrace");
	aa		(globdotmatch,	"globdotmatch");
	aa		(globnoescape,	"globnoescape");
	aa		(globslash,	"globslash");
	aa		(globsort,	"globsort");
	aa		(globtilde,	"globtilde");
	aa		(globpush,	"globpush");
	aa		(globwith,	"globwith");
	aa		(globnext,	"globnext");
	aa_fini		();
	opglob[0]=	opbyte[0];
};
