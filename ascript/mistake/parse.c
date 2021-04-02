/*	By Kyle Sallee from 2015 ... 2020 copyrighted.
	Used by ascript.c
	by parse.c some functions are provided.
*/

#define		PROGRAM		1

#ifndef		_GNU_SOURCE
#define		_GNU_SOURCE
#endif
#define		_POSIX_SOURCE
#define		_POSIX_C_SOURCE		199309L	/* for siginfo_t in sigaction */
#define		_XOPEN_SOURCE		700
#define		_XOPEN_SOURCE_EXTENDED
#define		__USE_XOPEN

#include	"ascript.h"
#include	"argot.h"

/*
#define		ZONE_MAP_SIZE
#define		ZONE_MAP_RESIZE
*/

__attribute__((cold))
__attribute__((noinline))
noreturn
static		void	miss		(void)
{	ZONE	*Z=	(ZONE *)	Gz.aat->zone;
	errx	(1,"%s%s%s%i%s%i%s%s%s",
		"File ",Z->name,
		" line ",Gz.aat->from>>0x20,
		" part ",Gz.aat->from &0xff,
		" argot ",Gz.aat->name,
		" the load failed.");
}

__attribute__((hot))
__attribute__((noinline))
static	CALIGN	void	adef1	(ARGOT **AA)
{	int		b=	errna;
	int		a=
	aload			(Gz.aat->name);

	if		yay	(a==0)
	{	errna=		b;
		AA[0]->at	();
	}
	else
	miss			();
}

#if	__SIZEOF_POINTER__	==	4
/* 22 min opcode route maybe more on ia32 */
__attribute__((hot))
static	CALIGN	void	adef0		(void)
{	PART		*L=		Gz.aat;

	ARGOT		**AA=
	aam_get				(L->name);

	ARGOT		*A=		*AA;

	if			yay	(A!=NULL)
	{	vector8x16	a,b;
		b=			*(vector8x16 *)	L->name;

		do
		{	a=		*(vector8x16 *)	A->name;
			a^=		b;
			if	yay	((a[0]|a[1])==0)
			{	A->at	();
				return;
			}
			A=		A->fore;
		}	while		(A!=NULL);
	}

	adef1				(AA);
}
#else
/* On gcc for __int128 more opcodes execute. */
/* On x86_64 20 min opcode route. */
__attribute__((hot))
static	CALIGN	void	adef0		(void)
{	PART		*L=		Gz.aat;

	uint64_t	a[2],*b;
	a[0]=				*(uint64_t *)	 L->name;
	a[1]=				*(uint64_t *)	(L->name+8);

	ARGOT		**AA=
	aam_get				(L->name);

	ARGOT		*A=		*AA;

	if			yay	(A!=NULL)
	do
	{	b=			(uint64_t *)	A->name;
/* for opcode xor xor or 2 opcode mov would be required */
		if		yay	(a[0]==b[0])
		if		yay	(a[1]==b[1])
		{	A->at		();
			return;
		}
		A=			A->fore;
	}	while			(A!=NULL);

	adef1				(AA);
}
#endif

static	inline	void	vamset	(VLESS *A)
{	A->vam=	&Gz.vam[bit128_to_bit16(A->map[0].addr)];
}

static	inline	ARGOT	**vam_set	(PART *L)
{	VLESS		*a=		L[0].arga;
	VLESS		*e=		L[1].arga;
	do
/*	{	if		yay	(a->op==varrefop)	*/
	{	if		yay	(a->vam==NULL)
		vamset			(a);
	}	while			(++a!=e);
}

__attribute__((always_inline))
static	inline	uint8_t	labellen	(uint8_t *a,uint8_t const b)
{	if		nay	(a[0x0]==b)	return		0x0;
	if		nay	(a[0x1]==b)	return		0x1;
	if		nay	(a[0x2]==b)	return		0x2;
	if		nay	(a[0x3]==b)	return		0x3;
	if		nay	(a[0x4]==b)	return		0x4;
	if		nay	(a[0x5]==b)	return		0x5;
	if		nay	(a[0x6]==b)	return		0x6;
	if		nay	(a[0x7]==b)	return		0x7;
	if		nay	(a[0x8]==b)	return		0x8;
	if		nay	(a[0x9]==b)	return		0x9;
	if		nay	(a[0xa]==b)	return		0xa;
	if		nay	(a[0xb]==b)	return		0xb;
	if		nay	(a[0xc]==b)	return		0xc;
	if		nay	(a[0xd]==b)	return		0xd;
	if		nay	(a[0xe]==b)	return		0xe;
	if		nay	(a[0xf]==b)	return		0xf;
						return		0x10;
}

static	inline	void	nearset		(PART_REFER *R, uint32_t const f)
{	uint16_t	b=
	bit128_to_bit16			(R->name)+f;
	PART_REFER	**LR=		&Gz.nearm[b];
	R->fore=			*LR;
	*LR=				R;
}

typedef	struct
{	uint8_t		*a;	/* text */
	PART		*L;	/* available line data */
	VLESS		*P;	/* available argot parameter data */
	ZONE	* const	z;	/* the zone pointer */
	PART_REFER	*J;	/* jump target references */
	uint64_t	from;
	uint8_t		*D;	/* limitless data */
}	PARSE_DATA;

/*
On x86_64
In CPU registers
the PARSE_DATA structure content
will probably be stored.
*/

static	inline	void	label1		(PARSE_DATA *S)
{	S->J++;
	__builtin_memcpy		(S->J->name,  S->a,LABEL_SIZE);
	uint8_t		a=
	labellen			(S->J->name,'\'');
	__builtin_memset		(S->J->name+a,0,   LABEL_SIZE);
	S->a+=				a+1;
	S->J->part=			S->L+1;
	nearset				(S->J,Gz.far_total);
/*	nearset				(S->J,S->far);	*/
}

static	inline	void	farset		(PART_REFER *R)
{	uint16_t	a=
	bit128_to_bit16			(R->name);
	PART_REFER	**LR=		&Gz.farm[a];
	R->fore=			*LR;
	*LR=				R;
}

static	inline	void	label2		(PARSE_DATA *S)
{	Gz.far_total++;
	S->J++;
	__builtin_memcpy		(S->J->name,  S->a,LABEL_SIZE);
	uint8_t		a=
	labellen			(S->J->name,'"');
	__builtin_memset		(S->J->name+a,0,   LABEL_SIZE);
	S->a+=				a+1;
	S->J->part=			S->L+1;
	farset				(S->J);
/*	farset				(S->J,&S->far);	*/
}

static	inline	uint8_t	selfy			(PARSE_DATA *S)
{	S->P->free=				(void *)	S->P;
	S->P->vam=				(VMETA **)	&S->P->free;
}

/* vless no longer invoked? */

/*
static	inline	uint8_t	*vless			(PARSE_DATA *S)
{	S->P->val=				&S->P->value;
	S->P->io.flag=				bitmap0use;
	return
	S->P->map[0].addr=			S->D;
}
*/

__attribute__((always_inline))
static	inline	uint8_t	ticklen		(uint8_t *a)
{	if		nay	(a[0x01]=='`')	return	0x01;
	if		nay	(a[0x02]=='`')	return	0x02;
	if		nay	(a[0x03]=='`')	return	0x03;
	if		nay	(a[0x04]=='`')	return	0x04;
	if		nay	(a[0x05]=='`')	return	0x05;
	if		nay	(a[0x06]=='`')	return	0x06;
	if		nay	(a[0x07]=='`')	return	0x07;
	if		nay	(a[0x08]=='`')	return	0x08;
	if		nay	(a[0x09]=='`')	return	0x09;
	if		nay	(a[0x0a]=='`')	return	0x0a;
	if		nay	(a[0x0b]=='`')	return	0x0b;
	if		nay	(a[0x0c]=='`')	return	0x0c;
	if		nay	(a[0x0d]=='`')	return	0x0d;
	if		nay	(a[0x0e]=='`')	return	0x0e;
	if		nay	(a[0x0f]=='`')	return	0x0f;
	if		nay	(a[0x10]=='`')	return	0x10;
	if		nay	(a[0x11]=='`')	return	0x11;
	if		nay	(a[0x12]=='`')	return	0x12;
	if		nay	(a[0x13]=='`')	return	0x13;
	if		nay	(a[0x14]=='`')	return	0x14;
	if		nay	(a[0x15]=='`')	return	0x15;
	if		nay	(a[0x16]=='`')	return	0x16;
	if		nay	(a[0x17]=='`')	return	0x17;
	if		nay	(a[0x18]=='`')	return	0x18;
	if		nay	(a[0x19]=='`')	return	0x19;
	if		nay	(a[0x1a]=='`')	return	0x1a;
	if		nay	(a[0x1b]=='`')	return	0x1b;
	if		nay	(a[0x1c]=='`')	return	0x1c;
	if		nay	(a[0x1d]=='`')	return	0x1d;
	if		nay	(a[0x1e]=='`')	return	0x1e;
	if		nay	(a[0x1f]=='`')	return	0x1f;
}

static	inline	void	tick1		(PARSE_DATA *S)
{	S->P->map[0].addr=		 S->P->text;
	__builtin_memcpy		(S->P->text,S->a,0x20);
	uint8_t		b=
	ticklen				(S->P->text);
	S->P->map[0].len=		b;
	__builtin_memset		(S->P->text+b,0,0x20);
	S->P++;
	S->a+=				b+1;
}

CALIGN
static	const	uint8_t
xX[]=	{   0,   0,   0,   0,   0,   0,   0,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,   1,   2,   3,   4,   5,   6,   7,
	    8,   9,   0,   0,   0,   0,   0,   0,
	    0,  10,  11,  12,  13,  14,  15,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,   0,   0,   0,   0,   0,   0,   0,
	    0,  10,  11,  12,  13,  14,  15,
	};


#include	"../argot/utf8.h"

__attribute__((always_inline))
static	inline	void	unicode	(uint8_t **a,uint8_t **b)
{	uint32_t
	c=		xX[b[0][1]];	c<<=4;
	c+=		xX[b[0][2]];	c<<=4;
	c+=		xX[b[0][3]];	c<<=4;
	c+=		xX[b[0][4]];	c<<=4;
	c+=		xX[b[0][5]];	c<<=4;
	c+=		xX[b[0][6]];
	(*b)+=		7;
	utf8_out	(a,c);
}

__attribute__((always_inline))
static	inline	void	tick_escape(uint8_t **a,uint8_t **b)
{	uint8_t		c=	**b;
	(*b)++;

	if		nay	(c=='n')	*(*a)++=	'\n';
	else	if	nay	(c=='0')	*(*a)++=	0;
/*	else	if	nay	(c=='t')	*(*a)++=	'\t';	*/
	else	if	nay	(c=='U')	unicode		(a,b);
/*	else	if	nay	(c=='e')	*(*a)++=	'\e';	*/
	else	{				*(*a)++=	'\\';
						*(*a)++=	c;
		}
}

static	inline	void	tick_parse	(uint8_t **a,uint8_t **b)
{	uint8_t		c;
	while				(1)
	{	c=			**b;
		(*b)++;
		if		nay	(c=='`')	return;
		if		yay	(c!='\\')
		{	**a=		c;
			(*a)++;
		}
		else	tick_escape	(a,b);
	}
}

static	inline	void	tick2		(PARSE_DATA *S)
{	uint8_t		*a=
	S->P->map[0].addr=		 S->P->text;
	uint8_t		*b=		 S->a;

	tick_parse			(&a,&b);
	S->P->map[0].len=		a-S->P->text;
	S->P++;
	S->a=				b;
}

static	inline	void	*roundx40	(void const * const a)
{	uintptr_t	b=		(uintptr_t)	a;
	b+=				0x3f;
	/* and    $0xffffffffffffffc0,%rax */
	b>>=				6;
	b<<=				6;
	return		(void *)	b;
}

static	inline	void	tick3		(PARSE_DATA *S)
{	uint8_t		*a=
	S->P->map[0].addr=		S->D;
	uint8_t		*b=		 S->a;
	tick_parse			(&a,&b);
	S->P->map[0].len=		a-S->D;
	S->P++;
	S->D=
	roundx40			(a);
	S->a=				b;
}

static	inline	void	tick		(PARSE_DATA *S)
{	selfy			(S);
	S->P->op=		varconstop;
	S->P->val=		&S->P->value;
	S->P->io.flag=		bitmap0use;

	static	CALIGN
	uint8_t		c[0x100];
	uint8_t		*a=	S->a;
	c['`']=			0;
	c['\\']=		0;
	c[a[0x00]]++;
	c[a[0x01]]++;
	c[a[0x02]]++;
	c[a[0x03]]++;
	c[a[0x04]]++;
	c[a[0x05]]++;
	c[a[0x06]]++;
	c[a[0x07]]++;
	c[a[0x08]]++;
	c[a[0x09]]++;
	c[a[0x0a]]++;
	c[a[0x0b]]++;
	c[a[0x0c]]++;
	c[a[0x0d]]++;
	c[a[0x0e]]++;
	c[a[0x0f]]++;
	c[a[0x10]]++;
	c[a[0x10]]++;
	c[a[0x11]]++;
	c[a[0x12]]++;
	c[a[0x13]]++;
	c[a[0x14]]++;
	c[a[0x15]]++;
	c[a[0x16]]++;
	c[a[0x17]]++;
	c[a[0x18]]++;
	c[a[0x19]]++;
	c[a[0x1a]]++;
	c[a[0x1b]]++;
	c[a[0x1c]]++;
	c[a[0x1d]]++;
	c[a[0x1e]]++;
	c[a[0x1f]]++;
	if		yay	(c['`'])
	{	if		(c['\\']==0)
		tick1		(S);		/* short simple */
		else
		tick2		(S);		/* short escaped */
	}
	else	tick3		(S);		/* long */
}


__attribute__((always_inline))
static	inline	uint8_t	barelen		(uint8_t *a)
{	if			nay	(','>=a[0x01])	return	0x01;
	if			nay	(','>=a[0x02])	return	0x02;
	if			nay	(','>=a[0x03])	return	0x03;
	if			nay	(','>=a[0x04])	return	0x04;
	if			nay	(','>=a[0x05])	return	0x05;
	if			nay	(','>=a[0x06])	return	0x06;
	if			nay	(','>=a[0x07])	return	0x07;
	if			nay	(','>=a[0x08])	return	0x08;
	if			nay	(','>=a[0x09])	return	0x09;
	if			nay	(','>=a[0x0a])	return	0x0a;
	if			nay	(','>=a[0x0b])	return	0x0b;
	if			nay	(','>=a[0x0c])	return	0x0c;
	if			nay	(','>=a[0x0d])	return	0x0d;
	if			nay	(','>=a[0x0e])	return	0x0e;
	if			nay	(','>=a[0x0f])	return	0x0f;
	if			nay	(','>=a[0x10])	return	0x10;
	if			nay	(','>=a[0x11])	return	0x11;
	if			nay	(','>=a[0x12])	return	0x12;
	if			nay	(','>=a[0x13])	return	0x13;
	if			nay	(','>=a[0x14])	return	0x14;
	if			nay	(','>=a[0x15])	return	0x15;
	if			nay	(','>=a[0x16])	return	0x16;
	if			nay	(','>=a[0x17])	return	0x17;
	if			nay	(','>=a[0x18])	return	0x18;
	if			nay	(','>=a[0x19])	return	0x19;
	if			nay	(','>=a[0x1a])	return	0x1a;
	if			nay	(','>=a[0x1b])	return	0x1b;
	if			nay	(','>=a[0x1c])	return	0x1c;
	if			nay	(','>=a[0x1d])	return	0x1d;
	if			nay	(','>=a[0x1e])	return	0x1e;
							return	0x1f;
}

__attribute__((hot))
static	CALIGN	void	vdef0		(void)
{	PART		*L=		Gz.aat;
	vam_set				(L);
	adef0				();
}

static	inline	void	var_or_num	(PARSE_DATA *S,uint8_t const * const b)
{	if				(S->P->map[0].addr[0]>'9')
	{	S->P->op=		varrefop;
		S->L->func=		vdef0;
	}
	else
	{	S->P->op=		varfixop;
		selfy			(S);
	}
}

static	inline	int	bare			(PARSE_DATA *S)
{	S->P->val=				&S->P->value;
	S->P->io.flag=				bitmap0use;
	uint8_t		*b=
	S->P->map[0].addr=			S->P->text;
	__builtin_memcpy			(b,S->a-1,0x20);

	uint8_t		a,
			c=			0;

	do
	{	c+=	barelen			(b+c);
	}
	while					(a=b[c],
						(a!= ',')&&
						(a!='\t')&&
						(a!='\n'));
	__builtin_memset			(b+c,0,0x20);
	S->P->map[0].len=			c;
	S->a+=					c;
	var_or_num				(S,b);
	S->P++;
	return					a;
}

static	inline	void	quote1		(PARSE_DATA *S)
{	selfy				(S);
	S->P->op=			varconstop;
	S->P->io.flag=			bitmap0use;
	S->P->val=			&S->P->value;
	S->P->value.b=			'\'';
	uint8_t		*b=
	S->P->map[0].addr=		S->P->text;
	__builtin_memcpy		(b,  S->a,LABEL_SIZE);
	uint8_t		a=
	labellen			(b,'\'');
	__builtin_memset		(b+a,0   ,LABEL_SIZE);
	S->a+=				a+1;
	S->P->map[0].len=		a;
	S->P++;
}

static	inline	void	quote2		(PARSE_DATA *S)
{	selfy				(S);
	S->P->op=			varconstop;
	S->P->io.flag=			bitmap0use;
	S->P->val=			&S->P->value;
	S->P->value.b=			'"';
	uint8_t		*b=
	S->P->map[0].addr=		S->P->text;
	__builtin_memcpy		(b,  S->a,LABEL_SIZE);
	uint8_t		a=
	labellen			(b,'"');
	__builtin_memset		(b+a,0   ,LABEL_SIZE);
	S->a+=				a+1;
	S->P->map[0].len=		a;
	S->P++;
}

__attribute__((always_inline))
static	inline	void	paraesc		(PARSE_DATA *S)
{	if		yay	(*(S->a++)=='\n')
	{	S->from+=	1L<<0x20;
		S->from&=	~0xffffffffL;
		S->from|=	1;
	}
}

static	inline	int	para		(PARSE_DATA *S)
{	uint8_t		d;
	while				(1)
	{	d=			*(S->a++);
		if		yay	(d >'`')
		use:
		switch			(		bare	(S))
		{	case	'\n':			return	'\n';
			case	',':			return	',';
		}
		else	if	nay	(d=='`')	tick	(S);
		else	if	nay	(d=='\\')	paraesc	(S);
		else	if	nay	(d> ',')	goto	use;
		else	if	nay	(d==',')	return	',';
		else	if	nay	(d=='\n')	return	'\n';
		else	if	nay	(d=='\t');
		else	if	nay	(d=='\'')	quote1	(S);
		else	if	nay	(d=='"')	quote2	(S);
		else	if	nay	(d==' ');
		else					goto	use;
	}
}

static	inline	int	argot			(PARSE_DATA *S)
{	S->L++;
	S->L->arga=				S->P;
	S->L->func=				adef0;
/*	S->L->zone=				S->z;	*/
	S->L->from=				S->from;
	S->L->far=				Gz.far_total;
/*	S->L->far=				S->far;	*/
	uint8_t		a,*b=			S->L->name;
	*b++=					S->a[-1];
	for					(;1;S->a++)
	if				yay	((a=S->a[0])>',')
	keep:
	*b++=					a;
	else	if			nay	(a==',')
	{	S->a++;		return		a;
	}
	else	if			nay	(a==' ')
	continue;
	else	if			nay	(a=='\t')
	return		para			(S);
	else	if			nay	(a=='\n')
	{	S->a++;		return		a;
	}
	else	goto				keep;

/*	switch					(a=*S->a)
	{	default:	*b++=		a;		*/
/*		case	' ':	break;	*/
/*		case	'\n':	goto		argot_end;	*/
/*		case	'\n':
		case	',':	S->a++;
				return		a;
*/
/*		case	'\t':	return	para	(S);	*/
/*	}	*/
}


static	inline	void	lead		(PARSE_DATA *S)
{	while				(1)
	{	uint8_t	d=		*(S->a++);
		if		yay	(d>',')
		use:
		switch			(argot(S))
		{	case	'\n':
			feed:
			S->from+=	1L<<0x20;
			S->from&=	~0xffffffffL;
/*			if	nay	(S->a>=S->lim)		return;	*/
			default:	/* case	',': */
			comma:
			S->from++;
		}
		else	if	nay	(d=='\n')		goto	feed;
		else	if	nay	(d==',')		goto	comma;
		else	if	nay	(d=='\'')		label1	(S);
		else	if	nay	(d=='"')		label2	(S);
		else	if	nay	(d=='\t')		continue;
		else	if	nay	(d==' ')		continue;
		else	if	yay	(d=='#')
		{	while		(*(S->a++)!='\n');	goto	feed;
		}
		else	if	nay	(d==0)			return;
		else						goto	use;
	}
}

__attribute__((cold))
static		void	_ret	(void)	{ Gz.aat--;}

static	inline	void	zone_done	(PARSE_DATA *S)
{
	Gz.far_total++;
/*	Gz.far_total=	S->far+1;	*/
	S->L[1].func=	_ret;
	S->from+=	1L<<0x20;
	S->L[1].from=	S->from;
/*	S->L[1].zone=	S->z;	*/
	S->L[1].arga=	S->P;
	S->L[2].func=	_ret;
	S->from+=	1L<<0x20;
	S->L[2].from=	S->from;
/*	S->L[2].zone=	S->z;	*/
	S->L[2].arga=	S->P;
	__builtin_memcpy(S->L[1].name,"fini",4);
	__builtin_memcpy(S->L[2].name,"fini",4);
	S->L+=		3;
}

__attribute__((flatten))
__attribute__((noinline))
static	CALIGN	void	parse	(uint8_t *A,ZONE * const z)
/*
static	CALIGN	void	parse	(uint8_t *A,size_t const t,ZONE * const z)
*/
{
/*	CALIGN	*/
	PARSE_DATA	S=
	{
/*		.z=			z,		*/
/*		.n=			1,
		.p=			1,
*/
		.from=			0x100000001,
		.D=			z->data,
		.J=			z->jump-1,
/*		.far=			Gz.far_total,	*/
/*		.lim=			A+t,		*/
		.P=			z->meta,
		.L=			z->part-1,
		.a=			A,
	};

	lead				(&S);
	zone_done			(&S);
}


__attribute__((noinline))
static	CALIGN	void	zone_minimal	(ZONE * const z)
{	z->data_size=
	z->part_size=
	z->meta_size=
	z->jump_size=			PAGE;

	void		*v=
	pps				(4*PAGE);
	z->data=	v;
	z->part=	v+		PAGE;
	z->meta=	v+		PAGE*2;
	z->jump=	v+		PAGE*3;
}

__attribute__((noinline))
static	CALIGN	void	bc	(uint32_t * const A,uint8_t const *a,size_t b)
{	A['\t']=
	A['\n']=
	A['\'']=
	A['"']=
	A[',']=			0;

	a+=			0xc;
	b-=			0xc;

	/* per 128 byte values counted one cmp one jmp */

	while			(1)
	{	A[a[0x00]]++;	A[a[0x01]]++;	A[a[0x02]]++;	A[a[0x03]]++;
		A[a[0x04]]++;	A[a[0x05]]++;	A[a[0x06]]++;	A[a[0x07]]++;
		A[a[0x08]]++;	A[a[0x09]]++;	A[a[0x0a]]++;	A[a[0x0b]]++;
		A[a[0x0c]]++;	A[a[0x0d]]++;	A[a[0x0e]]++;	A[a[0x0f]]++;

		A[a[0x10]]++;	A[a[0x11]]++;	A[a[0x12]]++;	A[a[0x13]]++;
		A[a[0x14]]++;	A[a[0x15]]++;	A[a[0x16]]++;	A[a[0x17]]++;
		A[a[0x18]]++;	A[a[0x19]]++;	A[a[0x1a]]++;	A[a[0x1b]]++;
		A[a[0x1c]]++;	A[a[0x1d]]++;	A[a[0x1e]]++;	A[a[0x1f]]++;

		A[a[0x20]]++;	A[a[0x21]]++;	A[a[0x22]]++;	A[a[0x23]]++;
		A[a[0x24]]++;	A[a[0x25]]++;	A[a[0x26]]++;	A[a[0x27]]++;
		A[a[0x28]]++;	A[a[0x29]]++;	A[a[0x2a]]++;	A[a[0x2b]]++;
		A[a[0x2c]]++;	A[a[0x2d]]++;	A[a[0x2e]]++;	A[a[0x2f]]++;

		A[a[0x30]]++;	A[a[0x31]]++;	A[a[0x32]]++;	A[a[0x33]]++;
		A[a[0x34]]++;	A[a[0x35]]++;	A[a[0x36]]++;	A[a[0x37]]++;
		A[a[0x38]]++;	A[a[0x39]]++;	A[a[0x3a]]++;	A[a[0x3b]]++;
		A[a[0x3c]]++;	A[a[0x3d]]++;	A[a[0x3e]]++;	A[a[0x3f]]++;

		A[a[0x40]]++;	A[a[0x41]]++;	A[a[0x42]]++;	A[a[0x43]]++;
		A[a[0x44]]++;	A[a[0x45]]++;	A[a[0x46]]++;	A[a[0x47]]++;
		A[a[0x48]]++;	A[a[0x49]]++;	A[a[0x4a]]++;	A[a[0x4b]]++;
		A[a[0x4c]]++;	A[a[0x4d]]++;	A[a[0x4e]]++;	A[a[0x4f]]++;

		A[a[0x50]]++;	A[a[0x51]]++;	A[a[0x52]]++;	A[a[0x53]]++;
		A[a[0x54]]++;	A[a[0x55]]++;	A[a[0x56]]++;	A[a[0x57]]++;
		A[a[0x58]]++;	A[a[0x59]]++;	A[a[0x5a]]++;	A[a[0x5b]]++;
		A[a[0x5c]]++;	A[a[0x5d]]++;	A[a[0x5e]]++;	A[a[0x5f]]++;

		A[a[0x60]]++;	A[a[0x61]]++;	A[a[0x62]]++;	A[a[0x63]]++;
		A[a[0x64]]++;	A[a[0x65]]++;	A[a[0x66]]++;	A[a[0x67]]++;
		A[a[0x68]]++;	A[a[0x69]]++;	A[a[0x6a]]++;	A[a[0x6b]]++;
		A[a[0x6c]]++;	A[a[0x6d]]++;	A[a[0x6e]]++;	A[a[0x6f]]++;

		A[a[0x70]]++;	A[a[0x71]]++;	A[a[0x72]]++;	A[a[0x73]]++;
		A[a[0x74]]++;	A[a[0x75]]++;	A[a[0x76]]++;	A[a[0x77]]++;
		A[a[0x78]]++;	A[a[0x79]]++;	A[a[0x7a]]++;	A[a[0x7b]]++;
		A[a[0x7c]]++;	A[a[0x7d]]++;	A[a[0x7e]]++;	A[a[0x7f]]++;
		if	nay	(0x100>b)
		return;
		a+=		0x80;
		b-=		0x80;
	}
}

typedef	struct
{	uint8_t		*m;
	size_t		s;
}	MFILE;

__attribute__((noinline))
static	CALIGN void	zone_count	(ZONE * const z,MFILE *f)
{	CALIGN
	uint32_t	C[0x100];

	bc				(C,f->m,f->s);

	z->data=	pps		(z->data_size=PAGE+f->s+C['\t']*0x30);

	z->part=	pps		(z->part_size=PAGE+
					(C['\n']+C[','])*	sizeof(PART));

	z->meta=	pps		(z->meta_size=PAGE+
					(C['\t'])*		sizeof(VLESS));

	z->jump=	pps		(z->jump_size=PAGE+
					(C['\'']+C['"'])*sizeof(PART_REFER)/4);
}

static	inline	void	mfile_init	(MFILE * const f,uint8_t const * const n)
{	int	a=
	open	(n,O_RDONLY);
	f->s=
	lseek	(a,0,SEEK_END);

	f->m=
	mmap	(NULL,f->s+0x40,PROT_READ,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
	mmap	(f->m,f->s     ,PROT_READ,MAP_PRIVATE|MAP_POPULATE|MAP_FIXED,a,0);
	close	(a);
}

static	CALIGN	void	zone_part	(ZONE *z)
{	PART		*L=		z->part;
	do
	{	L[0x0].zone=		z;
		L[0x1].zone=		z;
		L[0x2].zone=		z;
		L[0x3].zone=		z;
		L[0x4].zone=		z;
		L[0x5].zone=		z;
		L[0x6].zone=		z;
		L[0x7].zone=		z;
		L[0x8].zone=		z;
		L[0x9].zone=		z;
		L[0xa].zone=		z;
		L[0xb].zone=		z;
		L[0xc].zone=		z;
		L[0xd].zone=		z;
		L[0xe].zone=		z;
		L[0xf].zone=		z;
		L+=			0x10;
	}	while			(L->name[1]);
}

__attribute__((hot))
__attribute__((noinline))
__attribute__((unused))
static	CALIGN	void	zone_init_ni	(ZONE * const z,uint8_t const * const n)
{	z->name=			n;

	MFILE		f;
	mfile_init			(&f,n);

	if			yay	(0x8c>=f.s)
	zone_minimal			(z);
	else
	zone_count			(z,&f);

#ifdef		ZONE_MAP_SIZE
	warnx	("z->data	%p	%x",z->data,z->data_size);
	warnx	("z->part	%p	%x",z->part,z->part_size);
	warnx	("z->meta	%p	%x",z->meta,z->meta_size);
	warnx	("z->jump	%p	%x",z->jump,z->jump_size);
#endif

	parse				(f.m,z);
/*	parse				(f.m,f.s,z);	*/
	zone_part			(z);
	munmap				(f.m,f.s+0x40);
}

/*
For parse.h
the C compiler emitted opcodes are
100% less efficient
than hand coded asm.
*/
