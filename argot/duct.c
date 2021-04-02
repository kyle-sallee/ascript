/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"int.h"

#ifdef		__linux__
#include	<linux/memfd.h>

static	VMETA	A=	/* by duct pipe used for variable pipe.cap */
{	.name=		"pipe.cap",
	.len=		8,
	.op=		opint4,
};

__attribute__((hot))
SCV	ductmem01			(void)
{	int		b[4];
	b[3]=		fcntl		(1,F_GETFD);
	b[2]=		fcntl		(0,F_GETFD);
	b[1]=		highmake	(1);
	b[0]=		highwant	(0);

	int		a=
	mfdmust				();

	if				(a!=1)
	{	dup2must		(a,1);
		closemust		(a);
	}

	*Gz.at=				ductmem01;
	argot_next			();
	dup2must			(1,0);
	lseek				(0,0,SEEK_SET);
	closemust			(1);

	argot_next			();
	dup2must			(b[1],1);
	fcntl				(1,F_SETFD,b[3]);

	argot_next			();
	dup2must			(b[0],0);
	fcntl				(0,F_SETFD,b[2]);

	argot_next			();
}

__attribute__((hot))
SCV	ductmem1			(void)
{	int		b[2];
	b[0]=		fcntl		(1,F_GETFD);
	b[1]=		highmake	(1);

	int		a=
	mfdmust				();

	if				(a!=1)
	{	dup2must		(a,1);
		closemust		(a);
	}

	*Gz.at=				ductmem1;
	argot_next			();
	dup2must			(1,0);
	lseek				(0,0,SEEK_SET);
	closemust			(1);

	argot_next			();
	dup2must			(b[1],1);
	fcntl				(1,F_SETFD,b[0]);
	closemust			(0);

	argot_next			();
}

__attribute__((hot))
SCV	ductmem				(void)
{	int		a=
	mfdmust				();

	if			yay	(a!=1)
	{	dup2must		(a,1);
		closemust		(a);
	}

	*Gz.at=				ductmem;
	argot_next			();
	dup2must			(1,0);
	closemust			(1);
	lseek				(0,0,SEEK_SET);
	argot_next			();
}
#endif

__attribute__((hot))
SCV	ductpipe01			(void)
{	int		a[6];
	a[3]=		fcntl		(1,F_GETFD);
	a[2]=		fcntl		(0,F_GETFD);
	a[1]=		highmake	(1);
	a[0]=		highwant	(0);

	pipe				(a+4);

	if				(a[5]!=1)
	{	dup2must		(a[5],1);
		closemust		(a[5]);
	}

	a[4]=
	highmake			(a[4]);

	int		b=		(int)	*(int64_t *)	A.value.i;
	if			nay	(b>0)
	fcntl				(1,F_SETPIPE_SZ,b);

	*Gz.at=				ductpipe01;
	argot_next			();
	dup2must			(a[4],0);
	closemust			(a[4]);
	closemust			(1);

	argot_next			();
	dup2must			(a[1],1);
	fcntl				(1,F_SETFD,a[3]);

	argot_next			();
	dup2must			(a[0],0);
	fcntl				(1,F_SETFD,a[2]);
	argot_next			();
}

__attribute__((hot))
SCV	ductpipe1			(void)
{	int		a[4];
	a[0]=		fcntl		(1,F_GETFD);
	a[1]=		highmake	(1);

	pipe				(a+2);

	if				(a[3]!=1)
	{	dup2must		(a[3],1);
		closemust		(a[3]);
	}

	a[2]=
	highmake			(a[2]);

	int		b=		(int)	*(int64_t *)	A.value.i;
	if			nay	(b>0)
	fcntl				(1,F_SETPIPE_SZ,b);

	*Gz.at=				ductpipe1;
	argot_next			();
	dup2must			(a[2],0);
	closemust			(a[2]);
	closemust			(1);

	argot_next			();
	dup2must			(a[1],1);
	fcntl				(1,F_SETFD,a[3]);

	argot_next			();
}

__attribute__((hot))
SCV	ductpipe			(void)
{	int		a[2];
	pipe				(a);

	if			yay	(a[1]!=1)
	{	dup2must		(a[1],1);
		closemust		(a[1]);
	}

	a[0]=
	highmake			(a[0]);

	int		b=		(int)	*(int64_t *)	A.value.i;
	if			nay	(b>0)
	fcntl				(1,F_SETPIPE_SZ,b);

	*Gz.at=				ductpipe;
	argot_next			();
	dup2must			(a[0],0);
	closemust			(a[0]);
	closemust			(1);
	argot_next			();
}

__attribute__((constructor))
SCV	init			(void)
{	map_init		(&A);
	A.show=			Gz.out.den4;
	vattach_faster		(&A,"pipe.cap");
}

__attribute__((hot))
SCV	ducttmp01			(void)
{	int		b[4];
	b[3]=		fcntl		(1,F_GETFD);
	b[2]=		fcntl		(0,F_GETFD);
	b[1]=		highmake	(1);
	b[0]=		highwant	(0);

	int		a=
	open				("/tmp",O_RDWR|O_TMPFILE,0600);

	if				(a!=1)
	{	dup2must		(a,1);
		closemust		(a);
	}

	*Gz.at=				ducttmp01;
	argot_next			();
	dup2must			(1,0);
	lseek				(0,0,SEEK_SET);
	closemust			(1);

	argot_next			();
	dup2must			(b[1],1);
	fcntl				(1,F_SETFD,b[3]);

	argot_next			();
	dup2must			(b[0],0);
	fcntl				(0,F_SETFD,b[2]);

	argot_next			();
}

__attribute__((hot))
SCV	ducttmp1			(void)
{	int		b[2];
	b[0]=		fcntl		(1,F_GETFD);
	b[1]=		highmake	(1);

	int		a=
	open				("/tmp",O_RDWR|O_TMPFILE,0600);

	if				(a!=1)
	{	dup2must		(a,1);
		closemust		(a);
	}

	*Gz.at=				ducttmp1;
	argot_next			();
	dup2must			(1,0);
	lseek				(0,0,SEEK_SET);
	closemust			(1);

	argot_next			();
	dup2must			(b[1],1);
	fcntl				(1,F_SETFD,b[0]);
	closemust			(0);

	argot_next			();
}

__attribute__((hot))
SCV	ducttmp				(void)
{	int		a=
	open				("/tmp",O_RDWR|O_TMPFILE,0600);

	if			yay	(a!=1)
	{	dup2must		(a,1);
		closemust		(a);
	}

	*Gz.at=				ducttmp;
	argot_next			();
	dup2must			(1,0);
	closemust			(1);
	lseek				(0,0,SEEK_SET);
	argot_next			();
}

__attribute__((hot))
SCV	ductmap				(void)
{	int		a;
	ssize_t		b;
	VMETA		*A;

	a=	open			("/tmp",O_RDWR|O_TMPFILE,0600);
	if			nay	(0>a)
	goto				fail;

	b=
	copyall				(a,0);
	dup2				(a,0);
	close				(a);
	lseek				(0,0,SEEK_SET);

	if			nay	(0>b)
	goto				fail;

	A=				Gz.to[0];
	if			nay	(A->io.flag&textmapunmap)
	munmap				(A->textaddr,A->textsize);

	A->io.flag|=			textmapunmap;
	A->textlen=
	A->textsize=			b;
	A->textaddr=
	mmap				(NULL,b,PROT_READ|PROT_WRITE,
					 MAP_SHARED,0,0);
	if			nay	(A->textaddr==(void *)-1)
	goto				fail_late;

	*Gz.at=				ductmap;
	argot_skip			();
	return;

	fail_late:
	A->io.flag&=			~textmapunmap;
	A->textlen=			0;
	A->textaddr=			A->text;
	A->textsize=	sizeof		(A->text);

	fail:
	argot_next			();
}

__attribute__((hot))
SCV	ducttee				(void)
{	int		a;
	ssize_t		b;

	a=	open			("/tmp",O_RDWR|O_TMPFILE,0600);
	if			nay	(0>a)
	goto				fail;

	b=
	copyall				(a,0);
	dup2				(a,0);
	close				(a);
	lseek				(0,0,SEEK_SET);
	if			nay	(0>b)
	goto				fail;

	int		c,d;
	if				(Gz.to[0]->op->int_compat)
	{	c=			-1;
		d=			 Gz.to[0]->value.i4.l;
	}
	else
	{	c=
		d=	open		(Gz.to[0]->textaddr,
					 O_APPEND|O_CREAT|O_WRONLY,644);
	}
	copyall				(d,0);
	lseek				(0,0,SEEK_SET);
	if				(c>=0)
	close				(c);
	fail:
	*Gz.at=				ducttee;
	argot_next			();
}

static		void	duct	(void)
{	*Gz.at=		duct;
	argot_next	();
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190409",
	.official=	"20190409",
	.update=	"20200920"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(duct,		"duct");
	aa		(ductmap,	"ductmap");
	aa		(ducttee,	"ducttee");
	aa		(ductpipe01,	"ductpipe01");
	aa		(ductpipe1,	"ductpipe1");
	aa		(ductpipe,	"ductpipe");
#ifdef	__linux__
	aa		(ductmem,	"ductmem");
	aa		(ductmem1,	"ductmem1");
	aa		(ductmem01,	"ductmem01");
#else
	aa		(ducttmp,	"ductmem");
	aa		(ducttmp1,	"ductmem1");
	aa		(ducttmp01,	"ductmem01");
#endif
	aa		(ducttmp,	"ducttmp");
	aa		(ducttmp1,	"ducttmp1");
	aa		(ducttmp01,	"ducttmp01");
	aa_fini		();
};
