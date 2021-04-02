/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"a.h"
#include	"byte.h"

SCV			ato0	(void)
{	show_target		();
	uint8_t		*a=	Gz.to[0]->textaddr;
	uint8_t		*b=	Gz.to[0]->textlen+a;

	for			(;b>a;a++)
	if		nay	(*a==0xa)
	*a=			0;
	*Gz.at=			ato0;
	revise			(Gz.to[0]);
	argot_next		();
}

SCV			_0toa	(void)
{	show_target		();
	uint8_t		*a=	Gz.to[0]->textaddr;
	uint8_t		*b=	Gz.to[0]->textlen+a;

	for			(;b>a;a++)
	if		nay	(*a==0)
	*a=			0xa;
	*Gz.at=			_0toa;
	revise			(Gz.to[0]);
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	equalequal_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	size_t		a=	A->textlen;
	size_t		b=	B->textlen;
	if			((a==b)&&
				(memcmpa	(A->textaddr,
						 B->textaddr,a)==0))
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	notequal_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	size_t		a=	A->textlen;
	size_t		b=	B->textlen;
	if			((a!=b)||
				(memcmpa	(A->textaddr,
						 B->textaddr,a)))
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	less_			(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	size_t		a=	A->textlen;
	size_t		b=	B->textlen;
	size_t		c=	a < b ? a : b;

	int64_t		d=
	memcmpa		(A->textaddr,B->textaddr,c);

	if		yay	(d<0)	argot_skip	();
	else	if	yay	(d>0)	argot_next	();
	else	if		(a<b)	argot_skip	();
	else				argot_next	();
}

__attribute__((hot))
__attribute__((noinline))
SCV	lessequal_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	size_t		a=	A->textlen;
	size_t		b=	B->textlen;
	size_t		c=	a < b ? a : b;
	int64_t		d=
	memcmpa		(A->textaddr,B->textaddr,c);

	if			(d<0)	argot_skip	();
	else	if		(d>0)	argot_next	();
	else	if		(a<=b)	argot_skip	();
	else				argot_next	();
}

__attribute__((hot))
__attribute__((noinline))
SCV	more_			(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	size_t		a=	A->textlen;
	size_t		b=	B->textlen;
	size_t		c=	a < b ? a : b;
	int64_t		d=
	memcmpa		(A->textaddr,B->textaddr,c);
	if			(d>0)	argot_skip	();
	else	if		(d<0)	argot_next	();
	else	if		(a<b)	argot_skip	();
	else				argot_next	();
}

__attribute__((hot))
__attribute__((noinline))
SCV	moreequal_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	size_t		a=	A->textlen;
	size_t		b=	B->textlen;
	size_t		c=	a < b ? a : b;
	int64_t		d=
	memcmpa		(A->textaddr,B->textaddr,c);
	if			(d>0)	argot_skip	();
	else	if		(d<0)	argot_next	();
	else	if		(a<=b)	argot_skip	();
	else				argot_next	();
}

__attribute__((hot))
SCV	equal_			(void)
{	show_origin		();
	Gz.to[0]->textlen=	0;
	text_check		(Gz.to[0],
				 Gz.to[1]->textlen+0x10);
	VMETA		*A=	 Gz.to[0],
			*B=	 Gz.to[1];
	memcpya			(A->textaddr,B->textaddr,
				 A->textlen =B->textlen);
	revise			(Gz.to[0]);
	argot_next		();
}

SCV	add_			(void)
{	show_origin		();
	size_t		t=	 Gz.to[1]->textlen;

	text_check		(Gz.to[0],t+0x10);

	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];

	uint8_t		*a=	A->textaddr+
				A->textlen;

	A->textlen+=		B->textlen;
	memcpya			(a,B->textaddr,B->textlen);
	revise			(Gz.to[0]);
	argot_next		();
}

__attribute__((always_inline))
static	inline	void	bytealso(uint8_t c)
{	show_origin		();
	size_t		t=	 Gz.to[1]->textlen;

/*	text_check		(Gz.to[0],t+PAGE);	*/
	text_check		(Gz.to[0],t+0x10);

	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];

	uint8_t		*a=	A->textaddr+
				A->textlen;

	A->textlen+=		B->textlen+1;

	uint8_t		*b=	a+B->textlen;

	memcpya			(a,B->textaddr,B->textlen);
	*b=			c;
	revise			(Gz.to[0]);
	argot_next		();
}

/*
__attribute__((always_inline))
static	inline	void	bytealsorr(uint8_t c)
{	show_origin		();
	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];

	uint8_t		*a=	A->textaddr+
				A->textlen;

	A->textlen+=		B->textlen+1;

	uint8_t		*b=	a+B->textlen;

	memcpya			(a,B->textaddr,B->textlen);
	*b=			c;
	revise			(Gz.to[0]);
	argot_next		();
}

SCV	bytelinerr	(void);
SCV	bytelinerr7	(void)	{*Gz.at=bytelinerr ;bytealsorr	('\n');}
SCV	bytelinerr6	(void)	{*Gz.at=bytelinerr7;bytealsorr	('\n');}
SCV	bytelinerr5	(void)	{*Gz.at=bytelinerr6;bytealsorr	('\n');}
SCV	bytelinerr4	(void)	{*Gz.at=bytelinerr5;bytealsorr	('\n');}
SCV	bytelinerr3	(void)	{*Gz.at=bytelinerr4;bytealsorr	('\n');}
SCV	bytelinerr2	(void)	{*Gz.at=bytelinerr3;bytealsorr	('\n');}
SCV	bytelinerr1	(void)	{*Gz.at=bytelinerr2;bytealsorr	('\n');}
SCV	bytelinerr	(void)	{*Gz.at=bytelinerr1;bytealso	('\n');}
*/

__attribute__((noinline))
SCV	byteline_	(void)	{bytealso	('\n');}
__attribute__((noinline))
SCV	bytestring_	(void)	{bytealso	(0);}

SCV	and_			(void)
{	show_origin		();
	VMETA		*A=	Gz.to[0],
			*B=	Gz.to[1];

	uint8_t		*a=	A->textaddr+
				A->textlen;

	A->textlen+=		B->textlen;
	memcpya			(a,B->textaddr,B->textlen);
	revise			(Gz.to[0]);
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	subsub_			(void)
{	Gz.to[0]->textlen--;
	revise			(Gz.to[0]);
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytehave_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	void		*v;
	if			(B->textlen==1)
	v=		memchrb	(A->textaddr,
				 B->textaddr[0],
				 A->textlen);
	else
	v=		memmemb	(A->textaddr,
				 A->textlen,
				 B->textaddr,
				 B->textlen);
	argot_jump		(v!=NULL);
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytehavehead_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	int64_t		c;
	if			(B->textlen>A->textlen)
	c=			1;
	else
	if			(B->textlen==1)
	c=			(A->textaddr[0]!=B->textaddr[0]);
	else
	c=		memcmpa	(A->textaddr
				,B->textaddr
				,B->textlen);

	if			(c==0)
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytehavetail_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	int64_t		c;
	if			(B->textlen>A->textlen)
	c=			1;
	else
	if			(B->textlen==1)
	c=			(A->textaddr
				[A->textlen-1]!=B->textaddr[0]);
	else
	c=		memcmpa	(A->textaddr
				+A->textlen
				-B->textlen
				,B->textaddr
				,B->textlen);

	if			(c==0)
	argot_skip		();
	else
	argot_next		();
}

__attribute__((always_inline))
static	inline	int		notbounded	(uint8_t *a
						,uint32_t b
						,uint32_t c
						,uint8_t *d)
{	if		nay	(d==NULL)	return	0;
	if		nay	(a==d)		goto	tail;
	uint8_t		e=	d[-1];
	if		nay	(e==' ')	goto	tail;
	if		nay	(e=='\n')	goto	tail;
	if		nay	(e=='\t')	goto	tail;
						return	1;
	tail:
	if		nay	((a+b)==(d+c))	return	0;
			e=	d[c];
	if		nay	(e==' ')	return	0;
	if		nay	(e=='\n')	return	0;
	if		nay	(e=='\t')	return	0;
						return	1;
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytehaveword_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	uint8_t		*v=	A->textaddr;

	while			(1)
	{	v=	memmemb	(v
				,A->textaddr
				+A->textlen
				-v
				,B->textaddr
				,B->textlen);
		if		(notbounded(A->textaddr
					   ,A->textlen
					   ,B->textlen
					   ,v)==0)
		break;
		v++;
	}
	argot_jump		(v!=NULL);
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytelack_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	void		*v;
	if			(B->textlen==1)
	v=		memchrb	(A->textaddr,
				 B->textaddr[0],
				 A->textlen);
	else
	v=		memmemb	(A->textaddr,
				 A->textlen,
				 B->textaddr,
				 B->textlen);
	argot_jump		(v==NULL);
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytelackhead_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	int64_t		c;
	if			(B->textlen>A->textlen)
	c=			1;
	else
	if			(B->textlen==1)
	c=			(A->textaddr[0]!=B->textaddr[0]);
	else
	c=		memcmpa	(A->textaddr
				,B->textaddr
				,B->textlen);

	if			(c!=0)
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytelacktail_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	int64_t		c;
	if			(B->textlen>A->textlen)
	c=			1;
	else
	if			(B->textlen==1)
	c=			(A->textaddr
				[A->textlen-1]!=B->textaddr[0]);
	else
	c=		memcmpa	(A->textaddr
				+A->textlen
				-B->textlen
				,B->textaddr
				,B->textlen);

	if			(c!=0)
	argot_skip		();
	else
	argot_next		();
}

__attribute__((hot))
__attribute__((noinline))
SCV	bytelackword_		(void)
{	show_origin		();
	show_target		();
	VMETA		*A=	Gz.to[0];
	VMETA		*B=	Gz.to[1];
	uint8_t		*v=	A->textaddr;

	while			(1)
	{	v=	memmemb	(v
				,A->textaddr
				+A->textlen
				-v
				,B->textaddr
				,B->textlen);
		if		(notbounded(A->textaddr
					   ,A->textlen
					   ,B->textlen
					   ,v)==0)
		break;
		v++;
	}
	argot_jump		(v==NULL);
}

__attribute__((noinline))
__attribute__((hot))
SCV	not_		(void)
{	text_write	(Gz.to[0]);
	argot_next	();
}

SCV	at				(void)
{	errna=				0;
	VMETA		*A=		Gz.to[0],
			*B=		Gz.to[1];
	int		c,d;
	if				(B->op->int_compat)
	{	d=			B->value.i4.l;
		c=			-1;
	}
	else
	c=	d=	open		(B->textaddr,O_RDONLY);
	if			nay	(0>d)
	goto				fail;

	uint32_t	s,l=		A->textlen;
	ssize_t		e;
	uint8_t		*b;

	while				(1)
	{	s=			A->textsize;
		text_check		(A,s+HUGE);
		b=			A->textaddr+l;
		e=	readsome	(d,b,HUGE);
		if		nay	(0>=e)	break;
		l+=			e;
	}
	A->textlen=			l;
	if				(c>=0);
	close				(c);

	fail:
	A->io.success=			errna;
	*Gz.at=				at;
	argot_next			();
}

SCV	set				(void)
{	VLESS		*a,*b;
	argarange			(NULL,&a,&b);

	VMETA			*A;
	for				(;b>a;a++)
	{	A=	parapass	(a);
		show			(A);
		text_check		(Gz.to[0],A->textlen);
		memcpya			(Gz.to[0]  ->textaddr+
					 Gz.to[0]  ->textlen,
					 A         ->textaddr,
					 A         ->textlen);
		Gz.to[0]->textlen+=	 A         ->textlen;
	}
	*Gz.at=				set;
	argot_next			();
}

SCV	byteclear_		(void)
{	Gz.to[0]->textlen=	0;
	argot_next		();
}

static	void	byteclear	(void)
{	(*Gz.at=byteclear_)	();}

SCV	byte_		(void)	{tvarnewa	(byteinit);}
SCV	bytepage_	(void)	{tvarnewa	(bytepageinit);}
SCV	bytesize_	(void)	{tvarnewa	(bytesizeinit);}
SCV	byteio_		(void)	{tvarnewa	(byteioinit);}
SCV	bytehuge_	(void)	{tvarnewa	(bytehugeinit);}

__attribute__((hot))
__attribute__((noinline))
SCV	addadd_		(void)
{	show_target	();
	argot_next	();
}

#define	SHV	__attribute__((aligned(0x20)))	static	void

SHV	add		(void)	{(*Gz.at=add_)		();}
SHV	addadd		(void)	{(*Gz.at=addadd_)	();}
SHV	and		(void)	{(*Gz.at=and_)		();}
SHV	byte		(void)	{(*Gz.at=byte_)		();}
SHV	bytepage	(void)	{(*Gz.at=bytepage_)	();}
SHV	bytesize	(void)	{(*Gz.at=bytesize_)	();}
SHV	byteio		(void)	{(*Gz.at=byteio_)	();}
SHV	bytehuge	(void)	{(*Gz.at=bytehuge_)	();}
SHV	bytehave	(void)	{(*Gz.at=bytehave_)	();}
SHV	bytehavehead	(void)	{(*Gz.at=bytehavehead_)	();}
SHV	bytehavetail	(void)	{(*Gz.at=bytehavetail_)	();}
SHV	bytehaveword	(void)	{(*Gz.at=bytehaveword_)	();}
SHV	bytelack	(void)	{(*Gz.at=bytelack_)	();}
SHV	bytelackhead	(void)	{(*Gz.at=bytelackhead_)	();}
SHV	byteline	(void)	{(*Gz.at=byteline_)	();}
SHV	bytestring	(void)	{(*Gz.at=bytestring_)	();}
SHV	bytelacktail	(void)	{(*Gz.at=bytelacktail_)	();}
SHV	bytelackword	(void)	{(*Gz.at=bytelackword_)	();}
SHV	equal		(void)	{(*Gz.at=equal_)	();}
SHV	equalequal	(void)	{(*Gz.at=equalequal_)	();}
SHV	not		(void)	{(*Gz.at=not_)		();}
SHV	notequal	(void)	{(*Gz.at=notequal_)	();}
SHV	less		(void)	{(*Gz.at=less_)		();}
SHV	lessequal	(void)	{(*Gz.at=lessequal_)	();}
SHV	more		(void)	{(*Gz.at=more_)		();}
SHV	moreequal	(void)	{(*Gz.at=moreequal_)	();}
SHV	subsub		(void)	{(*Gz.at=subsub_)	();}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20170707",
	.official=	"20170707",
	.update=	"20200923"
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(bytehuge,	"bytehuge");
	aa		(bytepage,	"bytepage");
	aa		(bytesize,	"bytesize");
	aa		(byteio,	"byteio");
	aa		(byte,		"byte");
	aa		(ato0,		"ato0");
	aa		(_0toa,		"0toa");
	aa		(byteclear,	"byteclear");
	aa		(bytelack,	"bytelack");
	aa		(bytelackhead,	"bytelackhead");
	aa		(bytelacktail,	"bytelacktail");
	aa		(bytelackword,	"bytelackword");
	aa		(bytehave,	"bytehave");
	aa		(bytehavehead,	"bytehavehead");
	aa		(bytehavetail,	"bytehavetail");
	aa		(bytehaveword,	"bytehaveword");
	aa		(bytestring,	"bytestring");
	aa		(byteline,	"byteline");
/*	aa		(bytelinerr,	"bytelinerr");	*/
	aa_fini		();
};

__attribute__((constructor))
SCV	init			(void)
{	opbyte[0].add=		add;
	opbyte[0].addadd=	addadd;
	opbyte[0].and=		and;
	opbyte[0].at=		at;
	opbyte[0].equal=	equal;
	opbyte[0].not=		not;
	opbyte[0].subsub=	subsub;
	opbyte[0].set=		set;

	opbyte[0].equalequal=	opbyteconst[0].equalequal=	equalequal;
	opbyte[0].less=		opbyteconst[0].less=		less;
	opbyte[0].lessequal=	opbyteconst[0].lessequal=	lessequal;
	opbyte[0].more=		opbyteconst[0].more=		more;
	opbyte[0].moreequal=	opbyteconst[0].moreequal=	moreequal;
	opbyte[0].notequal=	opbyteconst[0].notequal=	notequal;
}
