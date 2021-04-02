/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"
#include	"exe.h"
#include	"int.h"
#include	"trek.h"
#include	<spawn.h>

#ifdef		__linux__
#include	<linux/memfd.h>
#endif

SCV	exenameuse	(void)
{	exedata		(Gz.to[0])->name=	Gz.to[1];
	*Gz.at=		exenameuse;
	argot_next	();
}

SCV	exeenvuse	(void)
{	exedata		(Gz.to[0])->env=	Gz.to[1];
	*Gz.at=		exeenvuse;
	argot_next	();
}

SCV	exeparause	(void)
{	exedata		(Gz.to[0])->para=	Gz.to[1];
	*Gz.at=		exeparause;
	argot_next	();
}

SCV	show_map			(VMETA *A)
{	A->show=			NULL;
/*	if			nay	(A->io.map==0)
	return;
*/

	if			nay	(A->io.flag&textmapunmap)
	{	munmap			(A->textaddr,A->textsize);
		A->textaddr=		A->text;
		A->io.flag&=		~textmapunmap;
	}

/*	A->op=				varbyteop;	*/
	A->io.flag|=			textmapuse;

	pid_t		a=		A->host->value.i;
	waitthis			(a,WEXITED);

/* ascript/ascript: symbol lookup error: ascript.2020.01/exe: undefined symbol: fstat */
/*	struct	stat	s;
	s.st_size=			0;
	fstat				(A->io.map,&s);
*/
	off_t		s=
	lseek				(A->io.map,0,SEEK_END);

	A->textlen=
	A->textsize=			s;

	int		d=		A->io.map;
	A->io.map=			0;
	if			yay	(s>0)
	{	A->io.flag|=		textmapunmap;
		A->textaddr=
		mmap			(NULL,s,PROT_READ|PROT_WRITE,
					 MAP_PRIVATE,d,0);
	}
	close				(d);
}

static	inline	void	fapper		(VMETA *a,
					 posix_spawn_file_actions_t *b,
					 int c)
{	int		d;

	if			yay	(a!=NULL)
	{	a->io.flag&=		~textmapuse;
		d=			a->io.map;
		if			(d==0)
		{
#ifdef	__linux__
			d=
			syscall		(SYS_memfd_create,"",0);
#else
			d=
			open		("/tmp",O_RDWR|O_TMPFILE,0600);
#endif
			d=
			highmake	(d);
			a->show=	show_map;
			a->io.map=	d;
		}
		posix_spawn_file_actions_adddup2
					(b,d,c);
	}
}

static	inline	void	sigchld_skip	(void)	{pids.skip=	1;}
static	inline	void	sigchld_resume	(void)
{	pids.skip=		0;
	if		nay	((volatile uint8_t) pids.miss)
	{	pids.miss=	0;
		sigqueue	(0,SIGCHLD,
				(union sigval){ .sival_int=0});
	}
}

static	inline	pid_t	common		(void)
{	char		**e,*n,**v;
	VMETA		*P,*E,*A=	Gz.to[0];
	EXEDATA		*a=
	exedata				(A);

	E=				a->env;
	if			yay	(E==NULL)
	E=				Gz.env;

	e=				(char **)	E->dataaddr;

	if			yay	(a->name!=NULL)
	n=				 a->name->textaddr;

	P=				a->para;
	if			yay	(P==NULL)
	v=				((char *[]){n,NULL});
	else
	{	reval			(P);
		v=			(char **)	P->dataaddr;
/* .name if created, but not used is a hacker error */
		if		yay	(a->name==NULL)
		n=			v[0];
	}

	posix_spawn_file_actions_t
			fa,*fap;

	VMETA		*K=		a->out;
	VMETA		*L=		a->err;
	if			yay	((K==NULL)&&(L==NULL))
	fap=				NULL;
	else
	{	posix_spawn_file_actions_init
					(  fap=&fa);
		fapper			(K,fap,1);
		fapper			(L,fap,2);
	}

	sigchld_skip			();
	pid_t		p=		0;

	A->io.success=
	errna=
	posix_spawnp			(&p,n,fap,NULL,v,e);

	if			nay	(fap!=NULL)
	{	posix_spawn_file_actions_destroy
					(fap);
	}

	if			nay	(errna!=0)
	goto				done;

	pids.now++;
	A->value.i=
	pids.last=			p;
	pids.done[p]=			0;
	pids.exit[p]=			0;
	pids.stop[p]=			0;
	pids.origin[p]=			a->origin;
	pids.target[p]=			a->target;

	if			nay	(a->pin!=NULL)
	pids.pin[p]=			 a->pin;

	done:
	sigchld_resume			();
	return				p;
}

__attribute__((noinline))
__attribute__((hot))
SCV	execute_		(void)
{	common		();
	argot_next	();
}

SCV	exeorigin_	(void)
{	exedata		(Gz.to[0])->origin=	Gz.to[1];
	argot_next	();
}


SCV	exetarget_	(void)
{	exedata		(Gz.to[0])->target=	Gz.to[1];
	argot_next	();
}

SCV	exepin				(void)
{	void		(**P)	(void);
	if				(Gz.to[1]->value.i=='\'')
	P=	nearfind_fast		(Gz.to[1]->textaddr,partfar(NULL));
	else
	P=	farfind_fast		(Gz.to[1]->textaddr);

	exedata	(Gz.to[0])->pin=	P;
	*Gz.at=			exepin;
	argot_next			();
}

SCV	exe	(void)	{tvarnewab(exeinit,	exe);}
SCV	exename	(void)	{tsubab(exenameinit,exename);}
SCV	exepara	(void)	{tsubab(exeparainit,exepara);}
SCV	exeenv	(void)	{tsubab(exeenvinit,	exeenv);}
SCV	exeout	(void)	{tsubab(exeoutinit,	exeout);}
SCV	exeerr	(void)	{tsubab(exeerrinit,	exeerr);}

static	void	exeorigin	(void)	{(*Gz.at=exeorigin_)	();}
static	void	execute		(void)	{(*Gz.at=execute_)	();}
static	void	exetarget	(void)	{(*Gz.at=exetarget_)	();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180228",
	.official=	"20180228",
	.update=	"20200909"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(exenameuse,	"exenameuse");
	aa		(exeenvuse,	"exeenvuse");
	aa		(exeparause,	"exeparause");
	aa		(exeorigin,	"exeorigin");
	aa		(exetarget,	"exetarget");
	aa		(exepin,	"exepin");
	aa		(exeerr,	"exeerr");
	aa		(exeout,	"exeout");
	aa		(exeenv,	"exeenv");
	aa		(exepara,	"exepara");
	aa		(exename,	"exename");
	aa		(execute,	"execute");
	aa		(exe,		"exe");
	aa_fini		();
};
