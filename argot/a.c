/*	By Kyle Sallee from 2015 .. 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"re.h"

__attribute__((always_inline))
static	inline	ZYGOTE	*zparse	(void)
{	return
	zygote_init		(parapass(arga(NULL))->textaddr);
}

SCV	zygoteparse	(void)
{	ZYGOTE		*z=
	zparse		();
	*Gz.at=		zygoteparse;
	argot_jump	(z!=NULL);
}

SCV	zygoteparsepin			(void)
{	ZYGOTE		*z=
	zparse				();
	*Gz.at=				zygoteparsepin;
	if			yay	(z!=NULL)
	{	void	(**L)	(void)=	Gz.at+2;
		(*(Gz.at=z->head))	();
		(*(Gz.at=L))		();
	}
	else
	argot_next			();
}

SCV	a		(void)
{	*Gz.at=		a;
	argot_next	();
}

__attribute__((hot))
static	void	ret_	(void)
{	return;
}

SCV	target_				(void)
{	Gz.to[0]=	parapass	(arga(NULL));
	argot_next			();
}

SCV	target				(void)
{	Gz.to[0]=	parapass	(arga(NULL));
	*Gz.at=				target_;
	argot_next			();
}

SCV	origin_				(void)
{	Gz.to[1]=	parapass	(arga(NULL));
	argot_next			();
}

SCV	origin				(void)
{	Gz.to[1]=	parapass	(arga(NULL));
	*Gz.at=				origin_;
	argot_next			();
}

SCV	name_		(void)
{	Gz.to[0]=	(VMETA *)	arga(NULL);
	argot_next	();
}

SCV	name		(void)
{	Gz.to[0]=	(VMETA *)	arga(NULL);
	*Gz.at=		name_;
	argot_next	();
}

static	inline	void	varlike	(VMETA *A)
{	if			(*A->vam!=A)
	__builtin_memset	(A->textaddr+A->textlen,0,0x10);
}

static	inline	VMETA	**vam	(VMETA *A)
{	return	Gz.hash.var+	bit128_to_bit16	(A->textaddr);
}

__attribute__((always_inline))
static	inline	uint8_t	vnr_do	(uint8_t **a,VMETA **A)
{	*a=
	scratch_do		(VAR_NAME_SIZE*2);

	__builtin_memcpy	(*a,Gz.to[0]->textaddr ,VAR_NAME_SIZE);
	__builtin_memset	(*a+Gz.to[0]->textlen,0,VAR_NAME_SIZE);
/*	if			(Gz.to[0]->vam!=NULL)
	*A=			*Gz.to[0]->vam;
	else
*/
	*A=			Gz.hash.var[bit128_to_bit16(*a)];
}

__attribute__((always_inline))
static	inline	uint8_t	vnr_done	(void)
{	scratch_done			(VAR_NAME_SIZE*2);
}

__attribute__((noinline))
SCV	resolve_		(void)
{	uint8_t			*a;
	VMETA			*A;
	vnr_do			(&a,&A);
	Gz.to[0]=
	vf_fast_name		(a,A);
	vnr_done		();
	argot_next		();
}

SCV			resolve		(void)
{	(*Gz.at=	resolve_)	();
}

__attribute__((noinline))
SCV	exist_			(void)
{	uint8_t			*a;
	VMETA			*A;
	vnr_do			(&a,&A);
	A=
	vf_safe_name		(a,A);
	vnr_done		();

	if			(A!=NULL)
	{	Gz.to[0]=	A;
		argot_skip	();
	}
	else	argot_next	();
}

SCV			exist		(void)
{	(*Gz.at=	exist_)		();
}

SCV	totarget_	(void)
{	Gz.to[0]=	Gz.to[1];
	argot_next	();
}

SCV	totarget	(void)
{	Gz.to[0]=	Gz.to[1];
	*Gz.at=	totarget_;
	argot_next	();
}

SCV	toorigin_	(void)
{	Gz.to[1]=	Gz.to[0];
	argot_next	();
}

SCV	toorigin	(void)
{	Gz.to[1]=	Gz.to[0];
	*Gz.at=	toorigin_;
	argot_next	();
}

SCV	targetnone_	(void)
{	Gz.to[0]=	NULL;
	argot_next	();
}

SCV	targetnone	(void)
{	Gz.to[0]=	NULL;
	*Gz.at=	targetnone_;
	argot_next	();
}

SCV	originnone_	(void)
{	Gz.to[1]=	NULL;
	argot_next	();
}

SCV	originnone	(void)
{	Gz.to[1]=	NULL;
	*Gz.at=		originnone_;
	argot_next	();
}

SCV	targetorigin_	(void)
{	VLESS		*a=
	arga		(NULL);
	Gz.to[0]=	parapass	(a);
	Gz.to[1]=	parapass	(a+1);
	argot_next	();
}

SCV			targetorigin	(void)
{	(*Gz.at=	targetorigin_)	();
}

SCV	targetoriginswap_	(void)
{	__atomic_exchange	(Gz.to,Gz.to+1,Gz.to+1,__ATOMIC_RELAXED);
	argot_next		();
}

SCV			targetoriginswap	(void)
{	(*Gz.at=	targetoriginswap_)	();
}

SCV	origincopy_	(void)
{	Gz.to[0]=	Gz.to[1];
	argot_next	();
}

SCV			origincopy	(void)
{	(*Gz.at=	origincopy_)	();
}

SCV	targetcopy_	(void)
{	Gz.to[1]=	Gz.to[0];
	argot_next	();
}

SCV			targetcopy	(void)
{	(*Gz.at=	targetcopy_)	();
}

SCV	scope_			(void)
{	VMETA		*A=	Gz.to[0];
	argot_next		();
	vardel			(A);
}

SCV	scope			(void)
{	VMETA		*A=	Gz.to[0];
	*Gz.at=			scope_;
	argot_next		();
	vardel			(A);
}

/* The origin var when scoped the target var is scoped */

SCV	scopesame		(void)
{	VMETA		*A,*B;
	for			(A=Gz.to[1];B=A->trash;A=B);
	A->trash=		   Gz.to[0];
	*Gz.at=			scopesame;
	argot_next		();
}

/*
SCV	negint			(void)
{	Gz.to[0]->val->i=	-Gz.to[0]->val->i;
	argot_next		();
}

SCV	negdouble		(void)
{	Gz.to[0]->val->d=	-Gz.to[0]->val->d;
	argot_next		();
}

SCV	_neg				(void)
{	if			yay	(Gz.to[0]->op->int_compat!=0)
	(*Gz.at=	negint)		();
	else
	(*Gz.at=	negdouble)	();
}
*/

#define	SV	__attribute__((aligned(0x20)))	static	void

SV	_add		(void){Gz.to[0]->op->add();}
SV	_addadd		(void){Gz.to[0]->op->addadd();}
SV	_and		(void){Gz.to[0]->op->and();}
SV	_at		(void){Gz.to[0]->op->at();}
SV	_div		(void){Gz.to[0]->op->div();}
SV	_equal		(void){Gz.to[0]->op->equal();}
SV	_equalequal	(void){Gz.to[0]->op->equalequal();}
SV	_less		(void){Gz.to[0]->op->less();}
SV	_lessequal	(void){Gz.to[0]->op->lessequal();}
SV	_more		(void){Gz.to[0]->op->more();}
SV	_moreequal	(void){Gz.to[0]->op->moreequal();}
SV	_mul		(void){Gz.to[0]->op->mul();}
SV	_next_		(void){argot_next();}
SV	_next		(void){*Gz.at=_next_;argot_next();}
SV	_not		(void){Gz.to[0]->op->not();}
SV	_notequal	(void){Gz.to[0]->op->notequal();}
SV	_or		(void){Gz.to[0]->op->or();}
SV	_query		(void){Gz.to[0]->op->query();}
SV	_set		(void){Gz.to[0]->op->set();}
SV	_sub		(void){Gz.to[0]->op->sub();}
SV	_subsub		(void){Gz.to[0]->op->subsub();}
SV	_xor		(void){Gz.to[0]->op->xor();}
SV	_rcl		(void){Gz.to[0]->op->rcl();}
SV	_rcr		(void){Gz.to[0]->op->rcr();}
SV	_shl		(void){Gz.to[0]->op->shl();}
SV	_shr		(void){Gz.to[0]->op->shr();}
SV	_mod		(void){Gz.to[0]->op->mod();}


SCV	call_		(void)
{	argot_next	();
	argot_next	();
}

SCV	call		(void)
{	*Gz.at=	call_;
	argot_next	();
	argot_next	();
}

__attribute__((aligned(0x20)))
static		void	ret	(void)
{	*Gz.at=	ret_;
}

/*
SCV	targettell_		(void)
{	if			(Gz.to[0]->op->tell!=NULL)
	Gz.to[0]->op->tell	(Gz.to+0);
	argot_next		();
}

SCV	targettell		(void)
{	if			(Gz.to[0]->op->tell!=NULL)
	Gz.to[0]->op->tell	(Gz.to+0);
	*Gz.at=			targettell_;
	argot_next		();
}

SCV	origintell_		(void)
{	if			(Gz.to[1]->op->tell!=NULL)
	Gz.to[1]->op->tell	(Gz.to+1);
	argot_next		();
}

SCV	origintell		(void)
{	if			(Gz.to[1]->op->tell!=NULL)
	Gz.to[1]->op->tell	(Gz.to+1);
	*Gz.at=			origintell_;
	argot_next		();
}
*/

SCV	targethost_	(void)
{	Gz.to[0]=	Gz.to[0]->host;
	argot_next	();
}

SCV	targethost	(void)
{	Gz.to[0]=	Gz.to[0]->host;
	*Gz.at=		targethost_;
	argot_next	();
}

SCV	originhost_	(void)
{	Gz.to[1]=	Gz.to[1]->host;
	argot_next	();
}

SCV	originhost	(void)
{	Gz.to[1]=	Gz.to[1]->host;
	*Gz.at=		originhost_;
	argot_next	();
}

#include	"trek.h"

__attribute__((aligned(0x20)))
static		void	gonearfast	(void)
{	(*(Gz.at=	 partsave(NULL)->p))	();
}

SCV	gonear			(uint16_t a)
{	void	(**N)	(void)=
	nearfind_faster		(arga(NULL)->textaddr,partfar(NULL),a);
	*Gz.at=			gonearfast;
	Gz.at=
	partsave(NULL)->p=	N;
	(*Gz.at)		();
}

SCV	gofarfast		(void)
{	Gz.at=
	farmfind_fast		(arga(NULL)->textaddr,partsave(NULL)->p);
	(*Gz.at)		();
}

SCV	pinnearfast			(void)
{	void	(**F)	(void)=		Gz.at;
	(*(Gz.at=partsave(NULL)->p))	();
	(*(Gz.at=F+1))			();
}

SCV	pinnear			(uint16_t a)
{	void	(**F)	(void)=	Gz.at;
	void	(**N)	(void)=
	nearfind_faster		(arga(NULL)->textaddr,partfar(NULL),a);

	*Gz.at=			pinnearfast;
	Gz.at=
	partsave(NULL)->p=	N;
	(*Gz.at)		();
	(*(Gz.at=F+1))		();
}

SCV	gofar			(uint16_t a)
{	*Gz.at=			gofarfast;
	partsave(NULL)->p=	&Gz.hash.far[a];
	Gz.at=
	farmfind_fast		(arga(NULL)->textaddr,partsave(NULL)->p);
	(*Gz.at)		();
}

SCV	pinfarfast		(void)
{	void	(**F)	(void)=	Gz.at;
	Gz.at=
	farmfind_fast		(arga(NULL)->textaddr,partsave(NULL)->p);
	(*Gz.at)		();
	(*(Gz.at=F+1))		();
}

SCV	pinfar			(uint16_t a)
{	void	(**F)	(void)=	Gz.at;

	*Gz.at=			pinfarfast;
	partsave(NULL)->p=	&Gz.hash.far[a];
	Gz.at=
	farmfind_fast		(arga(NULL)->textaddr,partsave(NULL)->p);

	(*Gz.at)		();
	(*(Gz.at=F+1))		();
}

SCV	go			(void)
{	uint16_t	a=
	jidx			(arga(NULL)[0].textaddr);
/*	if		yay	(arga(NULL)[0].value.b=='\'')	*/
	if		yay	(arga(NULL)[0].op==opnear)
	gonear			(a);
	else
	gofar			(a);
}

SCV	pin			(void)
{	uint16_t	a=
	jidx			(arga(NULL)[0].textaddr);
/*	if		yay	(arga(NULL)[0].value.b=='\'')	*/
	if		yay	(arga(NULL)[0].op==opnear)
	pinnear			(a);
	else
	pinfar			(a);
}

/*
An _Atomic int64_t * is not desired.
The opcode lock emission is not desired.
For lnx1 by gcc Gcc 3 opcodes or 5 opcodes
can be emitted.
Why it makes the inane 5 opcode choice is uncertain.
*/

#define	lnx00(a,N)	{--(*(_Atomic int64_t *)(a));	\
			 Gz.at=	(N);	(*N)	();}

#define	lnx0(a,N)	{Gz.at=	(N);	(*N)	();	--(*(a))}

#define	lnx1(a,N)	{Gz.at=	(N);	(*N)	();	--(*(a));}
#define	lnx2(a,N)	{lnx1((a),(N));		lnx1((a),(N));}
#define	lnx3(a,N)	{lnx2((a),(N));		lnx1((a),(N));}
#define	lnx4(a,N)	{lnx2((a),(N));		lnx2((a),(N));}
#define	lnx5(a,N)	{lnx4((a),(N));		lnx1((a),(N));}
#define	lnx6(a,N)	{lnx4((a),(N));		lnx2((a),(N));}
#define	lnx7(a,N)	{lnx4((a),(N));		lnx3((a),(N));}
#define	lnx8(a,N)	{lnx4((a),(N));		lnx4((a),(N));}
#define	lnx9(a,N)	{lnx8((a),(N));		lnx1((a),(N));}
#define	lnxa(a,N)	{lnx8((a),(N));		lnx2((a),(N));}
#define	lnxb(a,N)	{lnx8((a),(N));		lnx3((a),(N));}
#define	lnxc(a,N)	{lnx8((a),(N));		lnx4((a),(N));}
#define	lnxd(a,N)	{lnx8((a),(N));		lnx5((a),(N));}
#define	lnxe(a,N)	{lnx8((a),(N));		lnx6((a),(N));}
#define	lnxf(a,N)	{lnx8((a),(N));		lnx7((a),(N));}
#define	lnx10(a,N)	{lnx8((a),(N));		lnx8((a),(N));}

#define	lnx20(a,N)	{lnx10((a),(N));	lnx10((a),(N));}
/*
Beyond lnx20 the performance
does not improve.
*/

#define	lnx40(a,N)	{lnx20((a),(N));		lnx20((a),(N));}
#define	lnx80(a,N)	{lnx40((a),(N));		lnx40((a),(N));}
#define	lnx100(a,N)	{lnx80((a),(N));		lnx80((a),(N));}

#define	lnx(a,N,v)	{(*(a)=(v));	Gz.at=	(N);	(*N)	();}

/* This loops does conditional jump, branch prediction helps
   is fastest and improper
   Only when the counter value reaches 0
   the loop stops.
*/

/*
by gcc
__attribute__((optimize("align-loops=64")))
is probably ignored.
If obeyed the performance might not improve.
Of course C compilers regard source as a mild suggestion.
*/

__attribute__((noinline))
/*__attribute__((optimize("align-loops=64")))
*/
SCV	loop_				(void)
{	uint32_t	*a=
	&parapass			(arga(NULL))->value.i4.l;

	*Gz.at=				loop_;
	void		(**N)	(void)=	Gz.at+1;

	while				(*a>=0x20)
	lnx20				(a,N);

	switch				(*a)
	{	case	0x1f:	lnx	(a,N,0x1f);
		case	0x1e:	lnx	(a,N,0x1e);
		case	0x1d:	lnx	(a,N,0x1d);
		case	0x1c:	lnx	(a,N,0x1c);
		case	0x1b:	lnx	(a,N,0x1b);
		case	0x1a:	lnx	(a,N,0x1a);
		case	0x19:	lnx	(a,N,0x19);
		case	0x18:	lnx	(a,N,0x18);
		case	0x17:	lnx	(a,N,0x17);
		case	0x16:	lnx	(a,N,0x16);
		case	0x15:	lnx	(a,N,0x15);
		case	0x14:	lnx	(a,N,0x14);
		case	0x13:	lnx	(a,N,0x13);
		case	0x12:	lnx	(a,N,0x12);
		case	0x11:	lnx	(a,N,0x11);
		case	0x10:	lnx	(a,N,0x10);
		case	0xf:	lnx	(a,N,0xf);
		case	0xe:	lnx	(a,N,0xe);
		case	0xd:	lnx	(a,N,0xd);
		case	0xc:	lnx	(a,N,0xc);
		case	0xb:	lnx	(a,N,0xb);
		case	0xa:	lnx	(a,N,0xa);
		case	0x9:	lnx	(a,N,9);
		case	0x8:	lnx	(a,N,8);
		case	0x7:	lnx	(a,N,7);
		case	0x6:	lnx	(a,N,6);
		case	0x5:	lnx	(a,N,5);
		case	0x4:	lnx	(a,N,4);
		case	0x3:	lnx	(a,N,3);
		case	0x2:	lnx	(a,N,2);
		case	0x1:	lnx	(a,N,1);	*a=	0;
		default:	break;
	}

	argot_next			();
}

/*
The compiler because inane
the switch case statement also
must be inane.
And it still wastes opcode!
*/

__attribute__((aligned(0x20)))
static	inline	void	skip_	(void)
{	argot_skip		();
}

__attribute__((aligned(0x20)))
static		void	skip	(void)
{	(*Gz.at=	skip_)	();
}

__attribute__((aligned(0x20)))
static		void	loop	(void)
{	(*Gz.at=	loop_)	();
}

SCV		targetpush_	(void)
{	VMETA		*A=	Gz.to[0];
	argot_next		();
	Gz.to[0]=		A;
}

SCV		targetpush	(void)
{	VMETA		*A=	Gz.to[0];
	argot_next		();
	*Gz.at=			targetpush_;
	Gz.to[0]=		A;
}

SCV		originpush_	(void)
{	VMETA		*A=	Gz.to[1];
	argot_next		();
	Gz.to[0]=		A;
}

SCV		originpush	(void)
{	VMETA		*A=	Gz.to[1];
	argot_next		();
	*Gz.at=			originpush_;
	Gz.to[1]=		A;
}

SCV		chdir__		(void)
{	chdir			(parapass(arga(NULL))->textaddr);
	argot_next		();
}

static	void	chdir_		(void)
{	(*Gz.at=chdir__)	();
}

/*
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	ival	(VMETA *A)
{	uint8_t		*a=	A->textaddr;
	uint8_t		b=	A->textlen;
	if			(b==1)
	b= 		yay	(a[0]-'0');
	else	if		(b==2)
	b=			(a[0]-'0')*10 +(a[1]-'0');
	else
	b=			(a[0]-'0')*100+(a[1]-'0')*10 +a[2]-'0';
	A->value.i=		b;
}
*/

SCV			lax	(void)
{	*Gz.at=		lax;
	Gz.at[1]=	Gz.aide.adef0;
	argot_next	();
}

__attribute__((always_inline))
static	inline	void	targetcite_	(uint8_t a)
{	Gz.to[0]=	Gz.target_keep[a];
	argot_next	();
}

__attribute__((always_inline))
static	inline	void	origincite_	(uint8_t a)
{	Gz.to[1]=	Gz.origin_keep[a];
	argot_next	();
}

__attribute__((always_inline))
static	inline	void	targetkeep_	(uint8_t a)
{	VMETA		*A=		Gz.target_keep[a];
	Gz.target_keep[a]=		Gz.to[0];
	argot_next			();
	Gz.target_keep[a]=		A;
}

__attribute__((always_inline))
static	inline	void	originkeep_	(uint8_t a)
{	VMETA		*A=		Gz.origin_keep[a];
	Gz.origin_keep[a]=		Gz.to[1];
	argot_next			();
	Gz.origin_keep[a]=		A;
}

__attribute__((always_inline))
static	inline	void	targetkeep__	(uint8_t a,void (*b)(void))
{	VMETA		*A=		Gz.target_keep[a];
	Gz.target_keep[a]=		Gz.to[0];
	*Gz.at=				b;
	argot_next			();
	Gz.target_keep[a]=		A;
}

__attribute__((always_inline))
static	inline	void	originkeep__	(uint8_t a,void (*b)(void))
{	VMETA		*A=		Gz.origin_keep[a];
	Gz.origin_keep[a]=		Gz.to[1];
	*Gz.at=				b;
	argot_next			();
	Gz.origin_keep[a]=		A;
}

/*
SCV	targetkeep0_	(void)		{targetkeep_(0);};
SCV	targetkeep1_	(void)		{targetkeep_(1);};
SCV	targetkeep2_	(void)		{targetkeep_(2);};
SCV	targetkeep3_	(void)		{targetkeep_(3);};
SCV	targetkeep4_	(void)		{targetkeep_(4);};
SCV	targetkeep5_	(void)		{targetkeep_(5);};
SCV	targetkeep6_	(void)		{targetkeep_(6);};
SCV	targetkeep7_	(void)		{targetkeep_(7);};

SCV	originkeep0_	(void)		{originkeep_(0);};
SCV	originkeep1_	(void)		{originkeep_(1);};
SCV	originkeep2_	(void)		{originkeep_(2);};
SCV	originkeep3_	(void)		{originkeep_(3);};
SCV	originkeep4_	(void)		{originkeep_(4);};
SCV	originkeep5_	(void)		{originkeep_(5);};
SCV	originkeep6_	(void)		{originkeep_(6);};
SCV	originkeep7_	(void)		{originkeep_(7);};
*/

SCV	targetcite0_	(void)		{targetcite_(0);};
SCV	targetcite1_	(void)		{targetcite_(1);};
SCV	targetcite2_	(void)		{targetcite_(2);};
SCV	targetcite3_	(void)		{targetcite_(3);};
SCV	targetcite4_	(void)		{targetcite_(4);};
SCV	targetcite5_	(void)		{targetcite_(5);};
SCV	targetcite6_	(void)		{targetcite_(6);};
SCV	targetcite7_	(void)		{targetcite_(7);};

SCV	origincite0_	(void)		{origincite_(0);};
SCV	origincite1_	(void)		{origincite_(1);};
SCV	origincite2_	(void)		{origincite_(2);};
SCV	origincite3_	(void)		{origincite_(3);};
SCV	origincite4_	(void)		{origincite_(4);};
SCV	origincite5_	(void)		{origincite_(5);};
SCV	origincite6_	(void)		{origincite_(6);};
SCV	origincite7_	(void)		{origincite_(7);};

/*
SCV	targetkeep0	(void)		{(*Gz.at=targetkeep0_)();}
SCV	targetkeep1	(void)		{(*Gz.at=targetkeep1_)();}
SCV	targetkeep2	(void)		{(*Gz.at=targetkeep2_)();}
SCV	targetkeep3	(void)		{(*Gz.at=targetkeep3_)();}
SCV	targetkeep4	(void)		{(*Gz.at=targetkeep4_)();}
SCV	targetkeep5	(void)		{(*Gz.at=targetkeep5_)();}
SCV	targetkeep6	(void)		{(*Gz.at=targetkeep6_)();}
SCV	targetkeep7	(void)		{(*Gz.at=targetkeep7_)();}

SCV	originkeep0	(void)		{(*Gz.at=originkeep0_)();}
SCV	originkeep1	(void)		{(*Gz.at=originkeep1_)();}
SCV	originkeep2	(void)		{(*Gz.at=originkeep2_)();}
SCV	originkeep3	(void)		{(*Gz.at=originkeep3_)();}
SCV	originkeep4	(void)		{(*Gz.at=originkeep4_)();}
SCV	originkeep5	(void)		{(*Gz.at=originkeep5_)();}
SCV	originkeep6	(void)		{(*Gz.at=originkeep6_)();}
SCV	originkeep7	(void)		{(*Gz.at=originkeep7_)();}
*/

SCV	targetkeep0	(void)		{targetkeep__(0,targetkeep0);}
SCV	targetkeep1	(void)		{targetkeep__(1,targetkeep1);}
SCV	targetkeep2	(void)		{targetkeep__(2,targetkeep2);}
SCV	targetkeep3	(void)		{targetkeep__(3,targetkeep3);}
SCV	targetkeep4	(void)		{targetkeep__(4,targetkeep4);}
SCV	targetkeep5	(void)		{targetkeep__(5,targetkeep5);}
SCV	targetkeep6	(void)		{targetkeep__(6,targetkeep6);}
SCV	targetkeep7	(void)		{targetkeep__(7,targetkeep7);}

SCV	originkeep0	(void)		{originkeep__(0,originkeep0);}
SCV	originkeep1	(void)		{originkeep__(1,originkeep1);}
SCV	originkeep2	(void)		{originkeep__(2,originkeep2);}
SCV	originkeep3	(void)		{originkeep__(3,originkeep3);}
SCV	originkeep4	(void)		{originkeep__(4,originkeep4);}
SCV	originkeep5	(void)		{originkeep__(5,originkeep5);}
SCV	originkeep6	(void)		{originkeep__(6,originkeep6);}
SCV	originkeep7	(void)		{originkeep__(7,originkeep7);}

SCV	targetcite0	(void)		{(*Gz.at=targetcite0_)();}
SCV	targetcite1	(void)		{(*Gz.at=targetcite1_)();}
SCV	targetcite2	(void)		{(*Gz.at=targetcite2_)();}
SCV	targetcite3	(void)		{(*Gz.at=targetcite3_)();}
SCV	targetcite4	(void)		{(*Gz.at=targetcite4_)();}
SCV	targetcite5	(void)		{(*Gz.at=targetcite5_)();}
SCV	targetcite6	(void)		{(*Gz.at=targetcite6_)();}
SCV	targetcite7	(void)		{(*Gz.at=targetcite7_)();}

SCV	origincite0	(void)		{(*Gz.at=origincite0_)();}
SCV	origincite1	(void)		{(*Gz.at=origincite1_)();}
SCV	origincite2	(void)		{(*Gz.at=origincite2_)();}
SCV	origincite3	(void)		{(*Gz.at=origincite3_)();}
SCV	origincite4	(void)		{(*Gz.at=origincite4_)();}
SCV	origincite5	(void)		{(*Gz.at=origincite5_)();}
SCV	origincite6	(void)		{(*Gz.at=origincite6_)();}
SCV	origincite7	(void)		{(*Gz.at=origincite7_)();}

SCV	yaytarget_	(void)		{argot_jump(Gz.to[0]!=NULL);}
SCV	naytarget_	(void)		{argot_jump(Gz.to[0]==NULL);}
SCV	yayorigin_	(void)		{argot_jump(Gz.to[1]!=NULL);}
SCV	nayorigin_	(void)		{argot_jump(Gz.to[1]==NULL);}

SCV	yaytarget	(void)		{(*Gz.at=yaytarget_)();}
SCV	naytarget	(void)		{(*Gz.at=naytarget_)();}
SCV	yayorigin	(void)		{(*Gz.at=yayorigin_)();}
SCV	nayorigin	(void)		{(*Gz.at=nayorigin_)();}

SCV	success_	(void)		{argot_jump(Gz.to[0]->io.success==0);}
SCV	failure_	(void)		{argot_jump(Gz.to[0]->io.success!=0);}
SCV	successset_	(void)		{Gz.to[0]->io.success=0;argot_next();}
SCV	failureset_	(void)		{Gz.to[0]->io.success=1;argot_next();}

SCV	keepcite	(void)
{	static	uint8_t	did;
	*Gz.at=		keepcite;
	if	nay	(did!=0)
	goto		done;
	aa_init		();
	aa		(targetkeep0,	"targetkeep0");
	aa		(targetkeep1,	"targetkeep1");
	aa		(targetkeep2,	"targetkeep2");
	aa		(targetkeep3,	"targetkeep3");
	aa		(targetkeep4,	"targetkeep4");
	aa		(targetkeep5,	"targetkeep5");
	aa		(targetkeep6,	"targetkeep6");
	aa		(targetkeep7,	"targetkeep7");

	aa		(originkeep0,	"originkeep0");
	aa		(originkeep1,	"originkeep1");
	aa		(originkeep2,	"originkeep2");
	aa		(originkeep3,	"originkeep3");
	aa		(originkeep4,	"originkeep4");
	aa		(originkeep5,	"originkeep5");
	aa		(originkeep6,	"originkeep6");
	aa		(originkeep7,	"originkeep7");

	aa		(targetcite0,	"targetcite0");
	aa		(targetcite1,	"targetcite1");
	aa		(targetcite2,	"targetcite2");
	aa		(targetcite3,	"targetcite3");
	aa		(targetcite4,	"targetcite4");
	aa		(targetcite5,	"targetcite5");
	aa		(targetcite6,	"targetcite6");
	aa		(targetcite7,	"targetcite7");

	aa		(origincite0,	"origincite0");
	aa		(origincite1,	"origincite1");
	aa		(origincite2,	"origincite2");
	aa		(origincite3,	"origincite3");
	aa		(origincite4,	"origincite4");
	aa		(origincite5,	"origincite5");
	aa		(origincite6,	"origincite6");
	aa		(origincite7,	"origincite7");
	aa_fini		();
	done:
	argot_next	();

}


static	void	success		(void)	{(*Gz.at=success_)();}
static	void	failure		(void)	{(*Gz.at=failure_)();}
static	void	successset	(void)	{(*Gz.at=successset_)();}
static	void	failureset	(void)	{(*Gz.at=failureset_)();}

__attribute__((cold))
		void	segv	(void)
{	if		(Gz.to[0]==NULL)
	{	warnx	("%s",
			 "A    var      name\n"
			 "to   var      address\n"
			 "when resolved\n"
			 "the  var\n"
			 "when not      created\n"
			 "a    segfault becomes.\n"
			 "An   operator argot\n"
			 "when invoked\n"
			 "the  target\n"
			 "when empty\n"
			 "a    segfault becomes.\n");
		return;
	}

	VLESS	*L=	arga	(NULL);
	if		((L[0].op!=opvalue)&&
			 (L[0].textaddr[0]>='0')&&
			 (L[0].textaddr[0]<='9'))
	{	nan:
		warnx	("%s",
			 "Was a number intended,\n"
			 "but a suffix,\n"
			 "such as /b /o /d /f /x,\n"
			 "accidentally omitted?");
		return;
	}

	if		((L[1].op!=opvalue)&&
			 (L[1].textaddr[0]>='0')&&
			 (L[1].textaddr[0]<='9'))
	goto		nan;
}

const	ARGOT_INFO	AI=
{	.author=		"Kyle David Sallee",
	.author_email=		"kyle.sallee@gmail.com",
	.homepage=		"https://kyle-sallee.github.io/ascript/",
	.create=		"20170707",
	.official=		"20170707",
	.update=		"20200922",
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(a,		"a");
	aa		(lax,		"lax");
	aa		(re,		"re");
	aa		(keepcite,	"keepcite");

	aa		(zygoteparse,	"zygoteparse");
	aa		(zygoteparsepin,"zygoteparsepin");

	aa		(success,	"success");
	aa		(failure,	"failure");
	aa		(successset,	"successset");
	aa		(failureset,	"failureset");

	aa		(yaytarget,	"yaytarget");
	aa		(naytarget,	"naytarget");
	aa		(yayorigin,	"yayorigin");
	aa		(nayorigin,	"nayorigin");

	aa		(targetnone,	"targetnone");
	aa		(originnone,	"originnone");

	aa		(targetpush,	"targetpush");
	aa		(originpush,	"originpush");

	aa		(targethost,	"targethost");
	aa		(originhost,	"originhost");

/*	aa		(targettell,	"targettell");
	aa		(origintell,	"origintell");
*/

	aa		(totarget,	"totarget");
	aa		(toorigin,	"toorigin");

	aa		(call,		"call");
	aa		(ret,		"ret");

	aa		(targetorigin,	"targetorigin");
	aa		(targetoriginswap,"targetoriginswap");
	aa		(origincopy,	"origincopy");
	aa		(targetcopy,	"targetcopy");

	aa		(scope,		"scope");
	aa		(scopesame,	"scopesame");

	aa		(_add,		"+");
	aa		(_add,		"add");
	aa		(_addadd,	"++");
	aa		(_addadd,	"addadd");
	aa		(_and,		"&");
	aa		(_and,		"and");
	aa		(_at,		"@");
	aa		(_at,		"at");
	aa		(_div,		"/");
	aa		(_div,		"div");
	aa		(_equal,	"=");
	aa		(_equal,	"equal");
	aa		(_equalequal,	"==");
	aa		(_equalequal,	"equalequal");
	aa		(_less,		"<");
	aa		(_less,		"less");
	aa		(_lessequal,	"<=");
	aa		(_lessequal,	"lessequal");

	aa		(_more,		">");
	aa		(_more,		"more");
	aa		(_moreequal,	">=");
	aa		(_moreequal,	"moreequal");
	aa		(_mul,		"*");
	aa		(_mul,		"mul");
/*	aa		(_neg,		"neg");		*/
	aa		(_next,		"next");
	aa		(_not,		"!");
	aa		(_not,		"not");
	aa		(_notequal,	"!=");
	aa		(_notequal,	"notequal");
	aa		(_or,		"|");
	aa		(_or,		"or");
	aa		(_query,	"?");
	aa		(_query,	"query");
	aa		(_set,		"set");
	aa		(_sub,		"-");
	aa		(_sub,		"sub");
	aa		(_subsub,	"--");
	aa		(_subsub,	"subsub");
	aa		(_xor,		"xor");
	aa		(_rcl,		"rcl");
	aa		(_rcr,		"rcr");
	aa		(_shl,		"shl");
	aa		(_shr,		"shr");
	aa		(_mod,		"mod");

	aa		(loop,		"loop");
	aa		(skip,		"skip");
	aa		(pin,		"pin");
	aa		(go,		"go");

	aa		(resolve,	"resolve");
	aa		(exist,		"exist");

	aa		(chdir_,	"chdir");

	aa		(name,		"name");
	aa		(origin,	"origin");
	aa		(target,	"target");

	aa_fini		();
};
