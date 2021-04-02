/*	By Kyle Sallee from 2015 ... 2019 copyrighted.
	Used by ascript.c
	by script.c some functions are provided.
*/

#define		PROGRAM		1
#include	"ascript.h"
#include	"argot.h"

/*
#define		ZONE_MAP_CHANGE
#define		ZONE_MAP_RESIZE
*/

static		void	adef0		(void);
static		void	vdef0		(void);

typedef	struct
{	uint8_t		*m;
	size_t		s;
}	MFILE;

static		void	equalequal	(void);
static		void	notequal	(void);
static		void	less		(void);
static		void	lessequal	(void);
static		void	more		(void);
static		void	moreequal	(void);
static		void	mapuse1		(VMETA *);

__attribute__((constructor(104)))
static	CALIGN	void	operator_init	(void)
{	varfixop[0].equalequal=
	varconstop[0].equalequal=	equalequal;

	varfixop[0].notequal=
	varconstop[0].notequal=		notequal;

	varfixop[0].less=
	varconstop[0].less=		less;

	varfixop[0].lessequal=
	varconstop[0].lessequal=	lessequal;

	varfixop[0].more=
	varconstop[0].more=		more;

	varfixop[0].moreequal=
	varconstop[0].moreequal=	moreequal;

	varfixop[0].mapuse[1]=
	varconstop[0].mapuse[1]=	mapuse1;
}

static		void	mfile_init	(MFILE * const,uint8_t * const);
static		size_t	parse		(uint8_t *,size_t const,ZONE * const);
static		void	bc	(uint32_t * const,uint8_t const *,size_t);

__attribute__((hot))
	CALIGN	void	zone_init	(ZONE * const z,uint8_t * const n)
{	z->name=			n;

	MFILE		f;
	mfile_init			(&f,n);

	CALIGN
	uint32_t	C[0x100];

	C['\t']=			0;
	C['\n']=			0;
	C['\'']=			0;
	C['"']=				0;
	C[',']=				0;
	bc				(C,f.m,f.s);

	z->data=	pool		(z->data_size=f.s+C['\t']*0x30);

	z->part=	pool		(z->part_size=
					(C['\n']+C[',']+1)*
					sizeof(PART));

	z->meta=	pool		(z->meta_size=
					(C['\t']+1)*
					sizeof(VLESS));

	z->jump=	pool		(z->jump_size=
					(C['\'']+C['"']+1)*
					sizeof(PART_REFER)/4);

#ifdef		ZONE_MAP_CHANGE
	warnx	("z->data	%p	%x",z->data,z->data_size);
	warnx	("z->part	%p	%x",z->part,z->part_size);
	warnx	("z->meta	%p	%x",z->meta,z->meta_size);
	warnx	("z->jump	%p	%x",z->jump,z->jump_size);
#endif

	parse				(f.m,f.s,z);
	munmap				(f.m,f.s);

#ifdef		ZONE_MAP_CHANGE
	warnx	("aft parse");
	warnx	("z->data	%p	%x",z->data,z->data_size);
	warnx	("z->part	%p	%x",z->part,z->part_size);
	warnx	("z->meta	%p	%x",z->meta,z->meta_size);
	warnx	("z->jump	%p	%x",z->jump,z->jump_size);
#endif

}

/*
Because c can be checked
by the compiler
function bc
is partially unwound.
*/

#ifndef	FASTER
static	inline	void	bc	(uint32_t * const A,uint8_t const *a,size_t b)
{	uint8_t	const	*c;
	for	(c=a+b;c>a;A[*a++]++);
}
#else
__attribute__((noinline))
__attribute__((unused))
static	CALIGN	void	bc	(uint32_t * const A,uint8_t const *a,size_t b)
{	/* per 128 byte values counted one cmp one jmp */
	while		(b>=0x80)
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

		a+=	0x80;
		b-=	0x80;
	}

	if		(b>=0x40)
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

		a+=	0x40;
		b-=	0x40;
	}

	if		(b>=0x20)
	{	A[a[0x00]]++;	A[a[0x01]]++;	A[a[0x02]]++;	A[a[0x03]]++;
		A[a[0x04]]++;	A[a[0x05]]++;	A[a[0x06]]++;	A[a[0x07]]++;
		A[a[0x08]]++;	A[a[0x09]]++;	A[a[0x0a]]++;	A[a[0x0b]]++;
		A[a[0x0c]]++;	A[a[0x0d]]++;	A[a[0x0e]]++;	A[a[0x0f]]++;

		A[a[0x10]]++;	A[a[0x11]]++;	A[a[0x12]]++;	A[a[0x13]]++;
		A[a[0x14]]++;	A[a[0x15]]++;	A[a[0x16]]++;	A[a[0x17]]++;
		A[a[0x18]]++;	A[a[0x19]]++;	A[a[0x1a]]++;	A[a[0x1b]]++;
		A[a[0x1c]]++;	A[a[0x1d]]++;	A[a[0x1e]]++;	A[a[0x1f]]++;

		a+=	0x20;
		b-=	0x20;
	}

	if		(b>=0x10)
	{	A[a[0x00]]++;	A[a[0x01]]++;	A[a[0x02]]++;	A[a[0x03]]++;
		A[a[0x04]]++;	A[a[0x05]]++;	A[a[0x06]]++;	A[a[0x07]]++;
		A[a[0x08]]++;	A[a[0x09]]++;	A[a[0x0a]]++;	A[a[0x0b]]++;
		A[a[0x0c]]++;	A[a[0x0d]]++;	A[a[0x0e]]++;	A[a[0x0f]]++;
		a+=	0x10;
		b-=	0x10;
	}

	if		(b>=8)
	{	A[a[0x00]]++;	A[a[0x01]]++;	A[a[0x02]]++;	A[a[0x03]]++;
		A[a[0x04]]++;	A[a[0x05]]++;	A[a[0x06]]++;	A[a[0x07]]++;
		a+=	8;
		b-=	8;
	}

	if		(b>=4)
	{	A[a[0x00]]++;	A[a[0x01]]++;	A[a[0x02]]++;	A[a[0x03]]++;
		a+=	4;
		b-=	4;
	}

	if		(b>=2)
	{	A[a[0x00]]++;	A[a[0x01]]++;
		a+=	2;
		b-=	2;
	}

	if		(b!=0)
	A[a[0x00]]++;
}
#endif

static	inline	void	mfile_init	(MFILE * const f,uint8_t * const n)
{	int		a=
	open		(n,O_RDONLY);
	f->s=
	lseek		(a,0,SEEK_END);

	f->m=
	mmap		(NULL,f->s,PROT_READ,MAP_PRIVATE|MAP_POPULATE,a,0);
	close		(a);
}

static		void	_ret		(void);
static		void	farset		(PART_REFER *,uint32_t *);
static		void	nearset		(PART_REFER *,uint32_t const);
static		void	*roundx40	(void const * const);

typedef	struct
{	uint8_t		*a;	/* text */
	uint8_t	const	*lim;	/* this much text exists */
/*	VLESS		**AV;*/	/* available argot line parameter pointers */
	PART		*L;	/* available line data */
	VLESS		*P;	/* available argot parameter data */
	ZONE	* const	z;	/* the zone pointer */
	PART_REFER	*J;	/* jump target references */
	uint32_t	far;	/* far group integer */
	uint16_t	n;	/* the line number */
	int8_t		p;	/* the line part */
	uint8_t		*D;	/* limtless data */
}	PARSE_DATA;

/*
on x86_64
in memory
a PARSE_DATA structure
will probably not exist.
By the strcture
the data is merely collated.
However, among inine functions
as a function parameter
the PARSE_DATA structure
when passed
all the variables
remain accessible.
Thus per inline function
complicated parameter lists
are not required.
In fact since inline functions
are not actually called
the function parameters
do  not actually exist.
*/

static	inline	void	lead		(PARSE_DATA *);
static	inline	void	zone_resize	(PARSE_DATA *);
static	inline	void	zone_done	(PARSE_DATA *);

__attribute__((noinline))
static	CALIGN	size_t	parse	(uint8_t *A,size_t const t,ZONE * const z)
{	CALIGN
	PARSE_DATA	S=
	{	.z=			z,
		.n=			1,
		.p=			1,
		.D=			z->data,
		.J=			z->jump-1,
		.far=			Gz.far_total,
		.lim=			A+t,
		.P=			z->meta,
		.L=			z->part-1,
		.a=			A,
	};

	lead				(&S);
	zone_done			(&S);
	zone_resize			(&S);
}

static	inline	int	argot		(PARSE_DATA *);
static	inline	void	label1		(PARSE_DATA *);
static	inline	void	label2		(PARSE_DATA *);

/*
Spaghetti code is delicious!
Compilers are stupid!
From argot
two code paths only
can become.
By the compiler
this possibility
should be realized.
But if not
a couple cmp je
will be emitted.
*/

static	inline	void	lead		(PARSE_DATA *S)
{	while				(1)
	{	uint8_t	d=		*(S->a++);
		if		yay	(d>',')
		use:
		switch			(argot(S))
		{	case	'\n':
			feed:
			S->n++;
			S->p=		0;
			if	nay	(S->a>=S->lim)		return;
			default:	/* case	',': */
			comma:
			S->p++;
		}
		else	if	nay	(d=='\n')		goto	feed;
		else	if	nay	(d==',')		goto	comma;
		else	if	nay	(d=='\'')		label1	(S);
		else	if	nay	(d=='"')		label2	(S);
		else	if	nay	(d=='\t')		continue;
		else	if	nay	(d==' ')		continue;
		else	if	yay	(d!='#')		goto	use;
		else
		{	while		(*(S->a++)!='\n');	goto	feed;
		}
	}
}

/*
The obvious choice,
one byte value per unrolled loop iteration mov,
why not implement?

Most labels will be 4 byte or more.
For opcode count the 4 byte label is being considered.

The obvious method
if used
4 cmp 4 je 1 jmp
8 byte sized mov execute.

Total 17 opcodes execute.
Why 8 mov?
On IA32
on AMD64
memory to memory mov
is NOT supported.
Through a CPU register
the value
must mov.
That excludes consideration for rep movsb type opcodes
which the compiler refuses to emite.

The cmp je bridge
if used
on a memory address
4 cmp,
4 je,
2 jmp
2 4-byte mov are executed

Total 12 opcodes execute.
However, for branch merge
one more pure jmp executes.
A 5 opcode execution savings seems reasonable,
but the compiler might not be able to accomplish.
But other tricks exist.
Thus per byte mov
is less efficient.

By asm hackers only
this lore is wielded.
By the compiler
a loop can be unwound,
but similar efficiency
would not be achieved.

It only looks like crap,
because the C language
is crap.

This seriously begs the question
why an updated gcc compiler
is unable to emit the rep movsb opcodes?
To a memcpy function
to any      function
by a single call
the parser efficiency
would tank!

An amount a source a destination and rep movsb would suffice.
Do not expect memcpy or memmove ever emit rep movsb,
because it does not, unless it's hidden by a function call,
which is not desired anyway.

The label1 contained memcpy with known byte quantities
simply mov the value through CPU registers.
At most 6 different sized mov opcodes
might execute.

For each branch the amount of mov through register
and mov ...,0
can be adjusted to make each faster.
memcpy with exact amounts would not yield the best opcodes,
only certain values are ideal.
Sometimes by two opcodes 16 bytes if moved
the overage
to value 0
if set
can be faster.
Moving a value requires two opcodes.
A memory value
to 0
to set
one opcode merely
is executed.
This choice might not be as fast
on ia32 as compared with x86_64,
but then again nothing about ascript performance
is as fast on 32-bit CPU architecture.
On AMD64
with some finesss
for 1  byte
to  16 byte copies
merely 4 opcodes
can suffice.

The minimum branch and resume is 6 opcodes.
The maximum branch and resume is 8 opcodes.

The emitted opcodes
if not known
by the hacker
the code
can not be properly optimized.
With asm
as compared
this is another reason why compiled C
can never be as fast.
In asm
if coded
label1 code
would be smaller and faster and
the rep movsb opcode
would be used.
*/

#ifndef	FASTER
static	inline	void	label1		(PARSE_DATA *S)
{	uint8_t		*a;
	for				(a=S->a+1;*a!='\'';a++);
	S->J++;
	__builtin_memcpy		(S->J->name,   S->a   ,LABEL_SIZE);
	__builtin_memset		(S->J->name+(a-S->a),0,LABEL_SIZE);
	S->a=				a+1;
	S->J->part=			S->L+1;
	nearset				(S->J,S->far);
}

static	inline	void	label2		(PARSE_DATA *S)
{	uint8_t		*a;
	for				(a=S->a+1;*a!='"';a++);
	S->J++;
	__builtin_memcpy		(S->J->name,   S->a   ,LABEL_SIZE);
	__builtin_memset		(S->J->name+(a-S->a),0,LABEL_SIZE);
	S->a=				a+1;
	S->J->part=			S->L+1;
	farset				(S->J,&S->far);
}

static	inline	int	para			(PARSE_DATA *);
static	inline	int	argot			(PARSE_DATA *S)
{	S->L++;
	S->L->arga=				S->P;
	S->L->func=				adef0;
	S->L->zone=				S->z;
	S->L->ln=				S->n;
	S->L->part=				S->p;
	S->L->far=				S->far;
	uint8_t		a,*b=			S->L->name;
	*b++=					S->a[-1];
	for					(;1;S->a++)
	switch					(a=*S->a)
	{	default:	*b++=		a;
		case	' ':	break;
		case	'\n':
		case	',':	S->a++;
				return		a;
		case	'\t':	return	para	(S);
	}
}

#else

static	inline	void	label1		(PARSE_DATA *S)
{	S->J++;
	S->J->part=			S->L+1;
	uint8_t		*a=		S->a;
	uint8_t		*b=		S->J->name;

	if			nay	(a[1]=='\'')	/* 2 opcodes */
	{	memcpy			(b,a,1);	/* 2 opcode */
		S->a+=			2;		/* 1 opcode */
	}						/* 1 opcode */
	else	if		nay	(a[2]=='\'')
	{	memcpy			(b,a,2);	/* 2 opcode */
		S->a+=			3;
	}
	else	if		nay	(a[3]=='\'')
	{	memcpy			(b,a,4);	/* 2 opcode */
		memset			(b+3,0,1);	/* 1 opcode */
		S->a+=			4;
	}
	else	if		nay	(a[4]=='\'')
	{	memcpy			(b,a,4);	/* 2 opcode */
		S->a+=			5;
	}
	else	if		nay	(a[5]=='\'')
	{	memcpy			(b,a,5);	/* 4 opcode */
		S->a+=			6;
	}
	else	if		nay	(a[6]=='\'')
	{	memcpy			(b,a,6);	/* 4 opcode */
		S->a+=			7;
	}
	else	if		nay	(a[7]=='\'')
	{	memcpy			(b,a,8);	/* 2 opcode */
		memset			(b+7,0,1);	/* 1 opcode */
		S->a+=			8;
	}
	else	if		nay	(a[8]=='\'')
	{	memcpy			(b,a,8);	/* 2 opcode */
		S->a+=			9;
	}
	else	if		nay	(a[9]=='\'')
	{	memcpy			(b,a,9);	/* 4 opcode */
		S->a+=			0xa;
	}
	else	if		nay	(a[0xa]=='\'')
	{	memcpy			(b,a,0xa);	/* 4 opcode */
		S->a+=			0xb;
	}
	else	if			(memcpy(b,a,0x10), /* 2 opcode */
				nay	(a[0xb]=='\''))
	{	memset			(b+0xb,0,5);	/* 2 opcode */
		S->a+=			0xc;
	}
	else	if		nay	(a[0xc]=='\'')
	{	memset			(b+0xc,0,4);	/* 1 opcode */
		S->a+=			0xd;
	}
	else	if		nay	(a[0xd]=='\'')
	{	memset			(b+0xd,0,3);	/* 2 opcode */
		S->a+=			0xe;
	}
	else	if		nay	(a[0xe]=='\'')
	{	memset			(b+0xe,0,2);	/* 1 opcode */
		S->a+=			0xf;
	}
	else	if		nay	(a[0xf]=='\'')
	{	memset			(b+0xf,0,1);	/* 1 opcode */
		S->a+=			0x10;
	}
	else
	{	S->a+=			0x11;
	}

	nearset				(S->J,S->far);
}

static	inline	void	label2		(PARSE_DATA *S)
{	S->J++;
	S->J->part=			S->L+1;
	uint8_t		*a=		S->a;
	uint8_t		*b=		S->J->name;

	if			nay	(a[1]=='"')
	{	memcpy			(b,a,1);
		S->a+=			2;
	}
	else	if		nay	(a[2]=='"')
	{	memcpy			(b,a,2);
		S->a+=			3;
	}
	else	if		nay	(a[3]=='"')
	{	memcpy			(b,a,4);
		memset			(b+3,0,1);
		S->a+=			4;
	}
	else	if		nay	(a[4]=='"')
	{	memcpy			(b,a,4);
		S->a+=			5;
	}
	else	if		nay	(a[5]=='"')
	{	memcpy			(b,a,5);
		S->a+=			6;
	}
	else	if		nay	(a[6]=='"')
	{	memcpy			(b,a,6);
		S->a+=			7;
	}
	else	if		nay	(a[7]=='"')
	{	memcpy			(b,a,8);
		memset			(b+7,0,1);
		S->a+=			8;
	}
	else	if		nay	(a[8]=='"')
	{	memcpy			(b,a,8);
		S->a+=			9;
	}
	else	if		nay	(a[9]=='"')
	{	memcpy			(b,a,9);
		S->a+=			0xa;
	}
	else	if		nay	(a[0xa]=='"')
	{	memcpy			(b,a,0xa);
		S->a+=			0xb;
	}
	else	if			(memcpy(b,a,0x10),
				nay	(a[0xb]=='"'))
	{	memset			(b+0xb,0,5);
		S->a+=			0xc;
	}
	else	if		nay	(a[0xc]=='"')
	{	memset			(b+0xc,0,4);
		S->a+=			0xd;
	}
	else	if		nay	(a[0xd]=='"')
	{	memset			(b+0xd,0,3);
		S->a+=			0xe;
	}
	else	if		nay	(a[0xe]=='"')
	{	memset			(b+0xe,0,2);
		S->a+=			0xf;
	}
	else	if		nay	(a[0xf]=='"')
	{	memset			(b+0xf,0,1);
		S->a+=			0x10;
	}
	else
	{	S->a+=			0x11;
	}

	farset				(S->J,&S->far);
}

static	inline	int	para			(PARSE_DATA *);
static	inline	int	argot			(PARSE_DATA *S)
{	S->L++;
	S->L->arga=				S->P;
	S->L->func=				adef0;
	S->L->zone=				S->z;
	S->L->ln=				S->n;
	S->L->part=				S->p;
	S->L->far=				S->far;
	S->a--;
	uint8_t		*b=			S->L->name;

	while					(1)
	{		if		nay	(S->a[1]<=',')
		{	memcpy			(b,S->a,1);
			b+=			1;
			S->a+=			1;
		}
		else	if		nay	(S->a[2]<=',')
		{	memcpy			(b,S->a,2);
			b+=			2;
			S->a+=			2;
		}
		else	if		nay	(S->a[3]<=',')
		{	memcpy			(b,S->a,4);
			memset			(b+3,0,1);
			b+=			3;
			S->a+=			3;
		}
		else	if		nay	(S->a[4]<=',')
		{	memcpy			(b,S->a,4);
			b+=			4;
			S->a+=			4;
		}
		else	if		nay	(S->a[5]<=',')
		{	memcpy			(b,S->a,5);
			b+=			5;
			S->a+=			5;
		}
		else	if		nay	(S->a[6]<=',')
		{	memcpy			(b,S->a,6);
			b+=			6;
			S->a+=			6;
		}
		else	if		nay	(S->a[7]<=',')
		{	memcpy			(b,S->a,8);
			memset			(b+7,0,1);
			b+=			7;
			S->a+=			7;
		}
		else	if		nay	(S->a[8]<=',')
		{	memcpy			(b,S->a,8);
			b+=			8;
			S->a+=			8;
		}
		else	if		nay	(S->a[9]<=',')
		{	memcpy			(b,S->a,9);
			b+=			9;
			S->a+=			9;
		}
		else	if		nay	(S->a[0xa]<=',')
		{	memcpy			(b,S->a,0xa);
			b+=			0xa;
			S->a+=			0xa;
		}
		else	if			(memcpy(b,S->a,0x10),
					nay	(S->a[0xb]<=','))
		{	memset			(b+0xb,0,5);
			b+=			0xb;
			S->a+=			0xb;
		}
		else	if		nay	(S->a[0xc]<=',')
		{	memset			(b+0xc,0,4);
			b+=			0xc;
			S->a+=			0xc;
		}
		else	if		nay	(S->a[0xd]<=',')
		{	memset			(b+0xd,0,3);
			b+=			0xd;
			S->a+=			0xd;
		}
		else	if		nay	(S->a[0xe]<=',')
		{	memset			(b+0xe,0,2);
			b+=			0xe;
			S->a+=			0xe;
		}
		else	if		nay	(S->a[0xf]<=',')
		{	memset			(b+0xf,0,1);
			b+=			0xf;
			S->a+=			0xf;
		}
		else
		{	b+=			0x10;
			S->a+=			0x10;
		}

		while				(1)
		{	uint8_t	d=		*S->a++;
				if	nay	(d=='\n')	return	'\n';
			else	if	nay	(d=='\t')	return	para(S);
			else	if	nay	(d==',')	return	',';
			else	if	yay	(d!=' ')	{S->a--;break;}
			else	if	yay	(S->a[0]>',')		break;
		}
	}
}

#endif

static	inline	int	bare		(PARSE_DATA *);
static	inline	void	tick1		(PARSE_DATA *, uint8_t *);
static	inline	void	quote1		(PARSE_DATA *);
static	inline	void	quote2		(PARSE_DATA *);
static	inline	uint8_t *vless		(PARSE_DATA *);

static	inline	int	para		(PARSE_DATA *S)
{	uint8_t		d,m;
	while				(1)
	{	m=			0;
		skip:
		d=			*(S->a++);
		if		yay	(d >'`')
		use:
		switch			(bare(S))
		{	case	'\n':			return	'\n';
			case	',':			return	',';
		}
		else	if	nay	(d=='`')
		{	tick1		(S,&m);		goto	skip;
		}
		else	if	nay	(d=='\\')
		{	if	yay	(*(S->a++)=='\n')
			{	S->n++;
				S->p=	1;
			}
			goto		skip;
		}
		else	if	nay	(d> ',')	goto	use;
		else	if	nay	(d==',')	return	',';
		else	if	nay	(d=='\n')	return	'\n';
		else	if	nay	(d=='\t');
		else	if	nay	(d=='\'')	quote1	(S);
		else	if	nay	(d=='"')	quote2	(S);
		else	if	nay	(d==' ')	goto	skip;
		else					goto	use;
	}
}

static	inline	uint8_t	selfy			(PARSE_DATA *S)
{	S->P->free=				(void *)	S->P;
	S->P->vam=				(VMETA **)	&S->P->free;
}

static	inline	uint8_t	*vless			(PARSE_DATA *S)
{
#ifdef	SHARED_VAR
	S->P->map=				S->P->maps;
#endif
/*
	S->P->free=				(void *)	S->P;
	S->P->vam=				(VMETA **)	&S->P->free;
*/

	S->P->map[1].size=
	sizeof					(S->P->value);
	S->P->map[1].addr=			(void *)	&S->P->value;
	S->P->map[0].use=			1;
	return
	S->P->map[0].addr=			S->D;
}

static	inline	void	var_or_num	(PARSE_DATA *,uint8_t const * const);
static	inline	void	unicode		(PARSE_DATA *,uint8_t **);

#ifndef	FASTER
static	inline	int	bare			(PARSE_DATA *S)
{	uint8_t		a,*b=
	vless					(S);
	for					(S->a--;1;S->a++)
	switch					(a=*S->a)
	{	default:	*b++=		a;
				break;
		case	'\t':
		case	'\n':
		case	',':	var_or_num	(S,b);
				S->a++;
				return		a;
	}
}

static	inline	void	tick_escape	(PARSE_DATA *S,uint8_t **);
static	inline	void	tick1		(PARSE_DATA *S,uint8_t *m)
{	uint8_t		a,*b;
	if			yay	(*m==0)
	{	selfy			(S);
		b=
		vless			(S);
		*m=			1;
	}
	else
	{	S->P--;
		b=			S->P->map[0].addr+
					S->P->map[0].len;
	}
	S->P->op=			varconstop;

	while				(1)
	switch				(a=*S->a++)
	{	default:	*b++=	a;		break;
		case	'\\':	tick_escape	(S,&b);	break;
		case	'\n':	S->n++;			break;
		case	'`':	goto	done;
	}

	done:
	S->P->map[0].len=		b-S->P->map[0].addr;
/*
warnx	("S->P->map[0].addr=");
write	(2,S->P->map[0].addr,S->P->map[0].len);
write	(2,"\n",1);
*/
	S->P++;
	S->D=
	roundx40			(b);
}

static	inline	void	tick_escape_case	(PARSE_DATA *S, uint8_t **b)
{	uint8_t		a;
	switch					(a=*S->a++)
	{	case	'n':	*(*b)++=	'\n';	break;
		case	'0':	*(*b)++=	0;	break;
		case	't':	*(*b)++=	'\t';	break;
		case	'U':	unicode		(S,b);	break;
		case	'e':	*(*b)++=	'\e';	break;
		default:	*(*b)++=	'\\';
		case	'`':
		case	'\\':
				*(*b)++=	a;
	}
}

static	inline	void	tick_escape	(PARSE_DATA *S, uint8_t **b)
{	uint8_t		a=	*(S->a++);
	if		nay	(a=='n')	*(*b)++=	'\n';
	else	if	nay	(a=='0')	*(*b)++=	0;
	else	if	nay	(a=='t')	*(*b)++=	'\t';
	else	if	nay	(a=='U')	unicode		(S,b);
	else	if	nay	(a=='e')	*(*b)++=	'\e';
	else	if	nay	(a=='`')	goto		use;
	else	if	nay	(a=='\\')	goto		use;
	else	{				*(*b)++=	'\\';
	use:					*(*b)++=	a;
		}
}

#else

static	inline	int	bare		(PARSE_DATA *S)
{	uint8_t		*b=
	vless				(S);
	S->a--;
	goto				skip;

	while				(1)
	{	if		nay	(S->a[0]<=',');
		else
		skip:
		if		nay	(S->a[1]<=',')
		{	memcpy		(b,S->a,1);
			b+=		1;
			S->a+=		1;
		}
		else	if	nay	(S->a[2]<=',')
		{	memcpy		(b,S->a,2);
			b+=		2;
			S->a+=		2;
		}
		else	if	nay	(S->a[3]<=',')
		{	memcpy		(b,S->a,4);
			memset		(b+3,0,1);
			b+=		3;
			S->a+=		3;
		}
		else	if	nay	(S->a[4]<=',')
		{	memcpy		(b,S->a,4);
			b+=		4;
			S->a+=		4;
		}
		else	if	nay	(S->a[5]<=',')
		{	memcpy		(b,S->a,5);
			b+=		5;
			S->a+=		5;
		}
		else	if	nay	(S->a[6]<=',')
		{	memcpy		(b,S->a,6);
			b+=		6;
			S->a+=		6;
		}
		else	if	nay	(S->a[7]<=',')
		{	memcpy		(b,S->a,8);
			memset		(b+7,0,1);
			b+=		7;
			S->a+=		7;
		}
		else	if	nay	(S->a[8]<=',')
		{	memcpy		(b,S->a,8);
			b+=		8;
			S->a+=		8;
		}
		else	if	nay	(S->a[9]<=',')
		{	memcpy		(b,S->a,9);
			b+=		9;
			S->a+=		9;
		}
		else	if	nay	(S->a[0xa]<=',')
		{	memcpy		(b,S->a,0xa);
			b+=		0xa;
			S->a+=		0xa;
		}
		else	if		(memcpy(b,S->a,0x10),
				nay	(S->a[0xb]<=','))
		{	memset		(b+0xb,0,5);
			b+=		0xb;
			S->a+=		0xb;
		}
		else	if	nay	(S->a[0xc]<=',')
		{	memset		(b+0xc,0,4);
			b+=		0xc;
			S->a+=		0xc;
		}
		else	if	nay	(S->a[0xd]<=',')
		{	memset		(b+0xd,0,3);
			b+=		0xd;
			S->a+=		0xd;
		}
		else	if	nay	(S->a[0xe]<=',')
		{	memset		(b+0xe,0,2);
			b+=		0xe;
			S->a+=		0xe;
		}
		else	if	nay	(S->a[0xf]<=',')
		{	memset		(b+0xf,0,1);
			b+=		0xf;
			S->a+=		0xf;
		}
		else
		{	b+=		0x10;
			S->a+=		0x10;
			continue;
		}

		uint8_t		d;
		switch			(d=(*S->a++))
		{	case	'\t':	var_or_num	(S,b);	return	'\t';
			case	'\n':	var_or_num	(S,b);	return	'\n';
			case	',':	var_or_num	(S,b);	return	',';
			default:	S->a--;			goto	skip;
		}
	}
}

static	inline	uint8_t	*tick2		(PARSE_DATA *, uint8_t *);
static	inline	void	tick1		(PARSE_DATA *S,uint8_t *m)
{	uint8_t		*b;
	if			yay	(*m==0)
	{	selfy			(S);
		b=
		vless			(S);
		*m=			1;
	}
	else
	{	S->P--;
		b=			S->P->map[0].addr+
					S->P->map[0].len;
	}

	uint8_t		e[0x100];
	e['\n']=			0;
	e['\\']=			0;
	uint8_t		*c=		b;
	uint8_t		*a=		S->a;

	S->P->op=			varconstop;
	uint8_t		d;

	while				((d=*(S->a++))!='`')
	{	e[d]=			1;
		*b++=			d;
	}

	if			nay	((e['\n']|e['\\'])!=0)
	{	S->a=			a;
		b=
		tick2			(S,c);
	}

	S->P->map[0].len=		b-S->P->map[0].addr;
	S->P++;
	S->D=
	roundx40			(b);
}

static	inline	uint8_t	*tick2_escape		(PARSE_DATA *S, uint8_t *);

static	inline	uint8_t	*tick2			(PARSE_DATA *S, uint8_t *b)
{	uint8_t		d;
	while					(1)
	{	d=				*(S->a++);
		if			yay	(d>'`')
		use:
		*b++=				d;
		else	if		nay	(d=='`')
		{	*b=			0;
			return			b;
		}
		else	if		nay	(d=='\\')
		b=	tick2_escape		(S,b);
		else	if		yay	(d!='\n')
		goto				use;
		else	S->n++;
	}
}

static	inline	uint8_t	*tick2_escape	(PARSE_DATA *S, uint8_t *b)
{	uint8_t		d=	*(S->a++);
	if		nay	(d=='n')		*b++=	'\n';
	else	if	nay	(d=='0')		*b++=	0;
	else	if	nay	(d=='t')		*b++=	'\t';
	else	if	nay	(d=='U')		unicode	(S,&b);
	else	if	nay	(d=='e')		*b++=	'\e';
	else	if	nay	(d=='`')	use:	*b++=	d;
	else	if	nay	(d=='\\')	goto	use;
	else	{					*b++=	'\\';
							goto	use;
		}
	return			b;
}

#endif

static	inline	void	var_or_num	(PARSE_DATA *S,uint8_t const * const b)
{	if				(S->P->map[0].addr[0]>'9')
	{	S->P->op=		varrefop;
		S->L->func=		vdef0;
	}
	else
	{	S->P->op=		varfixop;
		selfy			(S);
	}
	S->P->map[0].len=		b-S->P->map[0].addr;
	S->P++;
	S->D=
	roundx40			(b);
}

/*
By   the    goto
a    jmp    opcode
is   not    emitted.
for  '`'
the  branch code
is   moved.
A    switch/case space similar savings
with if/else if
explicit         order checking
is   achieved.

By   block head bigots
the  goto  use
when forbidden
the  use
the  effect
is   not   learned
is   not   comprehended.

For  explicitly improbable branch
by   conditional jmp, such as je,
the  code is almost always reached.
Thus the code placement address
is   nearly arbitrary.
*/

/*
The RAM
while not considered fast
by indexed RAM addressing
for value acquisition
the branch predictor
is not required and
the opcode pipeline
is not reloaded.
For table use
less opcodes
are     required
comparison opcodes
are not required
conditional jumps
are not required.
*/

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

/*
I know, but...
rather than
the opcode add
with
the opcode mov
the table value
is being acquired.
Thus
rather than the accumulated value
the table value
is more easily bit shifted
or rather
less opcodes
are required.
It's counter intuitive,
because compilers are inane.
*/

/*
From mul
to shl
the compiler translates.
*/

static	inline	void	unicode	(PARSE_DATA *S, uint8_t **b)
{	uint32_t	a;

	a=		xX[S->a[1]]*0x100000;
	a+=		xX[S->a[2]]*0x10000;
	a+=		xX[S->a[3]]*0x1000;
	a+=		xX[S->a[4]]*0x100;
	a+=		xX[S->a[5]]*0x10;
	a+=		xX[S->a[6]];
	S->a+=		7;
	utf8_out	(b,a);
}

#ifndef	FASTER
static	inline	void	quote1		(PARSE_DATA *S)
{	uint8_t		*a;
	for				(a=S->a+1;*a!='\'';a++);

	selfy				(S);
	uint8_t		*b=
	vless				(S);
	S->D+=				0x10;
	S->P->op=			varconstop;
	S->P->value.b=			'\'';
	S->P++;
	__builtin_memcpy		(b,   S->a   ,LABEL_SIZE);
	__builtin_memset		(b+(a-S->a),0,LABEL_SIZE);
	S->a=				a+1;
}

static	inline	void	quote2		(PARSE_DATA *S)
{	uint8_t		*a;
	for				(a=S->a+1;*a!='"';a++);

	selfy				(S);
	uint8_t		*b=
	vless				(S);
	S->D+=				0x10;
	S->P->op=			varconstop;
	S->P->value.b=			'"';
	S->P++;
	__builtin_memcpy		(b,   S->a   ,LABEL_SIZE);
	__builtin_memset		(b+(a-S->a),0,LABEL_SIZE);
	S->a=				a+1;
}

#else
static	inline	void	quote1		(PARSE_DATA *S)
{	selfy				(S);
	uint8_t		*b=
	vless				(S);
	S->D+=				0x10;
	S->P->op=			varconstop;
	S->P->value.b=			'\'';
	S->P++;
	uint8_t		*a=		S->a;

	if			nay	(a[0]=='\'')
	{	S->a+=			1;
	}
	else	if		nay	(a[1]=='\'')
	{	memcpy			(b,a,1);
		S->a+=			2;
	}
	else	if		nay	(a[2]=='\'')
	{	memcpy			(b,a,2);
		S->a+=			3;
	}
	else	if		nay	(a[3]=='\'')
	{	memcpy			(b,a,4);
		memset			(b+3,0,1);
		S->a+=			4;
	}
	else	if		nay	(a[4]=='\'')
	{	memcpy			(b,a,4);
		S->a+=			5;
	}
	else	if		nay	(a[5]=='\'')
	{	memcpy			(b,a,5);
		S->a+=			6;
	}
	else	if		nay	(a[6]=='\'')
	{	memcpy			(b,a,6);
		S->a+=			7;
	}
	else	if		nay	(a[7]=='\'')
	{	memcpy			(b,a,8);
		memset			(b+7,0,1);
		S->a+=			8;
	}
	else	if		nay	(a[8]=='\'')
	{	memcpy			(b,a,8);
		S->a+=			9;
	}
	else	if		nay	(a[9]=='\'')
	{	memcpy			(b,a,9);
		S->a+=			0xa;
	}
	else	if		nay	(a[0xa]=='\'')
	{	memcpy			(b,a,0xa);
		S->a+=			0xb;
	}
	else	if			(memcpy(b,a,0x10),
				nay	(a[0xb]=='\''))
	{	memset			(b+0xb,0,5);
		S->a+=			0xc;
	}
	else	if		nay	(a[0xc]=='\'')
	{	memset			(b+0xc,0,4);
		S->a+=			0xd;
	}
	else	if		nay	(a[0xd]=='\'')
	{	memset			(b+0xd,0,3);
		S->a+=			0xe;
	}
	else	if		nay	(a[0xe]=='\'')
	{	memset			(b+0xe,0,2);
		S->a+=			0xf;
	}
	else	if		nay	(a[0xf]=='\'')
	{	memset			(b+0xf,0,1);
		S->a+=			0x10;
	}
	else
	{	S->a+=			0x11;
	}
}

static	inline	void	quote2		(PARSE_DATA *S)
{	selfy				(S);
	uint8_t		*b=
	vless				(S);
	S->D+=				0x10;
	S->P->op=			varconstop;
	S->P->value.b=			'"';
	S->P++;
	uint8_t		*a=		S->a;

	if			nay	(a[0]=='"')
	{	S->a+=			1;
	}
	else	if		nay	(a[1]=='"')
	{	memcpy			(b,a,1);
		S->a+=			2;
	}
	else	if		nay	(a[2]=='"')
	{	memcpy			(b,a,2);
		S->a+=			3;
	}
	else	if		nay	(a[3]=='"')
	{	memcpy			(b,a,4);
		memset			(b+3,0,1);
		S->a+=			4;
	}
	else	if		nay	(a[4]=='"')
	{	memcpy			(b,a,4);
		S->a+=			5;
	}
	else	if		nay	(a[5]=='"')
	{	memcpy			(b,a,5);
		S->a+=			6;
	}
	else	if		nay	(a[6]=='"')
	{	memcpy			(b,a,6);
		S->a+=			7;
	}
	else	if		nay	(a[7]=='"')
	{	memcpy			(b,a,8);
		memset			(b+7,0,1);
		S->a+=			8;
	}
	else	if		nay	(a[8]=='"')
	{	memcpy			(b,a,8);
		S->a+=			9;
	}
	else	if		nay	(a[9]=='"')
	{	memcpy			(b,a,9);
		S->a+=			0xa;
	}
	else	if		nay	(a[0xa]=='"')
	{	memcpy			(b,a,0xa);
		S->a+=			0xb;
	}
	else	if			(memcpy(b,a,0x10),
				nay	(a[0xb]=='"'))
	{	memset			(b+0xb,0,5);
		S->a+=			0xc;
	}
	else	if		nay	(a[0xc]=='"')
	{	memset			(b+0xc,0,4);
		S->a+=			0xd;
	}
	else	if		nay	(a[0xd]=='"')
	{	memset			(b+0xd,0,3);
		S->a+=			0xe;
	}
	else	if		nay	(a[0xe]=='"')
	{	memset			(b+0xe,0,2);
		S->a+=			0xf;
	}
	else	if		nay	(a[0xf]=='"')
	{	memset			(b+0xf,0,1);
		S->a+=			0x10;
	}
	else
	{	S->a+=			0x11;
	}
}
#endif

__attribute__((unused))
static	inline	void	zone_done	(PARSE_DATA *S)
{	Gz.far_total=	S->far+1;
	S->L[1].func=	_ret;
	S->L[1].ln=	++S->n;
	S->L[1].zone=	S->z;
	S->L[1].arga=	S->P;
	S->L[2].func=	_ret;
	S->L[2].ln=	++S->n;
	S->L[2].zone=	S->z;
	S->L[2].arga=	S->P;
	__builtin_memcpy(S->L[1].name,"fini",4);
	__builtin_memcpy(S->L[2].name,"fini",4);
	S->L+=		3;
}

static	inline	void	zone_resize	(PARSE_DATA *S)
{

#ifdef		ZONE_MAP_RESIZE
	size_t		T,U;
	T=				(void *) S->L - (void *) S->z->part;
	U=				S->z->part_size-T;
	if			yay	(U>=0)
	{
		if			(U>(PAGE*2))
		{	S->z->part=
			remust		(S->z->part,S->z->part_size,T,MREMAP_MAYMOVE);
			S->z->part_size=T;

/*
warn	("downsized z->part_size");
*/
		}
	}
	else
	{	warnx			("z->part_size=%lx",S->z->part_size);
		warnx			("required    =%lx",T);
	}

	T=				(void *) S->P - (void *) S->z->meta;
	U=				S->z->meta_size-T;
	if			yay	(U>=0)
	{
		if			(U>(PAGE*0x10))
		if			(T>0)
		{	S->z->meta=
			remust		(S->z->meta,S->z->meta_size,T,MREMAP_MAYMOVE);
/*
warn	("downsized z->meta_size afore=%x now=%x",z->meta_size,T);
*/
			S->z->meta_size=	T;
		}
	}
	else
	{	warnx			("z->meta_size=%lx",S->z->meta_size);
		warnx			("required    =%lx",T);
	}

	T=				(void *) S->D - (void *) S->z->data;
	U=				S->z->data_size-T;
	if			yay	(U>=0)
	{
		if			(U>=(PAGE*2))
		{	S->z->data=
			remust		(S->z->data,S->z->data_size,T,MREMAP_MAYMOVE);
			S->z->data_size=	T;
/*
warn	("downsized z->data_size");
*/
		}
	}
	else
	{	warnx			("z->data_size=%lx",S->z->data_size);
		warnx			("required    =%lx",T);
	}

	T=				(void *)S->J - (void *)S->z->jump;
	U=				S->z->jump_size-T;
	if			yay	(U>=0)
	{
		if			(U>=(PAGE*2))
		{	S->z->jump=
			remust		(S->z->jump,S->z->jump_size,T,MREMAP_MAYMOVE);
			S->z->jump_size=	T;
/*
warn	("downsized z->argv_size");
*/

		}
	}
	else
	{	warnx			("z->jump_size=%lx",S->z->jump_size);
		warnx			("required    =%lx",T);
	}
#endif
/*	mprotect			(S->z->argv,S->z->argv_size,PROT_READ);
*/

	mprotect			(S->z->jump,S->z->jump_size,PROT_READ);
}

__attribute__((cold))
static		void	_ret	(void)	{ Gz.aat--;}

static		void	miss	(void);

static	inline	void	vamset	(VLESS *A)
{	A->vam=	&Gz.vam[bit128_to_bit16(A->map[0].addr)];
}

static	inline	void	farset		(PART_REFER *R, uint32_t *f)
{	(*f)++;
	uint16_t	a=
	bit128_to_bit16			(R->name);
	PART_REFER	**LR=		&Gz.farm[a];
	R->fore=			*LR;
	*LR=				R;
}

static	inline	void	nearset		(PART_REFER *R, uint32_t const f)
{	uint16_t	b=
	bit128_to_bit16			(R->name)+f;
	PART_REFER	**LR=		&Gz.nearm[b];
	R->fore=			*LR;
	*LR=				R;
}

/*
static	inline	ARGOT	**aam_get	(PART *L)
{	return				&Gz.aam[bit128_to_bit16(L->name)];
}
*/

static	inline	ARGOT	**vam_set	(PART *L)
{	VLESS		*a=		L[0].arga;
	VLESS		*e=		L[1].arga;
	do
/*	{	if		yay	(a->op==varrefop)	*/
	{	if		yay	(a->vam==NULL)
		vamset			(a);
	}	while			(++a!=e);
}

__attribute__((hot))
static	CALIGN	void	vdef0		(void)
{	PART		*L=		Gz.aat;
	vam_set				(L);
	adef0				();
}

/*
from adef0
a push bx pop bx
to remove
adef1 exists.

adef1
if called
the paragraph aligned stack pointer
is required.

A line or
a line part
when first interpreted
adef0
runs.
The argot
if not already loaded
adef1
runs.
Thus
adef1
is infrequently invoked.

By a C hacker
a mere if block
would probably be written.
However,
by proper code segregation
adef0 minimal opcode route
is significantly shortened.

By an asm hacker
the opcodes are examined and
to reduce opcode emission
the implementation
is adjusted.

In almost no places
for ia32
different source code
is being used.
However,
adef0
is frequently invoked.
Thus,
the significance
is paramount.
*/

static		void	adef1		(ARGOT **);

#if	__SIZEOF_POINTER__	==	8

/* On x86_64 20 min opcode route */
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

#else

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
#endif

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

static	inline	void	*roundx40	(void const * const a)
{	uintptr_t	b=		(uintptr_t)	a;
	b+=				0x3f;
	/* and    $0xffffffffffffffc0,%rax */
	b>>=				6;
	b<<=				6;
	return		(void *)	b;
}

static	CALIGN	ARGOT	*exetacitaddr	(void);
static		void	miss_old	(void);

__attribute__((noinline))
static	CALIGN	void	miss		(void)
{	miss_old			();
	static	ARGOT	 *a;

	if			nay	(a==NULL)
	a=	exetacitaddr		();
	a->at				();
}

__attribute__((noinline))
static	CALIGN	ARGOT	*exetacitaddr	(void)
{	const
	static	uint8_t		a[][0x10]={"exetacit","exefast",};

	ARGOT		**b=
	&Gz.aam[bit128_to_bit16		(a[0])];

	ARGOT		*c=		*b;
	while				(c)
	if			yay	(__builtin_memcmp(
					 c->name,"exetacit",0xc)==0)
	return				c;

	aload				(a[1]);

	c=				*b;
	while				(c)
	if			yay	(__builtin_memcmp(
					 c->name,"exetacit",0xc)==0)
	return				c;
	miss_old			();
}


#include	<dlfcn.h>

__attribute__((cold))
__attribute__((noinline))
noreturn
static		void	miss_old	(void)
{	ZONE	*Z=	(ZONE *)	Gz.aat->zone;
	warnx	("%s %s","dlopen",dlerror());
	errx	(1,"%s%s%s%i%s%i%s%s%s%s",
		"file ",Z->name,
		" line ",Gz.aat->ln,
		" part ",Gz.aat->part,
		"\n","For the argot \"",Gz.aat->name,
		"\" the file was not discovered.");
}

#define	mhub	Gz.mhub

static		void	equalequal_	(void);
static		void	notequal_	(void);
static		void	less_		(void);
static		void	lessequal_	(void);
static		void	more_		(void);
static		void	moreequal_	(void);

__attribute__((hot))
static	CALIGN	void	equalequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	equalequal_)	();
}

__attribute__((hot))
static	CALIGN	void	notequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	notequal_)	();
}

__attribute__((hot))
static	CALIGN	void	less		(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	less_)		();
}

__attribute__((hot))
static	CALIGN	void	lessequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	lessequal_)	();
}

__attribute__((hot))
static	CALIGN	void	more		(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	more_)		();
}

__attribute__((hot))
static	CALIGN	void	moreequal	(void)
{	mhub.v[1]->op->fromtext		(mhub.v[0]);
	(Gz.aat->func=	moreequal_)	();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	equalequal_	(void)
{	mhub.v[1]->op->equalequal	();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	notequal_	(void)
{	mhub.v[1]->op->notequal		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	less_		(void)
{	mhub.v[1]->op->less		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	lessequal_	(void)
{	mhub.v[1]->op->lessequal	();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	more_		(void)
{	mhub.v[1]->op->more		();
}

__attribute__((noinline))
__attribute__((aligned(0x20)))
static		void	moreequal_	(void)
{	mhub.v[1]->op->moreequal	();
}

__attribute__((noinline))
__attribute__((aligned(0x10)))
static	CALIGN	void	mapuse1		(VMETA *A)
{	mhub.v[0]->op->fromtext		(A);
}

__attribute__((constructor(104)))
__attribute__((aligned(0x10)))
static		void	mhub_init	(void)
{	mhub.a=		mhub.v;
}

/*
The     strange source code and
the     comments
from    reading
90%     efficiency
might   be surmised.
Guess   again.

Even    at -O3
by      the compiler
the     emitted code
is      20% to 25% optimal.

The     code
if      optimal
the     memory usage
would   be less than half
the     execution duration
would   be less than half.

But     C
is      portable
like    a portapotty.
On      every architecture
by      the C language
the     performance
can     be flushed.

With    assembly
as      compared
in      C
while   written
the     ascript parser
will    never be as fast.
But     the C compiler crap emission
is      partially mitigated.
The     ascript parser
is      faster
than    what
a       C compiler
with    average C source code
can     achieve.

Ascript,
in      C
while   written,
faster  than C
performance
can     not  become
might   be   asserted.

By      non  asm  hackers
that    assertion
can     be   made.

Beyond  the source code
to      the opcodes
the     asm hacker's view
extends.
To      achieve more palatable opcode emission,
by      the asm hacker
the     source code
is      adjusted.

The     emitted opcode composition
is      not     perfect,
but     typical C      performance
can     be      exceeded.

C       is  a mathematician's language
rather  than  performance
convenience
was     intended.

By      unrequested switch/case boundary inane checking
by      the global variable deref acquisition
by      call jmp opcode combo PLT/GOT use
by      single opcode call not shrink wrapped inane stack adjustment
by      in register value/pointer inane retention push/pop soliciting
by      much more
by      inane ABI rules
the     performance
is      wasted.

In      any  function
by      the  C      compiler
2       or   more   unrequired opcodes
can     be   emitted.

In      a 10 opcode arrangement
a       push and pop
or      add sub on rsp
if      present
20%     efficiency
IS      ALREADY LOST!
*/
