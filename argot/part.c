/*	By Kyle Sallee in 2015 and 2016 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"int.h"
#include	"a.h"
#include	"part.h"
#include	"utf8.h"

/* part starts stored in *A and the ambit is *b */
SCV	ambit_acquire			(uint8_t *a,size_t t,
					 uint8_t *b,uint32_t *A)
{	uint8_t		*e=		a+t;
	uint8_t		*s=		a;
	uint32_t	c;
	*A++=				0;
	while				(1)
	{	c=	utf8_in		(&a);
		if		yay	(b[c]==0)
		{	if	yay	(e>a)		continue;
			*A=		a-s;
		}
		else
		{	*A++=		a-s;
			if	yay	(e>a)		continue;
		}
		return;
	}
}

__attribute__((always_inline))
static	inline	void	ambit_take	(void)
{	VMETA		*B=		Gz.to[0];
	if				(B->io.flag&datamapunmap)
	munmap				(B->dataaddr,B->datasize);
	B->io.flag&=			~datamapunmap;

	PARTDATA	*P=
	partdata			(B);
	VMETA		*A=		B->host;
	VMETA		*C=		P->ambit;

	size_t		t,T;

	/*	At the start an implicit partition exists.
		At the end   an implicit partition exists.
	*/

	P->now->i=			0;
	P->max->i=
	t=
	ambit_total			(A->textaddr,
					 A->textlen,
					 C->textaddr);
	T=
	sizeof				(uint32_t)*(t+1);

	/* The partition address dataarray in .part is adequately sized */

	B->datasize=			T;
	B->dataaddr=	pool		(T);

	uint32_t	*b=		(uint32_t *)	B->dataaddr;

	ambit_acquire			(A->textaddr,
					 A->textlen,
					 C->textaddr,b);

	B->textaddr=			A->textaddr;
	B->textlen=			b[1]-b[0];
}

SCV	partfind		(void)
{	ambit_take		();
	*Gz.at=			partfind;
	argot_next		();
}

__attribute__((noinline))
SCV	partnext_			(void)
{	VMETA		*B=		Gz.to[0];
	PARTDATA	*P=
	partdata			(B);

	int		d=		P->now->i+1;
	int		f=		P->max->i;

	if			yay	(f>d)
	{	P->now->i=		d;
		argot_skip		();
	}
	else
	{	P->now->i=		0;
		argot_next		();
	}
}

__attribute__((noinline))
SCV	partback_			(void)
{	VMETA		*B=		Gz.to[0];
	PARTDATA	*P=
	partdata			(B);

	int		d=		P->now->i-1;

	if				(d>=0)
	{	P->now->i=		d;
		argot_skip		();
	}
	else
	{	int	f=		P->max->i;
		P->now->i=		f-1;
		argot_next		();
	}
}

static	void	partnext	(void)	{(*Gz.at=partnext_)	();}
static	void	partback	(void)	{(*Gz.at=partback_)	();}

SCV		part		(void)	{tsubab(partsubnew,part);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200808"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(part,		"part");
	aa		(partfind,	"partfind");
	aa		(partback,	"partback");
	aa		(partnext,	"partnext");
	aa_fini		();
};
