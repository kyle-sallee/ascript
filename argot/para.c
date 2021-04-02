/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"para.h"

/*
OPERATOR	oppara[1];
*/

__attribute__((noinline))
SCV	paracopy_		(void)
{	VMETA		*B=
	parapass		(arga(NULL));
	show			(B);

	VMETA		*A=	Gz.active.para;
	A->datalen=		-1;
/*	Gz.active.para->io.flag&=	~datamapuse;	*/

	memcpya			(A->textaddr
				+A->textlen
				,B->textaddr
				,B->textlen);
	A->textlen+=		 B->textlen;
	argot_next		();
}

__attribute__((noinline))
SCV	paracopylink_		(void)
{	VMETA		*A,*B,*C;
	A=			Gz.active.para;
	B=	C=		Gz.to[0];
	uint8_t		*a=	A->textaddr+
				A->textlen;
	do
	{	show		(B);
		memcpya		(a
				,B->textaddr
				,B->textlen);
		a+=	 	B->textlen;
	}
	while			((B=B->link_next)!=C);
	A->textlen=		a-A->textaddr;
	A->datalen=		-1;
	argot_next		();
}

__attribute__((noinline))
SCV	parazero_		(void)
{	VMETA		*A=	Gz.active.para;
	A->io.flag&=		~datamapuse;
	A->textaddr[
	A->textlen++]=		0;
	argot_next		();
}

__attribute__((always_inline))
static	inline	int	spec	(uint8_t **a,uint8_t b,uint8_t ***c)
{	if		yay	(a[0][b]!=0)
	return			0;

	*a+=			b+1;

	if		yay	(a[0][0]!=0)
	{	**c=		 a[0];
		++*c;
		++*a;
	}
	return			1;
}

SCV	parabare		(void)
{	VMETA		*A=	Gz.active.para;
	A->textlen=		0;
	A->datalen=		-1;
	*Gz.at=			parabare;
	argot_next		();
}

static	inline	int	parafind	(void)
{	VMETA		*A=	Gz.active.para;
	VMETA		*B=	Gz.to[0];
	uint8_t		*a=	A->textaddr;
	uint32_t	r=	A->textlen;
	uint8_t		*b=	B->textaddr;
	uint32_t	c=	B->textlen;
	uint8_t		*f;

	for			(;(r>0)&&(f=memmem(a,r,b,c));a++,r--)
	if			(f==A->textaddr)	return	1;
	else	if		(f[-1]==0)		return	1;

	return			0;
}

SCV			parahave	(void)
{	*Gz.at=		parahave;
	if		(parafind())
	argot_skip	();
	else
	argot_next	();
}

SCV			paralack	(void)
{	*Gz.at=		paralack;
	if		(parafind())
	argot_next	();
	else
	argot_skip	();
}


static	CALIGN	void	para	(void)	{tvarnewab(parainit,para);}

/* to be fast paraomit is not intended */
static		void	paraomit		(void)
{	VMETA		*A=			Gz.active.para,
			*B=
	parapass				(arga(NULL));
	show					(B);

	uint8_t		*a,*b,*d,*f;
	uint32_t	c,e;

	a=	b=	parabyteaddr		(A);
	c=		*parabytelen		(A);

	d=					B->textaddr;
	e=					B->textlen;

	again:
	f=
/*	memmem					(b,c,d,e);	*/
	memmema					(b,c,d,e);
/* is memmema buggy? */

	if				nay	(f==NULL)	goto	miss;
	if				nay	(f==a)		goto	found;
	if				nay	(f[-1]!=0)
	{	b=				f+1;
		c-=				f+1-a;
		goto				again;
	}

	found:
	A->datalen=				-1;
	size_t		g=			A->textaddr+
						A->textlen-
						f-
						e;

	if					(g==0)
	memset					(f,0,0x4);
	else
	memmove					(f,f+e,g);
	A->textlen-=				e;

	*Gz.at=					paraomit;
	argot_next				();
	return;

	miss:
	*Gz.at=					paraomit;
	argot_next				();
}

__attribute__((noinline))
SCV	parawith_		(void)
{	VMETA		*A=	Gz.active.para;
	Gz.active.para=		Gz.to[0];
	argot_next		();
	Gz.active.para=		A;
}

static		void	paracopy	(void)
{	(*Gz.at=	paracopy_)	();
}

static		void	paracopylink	(void)
{	(*Gz.at=	paracopylink_)	();
}

static		void	parazero	(void)
{	(*Gz.at=	parazero_)	();
}


static		void	parawith	(void)
{	(*Gz.at=	parawith_)	();
}


const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180227",
	.official=	"20180227",
	.update=	"20200718"
};

__attribute__((constructor))
SCV	aainit				(void)
{	oppara[0]=			opbyte[0];
	aa_init				();
	aa				(para,		"para");
	aa				(parawith,	"parawith");
	aa				(paraomit,	"paraomit");
	aa				(parabare,	"parabare");
	aa				(parahave,	"parahave");
	aa				(paralack,	"paralack");
	aa				(parazero,	"parazero");
	aa				(paracopylink,	"paracopylink");
	aa				(paracopy,	"paracopy");
	aa_fini				();
};
