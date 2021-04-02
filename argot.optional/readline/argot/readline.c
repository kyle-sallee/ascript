/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"


#include	<stdlib.h>
#include	<stdio.h>
#include	<readline/readline.h>
#include	<readline/history.h>

SCV	rl			(void)
{	VLESS		*a,*b;
	argarange		(NULL,&a,&b);

	uintptr_t	c=	b-a;
	uint8_t 	*d;

	if			(c==2)
	{	VMETA	*B=
		parapass	(b-1);
		show		(B);
		d=		B->textaddr;
	}
	else	if		(c==1)
	d=			NULL;
	else	goto		done;

	uint8_t		*e=
	readline		(d);

	VMETA		*A=
	parapass		(a);

	size_t		f=
	strlenb			(e);

	text_check		(A,f+1);
	memcpy			(A->textaddr
				+A->textlen
				,e
				,f+1);
	A->textlen+=		f;
	free			(e);
	done:
	*Gz.at=			rl;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190704",
	.official=	"20180704",
	.update=	"20200926"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(rl,	"readline");
	aa_fini		();
};
