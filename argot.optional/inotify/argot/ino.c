/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"
#include	"ino.h"
#include	"int.h"
#include	"trek.h"

typedef	struct
{	PALIGN
	INO			b;
	PALIGN	WATCH		c	[0x2000];
	PALIGN	uint8_t		d	[0x2000*PAGE];
}	IMAPS;

static	IMAPS	im;

static	VMETA	iv[3]=
{	{.name="ino.move", .len=8,.op=opint4,.io.flag=datamapuse},
	{.name="ino.name", .len=8,.op=opbyte,.io.flag=textmapuse},
	{.name="ino.watch",.len=9,.op=opbyte,.io.flag=textmapuse},
};

SCV	pin_find		(uint32_t	*a
				,uint32_t	b
				,void		(*(**c))(void)
				,uint8_t	*d
				,uint32_t	e)
{	*c=
	nearfind_safe		(d,e);
	if		nay	(*c!=NULL)
	*a|=			b;
}

static	CALIGN	uint32_t	pin_want	(uint32_t f, WATCH *w)
{	uint32_t	a=	0;
	pin_find(&a,IN_ACCESS,		&w->P_IN_ACCESS,	"IN_ACCESS\0\0\0\0\0\0",f);
	pin_find(&a,IN_ATTRIB,		&w->P_IN_ATTRIB,	"IN_ATTRIB\0\0\0\0\0\0",f);
	pin_find(&a,IN_CLOSE_WRITE,	&w->P_IN_CLOSE_WRITE,	"IN_CLOSE_WRITE\0",f);
	pin_find(&a,IN_CLOSE_NOWRITE,	&w->P_IN_CLOSE_NOWRITE,	"IN_CLOSE_NOWRITE",f);
	pin_find(&a,IN_CREATE,		&w->P_IN_CREATE,	"IN_CREATE\0\0\0\0\0\0",f);
	pin_find(&a,IN_DELETE,		&w->P_IN_DELETE,	"IN_DELETE\0\0\0\0\0\0",f);
	pin_find(&a,IN_DELETE_SELF,	&w->P_IN_DELETE_SELF,	"IN_DELETE_SELF\0",f);
	pin_find(&a,IN_MODIFY,		&w->P_IN_MODIFY,	"IN_MODIFY\0\0\0\0\0\0",f);
	pin_find(&a,IN_MOVE_SELF,	&w->P_IN_MOVE_SELF,	"IN_MOVE_SELF\0\0\0",f);
	pin_find(&a,IN_MOVED_FROM,	&w->P_IN_MOVED_FROM,	"IN_MOVED_FROM\0\0",f);
	pin_find(&a,IN_MOVED_TO,	&w->P_IN_MOVED_TO,	"IN_MOVED_TO\0\0\0\0",f);
	pin_find(&a,IN_OPEN,		&w->P_IN_OPEN,		"IN_OPEN\0\0\0\0\0\0\0\0",f);
	return		a;
}

__attribute__((noinline))
SCV	inofar_		(void)
{	im.b.far=
	partfar(
	farfind_fast	(Gz.to[0]->textaddr));
	argot_next	();
}

__attribute__((noinline))
SCV	inowatch_			(void)
{	INO		*I=		&im.b;

	uint32_t	e=
	pin_want			(I->far,&I->w);

	int		d=
	inotify_add_watch		(I->i,Gz.to[0]->textaddr,e);

	if			yay	(d>=0)
	{	WATCH	*W=		im.c;
		W+=			d;
		__builtin_memcpy	(W    ,&I->w,sizeof(WATCH));
		__builtin_memcpy	(W->to,I->to,sizeof(I->to));

		W->s=			Gz.to[0]->textlen;
		uint8_t	*a=		im.d+d*PAGE;
		memcpya			(a,Gz.to[0]->textaddr,W->s);
		argot_skip		();
	}
	else	argot_next		();
}


SCV	ino_acquire	(void);

__attribute__((noinline))
SCV	inodone_		(void)
{	if			(--im.b.use>0)
	goto			skip;

	close			(im.b.i);
	Gz.sig[im.b.s]=		NULL;
	madvise			(&im,sizeof(im),MADV_DONTNEED);
	ino_acquire		();

	skip:
	argot_next		();
}

static	CALIGN	int	watch_del	(uint8_t *a,int s)
{	INO		*I=		&im.b;
	int		d=
	inotify_add_watch		(I->i,a,IN_MASK_ADD);
	if			yay	(d>=0)
	{	inotify_rm_watch	(I->i,d);
		im.c[d].s=		-1;
		return			0;
	}
	else	return			1;
}

__attribute__((noinline))
SCV	inoignore_		(void)
{	int		e=
	watch_del		(Gz.to[0]->textaddr
				,Gz.to[0]->textlen);
	argot_jump		(e==0);
}

SCV	pin_try			(uint32_t a,uint32_t b,void (**c)(void))
{	if		nay	((a&b)!=0)
	if			(c!=NULL)
	(*(Gz.at=c))		();
}

SCV	pin_all	(WATCH *w,uint32_t m)
{	pin_try	(m,IN_ACCESS,		w->P_IN_ACCESS);
	pin_try	(m,IN_ATTRIB,		w->P_IN_ATTRIB);
	pin_try	(m,IN_CLOSE_WRITE,	w->P_IN_CLOSE_WRITE);
	pin_try	(m,IN_CLOSE_NOWRITE,	w->P_IN_CLOSE_NOWRITE);
	pin_try	(m,IN_CREATE,		w->P_IN_CREATE);
	pin_try	(m,IN_DELETE,		w->P_IN_DELETE);
	pin_try	(m,IN_DELETE_SELF,	w->P_IN_DELETE_SELF);
	pin_try	(m,IN_MODIFY,		w->P_IN_MODIFY);
	pin_try	(m,IN_MOVE_SELF,	w->P_IN_MOVE_SELF);
	pin_try	(m,IN_MOVED_FROM,	w->P_IN_MOVED_FROM);
	pin_try	(m,IN_MOVED_TO,		w->P_IN_MOVED_TO);
	pin_try	(m,IN_OPEN,		w->P_IN_OPEN);
}

SCV	action					(int a,siginfo_t *b,void *c)
{	int		e=			errna;
	errna=					0;

	INO		*I=			&im.b;

	ssize_t		r=
	read					(I->i,&I->ieb.a,sizeof(IEB));

	target_object_to_stack			();
	void		(**L)	(void)=		Gz.at;

	struct	inotify_event	*i=		&I->ieb.a;

	while					(r>0)
	{
		/* ino.name */
		iv[1].textlen=			i->len;
		iv[1].textaddr=			i->name;

		if			nay	(i->mask&IN_Q_OVERFLOW)
		{	/* ino.watch */
			iv[2].io.success=	E2BIG;
			break;
		}

		WATCH		*w=		im.c;
		w+=				i->wd;

		/* ino.watch */
		iv[2].textaddr=			im.d+i->wd*PAGE;
		iv[2].textlen=			w->s;

		/* ino.move */
		iv[0].value.i=			i->cookie;

		__builtin_memcpy		(Gz.to,w->to,sizeof(w->to));
		pin_all				(w,i->mask);

		size_t		s=
		sizeof				(struct inotify_event)+i->len;
		void		*v=		i;
		v+=				s;
		i=				v;
		r-=				s;
	}

	Gz.at=					L;
	target_object_from_stack		();
	errna=					e;
}

/*
__attribute__((always_inline))
static	inline	int	max_watch	(void)
{	uint8_t		b[0x10];
	memset			(b,0,0x10);
	int		a;
	ssize_t		d;
	a=
	open			("/proc/sys/fs/inotify/max_user_watches",
				O_RDONLY);
	if		yay	(a>=0)
	{	d=
		read		(a,b,0x10);
		close		(a);
		if	nay	(__builtin_memcmp(b,"8192\n\0\0",8)!=0)
		{	VMETA	A;
			A.textlen=		d;
			A.textaddr=		 A.text;
			__builtin_memcpy	(A.text,b,0x10);
			Gz.out.inden		(&A);
			return			A.value.i;
		}
	}
	return			0x2000;
}
*/

SCV	inoto_			(void)
{	__builtin_memcpy	(im.b.to,Gz.to,sizeof(im.b.to));
	argot_next		();
}

static	void	inodo_		(void)
{	im.b.use++;
	argot_next		();
}

static		void	ino	(void)
{	*Gz.at=		ino;
	argot_next	();
}

static	void	inodo		(void)	{(*Gz.at=inodo_)	();}
static	void	inowatch	(void)	{(*Gz.at=inowatch_)	();}
static	void	inodone		(void)	{(*Gz.at=inodone_)	();}
static	void	inoignore	(void)	{(*Gz.at=inoignore_)	();}
static	void	inoto		(void)	{(*Gz.at=inoto_)	();}
static	void	inofar		(void)	{(*Gz.at=inofar_)	();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20180330",
	.official=	"20180330",
	.update=	"20200809"
};

__attribute__((always_inline))
static	inline	int	sig_init(int d)
{	int			s;
	for			(s=SIGRTMIN;Gz.sig[s];s++);

	Gz.sa[0].sa_flags=	SA_SIGINFO|SA_RESTART;
	Gz.sa[0].sa_sigaction=	action;

	sigaction		(s,Gz.sa,NULL);
	fcntl			(d,F_SETOWN,getpid());
	fcntl			(d,F_SETSIG,s);
	fcntl			(d,F_SETFL,O_ASYNC|O_NONBLOCK);
	Gz.sig[s]=		&im;
	return			s;
}

__attribute__((noinline))
SCV	ino_acquire		(void)
{	INO		*I=	&im.b;
	I->i=	highmake	(inotify_init());
	I->s=	sig_init	(I->i);
}

SCV	var_init			(void)
{	iv[0].show=			Gz.out.den4;
	iv[1].textsize=			PAGE;
	map_init			(iv+0);
	map_init			(iv+1);
	map_init			(iv+2);
	vattach_faster			(iv+0,"ino.move");
	vattach_faster			(iv+1,"ino.name");
	vattach_faster			(iv+2,"ino.watch");
	ino_acquire			();
}

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(ino,		"ino");
	aa		(inoto,		"inoto");
	aa		(inodo,		"inodo");
	aa		(inodone,	"inodone");
	aa		(inoignore,	"inoignore");
	aa		(inofar,	"inofar");
	aa		(inowatch,	"inowatch");
	aa_fini		();
	var_init	();
};
