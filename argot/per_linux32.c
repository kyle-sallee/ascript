/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	<sys/personality.h>

static	CALIGN	void	per_linux32	(void)
{	int		p=
	personality			(-1);
	*Gz.at=			per_linux32;
	if			yay	(p!=-1)
	if			yay	(personality(p|PER_LINUX32)!=-1)
	{	argot_skip		();
		personality		(p);
		return;
	}
	argot_next			();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20171021",
	.official=	"20171021",
	.update=	"20200222"
};

__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(per_linux32,	"per_linux32");
	aa_fini		();
};

