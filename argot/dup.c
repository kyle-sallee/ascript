/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"dup.h"

static	VMETA	da=
{	.name=		"dup.above",
	.len=		9,
	.value.i=	FDHIGH,
	.op=		opint4,
};

SCV	dupabove		(void)
{
/*	denwant			(Gz.to[0]->host);
	denwant			(Gz.to[1]);
*/

	reval			(Gz.to[1]);
	int		a=	Gz.to[0]->host->value.i4.l;
	int		b=	Gz.to[1]->      value.i4.l;
	int		c=
	fcntl			(a,F_DUPFD,b);
	Gz.to[0]->value.i=	c;
	*Gz.at=			dupabove;
	argot_jump		(c>=0);
}

SCV	dupexact		(void)
{
/*	denwant			(Gz.to[0]->host);
	denwant			(Gz.to[1]);
*/

	reval			(Gz.to[1]);
	int		a=	Gz.to[0]->host->value.i4.l;
	int		b=	Gz.to[1]->      value.i4.l;
	int		c=
	dup2			(a,b);
	Gz.to[0]->value.i=	c;
	*Gz.at=			dupexact;
	argot_jump		(c>=0);
}

SCV	dupend			(void)
{	VMETA		*A=	Gz.to[0];
	close			(A->value.i4.l);
	A->value.i=		-1;
	*Gz.at=			dupend;
	argot_next		();
}

SCV	dupendlate		(void)
{	VMETA		*A=	Gz.to[0];
	VMETA		**AA=	A->vam;
	*Gz.at=			dupendlate;
	argot_next		();
	VMETA		*B;
	for			(B=*AA;B;B=B->fore);
	if		yay	(A==B)
	{	close		(A->value.i4.l);
		A->value.i=	-1;
		return;
	}
}

SCV	duponexekeep		(void)
{	int		a=	 Gz.to[0]->value.i4.l;
	fcntl			(a,F_SETFD,FD_CLOEXEC);
	*Gz.at=			duponexekeep;
	argot_next		();
}

SCV	duponexegive		(void)
{	int		a=	 Gz.to[0]->value.i4.l;
	fcntl			(a,F_SETFD,0);
	*Gz.at=			duponexegive;
	argot_next		();
}

SCV	duponexecopy		(void)
{
/*	denwant			(Gz.to[0]->host);
*/
	int		a=	 Gz.to[0]->host->value.i4.l;

	int		b=
	fcntl			(a,F_GETFD);

	int		c=	Gz.to[0]->value.i;
	fcntl			(c,F_SETFD,b);
	*Gz.at=			duponexecopy;
	argot_next		();
}

SCV	ds_			(void)
{	int		a[3];
	VMETA		*A=	Gz.to[0];

/*	denwant			(A);
*/
	a[0]=			A->value.i;
	a[1]=	fcntl		(a[0],F_DUPFD_CLOEXEC,da.value.i4.l);
	a[2]=	fcntl		(a[0],F_GETFD);

	argot_next		();

	int		b=	errna;
	dup2must		(a[1],a[0]);
	fcntl			(a[0],F_SETFD,a[2]);
	closemust		(a[1]);
	errna=			b;
}

SCV	ds	(void)	{(*Gz.at=ds_)	();}
SCV	_dup	(void)	{tsubab(dupsubnew,_dup);}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20181028",
	.official=	"20181028",
	.update=	"20200809"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_dup,		"dup");
	aa		(ds,		"dupsave");
	aa		(dupend,	"dupend");
	aa		(dupendlate,	"dupendlate");
	aa		(duponexecopy,	"duponexecopy");
	aa		(duponexegive,	"duponexegive");
	aa		(duponexekeep,	"duponexekeep");
	aa		(dupabove,	"dupabove");
	aa		(dupexact,	"dupexact");
	aa_fini		();

	map_init	(&da);
	vattach_faster	(&da,"dup.above");
	da.show=	Gz.out.den4;
};
