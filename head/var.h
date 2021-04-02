/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by   var.h some functions are provided.

	Through PLT/GOT
	if called
	the symbol when resolved
	some 700+ opcodes execute and
	PLT/GOT call are a call + jump opcode pair

	This way
	when provided
	the function
	to invoke
	a single opcode call
	executes.

	Of course argot files become larger.
*/

#ifndef		A_VAR
#define		A_VAR

__attribute__((always_inline))
static	inline	void	map_init	(VMETA *A)
{
/*	A->val=				&A->value;	*/
	A->textaddr=	(void *)	&A->text;
	A->textsize=	sizeof		(A->text);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	vmeta_free	(VMETA *A)
{	VMETA		*B,*C=		NULL;

	__builtin_memset		(A,0,sizeof(VMETA));
/*	map_init			(A);
	A->free=			Gz.aide.var_free;
*/
	__atomic_exchange		(&Gz.next.vmeta_reuse
					,&A
					,&B
					,__ATOMIC_RELAXED);
	__atomic_compare_exchange_n	(&A->fore,&C,B,0
					,__ATOMIC_RELAXED
					,__ATOMIC_RELAXED);
/* An unlikely to impossible memory leak exists. */
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	vmeta_free_old	(VMETA *A)
{	VMETA		**B=		&A->fore;

	while				(1)
	{	*B=
		__atomic_exchange_n	(&Gz.next.vmeta_reuse
					,NULL
					,__ATOMIC_RELAXED);
		__atomic_exchange	(&Gz.next.vmeta_reuse
					,&A
					,&A
					,__ATOMIC_RELAXED);
		if		yay	(A==NULL)
		return;
		VMETA		*C;
		for			(C=A->fore;C->fore!=NULL;C=C->fore);
		B=			&C->fore;
	}
}

__attribute__((unused))
__attribute__((noinline))
SCV	var_free_aide		(VMETA *A)
{	if		nay	(A->io.flag&textmapunmap)
	munmap			(A->textaddr,A->textsize);
	if		nay	(A->io.flag&datamapunmap)
	munmap			(A->dataaddr,A->datasize);
	vmeta_free		(A);
}

__attribute__((unused))
static	CALIGN	VMETA	*vmeta_new	(void)
{	VMETA		*A;
	A=
	__atomic_exchange_n		(&Gz.next.vmeta_reuse
					,NULL
					,__ATOMIC_RELAXED);
	if			yay	(A==NULL)
	A=	__atomic_fetch_add	(&Gz.next.vmeta
					,sizeof(VMETA)
					,__ATOMIC_RELAXED);
	else
	{/*	__builtin_memset	(A,0,sizeof(VMETA));	*/
		Gz.next.vmeta_reuse=	A->fore;/* improbable memory leak */
		A->fore=		NULL;
	}
	map_init			(A);
	A->free=			Gz.aide.var_free;
	return				A;
}

__attribute__((unused))
static	CALIGN	VMETA	*vmeta_new_nps	(void)
{	VMETA		*A=
	vmeta_new			();

	uintptr_t	B=		(uintptr_t)	A;
	B&=				PAGE-1;
	if			nay	(B==0)
	{	VMETA	*C=		A;
		A=
		vmeta_new		();
		vmeta_free		(C);
	}
	return				A;
}


__attribute__((unused))
__attribute__((noinline))
SCV	var_from_vless			(VMETA **A)
{	VLESS		*B=		(VLESS *)	*A;

	VMETA		*C=
	vmeta_new			();
	C->vam=				B->vam;

	var_name_copy			(C->name,B->textaddr,
					 C->len= B->textlen);
	vattach_fast			(C);
	*A=				C;
}

/*	The strlen(n)
	when known
	the memcpy performance
	is ideal
*/

/*	For most inlined var_new invocations
	n's byte length is known.
	With immeidate values to memory address mov opcodes
	the memcpy invocation is replaced.
	Thus for strlen 0 opcodes are emitted.
	Because the function is inlined
	the memcpy strlen optimizations
	can become.
*/

/*
by the compiler at compile time the streln(a) value if known
better to minimize the opcode to write name
Instead of 2 opcodes to write 3 bytes one opcode to write 4 bytes ,etc...
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*var_new	(uint8_t const *a)
{	VMETA		*A=
	vmeta_new			();
	memcpy				(A->name,a,A->len=strlen(a));
	vattach				(A);
	return				A;
}

/*
__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*var_new_size	(uint8_t const *a,uint8_t b)
{	VMETA		*A=
	vmeta_new			();
	memcpy				(A->name,a,A->len=b);
	vattach				(A);
	return				A;
}
*/

/*	For most inlined var_new_sub invocations
	n's byte length is known.
	With immeidate values to memory address mov opcodes
	the memcpy invocation is replaced.
	Thus for strlen 0 opcodes are emitted.
	Because the function is inlined
	the memcpy strlen optimizations
	can become.
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*var_new_sub	(uint8_t const *a,VMETA *A)
{	VMETA		*B=
	vmeta_new			();
	B->trash=			A->trash;
	A->trash=			B;

	uint8_t	const	b=
	strlen				(a);

	B->host=			A;
	B->len=				A->len+b;

	__builtin_memcpy		(B->name,A->name,VAR_NAME_SIZE);
	memcpy				(B->name+A->len,a,b);
	vattach				(B);
	return				B;
}

/* By pcre2.c var_new_sub_len is invoked */


__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*var_new_sub_len(uint8_t const *n,VMETA *A,uint8_t c)
{	VMETA		*B=
	vmeta_new			();
	B->trash=			A->trash;
	A->trash=			B;

	B->host=			A;
	B->len=				c		+A->len;
	__builtin_memcpy		(B->name,A->name,VAR_NAME_SIZE);
	memcpy				(B->name        +A->len,n,c);
	vattach				(B);
	return				B;
}

__attribute__((unused))
__attribute__((noinline))
SCV	vardel			(VMETA * const A)
{	if		nay	(A->trash!=NULL)
	vardel			(A->trash);
	vdetach			(A);
	A->free			(A);
}

/*
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	var_name	(VMETA * const A,
					 uint8_t const * const a)
{	__builtin_memcpy		(A->name,a,A->len=strlen(a));
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	var_name_int	(VMETA * const A,
					 uint8_t const * const a,
					 int64_t const b)
{	__builtin_memcpy		(A->name,a,A->len=strlen(a));
	A->value.i=			b;
}
*/

static		uint8_t	varname_match	(void const * const,
					 void const * const);

__attribute__((unused))
__attribute__((returns_nonnull))
__attribute__((always_inline))
static	inline	VMETA	*vf_fast_name	(uint8_t *a,VMETA *A)
{	while				(1)
	{	if		yay	(A->fore==NULL)
		return			A;
		if		yay	(varname_match(a,A->name)==0)
		return			A;
		A=			A->fore;
	}
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*vf_safe_name	(uint8_t *a,VMETA *A)
{	while				(1)
	{	if		nay	(A==NULL)
		return			NULL;
		if		yay	(A->fore==NULL)
		return			A;
		if		yay	(varname_match(a,A->name)==0)
		return			A;
		A=			A->fore;
	}
}

/*	If not found then a segfault is intended.	*/
__attribute__((unused))
__attribute__((returns_nonnull))
__attribute__((always_inline))
static	inline	VMETA	*vf_fast	(VMETA *A,VMETA *B)
{	if			yay	(B->fore==NULL)
	return				B;

	uint8_t	const	*n=		A->textaddr;

	while				(1)
	if			yay	(varname_match(n,B->name)==0)
	return				B;
	else
	if			yay	((B=B->fore)==NULL)
	return				B;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*vf_safe	(VMETA *A, VMETA *B)
{	if			nay	(B==NULL)
	goto				fail;

	if			yay	(B->fore==NULL)
	return				B;

	uint8_t	const	*n=		A->textaddr;

	while				(B)
	if				(varname_match(n,B->name)==0)
	return				B;
	else
	B=				B->fore;
	fail:
	return				NULL;
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	uint8_t	varname_match_slow	(void const * const a,
						 void const * const b)
{	uint64_t	const	*A=	a;
	uint64_t	const	*B=	b;
	int				i;

	for				(i=VAR_NAME_SIZE/8;i;i--)
	if			nay	(*A++^*B++)
	return				1;
	return				0;
}

typedef	uint64_t	vector8x16	__attribute__((vector_size(0x10)));

__attribute__((unused))
__attribute__((always_inline))
static	inline	uint8_t	varname_match	(void const * const a,
					 void const * const b)
{	vector8x16	const	*A=	a;
	vector8x16	const	*B=	b;
	vector8x16			C;
	int				i;

	C[0]=				0;
	C[1]=				0;
	for				(i=VAR_NAME_SIZE/0x10;i;i--)
	C|=				*A++^*B++;
	return				((C[0]|C[1])!=0);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*parapass	(VLESS *A)
{
/*	if		((void *)  A->vam==(void *)A)
	return		(VMETA *)  A;
*/
	return	vf_fast	((VMETA *) A,*A->vam);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	VMETA	*parasafe	(VLESS *A)
{
/*	if		((void *)  A->vam==(void *)A)
	return		(VMETA *)  A;
*/
	return	vf_safe	((VMETA *) A,*A->vam);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	tvarnewa		(void (*A)(VMETA *))
{	VMETA		*B,**C;
	if		nay	(Gz.to[0]==NULL)
	goto			done;

	B=	vmeta_new	();
	var_name_copy		(B->name,Gz.to[0]->textaddr,
				 B->len= Gz.to[0]->textlen);
	if			(Gz.to[0]->op==opref)
	C=			 Gz.to[0]->vam;
	else
	C=			&Gz.hash.var[bit128_to_bit16(B->name)];
	B->vam=			C;
	vattach_fast		(B);
	Gz.to[0]=		B;
	A			(B);
	done:
	argot_next		();
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	tvarnewa_nps	(void (*A)(VMETA *))
{	VMETA		*B,**C;
	if		nay	(Gz.to[0]==NULL)
	goto			done;

	B=	vmeta_new_nps	();
	var_name_copy		(B->name,Gz.to[0]->textaddr,
				 B->len= Gz.to[0]->textlen);
	if			(Gz.to[0]->op==opref)
	C=			 Gz.to[0]->vam;
	else
	C=			&Gz.hash.var[bit128_to_bit16(B->name)];
	B->vam=			C;
	vattach_fast		(B);
	Gz.to[0]=		B;
	A			(B);
	done:
	argot_next		();
}

__attribute__((unused))
SCV	tvarnewab		(void (*A)(VMETA *),void (*B)(void))
{
/*	Gz.aat->func=			B;	*/
	*Gz.at=			B;
	tvarnewa				(A);
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	tsuba	(void (*A)(VMETA *))
{	A			(Gz.to[0]);
	argot_next		();
}

__attribute__((unused))
SCV	tsubab		(void (*A)(VMETA *),void (*B)(void))
{
	*Gz.at=		B;
	tsuba		(A);
}
#endif
