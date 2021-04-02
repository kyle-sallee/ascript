/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/


#ifndef		AAA
#define		AAA

/*
An   argot
when loaded
the  argot  names
must be     registered.

Variable argument list functions
can  not be   inlined.
What a   pity!
For      each argot registration
a    function
must be  invoked.

Per  line a single aa invocation is possible!
An   example  follows.
*/

/*
__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(byte,		"byte");
	aa		(bytelack,	"bytelack");
	aa		(bytehave,	"bytehave");
	aa_fini		();
};
*/

typedef	struct
{	uint8_t		a[ARGOT_NAME_SIZE];
}	AFIT;

__attribute__((const))
__attribute__((always_inline))
static	inline	ARGOT	**aam	(uint8_t const *a)
{	return		Gz.hash.argot+
	bit128_to_bit16	(a);
}

__attribute__((always_inline))
static	inline	void	aup	(ARGOT *A,void (*b)(void),AFIT const *c)
{	A->at=			b;
	ARGOT		**C=
	aam			(c->a);	/* at compile time computed */
	A->fore=		*C;
	*C=			A;
}

__attribute__((always_inline))
static	inline	void	aup_first(ARGOT *A,void (*b)(void),AFIT const *c)
{	A->at=			b;
	ARGOT		**C=
	aam			(c->a);	/* at compile time computed */
/*	A->fore=		*C;	*/
	*C=			A;
}

#define	aa_init()
#define	aa_fini()
#define	abc1(y,z)	y ## z
#define	abc0(y,z)	abc1(y,z)
#define	abc()	abc0	( argot_,__LINE__)
#define	aa(y,z)	static ARGOT abc()={.name=(z)};aup(&abc(),y,&(AFIT const){.a=z})
#define	aa_first(y,z)	static ARGOT abc()={.name=(z)};aup_first(&abc(),y,&(AFIT const){.a=z})
#endif
