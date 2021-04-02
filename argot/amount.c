/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"amount.h"
#include	"a.h"
#include	"utf8.h"

SCV	amountbytereset	(void)
{	__builtin_memset(Gz.to[0]->dataaddr,0,0x100*sizeof(uint32_t));
	*Gz.at=		amountbytereset;
	argot_next	();
}

SCV	amountbytecount		(void)
{	VMETA		*B=	Gz.to[0];
	uint32_t	*b=
	amountdata		(B);
	VMETA		*A=	B->host;
	uint8_t		*a=	A->textaddr;
	uint64_t	c=	A->textlen;

	for			(;c>=0x40;a+=0x40,c-=0x40)
	{	b[a[0x00]]++;	b[a[0x01]]++;	b[a[0x02]]++;	b[a[0x03]]++;
		b[a[0x04]]++;	b[a[0x05]]++;	b[a[0x06]]++;	b[a[0x07]]++;
		b[a[0x08]]++;	b[a[0x09]]++;	b[a[0x0a]]++;	b[a[0x0b]]++;
		b[a[0x0c]]++;	b[a[0x0d]]++;	b[a[0x0e]]++;	b[a[0x0f]]++;
		b[a[0x10]]++;	b[a[0x11]]++;	b[a[0x12]]++;	b[a[0x13]]++;
		b[a[0x14]]++;	b[a[0x15]]++;	b[a[0x16]]++;	b[a[0x17]]++;
		b[a[0x18]]++;	b[a[0x19]]++;	b[a[0x1a]]++;	b[a[0x1b]]++;
		b[a[0x1c]]++;	b[a[0x1d]]++;	b[a[0x1e]]++;	b[a[0x1f]]++;
		b[a[0x20]]++;	b[a[0x21]]++;	b[a[0x22]]++;	b[a[0x23]]++;
		b[a[0x24]]++;	b[a[0x25]]++;	b[a[0x26]]++;	b[a[0x27]]++;
		b[a[0x28]]++;	b[a[0x29]]++;	b[a[0x2a]]++;	b[a[0x2b]]++;
		b[a[0x2c]]++;	b[a[0x2d]]++;	b[a[0x2e]]++;	b[a[0x2f]]++;
		b[a[0x30]]++;	b[a[0x31]]++;	b[a[0x32]]++;	b[a[0x33]]++;
		b[a[0x34]]++;	b[a[0x35]]++;	b[a[0x36]]++;	b[a[0x37]]++;
		b[a[0x38]]++;	b[a[0x39]]++;	b[a[0x3a]]++;	b[a[0x3b]]++;
		b[a[0x3c]]++;	b[a[0x3d]]++;	b[a[0x3e]]++;	b[a[0x3f]]++;
	}

	if			(c>=0x20)
	{	c-=		    0x20;
		b[a[0x00]]++;	b[a[0x01]]++;	b[a[0x02]]++;	b[a[0x03]]++;
		b[a[0x04]]++;	b[a[0x05]]++;	b[a[0x06]]++;	b[a[0x07]]++;
		b[a[0x08]]++;	b[a[0x09]]++;	b[a[0x0a]]++;	b[a[0x0b]]++;
		b[a[0x0c]]++;	b[a[0x0d]]++;	b[a[0x0e]]++;	b[a[0x0f]]++;
		b[a[0x10]]++;	b[a[0x11]]++;	b[a[0x12]]++;	b[a[0x13]]++;
		b[a[0x14]]++;	b[a[0x15]]++;	b[a[0x16]]++;	b[a[0x17]]++;
		b[a[0x18]]++;	b[a[0x19]]++;	b[a[0x1a]]++;	b[a[0x1b]]++;
		b[a[0x1c]]++;	b[a[0x1d]]++;	b[a[0x1e]]++;	b[a[0x1f]]++;
		a+=		0x20;
	}

	if			(c>=0x10)
	{	c-=		    0x10;
		b[a[0x00]]++;	b[a[0x01]]++;	b[a[0x02]]++;	b[a[0x03]]++;
		b[a[0x04]]++;	b[a[0x05]]++;	b[a[0x06]]++;	b[a[0x07]]++;
		b[a[0x08]]++;	b[a[0x09]]++;	b[a[0x0a]]++;	b[a[0x0b]]++;
		b[a[0x0c]]++;	b[a[0x0d]]++;	b[a[0x0e]]++;	b[a[0x0f]]++;
		a+=		0x10;
	}

	if			(c>=8)
	{	c-=		    8;
		b[a[0x00]]++;	b[a[0x01]]++;	b[a[0x02]]++;	b[a[0x03]]++;
		b[a[0x04]]++;	b[a[0x05]]++;	b[a[0x06]]++;	b[a[0x07]]++;
		a+=		    8;
	}

	if			(c>=4)
	{	c-=		    4;
		b[a[0x00]]++;	b[a[0x01]]++;	b[a[0x02]]++;	b[a[0x03]]++;
		a+=		4;
	}

	if			(c>=2)
	{	c-=		    2;
		b[a[0x00]]++;	b[a[0x01]]++;
		a+=		    2;
	}

	if			(c==1)
	b[a[0]]++;

	*Gz.at=			amountbytecount;
	argot_next		();
}

SCV	amountbyteselect	(void)
{	uint8_t		d=	Gz.to[1]->textaddr[0];
	VMETA		*B=	Gz.to[0];
	uint32_t		*b=
	amountdata		(B);
	B->value.i=		b[d];
	*Gz.at=			amountbyteselect;
	argot_next		();
}

SCV	amountutf8reset	(void)
{	madvise		(Gz.to[0]->dataaddr,
			 Gz.to[0]->datasize,MADV_DONTNEED);
	*Gz.at=		amountutf8reset;
	argot_next	();
}

SCV	amountutf8count			(void)
{	VMETA		*B=		Gz.to[0];
	uint32_t	*b=
	amountdata			(B);
	VMETA		*A=		B->host;
	uint8_t		*a=		A->textaddr;
	uint64_t	c=		A->textlen;
	uint8_t		*d=		a+c;

	while				((d-a)>=0x100)
	{	b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;

		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;

		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;

		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
		b[utf8_in(&a)]++;	b[utf8_in(&a)]++;
	}

	while				(d>a)
	b[utf8_in(&a)]++;

	*Gz.at=				amountutf8count;
	argot_next			();
}

SCV	amountutf8select	(void)
{	uint8_t		*c=	Gz.to[1]->textaddr;
	uint32_t	d=	utf8_in(&c);
	VMETA		*B=	Gz.to[0];
	uint32_t		*b=
	amountdata		(B);
	B->value.i=		b[d];
	*Gz.at=			amountutf8select;
	argot_next		();
}

SCV	amountwordcount			(void)
{	VMETA		*B=		Gz.to[0];
	VMETA		*A=		B->host;
	uint8_t		*a=		A->textaddr;
	uint8_t		*b=		A->textaddr+
					A->textlen;
	uint32_t	c=		0;

	space:
	while				(b>a)
	if			yay	(*a++>0x20)
	goto				word;
	goto				done;

	word:
	c++;
	while				(b>a)
	if			nay	(0x21>*a++)
	goto				space;

	done:
	B->value.i+=			c;
	*Gz.at=				amountwordcount;
	argot_next			();
	return;
}

SCV	amountwordreset		(void)
{	Gz.to[0]->value.i=	0;
	*Gz.at=			amountwordreset;
	argot_next		();
}

SCV	amountbyte	(void)	{tsubab(amountbytesubnew,amountbyte);}
SCV	amountutf8	(void)	{tsubab(amountutf8subnew,amountutf8);}
SCV	amountword	(void)	{tsubab(amountwordsubnew,amountword);}
SCV	amount		(void)	{*Gz.at=amount;argot_next();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190916",
	.official=	"20190916",
	.update=	"20200719"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(amount,		"amount");

	aa		(amountbyte,		"amountbyte");
	aa		(amountbytecount,	"amountbytecount");
	aa		(amountbytereset,	"amountbytereset");
	aa		(amountbyteselect,	"amountbyteselect");

	aa		(amountutf8,		"amountutf8");
	aa		(amountutf8count,	"amountutf8count");
	aa		(amountutf8reset,	"amountutf8reset");
	aa		(amountutf8select,	"amountutf8select");

	aa		(amountword,		"amountword");
	aa		(amountwordcount,	"amountwordcount");
	aa		(amountwordreset,	"amountwordreset");
	aa_fini		();
};
