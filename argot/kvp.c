/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"kvp.h"
#include	"a.h"

/*
OPERATOR	opkvp[3];
*/

static	VMETA	*K;

SCV	kvpwith		(void)
{	VMETA	*k=	K;
	K=		Gz.to[0];
	*Gz.at=		kvpwith;
	argot_next	();
	K=		k;
}

static		ELEMENT	*find		(KVPD *,VMETA *);
static		ELEMENT	*make		(KVPD *,VMETA *);
static		void	val_append	(ELEMENT *, VMETA *);
static		void	val_equal	(ELEMENT *, VMETA *);
static		void	replace		(KVPD *,ELEMENT *);
static		void	unplace		(KVPD *,ELEMENT *);

__attribute__((always_inline))
static	inline	void	element_new	(KVPD *D,ELEMENT *E,VMETA *A)
{	if			(E->with!=NULL)
	return;

	ssize_t		s=	(A->textlen+PAGE-1)&~(PAGE-1);

	void		*v=
	pps			(PAGE+s);

	ELEMENT		*w=
	E->with=		v;
	w->text=		v+PAGE;
	w->size=		s;
	w->with=		E;
	w->link=		D->chain;
	D->chain=		w;
}

SCV	kvpnew				(void)
{	VMETA		*A=		K;
	VMETA		*B=		Gz.to[0];
	VMETA		*C=		Gz.to[1];

	KVPD		*K=	keys	(A);
	KVPD		*V=	vals	(A);

	ELEMENT		*k=
	make				(K,B);

	element_new			(V,k,C);

	val_append			(k->with,C);
	replace				(V,k->with);
	*Gz.at=			kvpnew;
	argot_next			();
}

SCV	kvpset				(void)
{	VMETA		*A=		K;
	VMETA		*B=		Gz.to[0];
	VMETA		*C=		Gz.to[1];

	KVPD		*K=	keys	(A);
	KVPD		*V=	vals	(A);

	ELEMENT		*k;
	k=
	make				(K,B);

	element_new			(V,k,C);

/*	else
	memset				(k->with->text,0,0x10);
*/
	val_equal			(k->with,C);
	replace				(V,k->with);
	*Gz.at=				kvpset;
	argot_next			();
}

SCV	kvpdel				(void)
{	VMETA		*A=		K;
	VMETA		*B=		Gz.to[0];

	KVPD		*K=	keys	(A);
	KVPD		*V=	vals	(A);

	ELEMENT		*k=
	find				(K,B);

	if			yay	(k!=NULL)
	{	unplace			(K,k);
		unplace			(V,k->with);
		munmap			(k->with->text,k->with->size);
		munmap			(k->with,PAGE);
		munmap			(k->text,k->size);
		munmap			(k,PAGE);
	}

	*Gz.at=				kvpdel;
	argot_next			();
}

SCV	kvpinv				(void)
{	size_t	const	s=	sizeof	(KVPD);
	int	const	f=		MREMAP_MAYMOVE|MREMAP_FIXED;
	KVPD		*n=	pps	(s*2);
	VMETA		*A=		K;
	mremap				(keys(A),s,s,f,n+1);
	mremap				(vals(A),s,s,f,n);
	A->dataaddr=			(void *)	n;
	*Gz.at=				kvpinv;
	argot_next			();
}

SCV	unplace				(KVPD *A, ELEMENT *B)
{	if			nay	(B->placed==0)
	return;
	B->placed=			0;
	ELEMENT		**C=		A->where+B->index;

	ELEMENT		*E,*D=		*C;
	if				(D==B)
	*C=				C[0]->next;
	else
	{	for			(;D!=B;E=D,D=D->next);
		E->next=		D->next;
	}

	E=				A->chain;
	if			yay	(E==B)
	A->chain=			B->next;
	else
	{	for			(;E!=B;D=E,E=E->next);
		D->next=		B->next;
	}
}

SCV	val_append		(ELEMENT *E, VMETA *A)
{	size_t		a=	E->len+A->textlen+0x10;
	if			(a>E->size)
	{	E->text=
		mremap		(E->text,E->size,a,MREMAP_MAYMOVE);
		E->size=	a;
	}

	memcpya			(E->text+
				 E->len,
				 A->textaddr,
				 A->textlen);
	E->len+=		 A->textlen;
	__builtin_memset	(E->text+E->len,0,0x10);
}

SCV	val_equal		(ELEMENT *E, VMETA *A)
{	size_t		a=	A->textlen+0x10;
	if			(a>E->size)
	{	E->text=
		mremap		(E->text,E->size,a,MREMAP_MAYMOVE);
		E->size=	a;
	}

	memcpya			(E->text,A->textaddr,E->len);
	E->len=			A->textlen;
	__builtin_memset	(E->text+E->len,0,0x10);
}

SCV	replace				(KVPD *A, ELEMENT *B)
{	unplace				(A,B);

	B->placed=			1;
	B->index=
	bit128_to_bit16			(B->text);

	ELEMENT		**C=		A->where+B->index;

	B->next=			C[0];
	C[0]=				B;
}

__attribute__((noinline))
SCV	equalkey0				(void)
{	__attribute__((aligned(0x20)))
	uint8_t		a[0x20];

	VMETA		*K=			Gz.to[0];	/* .key */
	VMETA		*A=			K->host;	/* kvp */
	VMETA		*k=			Gz.to[1];	/* key name */
	KVPV		*t=
	kvpv					(A);
	VMETA		*V=			t->val;		/* .val */

	__builtin_memcpy			(a,k->textaddr,0x10);
	size_t		b=			k->textlen;
	if					(0x10>b)
	__builtin_memset			(a+b,0,0x10);

	KVPD		*D=		keys	(A);
	ELEMENT		*F,**E=			D->where+
	bit128_to_bit16				(a);
	for					(F=*E;F!=NULL;F=F->next)
	if				yay	(F->len==k->textlen)
	if				yay	(memcmp( k->textaddr,
							 F->text,
							 k->textlen)==0)
	if				yay	(F->with!=NULL)
	{	V->textaddr=			F->with->text;
		V->textlen=			F->with->len;
		V->textsize=			F->with->size;
		V->io.flag|=			textmapunmap;
		K->io.success=			0;
		return;
	}

	V->textaddr=				 V->text;
	V->textsize=	sizeof			(V->text);
	V->textlen=				0;
	V->io.flag&=				~textmapunmap;
	K->io.success=				ENOENT;
}

__attribute__((aligned(0x20)))
static		void		equalkey	(void)
{	equalkey0		();
	*Gz.at=			equalkey;
	argot_next		();
}

__attribute__((noinline))
SCV	equalval0				(void)
{	__attribute__((aligned(0x20)))
	uint8_t		a[0x20];

	VMETA		*V=			Gz.to[0];	/* .val */
	VMETA		*A=			V->host;	/* kvp */
	VMETA		*v=			Gz.to[1];	/* val name */
	KVPV		*t=
	kvpv					(A);
	VMETA		*K=			t->key;		/* .key */

	__builtin_memcpy			(a,v->textaddr,0x10);
	size_t		b=			v->textlen;
	if					(0x10>b)
	__builtin_memset			(a+b,0,0x10);

	KVPD		*D=		vals	(A);
	ELEMENT		*F,**E=			D->where+
	bit128_to_bit16				(a);
	for					(F=*E;F!=NULL;F=F->next)
	if				yay	(F->len==v->textlen)
	if				yay	(memcmp(v->textaddr,
							F->text,
							v->textlen)==0)
	if				yay	(F->with!=NULL)
	{	K->textaddr=			F->with->text;
		K->textlen=			F->with->len;
		K->textsize=			F->with->size;
		K->io.flag|=			textmapunmap;
		V->io.success=			0;
		return;
	}
	K->textaddr=				 K->text;
	K->textsize=	sizeof			(K->text);
	K->textlen=				0;
	K->io.flag&=				~textmapunmap;
	V->io.success=				ENOENT;
}

static	void		equalval	(void)
{	equalval0	();
	*Gz.at=		equalval;
	argot_next	();
}

static	void		all		(VMETA *, KVPD *);

__attribute__((always_inline))
inline
SCV	all				(VMETA *A, KVPD *K)
{	uint8_t		*a=		A->textaddr;
	KVPV		*t=
	kvpv				(A->host);
	VMETA		*B=		t->ambit;	/* .ambit */
	uint8_t		*b=		B->textaddr;
	size_t		c=		B->textlen;
	ELEMENT		*E;
	for				(E=K->chain;E;E=E->link)
	{	memcpya			(a,E->text,E->len);
		a+=			E->len;
		memcpya			(a,b,c);
		a+=			c;
	}
	A->textlen=			a-A->textaddr;
}

__attribute__((always_inline))
inline
static	CALIGN	ELEMENT	*find		(KVPD *K,VMETA *A)
{	show				(A);

	__attribute__((aligned(0x20)))
	uint8_t		a[0x20];
	__builtin_memcpy		(a,A->textaddr,0x10);
	size_t		d=		A->textlen;
	if				(0x10>d)
	__builtin_memset		(a+d,0,0x10);

	ELEMENT		**e=		K->where+
	bit128_to_bit16			(a);
	ELEMENT		*f=		*e;

	for				(;yay(f!=NULL);f=f->next)
	if			yay	(f->len==A->textlen)
	if			yay	(memcmp(A->textaddr,f->text,
					A->textlen)==0)
	return				f;
	return				f;
}

__attribute__((noinline))
static	CALIGN	ELEMENT	*make		(KVPD *K,VMETA *A)
{	show				(A);
	__attribute__((aligned(0x20)))
	uint8_t		a[0x20];
	__builtin_memcpy		(a,A->textaddr,0x10);
	size_t		d=		A->textlen;
	if				(0x10>d)
	__builtin_memset		(a+d,0,0x10);

	ELEMENT		**e=		K->where+
	bit128_to_bit16			(a);

	ELEMENT		*f=		*e;

	for				(;yay(f!=NULL);f=f->next)
	if			yay	(f->len==A->textlen)
	if			yay	(memcmp(A->textaddr,f->text,
						A->textlen)==0)
	return				f;

	ssize_t		s=		(A->textlen+PAGE+0x10-1)&~(PAGE-1);

	void		*v=
	pps				(PAGE+s);
	f=				v;
	f->text=			v+PAGE;
	f->len=				A->textlen;
	f->size=			s;
	memcpya				(f->text,A->textaddr,f->len);
	__builtin_memset		(f->text+f->len,0,0x10);
	f->next=			*e;
	*e=				f;

	f->link=			K->chain;
	K->chain=			f;
	return				f;
}

SCV	show_keymap	(VMETA *D)	{all	(D,keys(D->host));}
SCV	show_valmap	(VMETA *D)	{all	(D,vals(D->host));}

SCV	kvp	(void)	{tvarnewab(kvpsubnew,kvp);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190823",
	.official=	"20190823",
	.update=	"20200924"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(kvp,		"kvp");
	aa		(kvpdel,	"kvpdel");
	aa		(kvpinv,	"kvpinv");
	aa		(kvpwith,	"kvpwith");
	aa		(kvpset,	"kvpset");
	aa		(kvpnew,	"kvpnew");
	aa_fini		();

	opkvp[1]=
	opkvp[2]=		opbyte[0];
	opkvp[1].equal=		equalkey;
	opkvp[2].equal=		equalval;
	opkvp[1].set=
	opkvp[2].set=		NULL;
};
