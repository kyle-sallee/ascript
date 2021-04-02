/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"
#include	"mdk.h"
#include	<endian.h>

__attribute__((always_inline))
static	inline	uint64_t	rol1	(uint64_t a)
{	return			(a<<1)+(a>>0x3f);
}

__attribute__((always_inline))
static	inline	uint64_t	eat	(uint64_t a,uint64_t b,uint64_t c)
{	a^=				b;
	a-=				b;
	a=	rol1			(a);
	a^=				c;
	a-=				c;
	return				a;
}

__attribute__((always_inline))
static	inline	uint64_t	eat0x40	(uint64_t a,uint64_t b,uint64_t *c)
{	a=	eat	(a,b+0x00,htole64(*(c+0x00)));
	a=	eat	(a,b+0x01,htole64(*(c+0x01)));
	a=	eat	(a,b+0x02,htole64(*(c+0x02)));
	a=	eat	(a,b+0x03,htole64(*(c+0x03)));
	a=	eat	(a,b+0x04,htole64(*(c+0x04)));
	a=	eat	(a,b+0x05,htole64(*(c+0x05)));
	a=	eat	(a,b+0x06,htole64(*(c+0x06)));
	a=	eat	(a,b+0x07,htole64(*(c+0x07)));
	a=	eat	(a,b+0x08,htole64(*(c+0x08)));
	a=	eat	(a,b+0x09,htole64(*(c+0x09)));
	a=	eat	(a,b+0x0a,htole64(*(c+0x0a)));
	a=	eat	(a,b+0x0b,htole64(*(c+0x0b)));
	a=	eat	(a,b+0x0c,htole64(*(c+0x0c)));
	a=	eat	(a,b+0x0d,htole64(*(c+0x0d)));
	a=	eat	(a,b+0x0e,htole64(*(c+0x0e)));
	a=	eat	(a,b+0x0f,htole64(*(c+0x0f)));
	a=	eat	(a,b+0x10,htole64(*(c+0x10)));
	a=	eat	(a,b+0x11,htole64(*(c+0x11)));
	a=	eat	(a,b+0x12,htole64(*(c+0x12)));
	a=	eat	(a,b+0x13,htole64(*(c+0x13)));
	a=	eat	(a,b+0x14,htole64(*(c+0x14)));
	a=	eat	(a,b+0x15,htole64(*(c+0x15)));
	a=	eat	(a,b+0x16,htole64(*(c+0x16)));
	a=	eat	(a,b+0x17,htole64(*(c+0x17)));
	a=	eat	(a,b+0x18,htole64(*(c+0x18)));
	a=	eat	(a,b+0x19,htole64(*(c+0x19)));
	a=	eat	(a,b+0x1a,htole64(*(c+0x1a)));
	a=	eat	(a,b+0x1b,htole64(*(c+0x1b)));
	a=	eat	(a,b+0x1c,htole64(*(c+0x1c)));
	a=	eat	(a,b+0x1d,htole64(*(c+0x1d)));
	a=	eat	(a,b+0x1e,htole64(*(c+0x1e)));
	a=	eat	(a,b+0x1f,htole64(*(c+0x1f)));
	a=	eat	(a,b+0x20,htole64(*(c+0x20)));
	a=	eat	(a,b+0x21,htole64(*(c+0x21)));
	a=	eat	(a,b+0x22,htole64(*(c+0x22)));
	a=	eat	(a,b+0x23,htole64(*(c+0x23)));
	a=	eat	(a,b+0x24,htole64(*(c+0x24)));
	a=	eat	(a,b+0x25,htole64(*(c+0x25)));
	a=	eat	(a,b+0x26,htole64(*(c+0x26)));
	a=	eat	(a,b+0x27,htole64(*(c+0x27)));
	a=	eat	(a,b+0x28,htole64(*(c+0x28)));
	a=	eat	(a,b+0x29,htole64(*(c+0x29)));
	a=	eat	(a,b+0x2a,htole64(*(c+0x2a)));
	a=	eat	(a,b+0x2b,htole64(*(c+0x2b)));
	a=	eat	(a,b+0x2c,htole64(*(c+0x2c)));
	a=	eat	(a,b+0x2d,htole64(*(c+0x2d)));
	a=	eat	(a,b+0x2e,htole64(*(c+0x2e)));
	a=	eat	(a,b+0x2f,htole64(*(c+0x2f)));
	a=	eat	(a,b+0x30,htole64(*(c+0x30)));
	a=	eat	(a,b+0x31,htole64(*(c+0x31)));
	a=	eat	(a,b+0x32,htole64(*(c+0x32)));
	a=	eat	(a,b+0x33,htole64(*(c+0x33)));
	a=	eat	(a,b+0x34,htole64(*(c+0x34)));
	a=	eat	(a,b+0x35,htole64(*(c+0x35)));
	a=	eat	(a,b+0x36,htole64(*(c+0x36)));
	a=	eat	(a,b+0x37,htole64(*(c+0x37)));
	a=	eat	(a,b+0x38,htole64(*(c+0x38)));
	a=	eat	(a,b+0x39,htole64(*(c+0x39)));
	a=	eat	(a,b+0x3a,htole64(*(c+0x3a)));
	a=	eat	(a,b+0x3b,htole64(*(c+0x3b)));
	a=	eat	(a,b+0x3c,htole64(*(c+0x3c)));
	a=	eat	(a,b+0x3d,htole64(*(c+0x3d)));
	a=	eat	(a,b+0x3e,htole64(*(c+0x3e)));
	a=	eat	(a,b+0x3f,htole64(*(c+0x3f)));
	return		a;
}

/*
__attribute__((unused))
static	inline	uint64_t	rol1_old	(uint64_t a)
{	uint64_t		b=	(a&0x8000000000000000)!=0;
	return			(a<<1)+b;
}
*/

SCV	reval_mdk				(VMETA *B)
{	show					(B->host);
	VMETA		*A=			 B->host;
	uint64_t	a=			-1;
	uint64_t	b=			0;
	uint64_t	*c=			(uint64_t *)	A->textaddr;
	void		*v=			(void *)	A->textaddr+
								(A->textlen
								 &~7);
	uint64_t	*e=			v;

	for					(;e>(c+0x40);c+=0x40,b+=0x40)
	a=	eat0x40				(a,b,c);

	for					(;e>c;c++,b++)
	a=	eat				(a,b,htole64(*c));

	uint64_t		f=		A->textlen&7;
	if				yay	(f)
	{	uint64_t	g=		0;
		switch				(f)
		{	case	1:	__builtin_memcpy	(&g,c,1);break;
			case	2:	__builtin_memcpy	(&g,c,2);break;
			case	3:	__builtin_memcpy	(&g,c,3);break;
			case	4:	__builtin_memcpy	(&g,c,4);break;
			case	5:	__builtin_memcpy	(&g,c,5);break;
			case	6:	__builtin_memcpy	(&g,c,6);break;
			case	7:	__builtin_memcpy	(&g,c,7);break;
		}
		a=	eat			(a,b,htole64(g));
	}

	B->value.i=				a;
}

SCV	mdk	(void)	{tsubab(mdksubnew,mdk);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180902",
	.official=	"20180902",
	.update=	"20200815"
};

#include	<dlfcn.h>
__attribute__((constructor))
SCV	aainit			(void)
{	aa_init			();
	aa			(mdk,	"mdk");
	aa_fini			();
};
