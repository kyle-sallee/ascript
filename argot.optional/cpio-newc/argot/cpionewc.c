/*	By Kyle Sallee in 2018 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"cpionewc.h"
#include	"a.h"

OPERATOR	opcpionewc[1];
static	VMETA	*N[2];

__attribute__((always_inline))
static	inline	uint8_t	readexpand	(VMETA *A,int const b)
{	ssize_t		d;
	A->textlen=			0;

	while				(1)
	{	text_check		(A,HUGE);
		d=	read		(b,A->textaddr+
					   A->textlen,HUGE);
		if		yay	(d>0)
		A->textlen+=		d;
		else	if	yay	(d==0)
		return			1;
		else	return		0;
	}
}

SCV	cpionewcload		(void)
{	int		c,d;

	if		yay	(Gz.to[0]->op->int_compat==0)
	{	show		(Gz.to[0]);
		c=
		d=
		open		(Gz.to[0]->textaddr,O_RDONLY);
	}
	else
	{
/*		denwant		(Gz.to[0]);	*/
		c=		-1;
		d=		Gz.to[0]->value.i;
	}
	uint8_t		a=
	readexpand		(N[1],d);
	if			(c>=0)
	close			(c);

	*Gz.at=			cpionewcload;
	argot_jump		(a);
}

__attribute__((always_inline))
static	inline	uint8_t	*readfull	(uint8_t *a)
{	int		b=
	open				(N[1]->textaddr,
					 O_RDONLY|O_NOATIME);
	ssize_t		c;

	while				(1)
	{	c=	read		(b,a,HUGE);
		if		yay	(c>0)
		a+=			c;
		else
		break;
	}
	close				(b);
	return				a;
}

__attribute__((noinline))
SCV	nibout			(uint8_t *b,uint64_t w)
{	static	uint8_t	const	T[0x10]=
	{	'0',	'1',	'2',	'3',
		'4',	'5',	'6',	'7',
		'8',	'9',	'A',	'B',
		'C',	'D',	'E',	'F'
	};

	*b++=			T[(w>>0x1c)&0xf];
	*b++=			T[(w>>0x18)&0xf];
	*b++=			T[(w>>0x14)&0xf];
	*b++=			T[(w>>0x10)&0xf];
	*b++=			T[(w>>0x0c)&0xf];
	*b++=			T[(w>>   8)&0xf];
	*b++=			T[(w>>   4)&0xf];
	*b++=			T[ w       &0xf];
}

__attribute__((noinline))
static	CALIGN	uint64_t	nibin		(uint8_t *b)
{	static	const	uint8_t	T[]=
	{	0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	1,	2,	3,	4,	5,	6,	7,
		8,	9,	0,	0,	0,	0,	0,	0,
		0,	0xa,	0xb,	0xc,	0xd,	0xe,	0xf,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	0,	0,
		0,	0xa,	0xb,	0xc,	0xd,	0xe,	0xf,
	};

	return	(T[b[0]]<<0x1c)	+
		(T[b[1]]<<0x18)	+
		(T[b[2]]<<0x14)	+
		(T[b[3]]<<0x10)	+
		(T[b[4]]<<0x0c)	+
		(T[b[5]]<<0x08)	+
		(T[b[6]]<<0x04)	+
		(T[b[7]]);
}

__attribute__((always_inline))
static	inline	SEEN	*linkseen	(CPIODATA *D,uint8_t *a, int b)
{	mode_t		m=		 D->s.st_mode&S_IFMT;
	if			yay	(D->s.st_nlink==1)	return	NULL;
	if			yay	(m!=S_IFREG)		return	NULL;

	SEEN		*S;
	for				(S=D->seen;S!=NULL;S=S->next)
	if			nay	(  D->s.st_ino==S->ino)
	if			yay	(  D->s.st_dev==S->dev)
	return				S;

	S=	pool			(sizeof(SEEN));
	memcpya				(S->name,a,S->len=b);
	S->dev=				D->s.st_dev;
	S->ino=				D->s.st_ino;
	S->next=			D->seen;
	D->seen=			S;
	return				NULL;
}

__attribute__((noinline))
static	CALIGN	uint8_t	add_pathname	(void)
{	show			(N[1]);
	errna=			0;
	VMETA		*B=	N[1];	/* .pathname */
	VMETA		*A=	N[0];	/* cpio newc buffer */

	CPIODATA	*a=
	cpiodata		(A);
	lstat			(  B->textaddr,&a->s);
	SEEN		*S=
	linkseen		(a,B->textaddr,B->textlen);

	text_check		(A,			sizeof(NEWC)+
				 B->textlen+4+	a->s.st_size);

	uint8_t		*b=	A->textaddr+	a->off;

	NEWC		*N=	(NEWC *)	b;
	__builtin_memcpy	(N->magic,	"070701",6);
	nibout			(N->ino,	a->s.st_ino);
	nibout			(N->mode,	a->s.st_mode);
	nibout			(N->uid,	a->s.st_uid);
	nibout			(N->gid,	a->s.st_gid);
	nibout			(N->nlink,	a->s.st_nlink);
	nibout			(N->mtime,	a->s.st_mtime);
	if		nay	((a->s.st_mode&S_IFMT)==S_IFDIR)
	a->s.st_size=		0;
	else	if	nay	(S!=NULL)
	a->s.st_size=		0;

	if		yay	(a->s.st_size)
	nibout			(N->size,	a->s.st_size);
	else
	__builtin_memset	(N->size,	'0',8);

	nibout			(N->devmajor,	major(a->s.st_dev));
	nibout			(N->devminor,	minor(a->s.st_dev));
	if		yay	(a->s.st_rdev==0)
	__builtin_memset	(N->rdevmajor,	'0',0x10);
	else
	{	nibout		(N->rdevmajor,	major(a->s.st_rdev));
		nibout		(N->rdevminor,	minor(a->s.st_rdev));
	}
	nibout			(N->namelen,			B->textlen+1);
	__builtin_memset	(N->empty,	'0',8);

	b+=	sizeof		(NEWC);
	memcpya			(b,		B->textaddr,	B->textlen);
	b+=							B->textlen;
	memset			(b,0,4);
	for			(b++;((uintptr_t)b)&3;b++);

	mode_t		m=	a->s.st_mode&S_IFMT;

	ssize_t		c;

	if		nay	(m==S_IFLNK)
	{	c=
		readlink	(B->textaddr,b,PATH_MAX);
		b+=		c;
		memset		(b,0,4);
		goto		done;
	}

	if		yay	(m==S_IFREG)
	if		yay	(a->s.st_size>0)
	b=	readfull	(b);

	done:
	for			(;((uintptr_t)b)&3;b++);
	a->off_old=		a->off;
	a->off=
	A->textlen=		b-A->textaddr;
	return			(errna==0);
}

__attribute__((noinline))
static	CALIGN	uint8_t	add_newc	(void)
{	VMETA		*B=		 N[1];	/* origin newc */

	CPIODATA	*b=
	cpiodata			(B);
	size_t		c=		b->off-
					b->off_old;

	VMETA		*A=		 N[0];	/* target newc */
	text_check			(A,c);
	CPIODATA	*a=
	cpiodata			(A);
	memcpya				(A->textaddr+a->off,
					 B->textaddr+b->off_old,c);
	a->off_old=			a->off;
	a->off+=			c;
	A->textlen+=			c;
	return				1;
}

SCV	cpionewcadd		(void)
{	uint8_t		a;
	if			(N[1]->op==opcpionewc)
	a=	add_newc	();
	else
	a=	add_pathname	();
	*Gz.at=			cpionewcadd;
	argot_jump		(a);
}

__attribute__((always_inline))
static	inline	void	statload	(CPIODATA *a,NEWC *b)
{	struct	stat	*s=		&a->s;
	s->st_ino=	nibin		(b->ino);
	s->st_mode=	nibin		(b->mode);
	s->st_uid=	nibin		(b->uid);
	s->st_gid=	nibin		(b->gid);
	s->st_nlink=	nibin		(b->nlink);
	s->st_mtime=	nibin		(b->mtime);
	s->st_size=	nibin		(b->size);
	s->st_dev=	makedev		(nibin(b->devmajor),
					 nibin(b->devminor));
	s->st_rdev=	makedev		(nibin(b->rdevmajor),
					 nibin(b->rdevminor));
	a->namelen=	nibin		(b->namelen);
}

SCV	cpionewcnext				(void)
{	VMETA		*A=			N[1];
	CPIODATA	*a=
	cpiodata				(A);
	a->off_old=						a->off;
	uint8_t		*b=			A->textaddr+	a->off;
	NEWC		*c=			(NEWC *)	b;
	statload				(a,c);

	if					(a->varhead)
	{	a->varhead->textaddr=	b;
		a->varhead->textlen=
		a->varhead->textsize=
		sizeof				(NEWC);
	}
	b+=	sizeof				(NEWC);

	a->name=				b;
	b+=					a->namelen;
	for					(;((uintptr_t)b)&3;b++);
	a->data=				b;

	for					(;nay(    *a->name=='/');
						 a->name++,a->namelen--);


	if					(a->varname)
	{	a->varname->textaddr=	a->name;
		a->varname->textlen=
		a->varname->textsize=	a->namelen-1;
	}


	if					(a->vardata)
	{	a->vardata->textaddr=	a->data;
		a->vardata->textlen=
		a->vardata->textsize=	a->s.st_size;
	}

	b+=					a->s.st_size;
	for					(;((uintptr_t)b)&3;b++);

	a->off=					b-	A->textaddr;

	uint8_t		d=			1;
	if				nay	(a->namelen==0xb)
	if				nay	(memcmp(a->name,
						 "TRAILER!!!\0",0xc)==0)
	d=					0;

	*Gz.at=					cpionewcnext;
	argot_jump				(d);
}

__attribute__((always_inline))
static	inline	void	filedata	(uint8_t *a,uint8_t *b,size_t c)
{	int		d=
	open				(a,O_CREAT|O_TRUNC|O_WRONLY,0600);
	write				(d,b,c);
	close				(d);
}

SCV	cpionewcmake			(void)
{	errna=				0;
	VMETA		*A=		N[1];
	CPIODATA	*a=
	cpiodata			(A);
	SEEN		*S=
	linkseen			(a,a->name,a->namelen);

	if			nay	(S!=NULL)
	{	link			(S->name,a->name);
		goto			done;
	}

	uint8_t		*name=		a->name;

	if			nay	(memmem(name,a->namelen,"/../",4)!=NULL)
	{	errna=			EINVAL;
		goto			done;
	}

	mode_t		m=		a->s.st_mode&S_IFMT;
	switch				(m)
	{	case	S_IFDIR:
		if		nay	(mkdir(name,0755))
		if		nay	(errna==EEXIST)
		errna=			0;
		break;
		case	S_IFBLK:
		case	S_IFCHR:
		case	S_IFIFO:
		mknod			(name,a->s.st_mode,a->s.st_rdev);
		break;
		case	S_IFLNK:;
		uint8_t	c=		a->data[a->s.st_size];
		a->data[a->s.st_size]=	0;
		symlink			(a->data,a->name);
		a->data[a->s.st_size]=	c;
		break;
		case	S_IFREG:
		filedata		(name,
					 a->data,
					 a->s.st_size);
		break;
	}

	if				(m!=S_IFLNK)
	{	chmod			(name,
					a->s.st_mode);
		chown			(name,
					 a->s.st_uid,
					 a->s.st_gid);
		a->T[0].tv_nsec=	UTIME_OMIT;
		a->T[1].tv_nsec=	0;
		a->T[1].tv_sec=		a->s.st_mtime;
		utimensat		(AT_FDCWD,name,a->T,0);
	}

	done:
	*Gz.at=				cpionewcmake;
	argot_jump			(errna==0);
}

__attribute__((noinline))
SCV	show_cpionewc			(VMETA *A)
{	CPIODATA	*a=
	cpiodata			(A);
	text_check			(A,0x300);
	uint8_t		*b=		A->textaddr+	a->off;
	NEWC		*c=		(NEWC *)	b;
	int	const	s=
	sizeof				(NEWC);
	memset				(c,'0',s);
	__builtin_memcpy		(c->magic,		"070701",6);
	nibout				(c->namelen,		0xb);
	nibout				(c->nlink,		1);
	__builtin_memcpy		(b+s,"TRAILER!!!\0",	0xc);
	A->textlen=			 b+s+			0xc-
					A->textaddr;

	A->textlen+=			 0x1ff;
	A->textlen&=			~0x1ff;

/*	if			yay	(	A->textlen&0x1ff)
	A->textlen+=			0x200-(	A->textlen&0x1ff);
*/
}

SCV	cpionewcsave	(void)
{	VMETA		*A=		N[0];
	show_cpionewc			(A);
	VMETA		*B=		Gz.to[0];
	int		b,c;
	if				(B->op->int_compat)
	{	b=			 B->value.i;
		c=			-1;
	}
	else
	{	c=
		b=
		open			(B->textaddr,
					 O_CREAT|O_TRUNC|O_WRONLY,0600);
	}
	ssize_t		d=
	writeall			(b,A->textaddr,A->textlen);
	if				(c>=0)
	close				(c);

	*Gz.at=				cpionewcsave;
	argot_jump			(d==A->textlen);
}

SCV	cpionewcpush_	(void)
{	VMETA	* volatile n[2];
	__builtin_memcpy	((void *) n,N,sizeof(n));
	argot_next		();
	__builtin_memcpy	(N,(void *) n,sizeof(n));
}

SCV	cpionewcwith_	(void)
{	__builtin_memcpy	(N,Gz.to,sizeof(N));
	argot_next		();
}

SCV	cpionewc	(void)	{tvarnewab(cpionewcsubnew,	cpionewc);}
SCV	cpionewcdata	(void)	{tsubab(cpionewcdatasubnew,	cpionewcdata);}
SCV	cpionewchead	(void)	{tsubab(cpionewcheadsubnew,	cpionewchead);}
SCV	cpionewcname	(void)	{tsubab(cpionewcnamesubnew,	cpionewcname);}
SCV	cpionewcstat	(void)	{tsubab(cpionewcstatsubnew,	cpionewcstat);}

SCV	cpionewcpush	(void)	{(*Gz.at=cpionewcpush_)	();}
SCV	cpionewcwith	(void)	{(*Gz.at=cpionewcwith_)	();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20200218",
	.official=	"20200218",
	.update=	"20200808"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(cpionewc,	"cpionewc");
	aa		(cpionewcpush,	"cpionewcpush");
	aa		(cpionewcwith,	"cpionewcwith");
	aa		(cpionewcdata,	"cpionewcdata");
	aa		(cpionewchead,	"cpionewchead");
	aa		(cpionewcname,	"cpionewcname");
	aa		(cpionewcstat,	"cpionewcstat");
	aa		(cpionewcadd,	"cpionewcadd");
	aa		(cpionewcload,	"cpionewcload");
	aa		(cpionewcmake,	"cpionewcmake");
	aa		(cpionewcsave,	"cpionewcsave");
	aa		(cpionewcnext,	"cpionewcnext");
	aa_fini		();
};

__attribute__((constructor))
SCV	init				(void)
{	opcpionewc[0].byte_compat=	1;
/*	opcpionewc[0].mapuse[0]=	show_cpionewc;	*/
}
