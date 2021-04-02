/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"argot.h"
#include	"a.h"

SCV	done		(void)
{	argot_skip	();
}

static	inline	int	al		(void)
{	VLESS		*a=	arga	(Gz.at),
			*b=	arga	(Gz.at+1);
	uint8_t		c;
	VMETA		*A;
	if			yay	(b>a)
	for				(c=0;b>a;a++)
	{	A=	parapass	(a);
		c|=
		ifaload			(A->textaddr);
	}
	return				c;
}

static	CALIGN	void	argotload	(void)
{	*Gz.at=	done;
	argot_jump	(al()==0);
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200414"
};

__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(argotload,	"argotload");
	aa_fini		();
};

