/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

/*
#define		VMETA_NOT_PAGE_START
*/
#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	"value.h"

CALIGN
static	uint8_t		intpn[0x20]="/var/tmp/ascript.int.0";

__attribute__((noinline))
__attribute__((unused))
SCV	fromtextden	(VMETA *A)
{	uint8_t		*a=	A->textaddr,
			*b=	A->textaddr+A->textlen;
	uint64_t	c;
	uint8_t		s;
	uint8_t		d;

	for			(c=0,s=0;b>a;a++)
	{	if	nay	(*a=='-')
		{	s=	1;
			break;
		}

		d=		*a-'0';
		if	nay	(0xa>d)
		goto		next;
	}

	for			(;b>a;a++)
	{	c*=		0xa;
		d=		*a-'0';
		if	nay	(d>0xa)	break;
		next:
		c+=		d;
	}

	if			(s!=0)
	c=			-c;
	A->value.i=		c;
}

__attribute__((unused))
__attribute__((noinline))
SCV	fromtextdenfix		(VMETA *A)
{	fromtextden		(A);
	uint64_t	a=	A->value.i/10000,
			b=	A->value.i%10000;
	A->value.i=		(a<<0x10)+b*65536/10000;
}

__attribute__((noinline))
__attribute__((unused))
SCV	fromtextoct		(VMETA *A)
{	uint8_t		*a=	A->textaddr,
			*b=	A->textaddr+A->textlen;
	uint64_t	c;
	uint8_t		d;

	for			(c=0;b>a;a++)
	{	d=		*a-'0';
		if	nay	(7>=d)
		goto		next;
	}

	for			(;b>a;a++)
	{	c<<=		3;
		d=		*a-'0';
		if	nay	(d>7)	break;
		next:
		c+=		d;
	}
	A->value.i=		c;
}

__attribute__((noinline))
__attribute__((unused))
SCV	fromtexthexden	(VMETA *A)
{	uint8_t		*a=	A->textaddr,
			*b=	A->textaddr+A->textlen;
	uint64_t	c;
	uint8_t		d;

	for			(c=0;b>a;a++)
	{	d=		Gz.dh.xX[*a];
		if	nay	(0x10>d)
		goto		next;
	}

	for			(;b>a;a++)
	{	c<<=		4;
		d=		Gz.dh.xX[*a];
		if	nay	(d>0x10)	break;
		next:
		c+=		d;
	}
	A->value.i=		c;
}

__attribute__((noinline))
__attribute__((unused))
SCV	fromtexthexden_slow	(VMETA *A)
{	uint8_t		*a=	A->textaddr,
			*b=	A->textaddr+A->textlen;
	uint64_t	c;
	uint8_t		d;

	for			(c=0;b>a;a++)
	{	d=		*a;
		switch		(d)
		{	case	'0':	goto	next0;
			case	'1':	goto	next1;
			case	'2':	goto	next2;
			case	'3':	goto	next3;
			case	'4':	goto	next4;
			case	'5':	goto	next5;
			case	'6':	goto	next6;
			case	'7':	goto	next7;
			case	'8':	goto	next8;
			case	'9':	goto	next9;
			case	'A':
			case	'a':	goto	nexta;
			case	'B':
			case	'b':	goto	nextb;
			case	'C':
			case	'c':	goto	nextc;
			case	'D':
			case	'd':	goto	nextd;
			case	'E':
			case	'e':	goto	nexte;
			case	'F':
			case	'f':	goto	nextf;
		}
	}

	for			(;b>a;a++)
	{	c<<=		4;
		d=		*a;
		switch		(d)
		{	case	'0':	next0:	d=0;	break;
			case	'1':	next1:	d=1;	break;
			case	'2':	next2:	d=2;	break;
			case	'3':	next3:	d=3;	break;
			case	'4':	next4:	d=4;	break;
			case	'5':	next5:	d=5;	break;
			case	'6':	next6:	d=6;	break;
			case	'7':	next7:	d=7;	break;
			case	'8':	next8:	d=8;	break;
			case	'9':	next9:	d=9;	break;
			case	'A':
			case	'a':	nexta:	d=0xa;	break;
			case	'B':
			case	'b':	nextb:	d=0xb;	break;
			case	'C':
			case	'c':	nextc:	d=0xc;	break;
			case	'D':
			case	'd':	nextd:	d=0xd;	break;
			case	'E':
			case	'e':	nexte:	d=0xe;	break;
			case	'F':
			case	'f':	nextf:	d=0xf;	break;
			default:	goto	done;
		}
		c+=		d;
	}
	done:
	A->value.i=		c;
}

SCV	set_			(void)
{	VMETA		*A=
	parapass		(arga(NULL));
	reval			(A);
	Gz.to[0]->value.i=	A->value.i;
	revise			(Gz.to[0]);
	argot_next		();
}

SCV		set	(void)
{	(*Gz.at=set_)	();
}

#define	ab()					\
	reval		(Gz.to[1]);		\
	reval		(Gz.to[0]);		\
	VMETA	*A=	 Gz.to[0];		\
	VMETA	*B=	 Gz.to[1]

#define	cd()					\
	VMETA	*A=	 Gz.to[0];		\
	VMETA	*B=	 Gz.to[1]

#define	a()				\
	reval		(Gz.to[0]);	\
	VMETA	*A=	 Gz.to[0]

#define	b()				\
	VMETA	*A=	 Gz.to[0]

#define	rev()				\
	revise		(A);		\
	argot_next	();

#define	NISCV	__attribute__((noinline))	static	CALIGN	void

NISCV	notand_slow	(void){ab();A->value.i&=~B->value.i;rev();}
/*
NISCV	neg_slow	(void){a ();A->value.i= -A->value.i;rev();}
*/
NISCV	not_slow	(void){a ();A->value.i= ~A->value.i;rev();}
NISCV	test_slow	(void){ab();argot_jump(A->value.i&B->value.i);}


NISCV	shl4_slow	(void){ab();A->value.i4.l<<=B->value.i4.l;rev();}
NISCV	shr4_slow	(void){ab();A->value.i4.l>>=B->value.i4.l;rev();}
NISCV	rcl4_slow	(void){ab();A->value.i4.l=
				   (A->value.i4.l<<	 B->value.i4.l)|
				   (A->value.i4.l>>(0x20-B->value.i4.l));rev();}

NISCV	rcr4_slow	(void){ab();A->value.i4.l=
				   (A->value.i4.l>>	 B->value.i4.l)|
				   (A->value.i4.l<<(0x20-B->value.i4.l));rev();}

NISCV	addadd4_slow	(void){a ();A->value.i4.l++;rev();}
NISCV	subsub4_slow	(void){a ();A->value.i4.l--;rev();}
NISCV	and4_slow	(void){ab();A->value.i4.l&=B->value.i4.l;rev();}
NISCV	or4_slow	(void){ab();A->value.i4.l|=B->value.i4.l;rev();}
NISCV	xor4_slow	(void){ab();A->value.i4.l^=B->value.i4.l;rev();}
NISCV	add4_slow	(void){ab();A->value.i4.l+=B->value.i4.l;rev();}
NISCV	div4_slow	(void){ab();A->value.i4.l/=B->value.i4.l;rev();}
NISCV	equal4_slow	(void){ab();A->value.i4.l= B->value.i4.l;rev();}
NISCV	mul4_slow	(void){ab();A->value.i4.l*=B->value.i4.l;rev();}
NISCV	mod4_slow	(void){ab();A->value.i4.l%=B->value.i4.l;rev();}
NISCV	sub4_slow	(void){ab();A->value.i4.l-=B->value.i4.l;rev();}
NISCV	equalequal4_slow(void){ab();argot_jump(A->value.i4.l==B->value.i4.l);}
NISCV	less4_slow	(void){ab();argot_jump(A->value.i4.l< B->value.i4.l);}
NISCV	lessequal4_slow	(void){ab();argot_jump(A->value.i4.l<=B->value.i4.l);}
NISCV	more4_slow	(void){ab();argot_jump(A->value.i4.l> B->value.i4.l);}
NISCV	moreequal4_slow	(void){ab();argot_jump(A->value.i4.l>=B->value.i4.l);}
NISCV	notequal4_slow	(void){ab();argot_jump(A->value.i4.l!=B->value.i4.l);}
/*
NISCV	test4_slow	(void){ab();argot_jump(A->value.i4.l& B->value.i4.l);}
*/

NISCV	shl8_slow	(void){ab();A->value.i<<=B->value.i;rev();}
NISCV	shr8_slow	(void){ab();A->value.i>>=B->value.i;rev();}
NISCV	rcl8_slow	(void){ab();A->value.i=
				   (A->value.i<<      B->value.i)|
				   (A->value.i>>(0x40-B->value.i));rev();}

NISCV	rcr8_slow	(void){ab();A->value.i=
				   (A->value.i>>      B->value.i)|
				   (A->value.i<<(0x40-B->value.i));rev();}

NISCV	addadd8_slow	(void){a ();A->value.i++;rev();}
NISCV	subsub8_slow	(void){a ();A->value.i--;rev();}
NISCV	and8_slow	(void){ab();A->value.i&=B->value.i;rev();}
NISCV	or8_slow	(void){ab();A->value.i|=B->value.i;rev();}
NISCV	xor8_slow	(void){ab();A->value.i^=B->value.i;rev();}
NISCV	add8_slow	(void){ab();A->value.i+=B->value.i;rev();}
NISCV	div8_slow	(void){ab();A->value.i/=B->value.i;rev();}
NISCV	equal8_slow	(void){ab();A->value.i= B->value.i;rev();}
NISCV	mul8_slow	(void){ab();A->value.i*=B->value.i;rev();}
NISCV	mod8_slow	(void){ab();A->value.i%=B->value.i;rev();}
NISCV	sub8_slow	(void){ab();A->value.i-=B->value.i;rev();}
NISCV	equalequal8_slow(void){ab();argot_jump(A->value.i==B->value.i);}
NISCV	less8_slow	(void){ab();argot_jump(A->value.i< B->value.i);}
NISCV	lessequal8_slow	(void){ab();argot_jump(A->value.i<=B->value.i);}
NISCV	more8_slow	(void){ab();argot_jump(A->value.i> B->value.i);}
NISCV	moreequal8_slow	(void){ab();argot_jump(A->value.i>=B->value.i);}
NISCV	notequal8_slow	(void){ab();argot_jump(A->value.i!=B->value.i);}
/*
NISCV	test8_slow	(void){ab();argot_jump(A->value.i& B->value.i);}
*/

NISCV	mul8fix_slow		(void)
{	ab			();
	int64_t		a=	A->value.i;
	a/=			0x10000;
	a*=			B->value.i;
	int64_t		b=	A->value.i;
	b%=			0x10000;
	b*=			B->value.i;
	b+=			0x8000;
	b/=			0x10000;
	A->value.i=		a+b;
	rev			();
}

NISCV	div8fix_slow 		(void)
{	ab			();
	int64_t		b,c;
	b=			A->value.i/B->value.i;
	c=			A->value.i%B->value.i;
	c*=			0x10000;
	c+=			0x8000;
	c/=			B->value.i;
	A->value.i=		b*0x10000+c;
	rev			();
}

NISCV	notand_fast	(void){cd();A->value.i&=~B->value.i;argot_next();}
/*
NISCV	neg_fast	(void){b ();A->value.i= -A->value.i;argot_next();}
*/
NISCV	not_fast	(void){b ();A->value.i= ~A->value.i;argot_next();}
NISCV	test_fast	(void){cd();argot_jump(A->value.i&B->value.i);}


NISCV	shl4_fast	(void){cd();A->value.i4.l<<=B->value.i4.l;argot_next();}
NISCV	shr4_fast	(void){cd();A->value.i4.l>>=B->value.i4.l;argot_next();}
NISCV	rcl4_fast	(void){cd();A->value.i4.l=
				   (A->value.i4.l<<	 B->value.i4.l)|
				   (A->value.i4.l>>(0x20-B->value.i4.l));argot_next();}

NISCV	rcr4_fast	(void){cd();A->value.i4.l=
				   (A->value.i4.l>>	 B->value.i4.l)|
				   (A->value.i4.l<<(0x20-B->value.i4.l));argot_next();}

NISCV	addadd4_fast	(void){b ();A->value.i4.l++;argot_next();}
NISCV	subsub4_fast	(void){b ();A->value.i4.l--;argot_next();}
NISCV	and4_fast	(void){cd();A->value.i4.l&=B->value.i4.l;argot_next();}
NISCV	or4_fast	(void){cd();A->value.i4.l|=B->value.i4.l;argot_next();}
NISCV	xor4_fast	(void){cd();A->value.i4.l^=B->value.i4.l;argot_next();}
NISCV	add4_fast	(void){cd();A->value.i4.l+=B->value.i4.l;argot_next();}
NISCV	div4_fast	(void){cd();A->value.i4.l/=B->value.i4.l;argot_next();}
NISCV	equal4_fast	(void){cd();A->value.i4.l= B->value.i4.l;argot_next();}
NISCV	mul4_fast	(void){cd();A->value.i4.l*=B->value.i4.l;argot_next();}
NISCV	mod4_fast	(void){cd();A->value.i4.l%=B->value.i4.l;argot_next();}
NISCV	sub4_fast	(void){cd();A->value.i4.l-=B->value.i4.l;argot_next();}
NISCV	equalequal4_fast(void){cd();argot_jump(A->value.i4.l==B->value.i4.l);}
NISCV	less4_fast	(void){cd();argot_jump(A->value.i4.l< B->value.i4.l);}
NISCV	lessequal4_fast	(void){cd();argot_jump(A->value.i4.l<=B->value.i4.l);}
NISCV	more4_fast	(void){cd();argot_jump(A->value.i4.l> B->value.i4.l);}
NISCV	moreequal4_fast	(void){cd();argot_jump(A->value.i4.l>=B->value.i4.l);}
NISCV	notequal4_fast	(void){cd();argot_jump(A->value.i4.l!=B->value.i4.l);}
/*
NISCV	test4_fast	(void){cd();argot_jump(A->value.i4.l& B->value.i4.l);}
*/

NISCV	shl8_fast	(void){cd();A->value.i<<=B->value.i;argot_next();}
NISCV	shr8_fast	(void){cd();A->value.i>>=B->value.i;argot_next();}
NISCV	rcl8_fast	(void){cd();A->value.i=
				   (A->value.i<<      B->value.i)|
				   (A->value.i>>(0x40-B->value.i));argot_next();}

NISCV	rcr8_fast	(void){cd();A->value.i=
				   (A->value.i>>      B->value.i)|
				   (A->value.i<<(0x40-B->value.i));argot_next();}

NISCV	addadd8_fast	(void){b ();A->value.i++;argot_next();}
NISCV	subsub8_fast	(void){b ();A->value.i--;argot_next();}
NISCV	and8_fast	(void){cd();A->value.i&=B->value.i;argot_next();}
NISCV	or8_fast	(void){cd();A->value.i|=B->value.i;argot_next();}
NISCV	xor8_fast	(void){cd();A->value.i^=B->value.i;argot_next();}
NISCV	add8_fast	(void){cd();A->value.i+=B->value.i;argot_next();}
NISCV	div8_fast	(void){cd();A->value.i/=B->value.i;argot_next();}
NISCV	equal8_fast	(void){cd();A->value.i= B->value.i;argot_next();}
NISCV	mul8_fast	(void){cd();A->value.i*=B->value.i;argot_next();}
NISCV	mod8_fast	(void){cd();A->value.i%=B->value.i;argot_next();}
NISCV	sub8_fast	(void){cd();A->value.i-=B->value.i;argot_next();}
NISCV	equalequal8_fast(void){cd();argot_jump(A->value.i==B->value.i);}
NISCV	less8_fast	(void){cd();argot_jump(A->value.i< B->value.i);}
NISCV	lessequal8_fast	(void){cd();argot_jump(A->value.i<=B->value.i);}
NISCV	more8_fast	(void){cd();argot_jump(A->value.i> B->value.i);}
NISCV	moreequal8_fast	(void){cd();argot_jump(A->value.i>=B->value.i);}
NISCV	notequal8_fast	(void){cd();argot_jump(A->value.i!=B->value.i);}
/*
NISCV	test8_fast		(void){cd();argot_jump(A->value.i& B->value.i);}
*/

NISCV	mul8fix_fast		(void)
{	cd			();
	int64_t		a=	A->value.i;
	a/=			0x10000;
	a*=			B->value.i;
	int64_t		b=	A->value.i;
	b%=			0x10000;
	b*=			B->value.i;
	b+=			0x8000;
	b/=			0x10000;
	A->value.i=		a+b;
	argot_next		();
}

NISCV	div8fix_fast 		(void)
{	cd			();
	int64_t		b,c;
	b=			A->value.i/B->value.i;
	c=			A->value.i%B->value.i;
	c*=			0x10000;
	c+=			0x8000;
	c/=			B->value.i;
	A->value.i=		b*0x10000+c;
	argot_next		();
}

/*
#define	select2_(na,nb)					\
	void		(*f[2])(void)={na,nb};		\
	uintptr_t	a;				\
	a=		(uintptr_t)Gz.to[0]->reval|	\
			(uintptr_t)Gz.to[0]->revise|	\
			(uintptr_t)Gz.to[1]->reval;	\
	(*Gz.at=f[a!=0])();
*/

#define	select1_(na,nb)					\
	uintptr_t	a;				\
	a=		(uintptr_t)Gz.to[0]->reval|	\
			(uintptr_t)Gz.to[0]->revise;	\
	if	yay	(a==0)				\
	(*Gz.at=na)	();				\
	else						\
	(*Gz.at=nb)	()

#define	select2_(na,nb)					\
	uintptr_t	a;				\
	a=		(uintptr_t)Gz.to[0]->reval|	\
			(uintptr_t)Gz.to[0]->revise|	\
			(uintptr_t)Gz.to[1]->reval;	\
	if	yay	(a==0)				\
	(*Gz.at=na)	();				\
	else						\
	(*Gz.at=nb)	()


#define	select2(name)	select2_	(name ## _fast,name ## _slow)
#define	select1(name)	select1_	(name ## _fast,name ## _slow)


SCV	notand		(void){select2(notand);}
/*
SCV	neg		(void){select2(neg);}
*/
SCV	not		(void){select1(not);}
SCV	test		(void){select2(test);}

SCV	addadd4		(void){select1(addadd4);}
SCV	subsub4		(void){select1(subsub4);}
SCV	add4		(void){select2(add4);}
SCV	and4		(void){select2(and4);}
SCV	or4		(void){select2(or4);}
SCV	xor4		(void){select2(xor4);}
SCV	div4		(void){select2(div4);}
SCV	equal4		(void){select2(equal4);}
SCV	mul4		(void){select2(mul4);}
SCV	mod4		(void){select2(mod4);}
SCV	sub4		(void){select2(sub4);}
SCV	equalequal4	(void){select2(equalequal4);}
SCV	less4		(void){select2(less4);}
SCV	lessequal4	(void){select2(lessequal4);}
SCV	more4		(void){select2(more4);}
SCV	moreequal4	(void){select2(moreequal4);}
SCV	notequal4	(void){select2(notequal4);}
/*
SCV	test4		(void){select2(test4);}
*/
SCV	shl4		(void){select2(shl4);}
SCV	shr4		(void){select2(shr4);}
SCV	rcl4		(void){select2(rcl4);}
SCV	rcr4		(void){select2(rcr4);}

SCV	addadd8		(void){select1(addadd8);}
SCV	subsub8		(void){select1(subsub8);}
SCV	add8		(void){select2(add8);}
SCV	and8		(void){select2(and8);}
SCV	or8		(void){select2(or8);}
SCV	xor8		(void){select2(xor8);}
SCV	div8		(void){select2(div8);}
SCV	equal8		(void){select2(equal8);}
SCV	mul8		(void){select2(mul8);}
SCV	mod8		(void){select2(mod8);}
SCV	sub8		(void){select2(sub8);}
SCV	equalequal8	(void){select2(equalequal8);}
SCV	less8		(void){select2(less8);}
SCV	lessequal8	(void){select2(lessequal8);}
SCV	more8		(void){select2(more8);}
SCV	moreequal8	(void){select2(moreequal8);}
SCV	notequal8	(void){select2(notequal8);}
/*
SCV	test8		(void){select2(test8);}
*/
SCV	shl8		(void){select2(shl8);}
SCV	shr8		(void){select2(shr8);}
SCV	rcl8		(void){select2(rcl8);}
SCV	rcr8		(void){select2(rcr8);}
SCV	div8fix		(void){select2(div8fix);}
SCV	mul8fix		(void){select2(mul8fix);}

SCV	int4_		(void){tvarnewa(int4init);}
SCV	int8_		(void){tvarnewa(int8init);}
SCV	fix8_		(void){tvarnewa(fix8init);}

SCV	int4		(void){(*Gz.at=int4_)();}
SCV	int8		(void){(*Gz.at=int8_)();}
SCV	fix8		(void){(*Gz.at=fix8_)();}

SCV	reval_bin	(VMETA *A){show(A->host);A->io.success=asbin(A->host->textaddr,&A->value.i);}
SCV	reval_den	(VMETA *A){show(A->host);A->io.success=asden(A->host->textaddr,&A->value.i);}
SCV	reval_fix	(VMETA *A){show(A->host);A->io.success=asfix(A->host->textaddr,&A->value.i);}
SCV	reval_dex	(VMETA *A){show(A->host);A->io.success=asdex(A->host->textaddr,&A->value.i);}
SCV	reval_oct	(VMETA *A){show(A->host);A->io.success=asoct(A->host->textaddr,&A->value.i);}

#define	assub(a,b)			\
	VMETA		*B=		\
	var_new_sub	((a),A);	\
	int8init	(B);		\
	B->reval=	(b)

ALIVE	asbin__	(VMETA *A){assub(".bin",reval_bin);}
ALIVE	asden__	(VMETA *A){assub(".den",reval_den);}
ALIVE	asfix__	(VMETA *A){assub(".fix",reval_fix);}
ALIVE	asdex__	(VMETA *A){assub(".dex",reval_dex);}
ALIVE	asoct__	(VMETA *A){assub(".oct",reval_oct);}

SCV	asbin_	(void){tsubab(asbin__,asbin_);}
SCV	asden_	(void){tsubab(asden__,asden_);}
SCV	asfix_	(void){tsubab(asfix__,asfix_);}
SCV	asdex_	(void){tsubab(asdex__,asdex_);}
SCV	asoct_	(void){tsubab(asoct__,asoct_);}

SCV	bin			(void)
{	VMETA		*A=	Gz.to[0];
	if			(A->op->int4_compat)
	{	A->show=	Gz.out.bin4;
		A->textlen=	0x20;
	}
	else
	{	A->show=	Gz.out.bin8;
		A->textlen=	0x40;
		if		((A->io.flag&textmapunmap)==0)
		map_add		(A,PAGE,0);
	}
	*Gz.at=			bin;
	argot_next		();
}

SCV	den			(void)
{	VMETA		*A=	Gz.to[0];
	if			(A->op->int4_compat)
	A->show=		Gz.out.den4;
	else
	A->show=		Gz.out.den8;
	*Gz.at=			den;
	argot_next		();
}

SCV	oct			(void)
{	VMETA		*A=	Gz.to[0];
	if			(A->op->int4_compat)
	{	A->show=	Gz.out.oct4;
		A->textlen=	0xc;
	}
	else
	{	A->show=	Gz.out.oct8;
		A->textlen=	0x18;
	}
	*Gz.at=			oct;
	argot_next		();
}

SCV	dex			(void)
{	VMETA		*A=	Gz.to[0];
	if			(A->op->int4_compat)
	{	A->show=	Gz.out.dex4;
		A->textlen=	8;
	}
	else
	{	A->show=	Gz.out.dex8;
		A->textlen=	0x10;
	}
	*Gz.at=			dex;
	argot_next		();
}

SCV	Dex			(void)
{	VMETA		*A=	Gz.to[0];
	if			(A->op->int4_compat)
	{	A->show=	Gz.out.Dex4;
		A->textlen=	8;
	}
	else
	{	A->show=	Gz.out.Dex8;
		A->textlen=	0x10;
	}
	*Gz.at=			Dex;
	argot_next		();
}

SCV	time_			(void)
{	Gz.to[0]->show=		Gz.out.time;
	*Gz.at=			time_;
	argot_next		();
}

SCV	nano			(void)
{	Gz.to[0]->show=		Gz.out.nano;
	Gz.to[0]->textlen=	9;
	*Gz.at=			nano;
	argot_next		();
}

SCV	revalorigin_		(void){reval(Gz.to[1]);argot_next();}
SCV	revaltarget_		(void){reval(Gz.to[0]);argot_next();}

static	void	revalorigin	(void){(*Gz.at=revalorigin_)();}
static	void	revaltarget	(void){(*Gz.at=revaltarget_)();}

static	void	_int_	(void)	{argot_next();}
static	void	_int	(void)	{(*Gz.at=_int_)();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_int,		"int");
/*	aa		(shl,		"shl");
	aa		(rcl,		"rcl");
	aa		(shr,		"shr");
	aa		(rcr,		"rcr");
	aa		(mod,		"mod");
*/

	aa		(revaltarget,	"revaltarget");
	aa		(revalorigin,	"revalorigin");

	aa		(notand,	"notand");
	aa		(test,		"test");

	aa		(asbin_,	"asbin");
	aa		(asden_,	"asden");
	aa		(asoct_,	"asoct");
	aa		(asdex_,	"asdex");
	aa		(asfix_,	"asfix");

	aa		(time_,		"time");
	aa		(nano,		"nano");
	aa		(bin,		"bin");
	aa		(den,		"den");
	aa		(oct,		"oct");
	aa		(dex,		"dex");
	aa		(Dex,		"Dex");

	aa		(fix8,		"fix8");
	aa		(int8,		"int8");
	aa		(int4,		"int4");

	aa_fini		();
};

__attribute__((always_inline))
static	inline	uint8_t	uden32_digits		(uint32_t a)
{	if	nay	(10>a)			return	1;
	if	nay	(100>a)			return	2;
	if	nay	(1000>a)		return	3;
	if	nay	(10000>a)		return	4;
	if	nay	(100000>a)		return	5;
	if	nay	(1000000>a)		return	6;
	if	nay	(10000000>a)		return	7;
	if	nay	(100000000>a)		return	8;
	if	nay	(1000000000>a)		return	9;
/*	if	nay	(10000000000>a)	*/	return	10;
}

__attribute__((always_inline))
static	inline	void	uden32_byte	(uint8_t **a,uint32_t *b)
{	uint32_t	c;
	uint8_t		d;
	c=		*b/10;
	d=		*b%10;
	*b=		c;
	**a=		d+'0';
	(*a)--;
}

__attribute__((noinline))
static	CALIGN	uint8_t	uden32		(uint8_t *a,uint32_t b)
{	if	nay		(1>b)
	{	*a=		0;
		return		1;
	}
	uint8_t		r=
	uden32_digits		(b);
	a+=			r-1;
	switch			(r)
	{	case	0xa:	uden32_byte	(&a,&b);
		case	9:	uden32_byte	(&a,&b);
		case	8:	uden32_byte	(&a,&b);
		case	7:	uden32_byte	(&a,&b);
		case	6:	uden32_byte	(&a,&b);
		case	5:	uden32_byte	(&a,&b);
		case	4:	uden32_byte	(&a,&b);
		case	3:	uden32_byte	(&a,&b);
		case	2:	uden32_byte	(&a,&b);
		case	1:	uden32_byte	(&a,&b);
		default:	return		r;
	}
}

/*
__attribute__((constructor))
SCV	uden32test		(void)
{	uint8_t		a[0x20];
	uint8_t		b;
	b=		uden32	(a,0x1000);write(1,a,b);write(1,"\n",1);
	b=		uden32	(a,0x10000);write(1,a,b);write(1,"\n",1);
	b=		uden32	(a,0x100000);write(1,a,b);write(1,"\n",1);
	b=		uden32	(a,0x1000000);write(1,a,b);write(1,"\n",1);
}
*/

SCV	outbin4			(VMETA *A)
{	uint32_t	a=	A->value.i4.l;
	uint8_t		*b=	A->textaddr;
	b[0x1f]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1e]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1d]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1c]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1b]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1a]=		'0'+((a&1)!=0);	a>>=1;
	b[0x19]=		'0'+((a&1)!=0);	a>>=1;
	b[0x18]=		'0'+((a&1)!=0);	a>>=1;
	b[0x17]=		'0'+((a&1)!=0);	a>>=1;
	b[0x16]=		'0'+((a&1)!=0);	a>>=1;
	b[0x15]=		'0'+((a&1)!=0);	a>>=1;
	b[0x14]=		'0'+((a&1)!=0);	a>>=1;
	b[0x13]=		'0'+((a&1)!=0);	a>>=1;
	b[0x12]=		'0'+((a&1)!=0);	a>>=1;
	b[0x11]=		'0'+((a&1)!=0);	a>>=1;
	b[0x10]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0f]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0e]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0d]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0c]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0b]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0a]=		'0'+((a&1)!=0);	a>>=1;
	b[0x09]=		'0'+((a&1)!=0);	a>>=1;
	b[0x08]=		'0'+((a&1)!=0);	a>>=1;
	b[0x07]=		'0'+((a&1)!=0);	a>>=1;
	b[0x06]=		'0'+((a&1)!=0);	a>>=1;
	b[0x05]=		'0'+((a&1)!=0);	a>>=1;
	b[0x04]=		'0'+((a&1)!=0);	a>>=1;
	b[0x03]=		'0'+((a&1)!=0);	a>>=1;
	b[0x02]=		'0'+((a&1)!=0);	a>>=1;
	b[0x01]=		'0'+((a&1)!=0);	a>>=1;
	b[0x00]=		'0'+((a&1)!=0);
}

SCV	outbin8			(VMETA *A)
{	uint64_t	a=	A->value.i;
	uint8_t		*b=	A->textaddr;
	b[0x3f]=		'0'+((a&1)!=0);	a>>=1;
	b[0x3e]=		'0'+((a&1)!=0);	a>>=1;
	b[0x3d]=		'0'+((a&1)!=0);	a>>=1;
	b[0x3c]=		'0'+((a&1)!=0);	a>>=1;
	b[0x3b]=		'0'+((a&1)!=0);	a>>=1;
	b[0x3a]=		'0'+((a&1)!=0);	a>>=1;
	b[0x39]=		'0'+((a&1)!=0);	a>>=1;
	b[0x38]=		'0'+((a&1)!=0);	a>>=1;
	b[0x37]=		'0'+((a&1)!=0);	a>>=1;
	b[0x36]=		'0'+((a&1)!=0);	a>>=1;
	b[0x35]=		'0'+((a&1)!=0);	a>>=1;
	b[0x34]=		'0'+((a&1)!=0);	a>>=1;
	b[0x33]=		'0'+((a&1)!=0);	a>>=1;
	b[0x32]=		'0'+((a&1)!=0);	a>>=1;
	b[0x31]=		'0'+((a&1)!=0);	a>>=1;
	b[0x30]=		'0'+((a&1)!=0);	a>>=1;
	b[0x2f]=		'0'+((a&1)!=0);	a>>=1;
	b[0x2e]=		'0'+((a&1)!=0);	a>>=1;
	b[0x2d]=		'0'+((a&1)!=0);	a>>=1;
	b[0x2c]=		'0'+((a&1)!=0);	a>>=1;
	b[0x2b]=		'0'+((a&1)!=0);	a>>=1;
	b[0x2a]=		'0'+((a&1)!=0);	a>>=1;
	b[0x29]=		'0'+((a&1)!=0);	a>>=1;
	b[0x28]=		'0'+((a&1)!=0);	a>>=1;
	b[0x27]=		'0'+((a&1)!=0);	a>>=1;
	b[0x26]=		'0'+((a&1)!=0);	a>>=1;
	b[0x25]=		'0'+((a&1)!=0);	a>>=1;
	b[0x24]=		'0'+((a&1)!=0);	a>>=1;
	b[0x23]=		'0'+((a&1)!=0);	a>>=1;
	b[0x22]=		'0'+((a&1)!=0);	a>>=1;
	b[0x21]=		'0'+((a&1)!=0);	a>>=1;
	b[0x20]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1f]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1e]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1d]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1c]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1b]=		'0'+((a&1)!=0);	a>>=1;
	b[0x1a]=		'0'+((a&1)!=0);	a>>=1;
	b[0x19]=		'0'+((a&1)!=0);	a>>=1;
	b[0x18]=		'0'+((a&1)!=0);	a>>=1;
	b[0x17]=		'0'+((a&1)!=0);	a>>=1;
	b[0x16]=		'0'+((a&1)!=0);	a>>=1;
	b[0x15]=		'0'+((a&1)!=0);	a>>=1;
	b[0x14]=		'0'+((a&1)!=0);	a>>=1;
	b[0x13]=		'0'+((a&1)!=0);	a>>=1;
	b[0x12]=		'0'+((a&1)!=0);	a>>=1;
	b[0x11]=		'0'+((a&1)!=0);	a>>=1;
	b[0x10]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0f]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0e]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0d]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0c]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0b]=		'0'+((a&1)!=0);	a>>=1;
	b[0x0a]=		'0'+((a&1)!=0);	a>>=1;
	b[0x09]=		'0'+((a&1)!=0);	a>>=1;
	b[0x08]=		'0'+((a&1)!=0);	a>>=1;
	b[0x07]=		'0'+((a&1)!=0);	a>>=1;
	b[0x06]=		'0'+((a&1)!=0);	a>>=1;
	b[0x05]=		'0'+((a&1)!=0);	a>>=1;
	b[0x04]=		'0'+((a&1)!=0);	a>>=1;
	b[0x03]=		'0'+((a&1)!=0);	a>>=1;
	b[0x02]=		'0'+((a&1)!=0);	a>>=1;
	b[0x01]=		'0'+((a&1)!=0);	a>>=1;
	b[0x00]=		'0'+((a&1)!=0);
}

SCV	outoct2			(VMETA *A)
{	uint16_t	a=	A->value.i4.l;
	uint32_t	*b=	(uint32_t *)	A->text;

	b[0]=			Gz.dh.oct[a>>0xc];
	b[1]=			Gz.dh.oct[a&0xfff];/*	a>>=0xc;	*/
}

SCV	outoct4			(VMETA *A)
{	uint32_t	a=	A->value.i4.l;
	uint32_t	*b=	(uint32_t *)	A->text;

	b[2]=			Gz.dh.oct[a&0xfff];	a>>=0xc;
	b[1]=			Gz.dh.oct[a&0xfff];	a>>=0xc;
	b[0]=			Gz.dh.oct[a      ];
}

SCV	outoct8			(VMETA *A)
{	uint64_t	a=	A->value.i;
	uint32_t	*b=	(uint32_t *)	A->text;

	b[5]=			Gz.dh.oct[a&0xfff];	a>>=0xc;
	b[4]=			Gz.dh.oct[a&0xfff];	a>>=0xc;
	b[3]=			Gz.dh.oct[a&0xfff];	a>>=0xc;
	b[2]=			Gz.dh.oct[a&0xfff];	a>>=0xc;
	b[1]=			Gz.dh.oct[a&0xfff];	a>>=0xc;
	b[0]=			Gz.dh.oct[a      ];
}

SCV	outdex8			(VMETA *A)
{
/*	A->textlen=		0x10;	*/	/* It's already set */
	uint64_t	a=	A->value.i;
	uint32_t	*b=	(uint32_t *)	A->text;
	b[3]=			Gz.dh.hex.full[(uint16_t)a];	a>>=0x10;
	b[2]=			Gz.dh.hex.full[(uint16_t)a];	a>>=0x10;
	b[1]=			Gz.dh.hex.full[(uint16_t)a];	a>>=0x10;
	b[0]=			Gz.dh.hex.full[(uint16_t)a];
}

SCV	outdex4			(VMETA *A)
{
/*	A->textlen=		8;	*/	/* It's already set */
	uint64_t	a=	A->value.i4.l;
	uint32_t	*b=	(uint32_t *)	A->text;
	b[1]=			Gz.dh.hex.full[(uint16_t)a];	a>>=0x10;
	b[0]=			Gz.dh.hex.full[(uint16_t)a];
}

SCV	outDex8			(VMETA *A)
{
/*	A->textlen=		0x10;	*/	/* It's already set */
	uint64_t	a=	A->value.i;
	uint32_t	*b=	(uint32_t *)	A->text;
	b[3]=			Gz.dh.hex.Full[(uint16_t)a];	a>>=0x10;
	b[2]=			Gz.dh.hex.Full[(uint16_t)a];	a>>=0x10;
	b[1]=			Gz.dh.hex.Full[(uint16_t)a];	a>>=0x10;
	b[0]=			Gz.dh.hex.Full[(uint16_t)a];
}

SCV	outDex4			(VMETA *A)
{
/*	A->textlen=		8;	*/	/* It's already set */
	uint64_t	a=	A->value.i4.l;
	uint32_t	*b=	(uint32_t *)	A->text;
	b[1]=			Gz.dh.hex.Full[(uint16_t)a];	a>>=0x10;
	b[0]=			Gz.dh.hex.Full[(uint16_t)a];
}

static	inline	void	outden4b(VMETA *A,uint32_t a,uint8_t s)
{	uint8_t		*b=	A->text+s;
	if		yay	(10000>a)
	{	*(uint32_t *)b=	Gz.dh.den.left.w[(uint16_t)a];
		A->textlen=	Gz.dh.den.next	[(uint16_t)a]+s;
		return;
	}
	uint32_t	c,d;
	uint8_t		e;
	if		yay	(100000000>a)
	{	c=		a/10000;
		d=		a%10000;
		e=		Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=	Gz.dh.den.left.w[(uint16_t)c];
		A->textlen=	e+4+s;
		b+=		e;
		*(uint32_t *)b=	Gz.dh.den.full.w[(uint16_t)d];
		return;
	}
	{	c=		a/100000000;
		d=		a%100000000;
		a=		d;
		e=		Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=	Gz.dh.den.left.w[(uint16_t)c];
		b+=		e;
		A->textlen=	e+8+s;

		c=		a/10000;
		d=		a%10000;
		*(uint32_t *)b=	Gz.dh.den.full.w[(uint16_t)c];
		b+=		4;
		*(uint32_t *)b=	Gz.dh.den.full.w[(uint16_t)d];
		return;
	}
}

SCV	outden4			(VMETA *A)
{	int32_t		a=	A->value.i4.l;
	if		yay	(a>=0)
	outden4b		(A,a,0);
	else
	{	A->text[0]=	'-';
		outden4b	(A,-a,1);
	}
}

ALIVE	outden8b			(VMETA *A,uint64_t a,uint8_t s)
{	if			nay	(0x100000000>a)
	{	outden4b		(A,a,s);
		return;
	}

	uint8_t		*b=		A->text+s;
	uint64_t	c,d;
	uint8_t		e;

	if			yay	(  1000000000000>a)
	{	c=			a /100000000;
		d=			a %100000000;
		a=			d;
		e=			Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=		Gz.dh.den.left.w[(uint16_t)c];
		b+=			e;
		A->textlen=		e+0xc+s;

		c=			a /10000;
		d=			a %10000;
		a=			c;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)d];
	}
	else
	if			yay	(  10000000000000000>a)
	{	c=			a /1000000000000;
		d=			a %1000000000000;
		a=			d;
		e=			Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=		Gz.dh.den.left.w[(uint16_t)c];
		b+=			e;
		A->textlen=		e+0xc+s;

		c=			a /100000000;
		d=			a %100000000;
		a=			d;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;

		c=			a /10000;
		d=			a %10000;
		a=			c;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)d];
		return;
	}
	else
	{	c=			a /10000000000000000;
		d=			a %10000000000000000;
		a=			d;
		e=			Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=		Gz.dh.den.left.w[(uint16_t)c];
		b+=			e;
		A->textlen=		e+0xc+s;

		c=			a /1000000000000;
		d=			a %1000000000000;
		a=			d;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;

		c=			a /100000000;
		d=			a %100000000;
		a=			d;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;

		c=			a /10000;
		d=			a %10000;
		a=			c;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)d];
	}
}

__attribute__((noinline))
SCV	outden8			(VMETA *A)
{	int64_t		a=	A->value.i;

	if		yay	(a>=0)
	outden8b		(A,a,0);
	else
	{	A->text[0]=	'-';
		outden8b	(A,-a,1);
	}
}

SCV	outfix8b			(VMETA *A,uint64_t a,uint8_t s)
{	uint8_t		*b=		A->text+s;
	uint64_t	c,d;
	uint8_t		e;

	uint32_t	f=		(uint16_t)a;
	f*=				  10000;
	f+=				0x8000;
	f/=				0x10000;

	uint32_t	g=		Gz.dh.den.full.w[(uint16_t)f];

	a>>=				0x10;

	if			nay	(10000>a)
	{	*(uint32_t *)b=		Gz.dh.den.left.w[(uint16_t)a];
		b+=			Gz.dh.den.next  [(uint16_t)a];

		done:
		*b++=			'.';
		*(uint32_t *)b=		g;
		b+=			4;
		A->textlen=		b-A->text;
		return;
	}
	if			nay	(  100000000>a)
	{	c=			a /10000;
		d=			a %10000;
		a=			d;
		e=			Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=		Gz.dh.den.left.w[(uint16_t)c];
		b+=			e;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)d];
		b+=			4;
		goto			done;
	}
	if			nay	(  1000000000000>a)
	{	c=			a /100000000;
		d=			a %100000000;
		a=			d;
		e=			Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=		Gz.dh.den.left.w[(uint16_t)c];
		b+=			e;

		c=			a /10000;
		d=			a %10000;
		a=			c;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)d];
		b+=			4;
		goto			done;
	}
	{	c=			a /1000000000000;
		d=			a %1000000000000;
		a=			d;
		e=			Gz.dh.den.next	[(uint16_t)c];
		*(uint32_t *)b=		Gz.dh.den.left.w[(uint16_t)c];
		b+=			e;

		c=			a /100000000;
		d=			a %100000000;
		a=			d;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;

		c=			a /10000;
		d=			a %10000;
		a=			c;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)c];
		b+=			4;
		*(uint32_t *)b=		Gz.dh.den.full.w[(uint16_t)d];
		b+=			4;
		goto			done;
	}
}

SCV	outfix8			(VMETA *A)
{	int64_t		a=	A->value.i;

	if		yay	(a>=0)
	outfix8b		(A,a,0);
	else
	{	A->text[0]=	'-';
		outfix8b	(A,-a,1);
	}
}

__attribute__((unused))
__attribute__((noinline))
SCV	outtime			(VMETA *A)
{	outden8			(A);
	if		nay	(A->textlen==1)
	{	A->textlen=	2;
		A->text[1]=	A->text[0];
		A->text[0]=	'0';
	}
}

__attribute__((unused))
__attribute__((noinline))
SCV	outnano			(VMETA *A)
{	uint32_t	a=	A->value.i4.l;
	uint8_t		*b=	A->text;
	uint32_t	c,d,e;
	c=			a/100000000;
	a-=			c*100000000;
	d=			a/10000;
	e=			a%10000;
	*(uint8_t  *)(b+0)=	c+'0';
	*(uint32_t *)(b+1)=	Gz.dh.den.full.w[(uint16_t)d];
	*(uint32_t *)(b+5)=	Gz.dh.den.full.w[(uint16_t)e];
}

SCV	table_gen	(void);

inline
SCV	intout			(void)
{	int		a;
	static
	struct	stat	b;

	a=
	open			(intpn,O_RDONLY,0400);
	if		yay	(a>=0)
	{	use:
		mmap		(&Gz.dh,sizeof(Gz.dh),PROT_READ,
				 MAP_FIXED|MAP_SHARED,a,0);
		close		(a);
		return;
	}

	uden32			(intpn+0x15,getuid());

	a=
	open			(intpn,O_RDONLY,0400);
	if		nay	(0>a)
	{	gen:
		table_gen	();
		return;
	}

	b.st_uid=		-1;
	fstat			(a,&b);
	if		yay	(b.st_uid==getuid())
	goto			use;
	else
	goto			gen;
}

SCV	dtgen		(void);
__attribute__((noinline))
SCV	table_gen		(void)
{	dtgen			();

	int		a=
	open			(intpn,O_CREAT|O_WRONLY,0404);

	if		nay	(0>a)
	if		yay	(geteuid()==0)
	{	mkdir		("/var",755);
		mkdir		("/var/tmp",1777);
		a=
		open		(intpn,O_CREAT|O_WRONLY,0404);
		if	nay	(0>a)
		return;
	}
	else	return;
	write			(a,&Gz.dh,sizeof(Gz.dh));
	close			(a);
}

__attribute__((always_inline))
static	inline	void	xX		(void)
{	memset				(Gz.dh.xX,0xff,0x100);
	int		a=		0;
	for				(;0x0a>a;a++)
		Gz.dh.xX['0'    +a]=	a;
	for				(;0x10>a;a++)
	{	Gz.dh.xX['A'-0xa+a]=	a;
		Gz.dh.xX['a'-0xa+a]=	a;
	}
}

static		void	ot_full_init		(void)
{	register
	uint32_t	v,*e;
	e=					Gz.dh.oct;
	v=					0x30303030;

	do
	{	do
		{	do
			{	*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
							v-=	0x00000008;
							v+=	0x00000100;
			}	while		(0x38000000>(v<<0x10));
							v-=	0x00000800;
							v+=	0x00010000;
		}	while			(0x38000000>(v<<8));
							v-=	0x00080000;
							v+=	0x01000000;
	}	while				(0x38000000> v);
}

static		void	dt_full_init	(void)
{	register
	uint32_t	v,*e;
	e=					(uint32_t *)Gz.dh.den.full.w;
	v=					0x30303030;

	do
	{	do
		{	do
			{	*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
				*e++=htobe32	(v);	v+=	0x00000001;
							v-=	0x0000000a;
							v+=	0x00000100;
			}	while		(0x3a000000>(v<<0x10));
							v-=	0x00000a00;
							v+=	0x00010000;
		}	while			(0x3a000000>(v<<8));
							v-=	0x000a0000;
							v+=	0x01000000;
	}	while				(0x3a000000> v);
}

__attribute__((unused))
__attribute__((noinline))
static		void	dt_full_init_slow	(void)
{	register uint8_t	a,b,c,d,*e;
	e=	(uint8_t *)	Gz.dh.den.full.w;
	for	(a='0';a<='9';a++)
	for	(b='0';b<='9';b++)
	for	(c='0';c<='9';c++)
	for	(d='0';d<='9';d++)
	{	*e++=a;	*e++=b;	*e++=c;	*e++=d;}
}

static		void	dt_left_init	(void)
{
/*	For the first memcpy also
	a rep movsq instruction was used
	then this would be so beautiful and compact.
	Alsa, compiler barfed mov instructions.
*/
	memcpy	(Gz.dh.den.left.w,     ((void *)Gz.dh.den.full.w)+3,         40);
	memcpy	(Gz.dh.den.left.w+10,  ((void *)Gz.dh.den.full.w)+42,    400-40);
	memcpy	(Gz.dh.den.left.w+100, ((void *)Gz.dh.den.full.w)+401,  4000-400);
	memcpy	(Gz.dh.den.left.w+1000,((void *)Gz.dh.den.full.w)+4000,40000-4000);
}

/*	dt_next_init is smaller and faster than dt_next_init_slow	*/
static		void	dt_next_init	(void)
{	__builtin_memset	(Gz.dh.den.next,	1,	8);
	__builtin_memset	(Gz.dh.den.next+8,	1,	2);

	__builtin_memset	(Gz.dh.den.next+10,	2,	6);
	__builtin_memset	(Gz.dh.den.next+16,	2,	80);
	__builtin_memset	(Gz.dh.den.next+96,	2,	4);

	__builtin_memset	(Gz.dh.den.next+100,	3,	4);
	__builtin_memset	(Gz.dh.den.next+104,	3,	996);

	__builtin_memset	(Gz.dh.den.next+1000,	4,	9000);
}

/*	dt_next_init_slow is proper larger and slower	*/
__attribute__((unused))
static		void	dt_next_init_slow	(void)
{	memset	(Gz.dh.den.next,     1,10);
	memset	(Gz.dh.den.next+10,  2,90);
	memset	(Gz.dh.den.next+100, 3,900);
	memset	(Gz.dh.den.next+1000,4,9000);
}

static	inline	void	asc	(void)
{	register uint8_t *a,*e;
	a=		(uint8_t *) Gz.dh.hex.full;
	e=	sizeof	(Gz.dh.hex.full)+a;

	for		(;e>a;a+=4)
	{	if	nay	(a[0]>'9')	a[0]+='a'-'0'-0xa;
		if	nay	(a[1]>'9')	a[1]+='a'-'0'-0xa;
		if	nay	(a[2]>'9')	a[2]+='a'-'0'-0xa;
		if	nay	(a[3]>'9')	a[3]+='a'-'0'-0xa;
	}
}

static	inline	void	full_init	(void)
{	register uint8_t	a,b,c,d,*e;
	e=			(uint8_t *)	Gz.dh.hex.full;

	for			(a=0;0x10>a;a++)
	for			(b=0;0x10>b;b++)
	for			(c=0;0x10>c;c++)
	for			(d=0;0x10>d;d++,e+=4)
	{	e[0]=a+0x30;
		e[1]=b+0x30;
		e[2]=c+0x30;
		e[3]=d+0x30;
	}
	asc			();
}

static	inline	void	left_init	(void)
{
memcpy	(Gz.dh.hex.left,       ((void *)Gz.dh.hex.full)+3,     0x40   -0x0);
memcpy	(Gz.dh.hex.left+0x10,  ((void *)Gz.dh.hex.full)+0x42,  0x400  -0x40);
memcpy	(Gz.dh.hex.left+0x100, ((void *)Gz.dh.hex.full)+0x401, 0x4000 -0x400);
memcpy	(Gz.dh.hex.left+0x1000,((void *)Gz.dh.hex.full)+0x4000,0x40000-0x4000);
}

static	inline	void	copy	(uint8_t *a,uint8_t *b)
{	uint8_t	c,*e;
	for		(e=b+0x40000;e>b;)
	if		('9'>=(c=*b++))
	*a++=		c;
	else
	*a++=		c-0x20;
}

static	inline	void	hex_move_init	(void)
{	memset		(Gz.dh.hex.next,       1,0x10);
	memset		(Gz.dh.hex.next+0x10,  2,0x100  -0x10);
	memset		(Gz.dh.hex.next+0x100, 3,0x1000 -0x100);
	memset		(Gz.dh.hex.next+0x1000,4,0x10000-0x1000);
}

SCV	dtgen			(void)
{	dt_full_init		();
	dt_left_init		();
	dt_next_init		();
	ot_full_init		();
	full_init		();
	copy			((uint8_t *)Gz.dh.hex.Full,(uint8_t *)Gz.dh.hex.full);
	left_init		();
	copy			((uint8_t *)Gz.dh.hex.Left,(uint8_t *)Gz.dh.hex.left);
	hex_move_init		();
	xX			();
	mprotect		(&Gz.dh,sizeof(Gz.dh),PROT_READ);
}

__attribute__((constructor))
SCV	init				(void)
{
	opint4[0].int_compat=		1;
	opint4[0].int4_compat=		1;

/*	opint4[0].fromtext=		fromtextint;	*/
	opint4[0].set=			set;
	opint4[0].equal=		equal4;
	opint4[0].add=			add4;
	opint4[0].sub=			sub4;
	opint4[0].addadd=		addadd4;
	opint4[0].subsub=		subsub4;
	opint4[0].or=			or4;
	opint4[0].and=			and4;
	opint4[0].div=			div4;
	opint4[0].mul=			mul4;
	opint4[0].mod=			mod4;
	opint4[0].not=			not;
	opint4[0].xor=			xor4;
	opint4[0].equalequal=		equalequal4;
	opint4[0].notequal=		notequal4;
	opint4[0].less=			less4;
	opint4[0].lessequal=		lessequal4;
	opint4[0].more=			more4;
	opint4[0].moreequal=		moreequal4;
	opint4[0].shl=			shl4;
	opint4[0].shr=			shr4;
	opint4[0].rcl=			rcl4;
	opint4[0].rcr=			rcr4;

	opint4[0].int_compat=		1;
	opint8[0].int8_compat=		1;
/*	opint8[0].fromtext=		fromtextint;	*/
	opint8[0].set=			set;
	opint8[0].equal=		equal8;
	opint8[0].add=			add8;
	opint8[0].sub=			sub8;
	opint8[0].addadd=		addadd8;
	opint8[0].subsub=		subsub8;
	opint8[0].or=			or8;
	opint8[0].and=			and8;
	opint8[0].div=			div8;
	opint8[0].mul=			mul8;
	opint8[0].mod=			mod8;
	opint8[0].not=			not;
	opint8[0].xor=			xor8;
	opint8[0].equalequal=		equalequal8;
	opint8[0].notequal=		notequal8;
	opint8[0].less=			less8;
	opint8[0].lessequal=		lessequal8;
	opint8[0].more=			more8;
	opint8[0].moreequal=		moreequal8;
	opint8[0].shl=			shl8;
	opint8[0].shr=			shr8;
	opint8[0].rcl=			rcl8;
	opint8[0].rcr=			rcr8;

	opfix8[0].int_compat=		1;
	opfix8[0].int_compat=		1;
/*	opfix8[0].fromtext=		fromtextdenfix;	*/
	opfix8[0].set=			set;
	opfix8[0].equal=		equal8;
	opfix8[0].add=			add8;
	opfix8[0].sub=			sub8;
	opfix8[0].addadd=		addadd8;
	opfix8[0].subsub=		subsub8;
	opfix8[0].or=			or8;
	opfix8[0].and=			and8;
	opfix8[0].div=			div8fix;
	opfix8[0].mul=			mul8fix;
	opfix8[0].mod=			mod8;
	opfix8[0].not=			not;
	opfix8[0].xor=			xor8;
	opfix8[0].equalequal=		equalequal8;
	opfix8[0].notequal=		notequal8;
	opfix8[0].less=			less8;
	opfix8[0].lessequal=		lessequal8;
	opfix8[0].more=			more8;
	opfix8[0].moreequal=		moreequal8;
	opfix8[0].shl=			shl8;
	opfix8[0].shr=			shr8;
	opfix8[0].rcl=			rcl8;
	opfix8[0].rcr=			rcr8;

	Gz.out.bin4=			outbin4;
	Gz.out.bin8=			outbin8;
	Gz.out.oct2=			outoct2;
	Gz.out.oct4=			outoct4;
	Gz.out.oct8=			outoct8;
	Gz.out.dex4=			outdex4;
	Gz.out.dex8=			outdex8;
	Gz.out.Dex4=			outDex4;
	Gz.out.Dex8=			outDex8;
	Gz.out.den4=			outden4;
	Gz.out.den8=			outden8;
	Gz.out.fix8=			outfix8;
	Gz.out.nano=			outnano;
	Gz.out.time=			outtime;
	Gz.out.uden32=			uden32;
	Gz.out.asden=			asden;
	intout				();
}
