/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"

__attribute__((aligned(0x20)))
static		void	ansi	(void)
{	*Gz.at=		ansi;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190516",
	.official=	"20190516",
	.update=	"20200512"
};

__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(ansi,		"ansi");
	aa_fini		();
};

typedef	struct
{	__attribute__((aligned(8)))
	uint8_t		a[0x10],b[8],c,d;
}	CC;

#define	va(a,b)	{	.name=(a),	.len=		strlen(a),	\
			.text=(b),	.textlen=	strlen(b),	\
			.op=		opbyte,				\
			.io.flag=	textmapuse	}

#define	vb(a)			\
	map_init	(A);	\
	vattach_faster	(A,a);	\
	A++

__attribute__((constructor))
static	CALIGN	void	init	(void)
{	static	VMETA		a[0x1f]=
	{	va	("ansi.up",		"\e[1A"),
		va	("ansi.down",		"\e[1B"),
		va	("ansi.fore",		"\e[1C"),
		va	("ansi.back",		"\e[1D"),
		va	("ansi.home",		"\e[H"),
		va	("ansi.save",		"\e[s"),
		va	("ansi.load",		"\e[u"),
		va	("ansi.clear",		"\e[2J"),
		va	("ansi.blank",		"\e[K"),
		va	("ansi.normal",		"\e[0m"),
		va	("ansi.bold",		"\e[1m"),
		va	("ansi.underscore",	"\e[4m"),
		va	("ansi.blink",		"\e[5m"),
		va	("ansi.reverse",	"\e[7m"),
		va	("ansi.conceal",	"\e[8m"),
		va	("ansi.fore.black",	"\e[30m"),
		va	("ansi.fore.red",	"\e[31m"),
		va	("ansi.fore.green",	"\e[32m"),
		va	("ansi.fore.yellow",	"\e[33m"),
		va	("ansi.fore.blue",	"\e[34m"),
		va	("ansi.fore.magenta",	"\e[35m"),
		va	("ansi.fore.cyan",	"\e[36m"),
		va	("ansi.fore.white",	"\e[37m"),
		va	("ansi.back.black",	"\e[40m"),
		va	("ansi.back.red",	"\e[41m"),
		va	("ansi.back.green",	"\e[42m"),
		va	("ansi.back.yellow",	"\e[43m"),
		va	("ansi.back.blue",	"\e[44m"),
		va	("ansi.back.magenta",	"\e[45m"),
		va	("ansi.back.cyan",	"\e[46m"),
		va	("ansi.back.white",	"\e[47m"),
	};

	VMETA		*A=		a;
	vb		("ansi.up");
	vb		("ansi.down");
	vb		("ansi.fore");
	vb		("ansi.back");
	vb		("ansi.home");
	vb		("ansi.save");
	vb		("ansi.load");
	vb		("ansi.clear");
	vb		("ansi.blank");
	vb		("ansi.normal");
	vb		("ansi.bold");
	vb		("ansi.underscore");
	vb		("ansi.blink");
	vb		("ansi.reverse");
	vb		("ansi.conceal");
	vb		("ansi.fore.black");
	vb		("ansi.fore.red");
	vb		("ansi.fore.green");
	vb		("ansi.fore.yellow");
	vb		("ansi.fore.blue");
	vb		("ansi.fore.magenta");
	vb		("ansi.fore.cyan");
	vb		("ansi.fore.white");
	vb		("ansi.back.black");
	vb		("ansi.back.red");
	vb		("ansi.back.green");
	vb		("ansi.back.yellow");
	vb		("ansi.back.blue");
	vb		("ansi.back.magenta");
	vb		("ansi.back.cyan");
	vb		("ansi.back.white");
}
