/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
/*
#include	"exefast.h"
*/
#include	"sire.h"
#include	<spawn.h>
#include	<stdlib.h>
#include	<stdnoreturn.h>
#ifdef		__linux__
#include	<linux/memfd.h>
#endif

typedef	struct
{	uint8_t	*a	[0x1000];
	uint8_t	b	[HUGE-sizeof(void *)*0x1000];
}		EXEDATA;
PALIGN	static	EXEDATA	ed;

__attribute__((noinline))
SCV	lastwait_	(void)
{	waitthis	(pids.last,WEXITED);
	argot_next	();
}

__attribute__((noinline))
SCV	allwait_	(void)
{	waitall		(WEXITED);
	argot_next	();
}

__attribute__((aligned(0x20)))
static	void	allwait		(void)
{	(*Gz.at=allwait_)	();
}

__attribute__((aligned(0x20)))
static	void	lastwait	(void)
{	(*Gz.at=lastwait_)	();
}

/*	Function exemust
	function exemust1
	when compiled
	on the stack
	garbage remains
	because
	to the appropriate line's argot
	by the innane gcc compiler
	rather than the jump opcode
	the call opcode
	is emitted.
*/

static	inline	void	sigchld_skip	(void)
{	pids.skip=	1;
}

static	inline	void	sigchld_resume	(void)
{	pids.skip=		0;
	if		nay	((volatile uint8_t) pids.miss)
	{	pids.miss=	0;
		sigqueue	(0,SIGCHLD,
				(union sigval){ .sival_int=0});
	}
}

__attribute__((noinline))
__attribute__((hot))
static	CALIGN	pid_t	spawner		(void)
{	char		**e=		(char **)	Gz.env[0].dataaddr;

	sigchld_skip			();

	pid_t		p;
	errna=	posix_spawnp		(&p,(char * )ed.a[0],NULL,NULL,
					    (char **)ed.a,e);

	if			yay	(errna==0)
	{	pids.now++;
		pids.last=		p;
		pids.done[p]=		0;
		pids.exit[p]=		0;
		pids.stop[p]=		0;
		pids.origin[p]=		NULL;
		pids.target[p]=		NULL;
		pids.pin[p]=		NULL;
		sigchld_resume		();
		return			p;
	}
	else
	{	sigchld_resume		();
		return			0;
	}
}

__attribute__((noinline))
SCV	exemust_		(void)
{	VMETA		*A=
	parapass		(arga(NULL));
/*	denwant			(A);		*/
	uint8_t		a=	A->value.i4.l;
	pid_t		p=	pids.last;
	waitthis		(p,WEXITED);
	argot_jump		(pids.exit[p]==a);
}

__attribute__((noinline))
SCV	acquire				(void)
{	uint8_t		*pd;
	VMETA		*A;
	VLESS		**D=
	aarga				(NULL);

	VLESS		*B=		D[0],
			*C=		D[1];

/*	VLESS		*B=	arga	(Gz.at),
			*C=	arga	(Gz.at+1);
*/

	for				(pd=ed.b;C>B;B++)
	{	A=	parapass	(B);
		show			(A);
		memcpya			(pd,A->textaddr,A->textlen);
		pd+=					A->textlen;
	}
	*pd=				0;

	/*	pd-1 explicit value 0 byte empty parameter circumvention */
	uint8_t		*pe,**pv;
	pe=				pd-1;
	pd=				ed.b;
	pv=				ed.a;
	*pv++=				pd;
	while				(1)
	{	while			(*pd++!=0);
		if		yay	(pe>pd)
		*pv++=			pd++;
		else
		break;
	}
	*pv=				NULL;
}

SCV	exeyield	(void)
{	acquire		();
	char	**e=	(char **)	Gz.env[0].dataaddr;

	errna=		0;
	execvpe		((char *)ed.a[0],(char **)ed.a,e);
	argot_next	();
}

__attribute__((noinline))
static	void	exemust		(void)
{	(*Gz.at=exemust_)	();
}

__attribute__((noinline))
static	void	exefast_	(void)
{	acquire			();
	argot_jump		(spawner()!=0);
}

static	void	exefastloaded	(void)
{	argot_next		();
}

SCV	exefast			(void)
{	VLESS		**A=
	aarga			(NULL);

	if			(A[0]!=A[1])
	(*Gz.at=exefast_)	();
	else
	(*Gz.at=exefastloaded)	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180228",
	.official=	"20180228",
	.update=	"20200721"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(exeyield,	"exeyield");
	aa		(exemust,	"exemust");
	aa		(exefast,	"exefast");
	aa		(lastwait,	".");
	aa		(allwait,	"..");
	aa_fini		();
};

extern	char	**environ;

__attribute__((constructor))
SCV	init	(void)
{	static	CALIGN	VMETA	ep;
	if			(Gz.env==NULL)
	{	Gz.env=		&ep;
		ep.dataaddr=	(void *)	environ;
	}
}
