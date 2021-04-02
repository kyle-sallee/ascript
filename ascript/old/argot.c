/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c and argots
	by argot.c some functions are provided.
*/

#define		PROGRAM		1

#include	"ascript.h"
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

static	CALIGN	void	insert		(void);
static	CALIGN	uint8_t	aloadlong	(uint8_t const * const);
static	CALIGN	void	symlink_acquire	(uint8_t *);
static	CALIGN	void	aloadreq	(uint8_t const * const);
static	inline	ARGOT	*aam_get	(uint8_t const * const);
static		uint8_t	aloadfail	(void);

__attribute__((hot))
__attribute__((noinline))
	CALIGN	uint8_t	aload		(uint8_t const * const a)
{	__builtin_memcpy		(strlen(LP)+Gz.ap.p[1],a,0x10);
	int		c=
	faccessat			(Gz.ap.d[0],Gz.ap.p[1],F_OK,AT_EACCESS);

	if			nay	(c!=0)
	return	aloadlong		(a);

	aloadreq			(a);
	insert				();
	if			yay	(Gz.ap.v!=NULL)
	return				0;
	return	aloadfail		();
}

	CALIGN	void	*ahandle	(uint8_t const * const a)
{	__builtin_memcpy		(Gz.ap.p+strlen(LP),a,0x10);
	insert				();
	return				Gz.ap.v;
}

#include	"argotlongname.h"

__attribute__((noinline))
static	CALIGN	uint8_t	aloadlong	(uint8_t const * const a)
{	uint8_t		b[0x10];
	memset				(b,0,0x10);
	longname			(b,a);
	symlink_acquire			(b);
	aloadreq			(b);

	insert				();
	if			yay	(Gz.ap.v!=NULL)
	return				0;
	return	aloadfail		();
}

/*
static	CALIGN	void	ifaload		(uint8_t *);
*/
	CALIGN	uint8_t	ifaload		(uint8_t const * const);

__attribute__((hot))
__attribute__((noinline))
	CALIGN	void	aloadreq	(uint8_t const * const a)
{	uint8_t		b[0x200];

	__builtin_memcpy		(Gz.ap.p[0]+strlen(LP)+4,a,0x10);
	int		c=
	openat				(Gz.ap.d[0],Gz.ap.p[0],O_RDONLY);

	if			yay	(0>c)
	done:
	{	__builtin_memcpy	(Gz.ap.p[1]+strlen(LP),a,0x10);
		return;
	}

	uint8_t		*d=		b+
	read				(c,b,0x200);
	close				(c);
	uint8_t		e[0x20];
	uint8_t		*f=		e,
			*g=		b;
	__builtin_memcpy		(e,g,0x10);

	while				(1)
	if				(f++,nay(*f=='\n'))
	{	__builtin_memset	(f,0,0x10);
		ifaload			(e);
		g+=			f-e+1;
		if		nay	(g>=d)
		goto			done;
		__builtin_memcpy	(e,g,0x10);
		f=			e;
	}
}

/*
__attribute__((hot))
__attribute__((noinline))
static	CALIGN	void	ifaload		(uint8_t *a)
*/

__attribute__((noinline))
	CALIGN	uint8_t	ifaload		(uint8_t const * const a)
{	ARGOT		*A=
	aam_get				(a);

	if			yay	(A==NULL)
	goto				load;

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

	load:
	return
	aload				(a);
}

static	inline	ARGOT	*aam_get	(uint8_t const * const a)
{	return	Gz.aam[bit128_to_bit16(a)];
}

__attribute__((always_inline))
static	inline	void	insert		(void)
{	Gz.ap.d[1]=
	open				(".",O_NONBLOCK|O_PATH|O_RDONLY);
	fchdir				(Gz.ap.d[0]);

	Gz.ap.v=
	dlopen				(Gz.ap.p[1],RTLD_GLOBAL|RTLD_LAZY);
	fchdir				(Gz.ap.d[1]);
	close				(Gz.ap.d[1]);
}

#include	<dlfcn.h>
/*
#include	<link.h>
*/

__attribute__((noinline))
static	CALIGN	void	symlink_acquire	(uint8_t *a)
{	__builtin_memcpy		(Gz.ap.p[2]+strlen(LP)+4,a,0x10);
	uint8_t				b[0x20];

	ssize_t		c=
	readlinkat			(Gz.ap.d[0],Gz.ap.p[2],b,0x20);

	if			yay	(0>=c)
	return;

	__builtin_memset		(c+b,0,0x10);
	__builtin_memcpy		(a,b+3,0x10);
}

__attribute__((constructor(105)))
static	CALIGN	void	ap_init	(void)
{	void		*v=
	dlopen			("libascript.so." MM,RTLD_LOCAL|RTLD_LAZY);
	dlinfo			(v,RTLD_DI_ORIGIN,Gz.ap.p[0]);
	dlclose			(v);

	int		b=
	open			(Gz.ap.p[0],O_NONBLOCK|O_PATH|O_RDONLY);
	Gz.ap.d[0]=
	fcntl			(b,F_DUPFD_CLOEXEC,FDHIGH);
	__builtin_memcpy	(Gz.ap.p[0],LP,strlen(LP));
	__builtin_memcpy	(Gz.ap.p[1],LP,strlen(LP));
	__builtin_memcpy	(Gz.ap.p[2],LP,strlen(LP));

	__builtin_memcpy	(Gz.ap.p[0]+   strlen(LP),"req/",4);
	__builtin_memcpy	(Gz.ap.p[2]+   strlen(LP),"alt/",4);

	close			(b);
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
