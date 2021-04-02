/*	By Kyle Sallee in 2020 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

/*
By this argot
per ascript process
the librt
repeated loading
is prevented.
By argot rt
some opcodes
while wasted
required libraries
if already loaded
to check
by what libdl does
MORE CPU opcodes
are wasted!
*/

#include	"ascript.h"

static		void	rt	(void)
{	*Gz.at=		rt;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200123",
	.official=	"20200123",
	.update=	"20200123"
};

__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(rt,		"rt");
	aa_fini		();
};

