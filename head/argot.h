/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by argot.c some functions are provided.
*/

#ifndef	AARGOT
#define	AARGOT	1


#include	<dlfcn.h>

#define	MM	as_string(MAJOR)	"."	as_string(MINOR)
#define	LP	"ascript."	MM	"/"

/*
#define		SMACK	1
*/

/*
ascript: smack moremore lessless
ascript: smack memadd subsub
For four argots only
name to address translation is slower
while for all others
name to address translation
is 2 opcodes faster.
Good choice?
*/


__attribute__((always_inline))
static	inline	void	insert		(uint8_t const *a)
{	__builtin_memcpy		(
	strlen				(LP)+Gz.ap.p[1],a,0x10);
	Gz.ap.v=
	dlopen				(Gz.ap.p[1],RTLD_GLOBAL|RTLD_LAZY);
}


__attribute__((always_inline))
static	inline	int	aload_init	(void)
{	int		a=
	open				(".",O_NONBLOCK|O_PATH|O_RDONLY);
	fchdir				(Gz.ap.d[0]);
	return				a;
}

__attribute__((always_inline))
static	inline	void	aload_fini	(int a)
{	fchdir				(a);
	close				(a);
}

__attribute__((always_inline))
static	inline	ARGOT	**aam_get	(uint8_t const * const a)
{	return	&Gz.hash.argot[bit128_to_bit16(a)];
}

SCV			aloadreq		(uint8_t const * const);
static		uint8_t	aloadfail		(void);

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint8_t	aload		(uint8_t const * const a)
{	int		b=
	aload_init			();
	aloadreq			(a);
	insert				(a);
	aload_fini			(b);

	if			yay	(Gz.ap.v!=NULL)
	return				0;
	return	aloadfail		();
}

__attribute__((unused))
static	CALIGN	void	*ahandle	(uint8_t const * const a)
{	int		b=
	aload_init			();
	insert				(a);
	aload_fini			(b);
	return				Gz.ap.v;
}

__attribute__((unused))
__attribute__((noinline))
static	CALIGN	uint8_t	ifaload		(uint8_t const * const a)
{	ARGOT		*A=
	*aam_get			(a);

/*
warnx	("ifaload a=\"%s\" A=%p",a,A);
if	(A!=NULL)
warnx	("A->name=%s",A->name);
*/

	if			yay	(A==NULL)
	require:
	return	aload			(a);

	uint64_t	b[2],*c;
	b[0]=				*(uint64_t *)(a);
	b[1]=				*(uint64_t *)(a+8);
	do
	{	c=			(uint64_t *)	A->name;
		if		yay	(b[0]==c[0])
		if		yay	(b[1]==c[1])
		return			0;
	}
	while				(A=A->fore);
	goto				require;
}

__attribute__((always_inline))
static	inline	uint8_t	*nl		(uint8_t *a)
{	if		(a[0x0]=='\n')	return	a+0x0;
	if		(a[0x1]=='\n')	return	a+0x1;
	if		(a[0x2]=='\n')	return	a+0x2;
	if		(a[0x3]=='\n')	return	a+0x3;
	if		(a[0x4]=='\n')	return	a+0x4;
	if		(a[0x5]=='\n')	return	a+0x5;
	if		(a[0x6]=='\n')	return	a+0x6;
	if		(a[0x7]=='\n')	return	a+0x7;
	if		(a[0x8]=='\n')	return	a+0x8;
	if		(a[0x9]=='\n')	return	a+0x9;
	if		(a[0xa]=='\n')	return	a+0xa;
	if		(a[0xb]=='\n')	return	a+0xb;
	if		(a[0xc]=='\n')	return	a+0xc;
	if		(a[0xd]=='\n')	return	a+0xd;
	if		(a[0xe]=='\n')	return	a+0xe;
/*	if		(a[0xf]=='\n')	return	a+0xf;	*/
					return	a+0xf;
}

__attribute__((hot))
__attribute__((noinline))
__attribute__((unused))
SCV	aloadreq	(uint8_t const * const a)
{	__builtin_memcpy		(Gz.ap.p[0]+strlen(LP)+4,a,0x10);
	int		b=
	open				(Gz.ap.p[0],O_RDONLY);

	if			yay	(0>b)
	return;

	uint8_t		*c=
	mmap				(NULL,PAGE,PROT_READ,MAP_PRIVATE,b,0);
	close				(b);
	if			nay	(c==(void *) -1)
	return;
	if			nay	(c[0]==0)
	goto				bail;

	uint8_t		d[0x20],*e,*f;
	e=	f=			c;

	while				(1)
	{	f=	nl		(e+1);
		__builtin_memcpy	(d   ,e   ,0x10);
		__builtin_memset	(d+(f-e),0,0x10);
		ifaload			(d);
		e=			f+1;
		if			(e[0]==0)
		{	bail:
			munmap		(c,PAGE);
			return;
		}
	}
}

static	inline	uint8_t	aloadfail	(void)
{	return 1;
}

/*
__attribute__((cold))
__attribute__((noinline))
static		uint8_t	aloadfail	(void)
{	warnx	("%s %s","dlopen",dlerror());
	return	1;
}
*/

#endif
