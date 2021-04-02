/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"a.h"
#include	<libgen.h>
#include	<libintl.h>
#include	<locale.h>
#include	<string.h>

/*
OPERATOR	oplc	[1];
*/

#define	namelenval(z)	.name=#z, .len=strlen(#z), .value.i=(z), .op=opbyte,
#define	namelen(z)	.name=z,  .len=strlen(z),		 .op=opbyte, .io.flag=textmapuse

VMETA		lcv	[0x10]=
{	{.name="LC",
	 .len=2,
	 .op=opbyteconst,
	 .io.flag=textmapuse},
	{namelen("LC_DOMAIN_DIR"),	.value.i=-1,.text="/usr/share/locale"},
	{namelen("LC_DOMAIN_NAME"),	.value.i=-1},

	{namelenval(LC_ALL)},
	{namelenval(LC_ADDRESS)},
	{namelenval(LC_COLLATE)},
	{namelenval(LC_CTYPE)},
	{namelenval(LC_IDENTIFICATION)},
	{namelenval(LC_MEASUREMENT)},
	{namelenval(LC_MESSAGES)},
	{namelenval(LC_MONETARY)},
	{namelenval(LC_NAME)},
	{namelenval(LC_NUMERIC)},
	{namelenval(LC_PAPER)},
	{namelenval(LC_TELEPHONE)},
	{namelenval(LC_TIME)},
};

__attribute__((noinline))
SCV	revise_lcv		(VMETA *A)
{	if			(A->value.i>=0)
	setlocale		(A->value.i,A->textaddr);
	else
	bindtextdomain		(
	textdomain		(lcv[2].textaddr),
				 lcv[1].textaddr);
}

__attribute__((noinline))
SCV	LC_			(void)
{	VMETA		*A=
	parapass		(arga(NULL));
	show			(A);

	char		*a=
	gettext			(A->textaddr);

	uint8_t		b;
	uint32_t	c;

	if			(a!=(char *)A->textaddr)
	{	b=		0;
		c=	strlen	(a);
	}
	else
	{	b=		ENOMSG;
		c=		A->textlen;
	}

	lcv[0].io.success=
	errna=			b;
	lcv[0].textaddr=	a;
	lcv[0].textlen=		c;
	argot_next		();
}

#include	<stdlib.h>	/* for getenv */

SCV	show_lcv			(VMETA *A)
{	A->io.flag|=			textmapuse;
	if				(A->textlen)
	return;

	uint8_t		*b=
	getenv				(A->name);
	if			yay	(b==NULL)
	return;

	A->textlen=
	strlenb				(b);
	memcpya				(A->textaddr,b,
					 A->textlen);
	A->textaddr[
	A->textlen]=			0;
}

static	void	LC		(void)	{(*Gz.at=LC_)		();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20181011",
	.official=	"20181011",
	.update=	"20200924"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(LC,	"LC");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{
/*	oplc[0]=			opbyte[0];
*/

	map_init			(lcv+0x0);
	vattach_faster			(lcv+0x0,"LC");
	map_init			(lcv+0x1);
	vattach_faster			(lcv+0x1,"LC_DOMAIN_DIR");
	map_init			(lcv+0x2);
	vattach_faster			(lcv+0x2,"LC_DOMAIN_NAME");
	map_init			(lcv+0x3);
	vattach_faster			(lcv+0x3,"LC_ALL");
	map_init			(lcv+0x4);
	vattach_faster			(lcv+0x4,"LC_ADDRESS");
	map_init			(lcv+0x5);
	vattach_faster			(lcv+0x5,"LC_COLLATE");
	map_init			(lcv+0x6);
	vattach_faster			(lcv+0x6,"LC_CTYPE");
	map_init			(lcv+0x7);
	vattach_faster			(lcv+0x7,"LC_IDENTIFICATION");
	map_init			(lcv+0x8);
	vattach_faster			(lcv+0x8,"LC_MEASUREMENT");
	map_init			(lcv+0x9);
	vattach_faster			(lcv+0x9,"LC_MESSAGES");
	map_init			(lcv+0xa);
	vattach_faster			(lcv+0xa,"LC_MONETARY");
	map_init			(lcv+0xb);
	vattach_faster			(lcv+0xb,"LC_NAME");
	map_init			(lcv+0xc);
	vattach_faster			(lcv+0xc,"LC_NUMERIC");
	map_init			(lcv+0xd);
	vattach_faster			(lcv+0xd,"LC_PAPER");
	map_init			(lcv+0xe);
	vattach_faster			(lcv+0xe,"LC_TELEPHONE");
	map_init			(lcv+0xf);
	vattach_faster			(lcv+0xf,"LC_TIME");

	int		a;
	for				(a=1;0x10>a;a++)
	{	lcv[a].revise=	revise_lcv;
		lcv[a].show=	show_lcv;
	}

	uint8_t		*c,*d;
	for				(c=Gz.arg.v[1]+1,
					 d=Gz.arg.v[1];*c!=0;c++)
	if			nay	(*c=='/')
	d=				c+1;

	size_t		e=
	lcv[2].textlen=			c-d;
	memcpya				(lcv[2].text,d,e);

	setlocale			(LC_ALL,"");
	bindtextdomain			(lcv[2].text,NULL);
	textdomain			(lcv[2].text);
}
