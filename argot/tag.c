/*	By Kyle Sallee in 2015, 2016, 2017, 2018, 2019, 2020 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"trek.h"

__attribute__((always_inline))
static	inline	int	tagcat		(void)
{	VLESS		*a,*b;
	argarange			(NULL,&a,&b);
	int		d=		(a->op==opnear);
	uint8_t		*c=		Gz.tag.name;
	VMETA		*A;
	do
	{	A=	parapass	(a);
		show			(A);
		__builtin_memcpy	(c,A->textaddr,LABEL_SIZE);
		c+=			 A->textlen;
	}
	while				(b>++a);
	__builtin_memset		(c,0,LABEL_SIZE);
	return				d;
}

__attribute__((noinline))
__attribute__((hot))
SCV	(**target(void))(void)
{	if			yay	(tagcat())
	return	nearfind_safe		(Gz.tag.name,partfar(NULL));
	else
	return	farfind_safe		(Gz.tag.name);
}

__attribute__((cold))
__attribute__((aligned(0x20)))
static		void	tag		(void)
{	*Gz.at=		tag;
	argot_next	();
}

SCV	tagyay			(void)
{	void		(**A)	(void)=
	target			();
	*Gz.at=			tagyay;
	argot_jump		(A!=NULL);
}

SCV	tagnay			(void)
{	void		(**A)	(void)=
	target			();
	*Gz.at=			tagnay;
	argot_jump		(A==NULL);
}

SCV	taggo			(void)
{	void		(**A)	(void)=
	target			();

	*Gz.at=			taggo;
	if		yay	(A!=NULL)
	(*(Gz.at=A))		();
	else
	argot_next		();
}

SCV	tagpin				(void)
{	void		(**A)	(void)=
	target				();

	void		(**L)	(void)=	Gz.at;
	*L=				tagpin;
	if			yay	(A!=NULL)
	{	(*(Gz.at=A  ))		();
		(*(Gz.at=L+2))		();
	}
	else	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200920",
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(tag,		"tag");
	aa		(tagnay,	"tagnay");
	aa		(tagyay,	"tagyay");
	aa		(tagpin,	"tagpin");
	aa		(taggo,		"taggo");
	aa_fini		();
};
