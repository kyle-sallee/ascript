/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"magic.h"
#include	"a.h"

__attribute__((always_inline))
static	inline	void	show_size	(VMETA *A,uint8_t const *b)
{	size_t		a;
	if				(b!=NULL)
	{	a=	strlenb		(b);
		memcpyb			(A->textaddr,b,a);
	}
	else
	a=				0;
	A->textlen=			a;
}

SCV	show_byte			(VMETA *B)
{	VMETA		*A=		B->host;
	show				(A);
	if			nay	(B->io.flag&datamapuse)
	magic_load			(B->value.p,NULL);

	uint8_t	const	*b=
	magic_buffer			(B->value.p,
					 A->textaddr,
					 A->textlen);
	show_size			(B,b);
}

SCV	show_dub			(VMETA *B)
{	VMETA		*A=		B->host;
/*	denwant				(A);	*/
	if			nay	(B->io.flag&datamapuse)
	magic_load			(B->value.p,NULL);
	uint8_t	const	*b=
	magic_descriptor		(B->value.p,A->value.i);
	show_size			(B,b);
}

SCV	show_name			(VMETA *B)
{	VMETA		*A=		B->host;
	show				(A);
	if			nay	(B->io.flag&datamapuse)
	magic_load			(B->value.p,NULL);

	uint8_t	const	*b=
	magic_file			(B->value.p,A->textaddr);
	show_size			(B,b);
}

__attribute__((always_inline))
static	inline	void	show_pair	(VMETA *C,int b)
{	VMETA		*B=		C->host;
	magic_setflags			(B->value.p,MAGIC_DEFAULT|b);
	B->show			(B);
	C->textaddr=			B->textaddr;
	C->textlen=			B->textlen;
}

SCV	show_all	(VMETA *C)
{	show_pair	(C,MAGIC_CONTINUE);
}

SCV	show_apple	(VMETA *C)
{	show_pair	(C,MAGIC_APPLE);
}

SCV	show_mime	(VMETA *C)
{	show_pair	(C,MAGIC_MIME);
}

SCV	show_text	(VMETA *C)
{	show_pair	(C,0);
}

SCV	show_error			(VMETA *C)
{	VMETA		*B=		C->host;
	uint8_t	const	*a=
	magic_error			(B->value.p);

	if				(a!=NULL)
	{	C->textlen=
		strlenb			(a);
		memcpyb			(C->textaddr,a,C->textlen);
	}
	else
	C->textlen=			0;
}

SCV	magicload			(void)
{	VMETA		*B=		Gz.to[0],
			*C=		Gz.to[1];

	int		a=
	magic_load			(B->value.p,C->textaddr);

	B->io.flag|=			datamapuse;
	*Gz.at=				magicload;
	argot_jump			(a==0);
}

SCV	magicbyte	(void){tsubab(magicbytesubnew,	magicbyte);}
SCV	magicdub	(void){tsubab(magicdubsubnew,	magicdub);}
SCV	magicname	(void){tsubab(magicnamesubnew,	magicname);}
SCV	magicall	(void){tsubab(magicallsubnew,	magicall);}
SCV	magicapple	(void){tsubab(magicapplesubnew,	magicapple);}
SCV	magicerror	(void){tsubab(magicerrorsubnew,	magicerror);}
SCV	magicmime	(void){tsubab(magicmimesubnew,	magicmime);}
SCV	magictext	(void){tsubab(magictextsubnew,	magictext);}

static		void	magic	(void)
{	*Gz.at=		magic;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190709",
	.official=	"20190709",
	.update=	"20200925"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(magicbyte,	"magicbyte");
	aa		(magicdub,	"magicdub");
	aa		(magicname,	"magicname");
	aa		(magicall,	"magicall");
	aa		(magicapple,	"magicapple");
	aa		(magicerror,	"magicerror");
	aa		(magicmime,	"magicmime");
	aa		(magictext,	"magictext");
	aa		(magic,		"magic");
	aa		(magicload,	"magicload");
	aa_fini		();
};
