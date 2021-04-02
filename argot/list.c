/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"a.h"
#include	"list.h"
#include	"utf8.h"

/*
OPERATOR	oplist[4];
*/

static	CALIGN	uint16_t	bindex	(uint8_t const *a,uint32_t b)
{	__attribute__((aligned(0x10)))
	uint8_t			C[0x10];
	uint8_t	const	*c;
	uint8_t		*d;
	int		e;

	if			(0x10>b)
	{	c=
		d=		C;
		e=		0x10;
		if		(b>8)
		{	memcpy	(d,a,8);
			a+=	8;
			d+=	8;
			b-=	8;
			e=	8;
		}
		if		(b>4)
		{	memcpy	(d,a,4);
			a+=	4;
			d+=	4;
			b-=	4;
			e-=	4;
		}
		for		(;b>0;b--,d++,a++,e--)	*d=	*a;
		for		(;e>0;e--,d++)		*d=	0;
	}
	else
	c=			a;

	return
	bit128_to_bit16		(c);
}

static	inline	void	element_attach	(ELEMENT **a,ELEMENT *b)
{	ELEMENT		**c;
	c=			&a[bindex(b->name,b->size)];
	b->next=		*c;
	*c=			b;
}

static	inline	ELEMENT		*find	(uint8_t *a,uint32_t b, ELEMENT **c)
{	ELEMENT		*E;
	for			(E=c[bindex(a,b)];E;E=E->next)
	if		yay	(E->size==b)
	if		yay	(memcmp(E->name,a,b)==0)
	return			E;
	return			NULL;
}

static	inline	uint8_t		pump	(uint8_t *a,uint32_t b, ELEMENT **c)
{	ELEMENT		*E=
	find			(a,b,c);
	if			(E!=NULL)
	{	E->seen++;
		return		0;
	}
	return			1;
}

SCV	show_list			(VMETA *A)
{	A->show=			NULL;

	if			yay	(A->io.flag&datamapunmap)
	{	A->io.flag&=		~datamapunmap;
		munmap			(A->dataaddr,A->datasize);
	}

	A->io.flag|=			textmapuse;

	LV		*v=
	lv				(A);
	show				(v->host);

	size_t		t=
	ambit_total			(v->host->textaddr,
					 v->host->textlen,
					 v->ambit->textaddr);

	A->value.i=			t;

	map_add				(A,0,
	sizeof				(ELEMENT **)*0x10000+
	sizeof				(ELEMENT)*(t+1));

	uint8_t		*a=		v->host->textaddr;
	uint8_t		*e=		v->host->textlen+a;

	ELEMENT		*E=	ela	(A);
	ELEMENT		**m=	elm	(A);
	uint8_t		*M=		(uint8_t *)	v->ambit->textaddr;
	uint32_t	c;
	E->name=			a;
	while				(e>a)
	{	c=
		utf8_in			(&a);
		if		yay	(M[c]==0)
		continue;
		E->size=		a-E->name;
		element_attach		(m,E++);
		E->name=		a;
	}
/* for sans ambit terminated entry */
/*	c=				E->name-a;
	if			nay	(c!=0)
	E->name=			NULL;
	else
	{	E->size=		c;
		element_attach		(m,E++);
	}
*/

	E->name=			NULL;
}

SCV	show_entire			(VMETA *A)
{	if				(A->io.flag&textmapuse)
	return;
	LSV		*v=
	lsv				(A);
	show				(v->host);
	show				(v->text);

	map_add				(A,v->text->textsize,0);

	uint8_t		*am=		((LV *)(v->host->text))->ambit->
					textaddr;

	uint8_t		*b=		A->textaddr;

	uint8_t		*a=		v->text->textaddr;
	uint8_t		*e=		v->text->textaddr+
					v->text->textlen;
	ELEMENT		E;
	ELEMENT		**m=	elm	(v->host);
	uint32_t	c;
	E.name=				a;
	while				(e>a)
	{	c=
		utf8_in			(&a);
		if		yay	(am[c]==0)		continue;

		/*	unterminated:	*/
		E.size=			a-E.name;
		uint8_t	*d=		E.name;
		E.name=			a;

		if		yay	(pump(d,E.size,m)==0)	continue;

		memcpy			(b,d,E.size);
		b+=			E.size;
	}
/* if not in the ordered list to output immediately send */
/* a sans ambit final entry would be atypical */
/*	if			nay	(a!=E.name)
	goto				unterminated;
*/

	ELEMENT		*F=	ela	(v->host);
	for				(; F->name!=NULL;F++)
	for				(c=F->seen,F->seen=0;c>0;c--)
	{	memcpy			(b,F->name,F->size);
		b+=			F->size;
	}

	A->io.flag|=			textmapuse;
	A->textlen=			b-A->textaddr;
}

SCV	show_single			(VMETA *A)
{	if				(A->io.flag&textmapuse)
	return;
	LSV		*v=
	lsv				(A);
	show				(v->host);
	show				(v->text);

	map_add				(A,
					 v->text->textsize,
					 v->host->datasize);

	uint8_t		*am=		((LV *)(v->host->text))->ambit->
					textaddr;

	uint8_t		*a=		v->text->textaddr;
	uint8_t		*e=		v->text->textaddr+
					v->text->textlen;
	ELEMENT		E;
	ELEMENT		*S=	ela	(A);
	ELEMENT		**sm=	elm	(A);
	ELEMENT		**m=	elm	(v->host);
	uint32_t	c;
	E.name=				a;
	while				(e>a)
	{	c=
		utf8_in			(&a);
		if		yay	(am[c]==0)		continue;

		/*	unterminated:	*/
		E.size=			a-E.name;
		uint8_t	*d=		E.name;
		E.name=			a;

		if		yay	(pump(d,E.size,m)==0)	continue;

		S->name=		d;
		S->size=		E.size;
		S->seen=		1;
		element_attach		(sm,S++);
	}
/* if not in the ordered list to output immediately send */
/* a sans ambit final entry would be atypical */
/*	if			nay	(a!=E.name)
	goto				unterminated;
*/

	uint8_t		*b=		A->textaddr;
	ELEMENT		*F;

	if				(S!=ela(A))
	{	F=		ela	(A);
		for			(;F->name!=NULL;F++)
		if		nay	( F->seen>0)
		{	F->seen=	0;
			memcpy		(b,F->name,F->size);
			b+=		F->size;
		}
	}

	F=			ela	(v->host);
	for				(;F->name!=NULL;F++)
	if			nay	( F->seen>0)
	{	F->seen=		0;
		memcpy			(b,F->name,F->size);
		b+=			F->size;
	}

	A->io.flag|=			textmapuse;
	A->textlen=			b-A->textaddr;
}

SCV	show_unique			(VMETA *A)
{	if				(A->io.flag&textmapuse)
	return;
	LSV		*v=
	lsv				(A);
	show				(v->host);
	show				(v->text);

	map_add				(A,
					 v->text->textsize,
					 v->host->datasize);

	uint8_t		*am=		((LV *)(v->host->text))->ambit->
					textaddr;

	uint8_t		*a=		v->text->textaddr;
	uint8_t		*e=		v->text->textaddr+
					v->text->textlen;
	ELEMENT		E;
	ELEMENT		*S=	ela	(A);
	ELEMENT		**sm=	elm	(A);
	ELEMENT		**m=	elm	(v->host);
	uint32_t	c;
	E.name=				a;
	while				(e>a)
	{	c=
		utf8_in			(&a);
		if		yay	(am[c]==0)		continue;

		/*	unterminated:	*/
		E.size=			a-E.name;
		uint8_t	*d=		E.name;
		E.name=			a;

		if		yay	(find(d,E.size,m)!=NULL)
		continue;

		S->name=		d;
		S->size=		E.size;
		S->seen=		1;
		element_attach		(sm,S++);
	}
/* if not in the ordered list to output immediately send */
/* a sans ambit final entry would be atypical */
/*	if			nay	(a!=E.name)
	goto				unterminated;
*/

	uint8_t		*b=		A->textaddr;
	ELEMENT		*F;

	if				(S!=ela(A))
	{	F=		ela	(A);
		for			(;F->name!=NULL;F++)
		if		nay	( F->seen>0)
		{	F->seen=	0;
			memcpy		(b,F->name,F->size);
			b+=		F->size;
		}
	}

	A->io.flag|=			textmapuse;
	A->textlen=			b-A->textaddr;
}

SCV	equal_list			(void)
{	VMETA		*A=		Gz.to[0];
	A->io.flag&=			~textmapuse;
	if			yay	(A->io.flag&datamapunmap)
	{	A->io.flag&=		~datamapunmap;
		munmap			(A->dataaddr,A->datasize);
	}
	*Gz.at=				equal_list;
	argot_next			();
}

SCV	equal_single			(void)
{	VMETA		*A=		Gz.to[0];
	lsv(A)->text=			Gz.to[1];
	A->io.flag&=			~textmapuse;

	if			yay	(A->io.flag&textmapunmap)
	{	A->io.flag&=		~textmapunmap;
		munmap			(A->textaddr,A->textsize);
	}

	if			yay	(A->io.flag&datamapunmap)
	{	A->io.flag&=		~datamapunmap;
		munmap			(A->dataaddr,A->textsize);
	}

	*Gz.at=				equal_single;
	argot_next			();
}

SCV	equal_entire			(void)
{	VMETA		*A=		Gz.to[0];
	lsv(A)->text=			Gz.to[1];
	A->io.flag&=			~textmapuse;

	if			yay	(A->io.flag&textmapunmap)
	{	A->io.flag&=		~textmapunmap;
		munmap			(A->textaddr,A->textsize);
	}

	*Gz.at=				equal_entire;
	argot_next			();
}

SCV	listambit			(void)
{	lv	(Gz.to[0])->ambit=	Gz.to[1];
	*Gz.at=				listambit;
	argot_next			();
}

SCV	list		(void)	{tsubab(listsubnew,		list);}
SCV	listsingle	(void)	{tsubab(listsinglesubnew,	listsingle);}
SCV	listentire	(void)	{tsubab(listentiresubnew,	listentire);}
SCV	listunique	(void)	{tsubab(listuniquesubnew,	listunique);}

SCV	listnew		(void)
{	Gz.to[0]->show=	show_list;
	*Gz.at=		listnew;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190706",
	.official=	"20190706",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(list,		"list");
	aa		(listambit,	"listambit");
	aa		(listnew,	"listnew");
	aa		(listunique,	"listunique");
	aa		(listentire,	"listentire");
	aa		(listsingle,	"listsingle");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	oplist[0]=
	oplist[1]=
	oplist[2]=
	oplist[3]=			opbyte[0];

	oplist[0].equal=		equal_list;
	oplist[1].equal=
	oplist[3].equal=		equal_single;
	oplist[2].equal=		equal_entire;
}
