/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"
#include	"ray.h"

static	VMETA		*op[2];

typedef	struct
{	VMETA		*op[2];
}	FUND;

__attribute__((always_inline))
static	inline	 FUND *	fund	(VMETA *A)
{	return	(FUND *)	 A->text +
	sizeof			(A->text)-
	sizeof			(FUND);
}

SCV	funop0		(void)
{	op[0]=		Gz.to[0];
	*Gz.at=		funop0;
	argot_next	();
}

SCV	funop1		(void)
{	op[1]=		Gz.to[0];
	*Gz.at=		funop1;
	argot_next	();
}

__attribute__((noinline))
SCV	reval_add_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		f->op[0]->value.i+
				f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_add_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				+f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_and_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i
				&f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_and_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				&f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_div_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i
				/f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_div_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				/f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_shl_fast	(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		f->op[0]->value.i<<
				f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_shl_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i<<
				 f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_mod_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i
				%f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_mod_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				%f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_shr_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i>>
				 f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_shr_slow	(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i>>
				 f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_mul_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i
				*f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_mul_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				*f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_neg_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		-f->op[0]->value.i;
}

__attribute__((noinline))
SCV	reval_neg_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	A->value.i=		-f->op[0]->value.i;
}

__attribute__((noinline))
SCV	reval_not_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		~f->op[0]->value.i;
}

__attribute__((noinline))
SCV	reval_not_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	A->value.i=		~f->op[0]->value.i;
}

__attribute__((noinline))
SCV	reval_or_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i
				|f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_or_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				|f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_sub_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i
				-f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_sub_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				-f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_xor_fast		(VMETA *A)
{	FUND		*f=
	fund			(A);
	A->value.i=		 f->op[0]->value.i
				^f->op[1]->value.i;
}

__attribute__((noinline))
SCV	reval_xor_slow		(VMETA *A)
{	FUND		*f=
	fund			(A);
	reval			(f->op[0]);
	reval			(f->op[1]);
	A->value.i=		 f->op[0]->value.i
				^f->op[1]->value.i;
}

static	inline	int	optimize1	(VMETA *A)
{
/*	intwant			(fund(A)->op[0]);	*/
	VMETA		*B=	 fund(A)->op[0];

	return			((uintptr_t)B->reval==0);
}

static	inline	int	optimize2	(VMETA *A)
{
/*	intwant			(fund(A)->op[0]);
	intwant			(fund(A)->op[1]);
*/

	VMETA		*B=	 fund(A)->op[0];
	VMETA		*C=	 fund(A)->op[1];

	return			(((uintptr_t)B->reval
				 |(uintptr_t)C->reval)==0);
}

#define	fun1(B,C)			\
	if	yay	(optimize1(A))	\
	(A->reval=B)	(A);		\
	else				\
	(A->reval=C)	(A)

#define	fun2(B,C)			\
	if	yay	(optimize2(A))	\
	(A->reval=B)	(A);		\
	else				\
	(A->reval=C)	(A)

SCV	reval_add	(VMETA *A){fun2(reval_add_fast,reval_add_slow);}
SCV	reval_and	(VMETA *A){fun2(reval_and_fast,reval_and_slow);}
SCV	reval_div	(VMETA *A){fun2(reval_div_fast,reval_div_slow);}
SCV	reval_mod	(VMETA *A){fun2(reval_mod_fast,reval_mod_slow);}
SCV	reval_mul	(VMETA *A){fun2(reval_mul_fast,reval_mul_slow);}
SCV	reval_neg	(VMETA *A){fun1(reval_neg_fast,reval_neg_slow);}
SCV	reval_not	(VMETA *A){fun1(reval_not_fast,reval_not_slow);}
SCV	reval_or	(VMETA *A){fun2(reval_or_fast ,reval_or_slow );}
SCV	reval_shl	(VMETA *A){fun2(reval_shl_fast,reval_shl_slow);}
SCV	reval_shr	(VMETA *A){fun2(reval_shr_fast,reval_shr_slow);}
SCV	reval_sub	(VMETA *A){fun2(reval_sub_fast,reval_sub_slow);}
SCV	reval_xor	(VMETA *A){fun2(reval_xor_fast,reval_xor_slow);}

__attribute__((cold))
static		void	fun	(void){argot_next();}

__attribute__((always_inline))
static	inline	void	rv	(void (*a)(VMETA *))
{	VMETA		*A=
	parapass		(arga(NULL));

	VMETA		*B=
	Gz.to[0]=
	vmeta_new		();
	memcpya			(B->name,A->textaddr,
				 B->len= A->textlen);
	vattach			(B);
	int8init		(B);
	B->reval=	a;
	B->trash=		op[0]->trash;
	op[0]->trash=		B;
	__builtin_memcpy	(fund(B)->op,op,sizeof(op));
}

__attribute__((always_inline))
static	inline	void	funnew	(void (*a)(VMETA *),void (*b)(void))
{	rv			(a);
	*Gz.at=			b;
	argot_next		();
}

SCV	funadd		(void){funnew	(reval_add,	funadd);}
SCV	funand		(void){funnew	(reval_and,	funand);}
SCV	fundiv		(void){funnew	(reval_div,	fundiv);}
SCV	funmod		(void){funnew	(reval_mod,	funmod);}
SCV	funmul		(void){funnew	(reval_mul,	funmul);}
SCV	funneg		(void){funnew	(reval_neg,	funneg);}
SCV	funnot		(void){funnew	(reval_not,	funnot);}
SCV	funor		(void){funnew	(reval_or,	funor );}
SCV	funshl		(void){funnew	(reval_shl,	funshl);}
SCV	funshr		(void){funnew	(reval_shr,	funshr);}
SCV	funsub		(void){funnew	(reval_sub,	funsub);}
SCV	funxor		(void){funnew	(reval_xor,	funxor);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20191210",
	.official=	"20191210",
	.update=	"20200818"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(fun,		"fun");
	aa		(funadd,	"funadd");
	aa		(funand,	"funand");
	aa		(fundiv,	"fundiv");
	aa		(funmod,	"funmod");
	aa		(funmul,	"funmul");
	aa		(funneg,	"funneg");
	aa		(funnot,	"funnot");
	aa		(funor,		"funor");
	aa		(funshl,	"funshl");
	aa		(funshr,	"funshr");
	aa		(funsub,	"funsub");
	aa		(funxor,	"funxor");
	aa		(funop0,	"funop0");
	aa		(funop1,	"funop1");
	aa_fini		();
};
