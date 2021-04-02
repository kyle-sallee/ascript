/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"argot.h"
#include	"a.h"
#include	<dlfcn.h>	/* to get the segv address */
#include	<execinfo.h>	/* for backtrace */
#include	<signal.h>
#include	<stdio.h>	/* for dprintf */

__attribute__((aligned(0x20)))
static		void	_segfault	(void)
{	argot_next	();
}

static	inline	void	*backshow	(void);
static	inline	void	argot_segv	(void *);
/*
static	inline	void	op_segv		(void);
*/
static		void	action		(int x,siginfo_t *i,void *v)
{	ZYGOTE		*z=
	script_zygote			();

	dprintf		(2,"Segmentation fault detected.\n");
	dprintf		(2,"%-10s%s\n",	"script",	z->file_name);
	dprintf		(2,"%-10s%i\n",	"line",		script_line_number());
	dprintf		(2,"%-10s",	"part");
	write		(2,partfrom(NULL),		partlen());
	dprintf		(2,"\n%-10s%p\n","target",	Gz.to[0]);
	dprintf		(2,"%-10s%p\n",	"origin",	Gz.to[1]);
	dprintf		(2,"%-10s%i\n",	"errno",	errna);
	dprintf		(2,"%-10s%s\n",	"errstr",	strerror(errna));
	dprintf		(2,"%-10s%p\n",	"address",	i->si_addr);

	if			(i->si_addr==NULL)
	dprintf			(2,"%s","A NULL value pointer was dereferenced. "
				"In the script "
				"at or afore the segfault "
				"an expected var address "
				"might not exist.");

	if			(errna==ENOMEM)
	dprintf			(2,"%s","A function mmap invocation failed?");

	uint8_t		*a;
	switch			(i->si_code)
	{	case	SEGV_MAPERR:	a="The address is not mapped";	break;
		case	SEGV_ACCERR:	a="The protection differs";	break;
	}
	dprintf			(2,"%-10s%s","why",a);

	void		*b=
	backshow		();
	argot_segv		(b);
}

/*
__attribute__((always_inline))
static	inline	void	op_segv		(void)
{	VMETA		*A=		Gz.to[0];
	if			yay	(A		!=NULL)
	if			yay	(A->op		!=NULL)
	if			yay	(A->op->segv	!=NULL)
	A->op->segv			();
}
*/

__attribute__((always_inline))
static	inline	void	argot_segv	(void *a)
{	Dl_info		b;
	dladdr				(a,&b);
	if				(b.dli_fname)
	{	uint8_t	const *c;
		uint8_t	const *d;
		c=
		d=			b.dli_fname;
		for			(;*c;c++)
		if			(*c=='/')
		d=			c+1;

		void	*e=
		ahandle			(d);
		void	(*f)		(void)=
		dlsym			(e,"segv");
		if		yay	(f!=NULL)
		f			();
	}
}

__attribute__((always_inline))
static	inline	void	*backshow	(void)
{	int		a;
	void		*b	[0x1000];

	dprintf			(2,"\nBacktrace folows\n");
	a=
	backtrace		(b,0x1000);
	backtrace_symbols_fd	(b,a,2);
	dprintf			(2,"Backtrace complete\n");
/*
warnx	("b[2]=%p",b[2]);
*/
	return			b[2];
}

__attribute__((unused))
const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20181012",
	.official=	"20181012",
	.update=	"20200707"
};

__attribute__((constructor))
static	CALIGN	void	aainit		(void)
{	aa_init		();
	aa		(_segfault,	"segfault");
	aa_fini		();
};


__attribute__((constructor))
static	CALIGN	void	init		(void)
{	Gz.sa[0].sa_flags=		SA_SIGINFO|SA_RESETHAND;
	Gz.sa[0].sa_sigaction=		action;
	Gz.sig[SIGSEGV]=		(void *)	-1;
	sigaction			(SIGSEGV,Gz.sa,NULL);
}
