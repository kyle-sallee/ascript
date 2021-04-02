/*	By Kyle Sallee from 2015 ... 2020 copyrighted.
	Used by ascript.c
	by script.c some functions are provided.
*/

/*
#define		PROGRAM		1
*/

/*
#include	"ascript.h"
*/
#include	"argot.h"
#include	"value.h"

__attribute__((cold))
__attribute__((noinline))
noreturn
static		void	miss		(void)
{	ZYGOTE	*Z=
	script_zygote	();
	errx		(errna=ENOENT,"%s%s%s%i%s%s%s"
			,"In script file ",Z->file_name
			," on line ",script_line_number()
			," for argot ",Gz.heap.name[Gz.at-Gz.heap.func]
			," the load failed.");
}

__attribute__((hot))
__attribute__((noinline))
__attribute__((regparm(1)))
SCV	adef1			(ARGOT **AA)
{	int		b=	errna;
	int		a=
	aload			(Gz.heap.name[Gz.at-Gz.heap.func]);

	if		yay	(a==0)
	{	errna=		b;
		AA[0]->at	();
	}
	else
	miss			();
}

/*
The gcc the compiler's indexing method
when allowed
more opcodes than required
are emitted.
*/

__attribute__((always_inline))
static	inline	uint8_t	*name	(void)
{	uintptr_t	a=	(void *)	Gz.at -
				(void *)	Gz.heap.func;
	a*=
	sizeof			(Gz.heap.name[0])/
	sizeof			(void *);

	return			(void *)	Gz.heap.name+a;
}

#if	__SIZEOF_POINTER__	==	4
__attribute__((hot))
SCV	adef0_aide			(void)
{
/*	uint8_t		*n=		Gz.heap.name[Gz.at-Gz.heap.func];*/
	uint8_t		*n=	name	();

	ARGOT		**AA=
	aam_get				(n);

	ARGOT		*A=		*AA;

	if			yay	(A!=NULL)
	{	vector8x16	a,b;
		b=			*(vector8x16 *)	n;

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
__attribute__((hot))
SCV	adef0_aide			(void)
{	uint8_t		*n=	name	();

/*	uint64_t	a[2],*b;
	a[0]=				*(uint64_t *)	 n;
	a[1]=				*(uint64_t *)	(n+8);
*/

	uint64_t	a[1],*b;
	a[0]=				*(uint64_t *)	 n;

	ARGOT		**AA=
	aam_get				(n);

	ARGOT		*A=		*AA;

	if			yay	(A!=NULL)
	do
	{	b=			(uint64_t *)	A->name;
/*
The low 8 bytes
when the same
the high 8 bytes
can not probably not differ.
For most argot names 8 bytes or less suffices.
For opcode xor xor or 2 opcode mov are required.
For x86_64 64-bit register comparison is possible.
*/
		if		yay	(a[0]==b[0])
/*		if		yay	(a[1]==b[1])	*/
		{	A->at		();
			return;
		}
		A=			A->fore;
	}	while			(A!=NULL);

	adef1				(AA);
}
#endif

static	inline	void	vamset	(VLESS *A)
{	A->vam=	&Gz.hash.var[bit128_to_bit16(A->textaddr)];
}

static	inline	ARGOT	**vam_set	(uint8_t i)
{	VLESS		*a=	arga	(Gz.at),
			*e=	arga	(Gz.at+1);
	do
	{	if		yay	(a->vam==NULL)
		vamset			(a);
/* for backtick enclosed text the vam is already set */
	}	while			(e>++a);
}

__attribute__((always_inline))
static	inline	uint8_t	labellen	(uint8_t *a,uint8_t const b)
{	if	nay	(a[0x0]==b)	return	0x0;
	if	nay	(a[0x1]==b)	return	0x1;
	if	nay	(a[0x2]==b)	return	0x2;
	if	nay	(a[0x3]==b)	return	0x3;
	if	nay	(a[0x4]==b)	return	0x4;
	if	nay	(a[0x5]==b)	return	0x5;
	if	nay	(a[0x6]==b)	return	0x6;
	if	nay	(a[0x7]==b)	return	0x7;
	if	nay	(a[0x8]==b)	return	0x8;
	if	nay	(a[0x9]==b)	return	0x9;
	if	nay	(a[0xa]==b)	return	0xa;
	if	nay	(a[0xb]==b)	return	0xb;
	if	nay	(a[0xc]==b)	return	0xc;
	if	nay	(a[0xd]==b)	return	0xd;
	if	nay	(a[0xe]==b)	return	0xe;
	if	nay	(a[0xf]==b)	return	0xf;
					return	0x10;
}

static	inline	void	nearset	(PART_REFER *R)
{	uint16_t	b=
	bit128_to_bit16		(R->name)+Gz.next.far;
	PART_REFER	**LR=	&Gz.hash.near[b];
	R->fore=		*LR;
	*LR=			R;
}

static	inline	void	label1	(uint8_t **text)
{	PART_REFER	*J=	Gz.next.pr++;
	__builtin_memcpy	(J->name,*text+1,LABEL_SIZE);
	uint8_t		a=
	labellen		(J->name,'\'');
	__builtin_memset	(J->name+a,0  ,LABEL_SIZE);
	*text+=			a+2;
	J->part=		Gz.next.part+1;
	nearset			(J);
}

static	inline	void	farset	(PART_REFER *R)
{	uint16_t	a=
	bit128_to_bit16		(R->name);
	PART_REFER	**LR=	&Gz.hash.far[a];
	R->fore=		*LR;
	*LR=			R;
}

static	inline	void	label2	(uint8_t **text)
{	Gz.next.far++;
	PART_REFER	*J=	Gz.next.pr++;
	__builtin_memcpy	(J->name,*text+1,LABEL_SIZE);
	uint8_t		a=
	labellen		(J->name,'"');
	__builtin_memset	(J->name+a,0  ,LABEL_SIZE);
	*text+=			a+2;
	J->part=		Gz.next.part+1;
	farset			(J);
}

static	inline	uint8_t	selfy	(VLESS *A)
{	A->vam=	(VMETA **)	A;
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

static	inline	void	*roundx10	(void const * const a)
{	uintptr_t	b=		(uintptr_t)	a;
	b+=				0x10;
	b&=				(uintptr_t)	~0xf;
	return				(void *)	b;
}

static	inline	void	tick3	(VLESS *A,uint8_t **text)
{	uint8_t		*a=
	A->textaddr=		Gz.next.data;
	uint8_t		*b=	*text+1;
	tick_parse		(&a,&b);
	A->textlen=		a-Gz.next.data;
	Gz.next.data=
	roundx10		(a);
	*text=			b;
}

static	inline	void	tick	(uint8_t **text)
{	VLESS		*A=	Gz.next.vless++;
	selfy			(A);
	A->op=			opconst;
/*	A->val=			&A->value;	*/
/*	A->io.flag=		textmapuse;	*/
	tick3			(A,text);
}

__attribute__((hot))
__attribute__((unused))
SCV	vdef0		(void)
{	vam_set		(Gz.at-Gz.heap.func);
	adef0_aide	();
}

static	inline	int	var_or_num	(VLESS         *       A)
/*					,uint8_t const * const b	*/
/*					,uint8_t               c)	*/
{	uint8_t	*b=	A->textaddr;
	uint8_t	c=	A->textlen;

	if	nay	(3>c)		return	0;
	if	yay	(b[c-2]!=' ')	return	0;
	if	yay	(value(A)==0)	return	1;
					return	0;
}

__attribute__((always_inline))
static	inline	int	bareend	(uint8_t a)
{	if		yay	(a> ',')	return	0;
	if			(a==',')	return	1;
	if			(a<='\n')	return	1;
						return	0;
}

__attribute__((always_inline))
static	inline	uint8_t	barelen		(uint8_t *a)
{	if	nay	(bareend(a[0x01]))	return	0x01;
	if	nay	(bareend(a[0x02]))	return	0x02;
	if	nay	(bareend(a[0x03]))	return	0x03;
	if	nay	(bareend(a[0x04]))	return	0x04;
	if	nay	(bareend(a[0x05]))	return	0x05;
	if	nay	(bareend(a[0x06]))	return	0x06;
	if	nay	(bareend(a[0x07]))	return	0x07;
	if	nay	(bareend(a[0x08]))	return	0x08;
	if	nay	(bareend(a[0x09]))	return	0x09;
	if	nay	(bareend(a[0x0a]))	return	0x0a;
	if	nay	(bareend(a[0x0b]))	return	0x0b;
	if	nay	(bareend(a[0x0c]))	return	0x0c;
	if	nay	(bareend(a[0x0d]))	return	0x0d;
	if	nay	(bareend(a[0x0e]))	return	0x0e;
	if	nay	(bareend(a[0x0f]))	return	0x0f;
	if	nay	(bareend(a[0x10]))	return	0x10;
	if	nay	(bareend(a[0x11]))	return	0x11;
	if	nay	(bareend(a[0x12]))	return	0x12;
	if	nay	(bareend(a[0x13]))	return	0x13;
	if	nay	(bareend(a[0x14]))	return	0x14;
	if	nay	(bareend(a[0x15]))	return	0x15;
	if	nay	(bareend(a[0x16]))	return	0x16;
	if	nay	(bareend(a[0x17]))	return	0x17;
	if	nay	(bareend(a[0x18]))	return	0x18;
	if	nay	(bareend(a[0x19]))	return	0x19;
	if	nay	(bareend(a[0x1a]))	return	0x1a;
	if	nay	(bareend(a[0x1b]))	return	0x1b;
	if	nay	(bareend(a[0x1c]))	return	0x1c;
	if	nay	(bareend(a[0x1d]))	return	0x1d;
	if	nay	(bareend(a[0x1e]))	return	0x1e;
	if	nay	(bareend(a[0x1f]))	return	0x1f;
	if	nay	(bareend(a[0x20]))	return	0x20;
	if	nay	(bareend(a[0x21]))	return	0x21;
	if	nay	(bareend(a[0x22]))	return	0x22;
	if	nay	(bareend(a[0x23]))	return	0x23;
	if	nay	(bareend(a[0x24]))	return	0x24;
	if	nay	(bareend(a[0x25]))	return	0x25;
	if	nay	(bareend(a[0x26]))	return	0x26;
	if	nay	(bareend(a[0x27]))	return	0x27;
	if	nay	(bareend(a[0x28]))	return	0x28;
	if	nay	(bareend(a[0x29]))	return	0x29;
	if	nay	(bareend(a[0x2a]))	return	0x2a;
	if	nay	(bareend(a[0x2b]))	return	0x2b;
	if	nay	(bareend(a[0x2c]))	return	0x2c;
	if	nay	(bareend(a[0x2d]))	return	0x2d;
	if	nay	(bareend(a[0x2e]))	return	0x2e;
	if	nay	(bareend(a[0x2f]))	return	0x2f;
	if	nay	(bareend(a[0x30]))	return	0x30;
	if	nay	(bareend(a[0x31]))	return	0x31;
	if	nay	(bareend(a[0x32]))	return	0x32;
	if	nay	(bareend(a[0x33]))	return	0x33;
	if	nay	(bareend(a[0x34]))	return	0x34;
	if	nay	(bareend(a[0x35]))	return	0x35;
	if	nay	(bareend(a[0x36]))	return	0x36;
	if	nay	(bareend(a[0x37]))	return	0x37;
	if	nay	(bareend(a[0x38]))	return	0x38;
	if	nay	(bareend(a[0x39]))	return	0x39;
	if	nay	(bareend(a[0x3a]))	return	0x3a;
	if	nay	(bareend(a[0x3b]))	return	0x3b;
	if	nay	(bareend(a[0x3c]))	return	0x3c;
	if	nay	(bareend(a[0x3d]))	return	0x3d;
	if	nay	(bareend(a[0x3e]))	return	0x3e;
	if	nay	(bareend(a[0x3f]))	return	0x3f;
	if	nay	(bareend(a[0x40]))	return	0x40;
	if	nay	(bareend(a[0x41]))	return	0x41;
	if	nay	(bareend(a[0x42]))	return	0x42;
	if	nay	(bareend(a[0x43]))	return	0x43;
	if	nay	(bareend(a[0x44]))	return	0x44;
						return	0x45;
}

static	inline	void	bare		(uint8_t **text)
{	VLESS		*A=		Gz.next.vless++;
/*	A->val=				&A->value;	*/
/*	A->io.flag=			textmapuse;	*/

/*	A->textaddr=			*text-1;	*/
	A->textaddr=			*text;

	*text+=
	A->textlen=
	barelen				(A->textaddr);

	if			yay	(var_or_num(A)==0)
	{	A->op=			opref;
		uint8_t	*a=		A->textaddr;
		uint8_t	b=		A->textlen;
		uint8_t	*c=
		A->textaddr=		Gz.next.data;
		Gz.next.data+=		(b+0xf)&~0xf;
		__builtin_memcpy	(c       ,a     ,0x10);
		__builtin_memcpy	(c  +0x10,a+0x10,0x10);
		__builtin_memset	(c+b     ,0     ,0x10);
		__builtin_memset	(c+b+0x10,0     ,0x10);
		vamset			(A);
	}
	else
	{	A->op=			opvalue;
		selfy			(A);
	}
}

static	inline	void	quote1	(uint8_t **text)
{	VLESS		*A=	Gz.next.vless++;
	selfy			(A);

	A->op=			opnear;
/*	A->io.flag=		textmapuse;	*/
/*	A->val=			&A->value;
	A->value.b=		'\'';		*/
	uint8_t		*b=
	A->textaddr=		Gz.next.data;
	Gz.next.data+=		0x20;
	__builtin_memcpy	(b,*text+1,LABEL_SIZE);
	uint8_t		a=
	labellen		(b,'\'');
	__builtin_memset	(b+a,0  ,LABEL_SIZE);
	A->textlen=		a;
	*text+=			a+2;
}

static	inline	void	quote2	(uint8_t **text)
{	VLESS		*A=	Gz.next.vless++;
	selfy			(A);
	A->op=			opfar;
/*	A->io.flag=		textmapuse;	*/
/*	A->val=			&A->value;
	A->value.b=		'"';		*/
	uint8_t		*b=
	A->textaddr=		Gz.next.data;
	Gz.next.data+=		0x20;
	__builtin_memcpy	(b,*text+1,LABEL_SIZE);
	uint8_t		a=
	labellen		(b,'"');
	__builtin_memset	(b+a,0  ,LABEL_SIZE);
	A->textlen=		a;
	*text+=			a+2;
}

static	inline	void	para		(uint8_t **text)
{	while				(1)
	{	again:;
		uint8_t	d=		**text;
		if		yay	(d >'`')	{use:	bare	(text);}
		else	if	nay	(d=='`')	tick	(text);
		else	if	nay	(d=='\\')	(*text)+=2;
		else	if	nay	(d> ',')	goto	use;
		else	if	nay	(d==',')	goto	done;
		else	if	nay	(d=='\n')	goto	done;
		else	if	nay	(d=='\t')	goto	next;
		else	if	nay	(d=='\'')	quote1	(text);
		else	if	nay	(d=='"')	quote2	(text);
		else	if	nay	(d==' ')	goto	next;
		else					goto	use;
	}
	next:	(*text)++;				goto	again;
	done:	(*text)++;
}

static	inline	void	argot	(uint8_t **text)
{	Gz.next.part++;
	uint32_t	i=	(Gz.next.part-Gz.heap.func);
	Gz.heap.arga[i]=	Gz.next.vless;
/*	Gz.heap.func[i]=	adef0_aide;	*/
	Gz.heap.from[i]=	*text;
	Gz.heap.far[i]=		Gz.next.far;
	uint8_t		a,*b=	Gz.heap.name[i];
	for			(*b++=**text,(*text)++;1;(*text)++)
	if		yay	((a=**text)>',')keep:	*b++=	a;
	else	if	nay	(a==',')	goto	done;
	else	if	nay	(a==' ')	continue;
	else	if	nay	(a=='\t')	goto	topara;
	else	if	nay	(a=='\n')	goto	done;
	else					goto	keep;
	topara:	para		(text);		return;
	done:	(*text)++;
}

static	inline	void	lead		(uint8_t **text)
{	while				(1)
	{	again:;
		uint8_t	d=		**text;
/*		(*text)++;		*/
		if		yay	(d>'\\')
		use:
		argot			(text);
		else	if	nay	(d=='\\')		(*text)+=2;
		else	if	yay	(d>',')			goto	use;
		else	if	nay	(d=='\'')		label1	(text);
		else	if	nay	(d=='"')		label2	(text);
		else	if	nay	(d=='\t')		goto	next;
		else	if	nay	(d==' ')		goto	next;
		else	if	nay	(d=='\n')		goto	next;
		else	if	nay	(d==',')		goto	next;
		else	if	yay	(d=='#')
		for			(;**text!='\n';(*text)++);
		else	if	nay	(d==0)			return;
		else						goto	use;
	}

	next:	(*text)++;					goto	again;
}

/*
__attribute__((cold))
static		void	_ret	(void)	{ Gz.at--;}
*/

static	inline	void	zone_done	(void)
{	Gz.next.far++;
	Gz.next.part++;
	uint32_t	i=	(Gz.next.part-Gz.heap.func);
/*	Gz.heap.func[i]=
	Gz.heap.func[i+1]=	_ret;
*/
	Gz.heap.arga[i]=	Gz.next.vless;
	__builtin_memcpy	(Gz.heap.name[i  ],"FINI",4);
	__builtin_memcpy	(Gz.heap.name[i+1],"FINI",4);
	Gz.next.part+=		2;
}

/*
sans memory barrier
by gcc the desired opcode sequence is not be emitted
*/

static	inline	void	addr_fill		(void (**       A)(void)
						,void (** const B)(void)
						,void (*  const C)(void))
{	while					(1)
	{	A[0x00]=A[0x01]=A[0x02]=A[0x03]=
		A[0x04]=A[0x05]=A[0x06]=A[0x07]=
		A[0x08]=A[0x09]=A[0x0a]=A[0x0b]=
		A[0x0c]=A[0x0d]=A[0x0e]=A[0x0f]=C;
__asm__ __volatile__ ("":::"memory");
		A+=				0x10;
		if			nay	(A>(B+2))
		return;
	}
}

__attribute__((flatten))
__attribute__((noinline))
SCV	parse			(ZYGOTE * const z)
{	z[0].head=		Gz.next.part+1;
	uint8_t		*a=	z->file_head;
	lead			(&a);
	addr_fill		(z[0].head
				,Gz.next.part
				,Gz.aide.adef0);
	zone_done		();
	z[1].head=		Gz.next.part;
}

SCV	zygote_file_map		(ZYGOTE *z)
{	int	a=	open	(z->file_name,O_RDONLY);
	z->file_size=	lseek	(a,0,SEEK_END);

	z->file_head=	mmap	(NULL
				,z->file_size+0x40
				,PROT_READ,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
			mmap	(z->file_head
				,z->file_size
				,PROT_READ,MAP_PRIVATE|MAP_POPULATE|MAP_FIXED
				,a,0);
	close			(a);
}

__attribute__((hot))
__attribute__((noinline))
__attribute__((unused))
static	CALIGN	ZYGOTE	*zygote_init_aide	(uint8_t const * const n)
{	uint16_t	a=
	strlenb			(n);
	ZYGOTE		*z=	Gz.next.zygote++;
	z->file_name=		Gz.next.data;
	Gz.next.data=
	roundx10		(Gz.next.data+a);
	memcpyb			(z->file_name,n,a);
	z->file_name[a]=	0;
	zygote_file_map		(z);
	parse			(z);
	return			z;
}

/*
For parse.h
the C compiler emitted opcodes are
less efficient
than hand coded asm.
*/
