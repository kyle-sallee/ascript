/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"top.h"
#include	"utf8.h"

static	CALIGN	int	element_map	(VMETA *A)
{	TSV		*a=		(TSV *)	A->text;

	uint8_t		*t=		a->host->textaddr;
	uint8_t		*T=		a->host->textaddr+
					a->host->textlen;
	uint8_t		*d;
	uint32_t	c;
	uint8_t		*M=		(uint8_t *)	a->ambit->textaddr;
	ELEMENT		*e=	ele	(A);

	while				(1)
	{	while			(T>t)
		{	d=		t;
			c=
			utf8_in		(&t);
			if		(M[c]==0)	break;
		}

		if		nay	(t>=T)
		return			e-
		ele			(A);

		e->a=
		t=			d;
		while			(T>t)
		{	d=		t;
			c=
			utf8_in		(&t);
			if	nay	(M[c]!=0)
			break;
		}
		e->b=			d-e->a;
		e++;
	}
}

static	CALIGN	uint16_t	bindex(uint8_t const *a,uint32_t c)
{	static
	CALIGN
	uint8_t			B[0x20];
	__builtin_memcpy	(B,  a,0x10);
	__builtin_memset	(B+c,0,0x10);
	return
	bit128_to_bit16		(B);
}

SCV	insert				(ELEMENT	*e,
					 TSC		**M,
					 TSC		**Z)
{	uint16_t	i=
	bindex				(e->a,e->b);

	TSC		*N=		M[i];

	for				(;N;N=N->tsm)
	if			nay	(N->b=e->b)
	if			nay	(N->a[0]==e->a[0])
	if			yay	(memcmp(N->a,e->a,e->b)==0)
	{	e->c=			N;
		return;
	}


/*	unmatch:	*/
	N=				*Z;
	e->c=				N;
	(*Z)++;
	N->a=				e->a;
	N->b=				e->b;
	N->tsm=				M[i];
	M[i]=				N;
}

SCV	want			(ELEMENT *e,TSC **Z)
{	WANT		*W=	(WANT *)	*Z;
	(*Z)++;

	W->e=			e;
	W->next=		e[1].c->want;
	e[1].c->want=		W;
}

__attribute__((noinline))
SCV	recur_first		(ELEMENT *e,VMETA *C)
{	errna=			EDEADLOCK;
	e->c->seen=		2;
	__builtin_memcpy	(C->textaddr+C->textlen,"recursion: ",0xb);
	C->textlen+=		0xb;
	memcpya			(C->textaddr+C->textlen,e->a,e->b);
	C->textlen+=		e->b;
	C->textaddr[
	C->textlen++]=		'\n';
}

static		uint8_t	recur		(ELEMENT *e,VMETA *C)
{	if		nay	(e->c->seen==1)
	recur_first		(e,C);
	return			1;
}

__attribute__((noinline))
static	CALIGN	uint8_t	output	(ELEMENT *e,uint8_t **t,VMETA *E, VMETA *C)
{	if		nay	(e->c->seen!=0)
	return	recur		(e,C);

	WANT		*w;
	uint8_t		r=	0;

	for			(e->c->seen=1,
				 w=e->c->want;w;w=w->next)
	{
		if		(w->e->c->sent==0)
		r=	output	(w->e,t,E,C);

		if	nay	(r)
		recur		(e,C);

	}

	e->c->sent=		1;

	memcpya			(*t,e->a,e->b);
	(*t)+=			e->b;
	memcpya			(*t,E->textaddr,E->textlen);
	(*t)+=			E->textlen;

	return			r;
}

SCV	tsort				(VMETA *A)
{	TSC		**M=	tscm	(A);
	TSC		*Z=	tsc	(A);


	ELEMENT		*e=	ele	(A);

	for				(;e->a;e++)
	insert				(e,M,&Z);

	e=			ele	(A);

	for				(;e->a;e+=2)
	if				(e[0].c!=e[1].c)
	want				(e,&Z);

	errna=				0;
	uint8_t		*t=		A->textaddr;
	e=			ele	(A);

	TSV		*a=		(TSV *)	A->text;
	for				(;e->a;e++)
	if				(e->c->sent==0)
	output				(e,&t,a->part,a->fail);

	A->textlen=			t-A->textaddr;
}

static	CALIGN	int32_t	gloss		(VMETA *A)
{	TSV		*a=		(TSV *)	A->text;
	return
	ambit_total			(a->host->textaddr,
					 a->host->textlen,
					 a->ambit->textaddr);
}

SCV	show_top			(VMETA *A)
{	A->show=			NULL;
	if				(A->io.flag&textmapunmap)
	munmap				(A->textaddr,A->textsize);

	TSV		*a=		(TSV *)	A->text;
	map_add				(A,a->host->textsize,0);

	A->value.i=
	gloss				(A);

	size_t		b=
	sizeof				(TSC *)		* 0x10000+
	sizeof				(ELEMENT)	* 2*A->value.i+
	sizeof				(TSC)		* 3*A->value.i;

	A->datasize=			b;
	A->dataaddr=
	pps				(b);

	int
	ec=
	element_map			(A);

	if			nay	((ec==0)||(ec&1))
	{	munmap			(A->dataaddr,A->datasize);
		A->io.success=
		errna=			EIO;
		memcpy			(a->fail->textaddr,"unpaired input\n",
					 a->fail->textlen=0xf);
		return;
	}

	tsort				(A);
	A->io.flag|=			textmapuse;
	munmap				(A->dataaddr,A->datasize);
}

SCV	topambit		(void)
{	VMETA		*A=	Gz.to[0];
	TSV		*a=	(TSV *)	A->text;
	VMETA		*B=	Gz.to[1];
	if			(B->op!=opambit)
	a->host=		B;
	else
	a->ambit=		B;
	A->io.flag&=		~textmapuse;
	*Gz.at=			topambit;
	argot_next		();
}

SCV	top	(void)	{tsubab(topsubnew,top);}

SCV	topnew			(void)
{
/*	Gz.to[0]->io.flag&=	~textmapuse;	*/
	Gz.to[0]->show=		show_top;
	*Gz.at=			topnew;
	argot_next		();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180516",
	.official=	"20180516",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(top,		"top");
	aa		(topambit,	"topambit");
	aa		(topnew,	"topnew");
	aa_fini		();
};
