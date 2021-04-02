/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	<iconv.h>

typedef	struct
{	VMETA		*to[2];
}	ICONVDATA;

static	ICONVDATA	id;

SCV	iconvrecode			(void)
{	errna=				0;

	text_check			(Gz.to[0],
					 Gz.to[1]->textlen*4);

	iconv_t		I=
	iconv_open			(id.to[0]->textaddr,
					 id.to[1]->textaddr);

	if			nay	(I==(iconv_t) -1)
	goto				fail;

	char
	*a=				Gz.to[1]->textaddr,
	*c=				Gz.to[0]->textaddr+
					Gz.to[0]->textlen;

	size_t
	b=				Gz.to[1]->textlen,
	d=				Gz.to[0]->textsize-
					Gz.to[0]->textlen;

	int		e=
	iconv				(I,&a,&b,&c,&d);
	iconv_close			(I);

	Gz.to[0]->textlen=		(void *)	c-
					(void *)	Gz.to[0]->textaddr;
	Gz.to[0]->textaddr[
	Gz.to[0]->textlen]=		0;

	*Gz.at=				iconvrecode;
	argot_jump			(e==0);
	return;

	fail:
	argot_next			();
	return;
}

SCV	_iconv			(void)
{	__builtin_memcpy	(id.to,Gz.to,sizeof(id.to));
	*Gz.at=			_iconv;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180413",
	.official=	"20180413",
	.update=	"20200625"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_iconv,	"iconv");
	aa		(iconvrecode,	"iconvrecode");
	aa_fini		();
};

