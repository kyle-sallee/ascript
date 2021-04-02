/*	By Kyle Sallee in 2017 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

#include	"ascript.h"
#include	"byte.h"
#include	"a.h"
#include	"pcre2.h"
#include	<stdio.h>

static	PALIGN
uint8_t	fv		[0x10000];

typedef	struct
{	uint8_t		a[0x20];
}	FIT;

/*
The value    a     because known
the function lefty because inlined
at  compile  time
the return   value
is  computed
*/

static inline	uint8_t	lefty	(uint32_t a)
{	if	(a&0x0001)	return	0x00;
	if	(a&0x0002)	return	0x01;
	if	(a&0x0004)	return	0x02;
	if	(a&0x0008)	return	0x03;
	if	(a&0x0010)	return	0x04;
	if	(a&0x0020)	return	0x05;
	if	(a&0x0040)	return	0x06;
	if	(a&0x0080)	return	0x07;
	if	(a&0x0100)	return	0x08;
	if	(a&0x0200)	return	0x09;
	if	(a&0x0400)	return	0x0a;
	if	(a&0x0800)	return	0x0b;
	if	(a&0x1000)	return	0x0c;
	if	(a&0x2000)	return	0x0d;
	if	(a&0x4000)	return	0x0e;
	if	(a&0x8000)	return	0x0f;

	if	(a&0x00010000)	return	0x10;
	if	(a&0x00020000)	return	0x11;
	if	(a&0x00040000)	return	0x12;
	if	(a&0x00080000)	return	0x13;
	if	(a&0x00100000)	return	0x14;
	if	(a&0x00200000)	return	0x15;
	if	(a&0x00400000)	return	0x16;
	if	(a&0x00800000)	return	0x17;
	if	(a&0x01000000)	return	0x18;
	if	(a&0x02000000)	return	0x19;
	if	(a&0x04000000)	return	0x1a;
	if	(a&0x08000000)	return	0x1b;
	if	(a&0x10000000)	return	0x1c;
	if	(a&0x20000000)	return	0x1d;
	if	(a&0x40000000)	return	0x1e;
	if	(a&0x80000000)	return	0x1f;
}

__attribute__((always_inline))
static	inline	void	vini		(uint32_t a,FIT const *b)
{	fv[bit128_to_bit16(b->a)]=	lefty(a);
/*	fv[bit128_to_bit16(b->a)]=	a;
*/
}

#define	va(c,d)	vini((c),&(FIT const){.a=(d)})

inline	__attribute__((always_inline))
SCV		fv_init	(void)
{	va	(PCRE2_ALLOW_EMPTY_CLASS,	"ALLOW_EMPTY_CLASS");
	va	(PCRE2_ALT_BSUX,		"ALT_BSUX");
	va	(PCRE2_ALT_CIRCUMFLEX,		"ALT_CIRCUMFLEX");
	va	(PCRE2_ALT_VERBNAMES,		"ALT_VERBNAMES");
	va	(PCRE2_ANCHORED,		"ANCHORED");
	va	(PCRE2_CASELESS,		"CASELESS");
	va	(PCRE2_DOLLAR_ENDONLY,		"DOLLAR_ENDONLY");
	va	(PCRE2_DOTALL,			"DOTALL");
	va	(PCRE2_DUPNAMES,		"DUPNAMES");
	va	(PCRE2_EXTENDED,		"EXTENDED");
	va	(PCRE2_FIRSTLINE,		"FIRSTLINE");
	va	(PCRE2_MATCH_UNSET_BACKREF,	"MATCH_UNSET_BACKREF");
	va	(PCRE2_MULTILINE,		"MULTILINE");
	va	(PCRE2_NEVER_BACKSLASH_C,	"NEVER_BACKSLASH_C");
	va	(PCRE2_NEVER_UCP,		"NEVER_UCP");
	va	(PCRE2_NEVER_UTF,		"NEVER_UTF");
	va	(PCRE2_NO_AUTO_CAPTURE,		"NO_AUTO_CAPTURE");
	va	(PCRE2_NO_AUTO_POSSESS,		"NO_AUTO_POSSESS");
	va	(PCRE2_NO_DOTSTAR_ANCHOR,	"NO_DOTSTAR_ANCHOR");
	va	(PCRE2_NO_START_OPTIMIZE,	"NO_START_OPTIMIZE");
	va	(PCRE2_NO_UTF_CHECK,		"NO_UTF_CHECK");
	va	(PCRE2_UCP,			"UCP");
	va	(PCRE2_UNGREEDY,		"UNGREEDY");
	va	(PCRE2_UTF,			"UTF");
	va	(PCRE2_NO_JIT,			"NO_JIT");
	va	(PCRE2_NOTBOL,			"NOTBOL");
	va	(PCRE2_NOTEOL,			"NOTEOL");
	va	(PCRE2_NOTEMPTY,		"NOTEMPTY");
	va	(PCRE2_NOTEMPTY_ATSTART,	"NOTEMPTY_ATSTART");
	va	(PCRE2_PARTIAL_SOFT,		"PARTIAL_SOFT");
	va	(PCRE2_PARTIAL_HARD,		"PARTIAL_HARD");
	va	(PCRE2_JIT_COMPLETE,		"JIT_COMPLETE");
	va	(PCRE2_JIT_PARTIAL_SOFT,	"JIT_PARTIAL_SOFT");
	va	(PCRE2_JIT_PARTIAL_HARD,	"JIT_PARTIAL_HARD");
}


SCV	_pcre2	(void)	{tvarnewab(pcre2subnew,_pcre2);}

static		void	errtext_update	(VMETA *);
static		int	prepare		(VMETA *);
static		int	match_find	(VMETA *);
static		void	reference_update(VMETA *);

SCV	_pcre2match			(void)
{	VMETA		*A=		Gz.to[0];
	int		a=
	match_find			(A);

	*Gz.at=				_pcre2match;
	if			yay	(a>0)
	{	reference_update	(A);
		argot_skip		();
	}
	else
	{	errtext_update		(A);
		argot_next		();
		return;
	}
}

SCV	_pcre2nextstring		(void)
{	VMETA		*A=		Gz.to[0];
	PDATA		*P=
	pdata				(A);
/*	VMETA		*J=		P->from;	*/
	VMETA		*E=		P->input;
	uint8_t		*a=		E->textaddr;
	PCRE2_SIZE	c=		E->textlen;
	int64_t		b=		P->from->i;
	uint8_t		d;
	for				(;(c>b)&&((d=a[b++])!=0);)
/*	P->start_from=		b;	*/
	P->from->i=			b;
	*Gz.at=				_pcre2nextstring;
	argot_jump			(d==0);
}

SCV	_pcre2input			(void)
{	VMETA		*A=		Gz.to[0];
	PDATA		*P=
	pdata				(A);
	P->input=			Gz.to[1];
	P->from->i=			0;
	*Gz.at=				_pcre2input;
	argot_next			();
}

SCV	_pcre2linematch				(void)
{	VMETA		*A=			Gz.to[0];
	PDATA		*P=
	pdata					(A);
	VMETA		*E=			P->input;	/* .input */
	VMETA		*I=			P->output;	/* .output */
	text_check				(I,E->textlen);
	I->io.flag|=				textmapuse;

	uint8_t		*e,*f,*h,*t;

	PCRE2_SIZE	*ov=			P->ov;

	f=					E->textaddr+E->textlen;

	again:;
	int		a=
	match_find				(A);

	if				nay	(0>a)
	{	I->textaddr[
		I->textlen]=			0;
		*Gz.at=				_pcre2linematch;
		argot_next			();
		return;
	}

/*	e=					E->textaddr+P->start_from;
*/
	e=					E->textaddr+P->from->i;
	h=					E->textaddr+ov[0];

	for					(;e<h;h--)
	if				nay	(*h=='\n')
	{	h++;
		break;
	}

	t=					E->textaddr+ov[1];

	while					(f>t)
	if				nay	(*t++=='\n')
	break;

	size_t		s=			t-h;
	memcpya					(I->textaddr+
						 I->textlen,h,s);
	I->textlen+=				s;
/*	P->start_from=			t-E->textaddr;
*/
	P->from->i=				t-E->textaddr;
	goto					again;
}

SCV	_pcre2linediffer			(void)
{	VMETA		*A=			Gz.to[0];
	PDATA		*P=
	pdata					(A);
	VMETA		*E=			P->input;	/* .input */
	VMETA		*I=			P->output;	/* .output */
	text_check				(I,E->textlen);
	I->io.flag|=				textmapuse;

	uint8_t		*e,*f,*h,*t;

	PCRE2_SIZE	*ov=			P->ov;

	f=					E->textaddr+E->textlen;

	again:;
	int		a=
	match_find				(A);

	if				nay	(0>a)
	{	I->textaddr[
		I->textlen]=			0;
		*Gz.at=				_pcre2linediffer;
		argot_next			();
		return;
	}

/*	e=					E->textaddr+P->start_from;
*/
	e=					E->textaddr+P->from->i;
	h=					E->textaddr+ov[0];

	for					(;e<h;h--)
	if				nay	(*h=='\n')
	{	h++;
		break;
	}

	size_t		s=			h-e;
	memcpya					(I->textaddr+
						 I->textlen,e,s);
	I->textlen+=				s;

	t=					E->textaddr+ov[1];

	while					(f>t)
	if				nay	(*t++=='\n')
	break;

/*	P->start_from=			t-E->textaddr;
*/
	P->from->i=				t-E->textaddr;
	goto					again;
}

/*
__attribute__((noinline))
*/
static	CALIGN	int	match_find	(VMETA *A)
{	PDATA		*P=
	pdata				(A);

	VMETA		*K=		P->refer;	/* .refer */

	VMETA		*E=		P->input;	/* .input */
	int		i=
	pcre2_match			(P->code,
					 E->textaddr,
					 E->textlen,
/*					 P->start_from,	*/
					 P->from->i,
					 P->options_match,
					 P->match_data,
					 NULL);

	if				(i>=0)
	{	K->value.i=
		P->match_count=		i;
		P->error_code=		0;
	}
	else
	P->error_code=			i;
	return				i;
}

/*
__attribute__((noinline))
*/
static		void	reference_update(VMETA *A)
{	PDATA		*P=
	pdata				(A);
	VMETA		*E=		P->input;	/* .input */
	uint8_t		*a=		E->textaddr;

	PCRE2_SIZE	*ov=		P->ov;
/*	P->start_from+=		ov[1];
*/
	P->from->i+=			ov[1];

	VMETA		*K=		P->refer;	/* .refer */
	VMETA		*L=		K->trash;
	for				(;L;L=L->trash)
	{	L->io.flag|=		textmapuse;

		if			(L->dataaddr[0]==0)
		{	L->textaddr=	a    +ov[0];
			L->textlen=	ov[1]-ov[0];
			ov+=		2;
		}
		else			break;
	}

	int		name_off=	K->len+1;
	uint8_t		*t;
	uint8_t		*e=		P->name_table_end;

	for				(;L;L=L->trash)
	for				(/* L->datause=0, */
					 L->io.flag|=textmapuse,
					 L->textlen=0,
					 t=(uint8_t *)	P->name_table;
					 e>t;
					 t+=2+P->name_entry_size)
	if			nay	(strcmpa(L->name+name_off,t+2)==0)
	{	uint8_t	d=		*(uint8_t *)	(t+1);
		ov=			P->ov+d*2;
		d=			ov[1]-ov[0];
		L->textlen=		d;
		L->textaddr=		a    +ov[0];
		if			(d>0)
		break;
	}
}

static		void	reference_variables_create	(VMETA *);

static		int	prepare_set	(VMETA *);

SCV	_pcre2compile			(void)
{	VMETA		*A=		Gz.to[0];
	int		a=
	prepare_set			(A);
	*Gz.at=				_pcre2compile;
	if			yay	(a==0)
	argot_skip			();
	else
	{	errtext_update		(A);
		argot_next		();
	}
}

__attribute__((unused))
static		int	prepare		(VMETA *A)
{	PDATA		*P=
	pdata				(A);

	if			nay	((P->code==NULL)||
					 (P->rx->textlen	!=0))
/*	||
					 (P->options_compile		!=0)||
					 (P->options_compile_jit	!=0))
*/

	return
	prepare_set			(A);
	return				0;
}

/*
__attribute__((noinline))
*/

static		int	prepare_set	(VMETA *A)
{	PDATA		*P=
	pdata				(A);
	VMETA		*C=		P->errtext;	/* .errtext */
	VMETA		*D=		P->rx;		/* .rx */
	VMETA		*K=		P->refer;	/* .refer */

/*	P->start_from=		0;
*/
	P->from->i=			0;
	P->errint->i=			0;

	C->textaddr[
	C->textlen=0]=		0;	/* .errtext */

/*	P->input=			E->textaddr;
	P->input_len=			E->textlen;
*/

	if				(P->code)
	pcre2_code_free			(P->code);

	if				(P->match_data)
	pcre2_match_data_free		(P->match_data);

	if				(K->trash)
	{	vardel			(K->trash);
		K->trash=		NULL;
	}

	P->code=
	pcre2_compile			(D->textaddr,
					 D->textlen,
					 P->options_compile,
					 &P->error_code,
					 &P->error_offset,
					 NULL);

	if			nay	(P->code==NULL)
	goto				fail;

	if				((P->options_match&PCRE2_NO_JIT)==0)
	pcre2_jit_compile		(P->code,P->options_compile_jit);

	P->match_data=
	pcre2_match_data_create_from_pattern
					(P->code,NULL);
	reference_variables_create	(A);

	P->ov=
	pcre2_get_ovector_pointer	(P->match_data);


	pcre2_pattern_info		(P->code,
					 PCRE2_INFO_NAMEENTRYSIZE,
					&P->name_entry_size);

	pcre2_pattern_info		(P->code,
					 PCRE2_INFO_NAMECOUNT,
					&P->name_count);

	pcre2_pattern_info		(P->code,
					 PCRE2_INFO_NAMETABLE,
					&P->name_table);

	P->name_table_end=		(uint8_t *)
					 P->name_table+
					(P->name_entry_size+2)*
					 P->name_count;

	return				0;

	fail:
	errtext_update			(A);
	return				1;
}

static		void	reference_variables_create	(VMETA *A)
{	PDATA		*P=
	pdata					(A);
	VMETA		*K=			P->refer;	/* .refer */
	if				nay	(K->trash!=NULL)
	vardel					(K->trash);

	VMETA		*D=			P->rx;		/* .rx */
	uint8_t		*a,*e=			D->textaddr+
						D->textlen;
	int		c;
	VMETA		*L;
	static	uint8_t	asc	[3][PAGE];
	asc[0][0]=				' ';
	asc[2][0]=				'A';

	uint8_t		*b;
	for					(a=D->textaddr;e>a;a++)
	if				nay	(a[0]=='(')
	if				nay	(a[1]=='?')
	{	a+=				2;
		b=				a+1;

		if			nay	(a[0]=='P')
		a++;

		if			nay	(a[0]=='<')
		{	if		yay	(a[1]!='=')
			for			(;(e>b)&&(b[0]!='>');b++);
		}
		else	if			(a[0]=='\'')
		for				(;(e>b)&&(b[0]!='\'');b++);

		a++;
		c=				b-a;
		if			yay	(c>0)
		if			yay	(0x3f>c)
		{	memcpy			(asc[0]+1,a,c);
			L=
			var_new_sub_len		(asc[0],K,c+1);
			L->op=			opbyte;
			L->io.flag|=		textmapuse;
/*			L->dataaddr=		asc[0];
			L->datasize=		PAGE;
*/
			L->dataaddr=		asc[2];
/* WHAT? */
		}
	}

	for					(c=0,a=D->textaddr;e>a;a++)
	if				nay	(a[0]=='(')
	if				yay	(a[1]!='?')
	{	a++;
		c++;
	}

	for					(;c>=0;c--)
	{	/* sprintf is slow */
		int	d=
		sprintf				(asc[0]+1,"%i",c);
		L=
		var_new_sub_len			(asc[0],K,d+1);
		L->io.flag|=			textmapuse;
/*		L->dataaddr=			asc[0];
		L->datasize=			PAGE;
*/
		L->dataaddr=			asc[1];
/* WHAT? */
	}

	/*	upon  completion
		at    K->trash
		in    proper  order
		from  0
		until whatever
		the   numeric references
		are   chained
		Aft   numeric references
		the   named   references are chained.
	*/
}

static		void	errtext_update	(VMETA *A)
{	PDATA		*P=
	pdata				(A);
	VMETA		*C=		P->errtext;	/* .errtext */
	P->errint->i=			P->error_code;

	pcre2_get_error_message		(P->error_code,
					 C->textaddr,
					 C->textsize);
}

__attribute__((always_inline))
static	inline	uint32_t	flag	(VLESS *a)
{	return	1<<fv[bit128_to_bit16(parapass(a)->textaddr)];
}

__attribute__((noinline))
static	CALIGN	uint32_t	flags	(void)
{	VLESS		*a,*b;
	argarange			(NULL,&a,&b);
	uint32_t	c=		0;

	for				(c=0;b>a;a++)
	c|=	flag			(a);
	return				c;
}

SCV	pcre2flagcompile		(void)
{	VMETA		*A=		Gz.to[0];
	PDATA		*b=
	pdata				(A);
	b->options_compile=	flags	();
	*Gz.at=				pcre2flagcompile;
	argot_next			();
}

SCV	pcre2flagjit			(void)
{	VMETA		*A=		Gz.to[0];
	PDATA		*b=
	pdata				(A);
	b->options_compile_jit=	flags	();
	*Gz.at=				pcre2flagjit;
	argot_next			();
}

SCV	pcre2flagmatch			(void)
{	VMETA		*A=		Gz.to[0];
	PDATA		*b=
	pdata				(A);
	b->options_match=	flags	();
	*Gz.at=				pcre2flagmatch;
	argot_next			();
}

__attribute__((cold))
		void	segv	(void)
{	VMETA		*A=	Gz.to[0];
	if			(A->op!=oppcre2)	return;
	PDATA		*P=
	pdata			(A);
	if			(P->code==NULL)
	warnx			("A match afore acquisition "
				 "the regular expression compilation "
				 "is required.");
}

const	ARGOT_INFO	AI=
{	.author=	"Kyle David Sallee",
	.author_email=	"kyle.sallee@gmail.com",
	.homepage=	"https://kyle-sallee.github.io/ascript/",
	.create=	"20190331",
	.official=	"20190331",
	.update=	"20200827",
};

__attribute__((constructor))
SCV	aainit		(void)
{	aa_init		();
	aa		(_pcre2,		"pcre2");
	aa		(_pcre2input,		"pcre2input");
	aa		(pcre2flagjit,		"pcre2flagjit");
	aa		(pcre2flagmatch,	"pcre2flagmatch");
	aa		(_pcre2nextstring,	"pcre2nextstring");
	aa		(_pcre2match,		"pcre2match");
	aa		(_pcre2linediffer,	"pcre2linediffer");
	aa		(_pcre2linematch,	"pcre2linematch");
	aa		(pcre2flagcompile,	"pcre2flagcompile");
	aa		(_pcre2compile,		"pcre2compile");
	aa_fini		();
	fv_init		();
};

__attribute__((unused))
SCV	init_old	(void)
{

static	VMETA		a[0x22]=
{	{	.name=		"PCRE2_ALLOW_EMPTY_CLASS",
		.len=strlen(	"PCRE2_ALLOW_EMPTY_CLASS"),
		.value.i=	 PCRE2_ALLOW_EMPTY_CLASS},
	{	.name=		"PCRE2_ALT_BSUX",
		.len=strlen(	"PCRE2_ALT_BSUX"),
		.value.i=	 PCRE2_ALT_BSUX},
	{	.name=		"PCRE2_ALT_CIRCUMFLEX",
		.len=strlen(	"PCRE2_ALT_CIRCUMFLEX"),
		.value.i=	 PCRE2_ALT_CIRCUMFLEX},
	{	.name=		"PCRE2_ALT_VERBNAMES",
		.len=strlen(	"PCRE2_ALT_VERBNAMES"),
		.value.i=	 PCRE2_ALT_VERBNAMES},
	{	.name=		"PCRE2_ANCHORED",
		.len=strlen(	"PCRE2_ANCHORED"),
		.value.i=	 PCRE2_ANCHORED},
	{	.name=		"PCRE2_CASELESS",
		.len=strlen(	"PCRE2_CASELESS"),
		.value.i=	 PCRE2_CASELESS},
	{	.name=		"PCRE2_DOLLAR_ENDONLY",
		.len=strlen(	"PCRE2_DOLLAR_ENDONLY"),
		.value.i=	 PCRE2_DOLLAR_ENDONLY},
	{	.name=		"PCRE2_DOTALL",
		.len=strlen(	"PCRE2_DOTALL"),
		.value.i=	 PCRE2_DOTALL},
	{	.name=		"PCRE2_DUPNAMES",
		.len=strlen(	"PCRE2_DUPNAMES"),
		.value.i=	 PCRE2_DUPNAMES},
	{	.name=		"PCRE2_EXTENDED",
		.len=strlen(	"PCRE2_EXTENDED"),
		.value.i=	 PCRE2_EXTENDED},
	{	.name=		"PCRE2_FIRSTLINE",
		.len=strlen(	"PCRE2_FIRSTLINE"),
		.value.i=	 PCRE2_FIRSTLINE},
	{	.name=		"PCRE2_MATCH_UNSET_BACKREF",
		.len=strlen(	"PCRE2_MATCH_UNSET_BACKREF"),
		.value.i=	 PCRE2_MATCH_UNSET_BACKREF},
	{	.name=		"PCRE2_MULTILINE",
		.len=strlen(	"PCRE2_MULTILINE"),
		.value.i=	 PCRE2_MULTILINE},
	{	.name=		"PCRE2_NEVER_BACKSLASH_C",
		.len=strlen(	"PCRE2_NEVER_BACKSLASH_C"),
		.value.i=	 PCRE2_NEVER_BACKSLASH_C},
	{	.name=		"PCRE2_NEVER_UCP",
		.len=strlen(	"PCRE2_NEVER_UCP"),
		.value.i=	 PCRE2_NEVER_UCP},
	{	.name=		"PCRE2_NEVER_UTF",
		.len=strlen(	"PCRE2_NEVER_UTF"),
		.value.i=	 PCRE2_NEVER_UTF},
	{	.name=		"PCRE2_NO_AUTO_CAPTURE",
		.len=strlen(	"PCRE2_NO_AUTO_CAPTURE"),
		.value.i=	 PCRE2_NO_AUTO_CAPTURE},
	{	.name=		"PCRE2_NO_AUTO_POSSESS",
		.len=strlen(	"PCRE2_NO_AUTO_POSSESS"),
		.value.i=	 PCRE2_NO_AUTO_POSSESS},
	{	.name=		"PCRE2_NO_DOTSTAR_ANCHOR",
		.len=strlen(	"PCRE2_NO_DOTSTAR_ANCHOR"),
		.value.i=	 PCRE2_NO_DOTSTAR_ANCHOR},
	{	.name=		"PCRE2_NO_START_OPTIMIZE",
		.len=strlen(	"PCRE2_NO_START_OPTIMIZE"),
		.value.i=	 PCRE2_NO_START_OPTIMIZE},
	{	.name=		"PCRE2_NO_UTF_CHECK",
		.len=strlen(	"PCRE2_NO_UTF_CHECK"),
		.value.i=	 PCRE2_NO_UTF_CHECK},
	{	.name=		"PCRE2_UCP",
		.len=strlen(	"PCRE2_UCP"),
		.value.i=	 PCRE2_UCP},
	{	.name=		"PCRE2_UNGREEDY",
		.len=strlen(	"PCRE2_UNGREEDY"),
		.value.i=	 PCRE2_UNGREEDY},
	{	.name=		"PCRE2_UTF",
		.len=strlen(	"PCRE2_UTF"),
		.value.i=	 PCRE2_UTF},
	{	.name=		"PCRE2_NO_JIT",
		.len=strlen(	"PCRE2_NO_JIT"),
		.value.i=	 PCRE2_NO_JIT},
	{	.name=		"PCRE2_NOTBOL",
		.len=strlen(	"PCRE2_NOTBOL"),
		.value.i=	 PCRE2_NOTBOL},
	{	.name=		"PCRE2_NOTEOL",
		.len=strlen(	"PCRE2_NOTEOL"),
		.value.i=	 PCRE2_NOTEOL},
	{	.name=		"PCRE2_NOTEMPTY",
		.len=strlen(	"PCRE2_NOTEMPTY"),
		.value.i=	 PCRE2_NOTEMPTY},
	{	.name=		"PCRE2_NOTEMPTY_ATSTART",
		.len=strlen(	"PCRE2_NOTEMPTY_ATSTART"),
		.value.i=	 PCRE2_NOTEMPTY_ATSTART},
	{	.name=		"PCRE2_PARTIAL_SOFT",
		.len=strlen(	"PCRE2_PARTIAL_SOFT"),
		.value.i=	 PCRE2_PARTIAL_SOFT},
	{	.name=		"PCRE2_PARTIAL_HARD",
		.len=strlen(	"PCRE2_PARTIAL_HARD"),
		.value.i=	 PCRE2_PARTIAL_HARD},
	{	.name=		"PCRE2_JIT_COMPLETE",
		.len=strlen(	"PCRE2_JIT_COMPLETE"),
		.value.i=	 PCRE2_JIT_COMPLETE},
	{	.name=		"PCRE2_JIT_PARTIAL_SOFT",
		.len=strlen(	"PCRE2_JIT_PARTIAL_SOFT"),
		.value.i=	 PCRE2_JIT_PARTIAL_SOFT},
	{	.name=		"PCRE2_JIT_PARTIAL_HARD",
		.len=strlen(	"PCRE2_JIT_PARTIAL_HARD"),
		.value.i=	 PCRE2_JIT_PARTIAL_HARD},
};

	int		b;
	for				(b=0;0x22>b;b++)
	{	map_init		(a+b);
/*		intconstsubnew		(a+b);	*/
		int4init		(a+b);
		vattach			(a+b);
	}
}
