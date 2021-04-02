/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#ifndef		_A_BSORT_H
#define		_A_BSORT_H

#ifndef		_GNU_SOURCE
#define		_GNU_SOURCE
#endif
#include	"ascript.h"
#include	"ksort.h"

/* By S the sorted list tail is appended */
static	SORT_INDEX		*S;

__attribute__((always_inline))
static	inline	void	sappend		(SORT_INDEX *A)
{	S->next=	A;
	S=		A;
}

SCV	bcmp0	(SORT_INDEX *, uint32_t);
SCV	bcmp1	(SORT_INDEX *, uint32_t);
SCV	bcmp2	(SORT_INDEX *, uint32_t);
SCV	bcmp3	(SORT_INDEX *, uint32_t);
SCV	bcmp4	(SORT_INDEX *, uint32_t);
SCV	bcmp5	(SORT_INDEX *, uint32_t);
SCV	bcmp6	(SORT_INDEX *, uint32_t);
SCV	bcmp7	(SORT_INDEX *, uint32_t);
SCV	bcmpx	(SORT_INDEX *, uint32_t);

__attribute__((noinline))
SCV	bcmpx				(SORT_INDEX *a, uint32_t b)
{	SORT_INDEX	*A,
			*B=		NULL,
			*C=		a,
			*D;
	b++;

	do
	if				(C->len>b)
	{	D=			C->next;
		C->next=		B;
		B=			C;
		C=			D;
	}
	else
	goto				have_a;
	while				(C!=NULL);

	bcmp7				(B,b);
	return;

	have_a:
	A=				C;
	C=				C->next;
	while				(C!=NULL)
	if				(C->len>b)
	{	D=			C->next;
		C->next=		B;
		B=			C;
		C=			D;
	}
	else
	{	A->again++;
		C=			C->next;
	}

	sappend				(A);

	if				(B      !=NULL)
	{	if			(B->next!=NULL)
		bcmp7			(B,b);
		else
		sappend			(B);
	}
}

__attribute__((always_inline))
static	inline	void	bcmpi		(SORT_INDEX *a, uint32_t b,uint8_t c,
					void (*d)(SORT_INDEX *,uint32_t))
{
/* a has at least two linked */

	SORT_INDEX	*A,
			*B,
			*C,
			*D,
			*E;

	C=				a;
	if				((*(uint8_t *)(C->text+b)&c)==0)
	goto				have_a;
	else
	goto				have_b;

	do
	if				((*(uint8_t *)(C->text+b)&c)==0)
	{	have_a:
		E=			C;
		C=			C->next;
	}
	else
	{	E->next=		NULL;
		A=			a;
		D=			C->next;
		C->next=		NULL;
		B=			C;
		goto			have_both;
	}
	while				(C!=NULL);

	d				(a,b);
	return;

	do
	if				((*(uint8_t *)(C->text+b)&c)!=0)
	{	have_b:
		E=			C;
		C=			C->next;
	}
	else
	{	E->next=		NULL;
		B=			a;
		D=			C->next;
		C->next=		NULL;
		A=			C;
		goto			have_both;
	}
	while				(C!=NULL);

	d				(a,b);
	return;

	have_both:
	while				(D!=NULL)
	{	C=			D;
		D=			D->next;
		if			((*(uint8_t *)(C->text+b)&c)==0)
		{	C->next=	A;
			A=		C;
		}
		else
		{	C->next=	B;
			B=		C;
		}
	}

	if			nay	(A->next==NULL)
	{	sappend			(A);
		if			(B->next!=NULL)
		d			(B,b);
		else
		sappend			(B);
	}
	else
	{	d			(A,b);
		if			(B->next!=NULL)
		d			(B,b);
		else
		sappend			(B);
	}
}

#define	SCVNI	__attribute__((noinline))	static	CALIGN	void

SCVNI	bcmp0	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x01,bcmpx);}
SCVNI	bcmp1	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x02,bcmp0);}
SCVNI	bcmp2	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x04,bcmp1);}
SCVNI	bcmp3	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x08,bcmp2);}
SCVNI	bcmp4	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x10,bcmp3);}
SCVNI	bcmp5	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x20,bcmp4);}
SCVNI	bcmp6	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x40,bcmp5);}
SCVNI	bcmp7	(SORT_INDEX *a, uint32_t b)	{bcmpi	(a,b,0x80,bcmp6);}

__attribute__((unused))
static	CALIGN	SORT_INDEX	*bsort	(SORT_INDEX *v,uint32_t b)
{	SORT_INDEX		s;
	S=			&s;

	if			(v[b-1].len==0)
	{	v[b-2].next=	NULL;
		s.next=		&v[b-1];
		S=		S->next;
	}

	bcmp7			(v,0);
	return			s.next;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint32_t	indexb	(VMETA			*A,
					 SORT_INDEX		*i,
					 uint8_t	const	sep)
{	uint8_t			*a=	A->textaddr;
	size_t			T=	A->textlen;
	SORT_INDEX *	const	I=	i;
	uint8_t		const	*E=	a+T;

	uintptr_t		f=	0;	/* empty line count */
	uint32_t		b=	0;

	while				(E>a)
	{	i->text=		a;
		for			(i->text=a;*a!=sep;a++);
		b=			(void *)	a-	i->text;
		a++;
		if			(b!=0)
		{	i->len=		b;
			i->next=	i+1;
			i++;
		}
		else	f++;
	}

	if				(f!=0)
	{	i->text=		a;
		i->len=			0;
		i->again=		f-1;
		i++;
	}
	else	i[-1].next=		NULL;
	return				i-I;
}

__attribute__((noinline))
__attribute__((unused))
static	CALIGN	void	neworderb	(VMETA *A,SORT_INDEX *i,uint8_t sep)
{	uint8_t		*a;
	int32_t		b;

	for				(a=A->textaddr;i;i=i->next)
	for				(b=i->again;b>=0;b--)
	{	memcpya			(a,i->text,i->len);
		a+=			i->len;
		*a++=			sep;
	}

	A->textlen=			a-A->textaddr;
}
#endif
