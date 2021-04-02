/*	By Kyle Sallee in 2019 copyrighted.
	From other projects source code was not copied.
	In the ascript manual page; the license is provided.
*/

/*
A common assumption follows.
The C library  provided string  functions performance and
the C compiler provided builtin functions performance
can not be exceeded.
Wrong!

More factors matter than
can be easily explained.
This comment will not explain.
An asm hacker only would comprehend
and already knows.

By Kyle Sallee's performance boosting hacks
the memory
is  over  read
is  over  written
is  corrupted.

When used
segfaults
are solicited.

Kyle Sallee's data only
is safe.
Why?
Kyle Sallee's data
awesomely     differs.
:P
Do not copy!
Kyle Sallee's performance hacks
do not use!

Rather than fully tested
some hacks
are experimental.

The  compiler emitted opcode asm
when viewed
then by kyle
what works
is   known.

The  asm reading
when unable
the  comprehension also
is   unable.
*/

#ifndef		A_STRING
#define		A_STRING

#include	<stdint.h>
#include	<string.h>

__attribute__((always_inline))
static	inline	void	var_name_copy	(uint8_t *a, uint8_t *b, uint8_t c)
{	__builtin_memcpy	(a     ,b     ,0x10);
/*	if		nay	(c>0x10)*/
	__builtin_memcpy	(a+0x10,b+0x10,0x10);
}

#if	__SIZEOF_POINTER__	==	4
__attribute__((unused))
static	CALIGN	int32_t	ascript_memcmp	(void const *a, void const *b, size_t c)
{	uint32_t	A,B;

	uintptr_t	d=		b-a;
	uint8_t		e=		c&3;
	for				(c-=e;c;a+=4,c-=4)
	if			nay	(( (A=*(int32_t *) a  ))!=
					   (B=*(int32_t *)(a+d)))
	{	return
		be32toh			(A)-
		be32toh			(B);
	}

	if			nay	(e==0)
	return				0;

	uintptr_t	f;
	f=				(uintptr_t)a&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;
	f=				(uintptr_t)(a+d)&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;

	e=				(8-e)*8;
	A=	be32toh			(*(int32_t *) a   );
	B=	be32toh			(*(int32_t *)(a+d));
	A>>=				e;
	B>>=				e;
	return				A-B;

	safe:
	A=				*(uint8_t *) a;
	B=				*(uint8_t *)(a+d);

	for				(e--;e;e--,a++)
	{	A<<=			8;	A+=	*(uint8_t *) a;
		B<<=			8;	B+=	*(uint8_t *)(a+d);
	}
	return				A-B;
}
#else
__attribute__((unused))
static	CALIGN	int64_t	ascript_memcmp	(void const *a, void const *b, size_t c)
{	uint64_t	A,B;

	uintptr_t	d=		b-a;
	uint8_t		e=		c&7;
	for				(c-=e;c;a+=8,c-=8)
	if			nay	(( (A=*(int64_t *) a  ))!=
					   (B=*(int64_t *)(a+d)))
	{	return
		be64toh			(A)-
		be64toh			(B);
	}

	if			nay	(e==0)
	return				0;

	uintptr_t	f;
	f=				(uintptr_t)a&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;
	f=				(uintptr_t)(a+d)&(PAGE-1);
	if			nay	((f+e)>PAGE)
	goto				safe;

	e=				(8-e)*8;
	A=	be64toh			(*(int64_t *) a   );
	B=	be64toh			(*(int64_t *)(a+d));
	A>>=				e;
	B>>=				e;
	return				A-B;

	safe:
	A=				*(uint8_t *) a;
	B=				*(uint8_t *)(a+d);

	for				(e--;e;e--,a++)
	{	A<<=			8;	A+=	*(uint8_t *) a;
		B<<=			8;	B+=	*(uint8_t *)(a+d);
	}
	return				A-B;
}
#endif
/*	With ascript_memcpy
	padding is not required
	with SSE2 opcodes
	memcpy implementation.

	From an argot
	when first invoked
	in the PLT/GOT from symbol name to address resolution
	must become, which is a performance hit.
	On subsequent invocation
	an opcode call opcode jmp combo executes.
	In argot fewer opcodes when required ascript_memcpy
	can be invoked.
	However, from the overhead from the register push/pop
	reduced performance can be anticipated.
	a with the difference between b and a was tried,
	but the compiler doesn't do as told!
*/

__attribute__((unused))
static	CALIGN	void	ascript_memcpy	(void *a, void const *b, size_t c)
{	if			nay	(8>=c)
	goto				tiny;

	if			nay	( c>=0x40)
	for				(;c>=0x40;a+=0x40,b+=0x40,c-=0x40)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		__builtin_memcpy	(a+0x20,b+0x20,	0x10);
		__builtin_memcpy	(a+0x30,b+0x30,	0x10);
	}

	if			nay	(c==0)
		return;

	if			nay	(c==0x20)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		return;
	}

	if			nay	(c>=0x20)
	{	__builtin_memcpy	(a,	b,	0x10);
		__builtin_memcpy	(a+0x10,b+0x10,	0x10);
		a+=			0x20;
		b+=			0x20;
		c-=			0x20;
	}

	if			nay	(c==0x10)
	{	__builtin_memcpy	(a,	b,	0x10);
		return;
	}

	if			nay	(c>0x10)
	{	__builtin_memcpy	(a,	b,	0x10);
		a+=			0x10;
		b+=			0x10;
		c-=			0x10;
	}

	tiny:
	if			nay	(c==0x8)
	{	__builtin_memcpy	(a,	b,	0x8);
		return;
	}

	if			nay	(c>0x8)
	{	__builtin_memcpy	(a,	b,	0x8);
		a+=			0x8;
		b+=			0x8;
		c-=			0x8;
	}

	if			nay	(c==0x4)
	{	__builtin_memcpy	(a,	b,	0x4);
		return;
	}

	if			nay	(c>0x4)
	{	__builtin_memcpy	(a,	b,	0x4);
		a+=			0x4;
		b+=			0x4;
		c-=			0x4;
	}

	if			nay	(c>=0x2)
	{	__builtin_memcpy	(a,	b,	0x2);
		a+=			0x2;
		b+=			0x2;
		c-=			0x2;
	}

	if			nay	(c>0)
	{	__builtin_memcpy	(a,	b,	0x1);
	}
}

/* By memcpya between speed and size a good compromise is provided.
   By memcpya by 15 bytes the source can be overread.
   By memcpya by 15 bytes the target can be overwritten.

Changed.
By memcpya 8 bytes source/target can be overread/overwritten.
*/

/* 8>=t when so the 4 opcode route, the best performance, becomes. */
/* fast, small, must pad, nocall */
__attribute__((unused))
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpya		(void *a,void const *b,size_t c)
{/*	if	yay	(8   >=c)	__builtin_memcpy	(a,b,8);*/
/*	else */
	__builtin_memcpy(a     ,b     ,0x10);if	yay	(0x10>=c)	return;
	__builtin_memcpy(a+0x10,b+0x10,0x10);if	nay	(0x20>=c)	return;
	__builtin_memcpy(a+0x20,b+0x20,0x10);if	nay	(0x30>=c)	return;
	__builtin_memcpy(a+0x30,b+0x30,0x10);if	nay	(0x40>=c)	return;
	__builtin_memcpy(a+0x40,b+0x40,c-0x40);
}

/* 8>=c when so the 4 opcode route, the best performance, becomes. */
/* fast, small, must pad, nocall */
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpya_slower		(void *a,void const *b,size_t c)
{	__builtin_memcpy			(a,b,8);
	if				yay	(8>=c)
	return;
	__builtin_memcpy			(a+8,b+8,8);
	if				nay	(0x10>=c)
	return;
	__builtin_memcpy			(a+0x10,b+0x10,0x10);
	if				nay	(0x20>=c)
	return;
	__builtin_memcpy			(a+0x20,b+0x20,0x10);
	if				nay	(0x30>=c)
	return;
	__builtin_memcpy			(a+0x30,b+0x30,0x10);
	if				nay	(0x40>=c)
	return;

	void		*e=			a+c;
	uintptr_t	d=			b-a;
	a+=					0x40;
	intptr_t	f=			e-a;

	if				nay	(f>0x80)
	{	e-=				0x80;
		for				(;e>a;a+=0x40)
		{	__builtin_memcpy	(a     ,a+d     ,0x10);
			__builtin_memcpy	(a+0x10,a+d+0x10,0x10);
			__builtin_memcpy	(a+0x20,a+d+0x20,0x10);
			__builtin_memcpy	(a+0x30,a+d+0x30,0x10);
		}
		e+=				0x80;
		f=				e-a;
	}

	if				nay	(f>0x40)
	{	e-=				0x40;
		for				(;e>a;a+=0x10)
		__builtin_memcpy		(a, a+d, 0x10);
		e+=				0x40;
	}

	if	nay	(f>0x30)	__builtin_memcpy(a+0x30,a+d+0x30,0x10);
	if	nay	(f>0x20)	__builtin_memcpy(a+0x20,a+d+0x20,0x10);
	if	nay	(f>0x10)	__builtin_memcpy(a+0x10,a+d+0x10,0x10);
	if	nay	(f>0)		__builtin_memcpy(a     ,a+d     ,0x10);

/*	By   the compiler
	the  if  branches
	are      properly stacked.
	Thus the first conditional pair
	when so
	the      other conditional pairs
	do   not execute.
*/
}

/*
To value 0 possible trailing bytes are set.
A variable name
when set
and non zero trailing bytes
when possible
memcpyt is best.
memcpyt could be significantly improved.
*/
/* small, must pad, nocall */
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpyt		(void *a,void const *b,size_t t)
{	memcpya				(a,b,t);
	memset				(a+t,0,0x10);
/*	void	* const	c=		a+t;
	do
	{	__builtin_memcpy	(a,b,0x10);
		a+=			0x10;
		b+=			0x10;
	}
	while				(c>a);
	memset				(c,0,0x10);
*/
}


/* fast, small, must pad, nocall */
/* Best when 0x10>=t */
/* slower when 0x8>=t */
/*
__attribute__((unused))
static	inline	void	memcpya_afore	(void *a, void const *b, size_t t)
{	__builtin_memcpy		(a,b,0x10);
	if			yay	(0x10>=t)
	return;

	void	const	*c=		a+t-0x10;
	do
	{	a+=			0x10;
		b+=			0x10;
		__builtin_memcpy	(a,b,0x10);
	}	while			(c>=a);
}
*/


#if	__SIZEOF_POINTER__	==	8
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpyaa	(void *a,void const *b,size_t c)
{	memcpya				(a,b,c);
}
#else

/* fast, small, must pad, nocall */
/* 4>=t when probable memcpyaa is best */
/* To mov a single unicode value or append a line feed byte
   a 4 byte mov suffices
   Good for ia32 and it's 4 byte pointers.
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpyaa	(void *a,void const *b,size_t c)
{	memcpya				(a,b,c);
}
#endif

/* memcpyb requires revision, not good enough yet */

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpyb	(void *a,void const *b,size_t t)
{	size_t		s=		0;

	do
	{	__builtin_memcpy	(a+s,b+s,0x10);
		s+=			0x10;
	}	while			(t>s);
}

/* When t>0x40 by memcpyb best performance becomes */
/* slow, large, no call, no pad */
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpyb_old	(void *a,void const *b,size_t t)
{	uintptr_t	c=		b-a;
	void		*d=		a+t;

	for				(;(d-a)>=0x40;a+=0x40)
	{	__builtin_memcpy	(a     ,a+c     ,0x10);
		__builtin_memcpy	(a+0x10,a+c+0x10,0x10);
		__builtin_memcpy	(a+0x20,a+c+0x20,0x10);
		__builtin_memcpy	(a+0x30,a+c+0x30,0x10);
	}

	for				(;(d-a)>=0x10;a+=0x10)
	__builtin_memcpy		(a,a+c,0x10);

	if			nay	((d-a)>=8)
	{	__builtin_memcpy	(a,a+c,8);
		a+=			8;
	}

	if			nay	((d-a)>=4)
	{	__builtin_memcpy	(a,a+c,4);
		a+=			4;
	}

	if			nay	((d-a)>=2)
	{	__builtin_memcpy	(a,a+c,2);
		a+=			2;
	}

	if			nay	((d-a)==1)
	{	__builtin_memcpy	(a,a+c,1);
	}
}

/* When t>8 best performance becomes */
/* fast, small, must pad, nocall */
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpyc		(void *a,void const *b,size_t t)
{	void	* const	c=		a+t;

	do
	{	__builtin_memcpy	(a,b,0x10);
		a+=			0x10;
		b+=			0x10;
	}	while			(c>a);
}

/* When t>0x40 by memcpyd best performance becomes */
/* medium speed, medium size, no call, must pad */

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpyd		(void *a,void const *b,size_t c)
{	void		*d=		a+c;
	uintptr_t	e=		b-a;

	do
	{	__builtin_memcpy	(a     ,a+e     ,0x10);
		__builtin_memcpy	(a+0x10,a+e+0x10,0x10);
		__builtin_memcpy	(a+0x20,a+e+0x20,0x10);
		__builtin_memcpy	(a+0x30,a+e+0x30,0x10);
		a+=			0x40;
	}
	while				(d>a);
}

/* small, calls, at least in source and dest must pad */
/* memcpye is only good when in the caller function the push and pop
   are already unavoidable.
*/

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	memcpye		(void *a,void const *b,size_t c)
{	__builtin_memcpy		(a,b,8);
	if			yay	(8>=c)
	return;
	__builtin_memcpy		(a+8,b+8,8);
	if			yay	(0x10>=c)
	return;
	memcpy				(a+0x10,b+0x10,c-0x10);
}

/* most strings are 64 bytes or less */
/* fast, no pad, no call, large */
__attribute__((always_inline))
static	inline	size_t	bytelen		(uint8_t const *a,uint8_t const b)
{	{	if		nay	(a[0]==b)	return	0;
		if		nay	(a[1]==b)	return	1;
		if		nay	(a[2]==b)	return	2;
		if		nay	(a[3]==b)	return	3;
		if		nay	(a[4]==b)	return	4;
		if		nay	(a[5]==b)	return	5;
		if		nay	(a[6]==b)	return	6;
		if		nay	(a[7]==b)	return	7;
		if		nay	(a[8]==b)	return	8;
		if		nay	(a[9]==b)	return	9;
		if		nay	(a[0xa]==b)	return	0xa;
		if		nay	(a[0xb]==b)	return	0xb;
		if		nay	(a[0xc]==b)	return	0xc;
		if		nay	(a[0xd]==b)	return	0xd;
		if		nay	(a[0xe]==b)	return	0xe;
		if		nay	(a[0xf]==b)	return	0xf;
		if		nay	(a[0x10]==b)	return	0x10;
		if		nay	(a[0x11]==b)	return	0x11;
		if		nay	(a[0x12]==b)	return	0x12;
		if		nay	(a[0x13]==b)	return	0x13;
		if		nay	(a[0x14]==b)	return	0x14;
		if		nay	(a[0x15]==b)	return	0x15;
		if		nay	(a[0x16]==b)	return	0x16;
		if		nay	(a[0x17]==b)	return	0x17;
		if		nay	(a[0x18]==b)	return	0x18;
		if		nay	(a[0x19]==b)	return	0x19;
		if		nay	(a[0x1a]==b)	return	0x1a;
		if		nay	(a[0x1b]==b)	return	0x1b;
		if		nay	(a[0x1c]==b)	return	0x1c;
		if		nay	(a[0x1d]==b)	return	0x1d;
		if		nay	(a[0x1e]==b)	return	0x1e;
		if		nay	(a[0x1f]==b)	return	0x1f;
		if		nay	(a[0x20]==b)	return	0x20;
		if		nay	(a[0x21]==b)	return	0x21;
		if		nay	(a[0x22]==b)	return	0x22;
		if		nay	(a[0x23]==b)	return	0x23;
		if		nay	(a[0x24]==b)	return	0x24;
		if		nay	(a[0x25]==b)	return	0x25;
		if		nay	(a[0x26]==b)	return	0x26;
		if		nay	(a[0x27]==b)	return	0x27;
		if		nay	(a[0x28]==b)	return	0x28;
		if		nay	(a[0x29]==b)	return	0x29;
		if		nay	(a[0x2a]==b)	return	0x2a;
		if		nay	(a[0x2b]==b)	return	0x2b;
		if		nay	(a[0x2c]==b)	return	0x2c;
		if		nay	(a[0x2d]==b)	return	0x2d;
		if		nay	(a[0x2e]==b)	return	0x2e;
		if		nay	(a[0x2f]==b)	return	0x2f;
		if		nay	(a[0x30]==b)	return	0x30;
		if		nay	(a[0x31]==b)	return	0x31;
		if		nay	(a[0x32]==b)	return	0x32;
		if		nay	(a[0x33]==b)	return	0x33;
		if		nay	(a[0x34]==b)	return	0x34;
		if		nay	(a[0x35]==b)	return	0x35;
		if		nay	(a[0x36]==b)	return	0x36;
		if		nay	(a[0x37]==b)	return	0x37;
		if		nay	(a[0x38]==b)	return	0x38;
		if		nay	(a[0x39]==b)	return	0x39;
		if		nay	(a[0x3a]==b)	return	0x3a;
		if		nay	(a[0x3b]==b)	return	0x3b;
		if		nay	(a[0x3c]==b)	return	0x3c;
		if		nay	(a[0x3d]==b)	return	0x3d;
		if		nay	(a[0x3e]==b)	return	0x3e;
		if		nay	(a[0x3f]==b)	return	0x3f;
	}

	size_t		c;
	for				(a+=0x40,c=0x40;1;a+=0x40,c+=0x40)
	{	if		nay	(a[0]==b)	return	c;
		if		nay	(a[1]==b)	return	c+1;
		if		nay	(a[2]==b)	return	c+2;
		if		nay	(a[3]==b)	return	c+3;
		if		nay	(a[4]==b)	return	c+4;
		if		nay	(a[5]==b)	return	c+5;
		if		nay	(a[6]==b)	return	c+6;
		if		nay	(a[7]==b)	return	c+7;
		if		nay	(a[8]==b)	return	c+8;
		if		nay	(a[9]==b)	return	c+9;
		if		nay	(a[0xa]==b)	return	c+0xa;
		if		nay	(a[0xb]==b)	return	c+0xb;
		if		nay	(a[0xc]==b)	return	c+0xc;
		if		nay	(a[0xd]==b)	return	c+0xd;
		if		nay	(a[0xe]==b)	return	c+0xe;
		if		nay	(a[0xf]==b)	return	c+0xf;
		if		nay	(a[0x10]==b)	return	c+0x10;
		if		nay	(a[0x11]==b)	return	c+0x11;
		if		nay	(a[0x12]==b)	return	c+0x12;
		if		nay	(a[0x13]==b)	return	c+0x13;
		if		nay	(a[0x14]==b)	return	c+0x14;
		if		nay	(a[0x15]==b)	return	c+0x15;
		if		nay	(a[0x16]==b)	return	c+0x16;
		if		nay	(a[0x17]==b)	return	c+0x17;
		if		nay	(a[0x18]==b)	return	c+0x18;
		if		nay	(a[0x19]==b)	return	c+0x19;
		if		nay	(a[0x1a]==b)	return	c+0x1a;
		if		nay	(a[0x1b]==b)	return	c+0x1b;
		if		nay	(a[0x1c]==b)	return	c+0x1c;
		if		nay	(a[0x1d]==b)	return	c+0x1d;
		if		nay	(a[0x1e]==b)	return	c+0x1e;
		if		nay	(a[0x1f]==b)	return	c+0x1f;
		if		nay	(a[0x20]==b)	return	c+0x20;
		if		nay	(a[0x21]==b)	return	c+0x21;
		if		nay	(a[0x22]==b)	return	c+0x22;
		if		nay	(a[0x23]==b)	return	c+0x23;
		if		nay	(a[0x24]==b)	return	c+0x24;
		if		nay	(a[0x25]==b)	return	c+0x25;
		if		nay	(a[0x26]==b)	return	c+0x26;
		if		nay	(a[0x27]==b)	return	c+0x27;
		if		nay	(a[0x28]==b)	return	c+0x28;
		if		nay	(a[0x29]==b)	return	c+0x29;
		if		nay	(a[0x2a]==b)	return	c+0x2a;
		if		nay	(a[0x2b]==b)	return	c+0x2b;
		if		nay	(a[0x2c]==b)	return	c+0x2c;
		if		nay	(a[0x2d]==b)	return	c+0x2d;
		if		nay	(a[0x2e]==b)	return	c+0x2e;
		if		nay	(a[0x2f]==b)	return	c+0x2f;
		if		nay	(a[0x30]==b)	return	c+0x30;
		if		nay	(a[0x31]==b)	return	c+0x31;
		if		nay	(a[0x32]==b)	return	c+0x32;
		if		nay	(a[0x33]==b)	return	c+0x33;
		if		nay	(a[0x34]==b)	return	c+0x34;
		if		nay	(a[0x35]==b)	return	c+0x35;
		if		nay	(a[0x36]==b)	return	c+0x36;
		if		nay	(a[0x37]==b)	return	c+0x37;
		if		nay	(a[0x38]==b)	return	c+0x38;
		if		nay	(a[0x39]==b)	return	c+0x39;
		if		nay	(a[0x3a]==b)	return	c+0x3a;
		if		nay	(a[0x3b]==b)	return	c+0x3b;
		if		nay	(a[0x3c]==b)	return	c+0x3c;
		if		nay	(a[0x3d]==b)	return	c+0x3d;
		if		nay	(a[0x3e]==b)	return	c+0x3e;
		if		nay	(a[0x3f]==b)	return	c+0x3f;
	}
}

/* fast, no pad, no call, large */
__attribute__((unused))
__attribute__((always_inline))
static	inline	size_t	strlena	(uint8_t const *a)
{	return	bytelen		(a,0);
}

/* slow, no pad, no call */
__attribute__((unused))
__attribute__((always_inline))
static	inline	size_t	strlenb		(uint8_t const *a)
{	uint8_t	const	*b;
	for		(b=a;*b;b++);
	return		b-a;
}


#include	<endian.h>
/* fast, nocall */
/*
With function memcmp as compared
the  function memcmpa
is almost invariably faster
The total length
at compile time
if known
if known and
1, 2, 4, or 8
__builtin_memcmp
might be faster.
*/


#if	__SIZEOF_POINTER__	==	4
__attribute__((unused))
__attribute__((always_inline))
static	inline	int	memcmpa		(void   const *a,
					 void   const *b,
					 size_t const  c)
{	size_t			d=	0;

	for				(;(c-d)>=4;d+=4)
	if			nay	(*(uint32_t *)(a+d)!=
					 *(uint32_t *)(b+d))
	return
	htobe32				(*(uint32_t *)(a+d))-
	htobe32				(*(uint32_t *)(b+d));
	if				(c==d)
	return				0;

	int8_t			e;
	for				(;c>d;d++)
	{	e=			*(uint8_t *)(a+d)-
					*(uint8_t *)(b+d);
		if		nay	(e!=0)
		return			e;
	}
	return				0;
}
#else
__attribute__((unused))
__attribute__((always_inline))
static	inline	int64_t	memcmpa		(void   const *a,
					 void   const *b,
					 size_t const  c)
{	size_t			d=	0;

	for				(;(c-d)>=8;d+=8)
	if			nay	(*(uint64_t *)(a+d)!=
					 *(uint64_t *)(b+d))
	return
	htobe64				(*(uint64_t *)(a+d))-
	htobe64				(*(uint64_t *)(b+d));
	if				(c==d)
	return				0;

	int8_t			e;
	for				(;c>d;d++)
	{	e=			*(uint8_t *)(a+d)-
					*(uint8_t *)(b+d);
		if		nay	(e!=0)
		return			e;
	}
	return				0;
}
#endif


__attribute__((unused))
__attribute__((always_inline))
static	inline	void	*memchra	(void     const *a,
					 uint8_t  const  b,
					 uint32_t const  c)
{	void	const	*e=		a+c;
	for				(;e>a;a++)
	if			nay	(*(uint8_t *)a==b)
	return				(void *)	a;
	return				NULL;
}

#define	mcb(d)	if	nay	(((uint8_t *)a)[(d)]==b)	return	(void *)a+(d)

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	*memchrb	(void    const *a,
					 uint8_t const  b,
					 uint32_t       c)
{	for			(;c>=0x40;a+=0x40,c-=0x40)
	{	mcb		(0x00);
		mcb		(0x01);
		mcb		(0x02);
		mcb		(0x03);
		mcb		(0x04);
		mcb		(0x05);
		mcb		(0x06);
		mcb		(0x07);
		mcb		(0x08);
		mcb		(0x09);
		mcb		(0x0a);
		mcb		(0x0b);
		mcb		(0x0c);
		mcb		(0x0d);
		mcb		(0x0e);
		mcb		(0x0f);
		mcb		(0x10);
		mcb		(0x11);
		mcb		(0x12);
		mcb		(0x13);
		mcb		(0x14);
		mcb		(0x15);
		mcb		(0x16);
		mcb		(0x17);
		mcb		(0x18);
		mcb		(0x19);
		mcb		(0x1a);
		mcb		(0x1b);
		mcb		(0x1c);
		mcb		(0x1d);
		mcb		(0x1e);
		mcb		(0x1f);
		mcb		(0x20);
		mcb		(0x21);
		mcb		(0x22);
		mcb		(0x23);
		mcb		(0x24);
		mcb		(0x25);
		mcb		(0x26);
		mcb		(0x27);
		mcb		(0x28);
		mcb		(0x29);
		mcb		(0x2a);
		mcb		(0x2b);
		mcb		(0x2c);
		mcb		(0x2d);
		mcb		(0x2e);
		mcb		(0x2f);
		mcb		(0x30);
		mcb		(0x31);
		mcb		(0x32);
		mcb		(0x33);
		mcb		(0x34);
		mcb		(0x35);
		mcb		(0x36);
		mcb		(0x37);
		mcb		(0x38);
		mcb		(0x39);
		mcb		(0x3a);
		mcb		(0x3b);
		mcb		(0x3c);
		mcb		(0x3d);
		mcb		(0x3e);
		mcb		(0x3f);
	}
	if			(c>0)
	return	memchra		(a,b,c);
	else
	return			NULL;
}

/* By __builtin_memchr the memchr function is invoked */
/* fast, nocall */
__attribute__((unused))
__attribute__((always_inline))
static	inline	void	*memmema		(void const *a, size_t       A,
						 void const *b, size_t const B)
{	uint8_t	const	c=			*(uint8_t *)	b;
	void	const	*d=			a+A;
	size_t		e;
	int64_t		f;

	while				(d>a)
	{	a=	memchra		(a,c,d-a);
		if		nay	(a==NULL)	return	NULL;
		e=			d-a;
		if		nay	(B>=e)		return	NULL;
		f=	memcmpa		(a,b,B);
		if		nay	(f==0)		return	(void *) a;
		a++;
	}
}

__attribute__((unused))
__attribute__((always_inline))
static	inline	void	*memmemb	(void const *a, size_t       A
					,void const *b, size_t const B)
{	uint8_t	const	c=		*(uint8_t *)	b;
	void	const	*d=		a+A;
	size_t		e;
	int64_t		f;

	while				(d>a)
	{	a=	memchrb		(a,c,d-a);
		if		nay	(a==NULL)	return	NULL;
		e=			d-a;
		if		nay	(B>e)		return	NULL;
		f=	memcmpa		(a,b,B);
		if		nay	(f==0)		return	(void *) a;
		a++;
	}
}

/* fast, nocall */
/* do not use because in memcmpb by __builtin_memcmp actual memcmp is called */
/*
__attribute__((unused))
static		void	*memmemb	(void const *a, size_t       A,
					 void const *b, size_t const B)
{	uint8_t		c=			*(uint8_t *)	b;
	void		*d;
	int64_t		e;

	while					(1)
	{	d=	memchra	(a,c,A);
		if	nay		(d==NULL)	return	NULL;
		A=				A-(d-a);
		if	nay		(B>A)		return	NULL;
		e=	memcmpb			(d,b,B);
		if	nay		(e==0)		return	d;
		a=				d+1;
		A--;
	}
}
*/

/* no call */
__attribute__((unused))
__attribute__((always_inline))
static	inline	size_t	strcpya		(uint8_t * const d,uint8_t const * const s)
{	size_t
	t=	strlenb	(s);
	memcpyb		(d,s,t+1);
	return		t;
}

/* no call */
__attribute__((unused))
static	inline	size_t	strncpya	(uint8_t * const d,uint8_t const * const s,size_t const m)
{	size_t		t=
	strlenb		(s);
	if		(m>t);
	else
	t=		m-1;
	memcpyb		(d,s,t);
	d[t]=		0;
	return		t;
}

/* not quite ideal */
/* no call */
__attribute__((unused))
__attribute__((always_inline))
static	inline	int	strcmpa			(const char *a,const char *b)
{	int		A,B;

	while					(1)
	{	A=				*a;
		B=				*b;
		A-=				B;
		if				(A==0)
		{	if			(B!=0)
			{	a++;
				b++;
			}
			else
			return			0;
		}
		else
		return				A;
	}
}

/* padding not required return 0 if same */
__attribute__((unused))
__attribute__((always_inline))
static	inline	uint8_t	samebytexor(void   const *a,
				 void   const *b,
				 size_t const c,
				 size_t const d)
{	if		nay	(c!=d)
	return			1;
	size_t		e=	c;

	uint64_t	f;
	if		nay	( e>=0x40)
	for			(;e>=0x40;e-=0x40,a+=0x40,b+=0x40)
	{	f=		(*(uint64_t *)(a     )^*(uint64_t *)(b));
		f|=		(*(uint64_t *)(a+8   )^*(uint64_t *)(b+8));
		f|=		(*(uint64_t *)(a+0x10)^*(uint64_t *)(b+0x10));
		f|=		(*(uint64_t *)(a+0x18)^*(uint64_t *)(b+0x18));
		f|=		(*(uint64_t *)(a+0x20)^*(uint64_t *)(b+0x20));
		f|=		(*(uint64_t *)(a+0x28)^*(uint64_t *)(b+0x28));
		f|=		(*(uint64_t *)(a+0x30)^*(uint64_t *)(b+0x30));
		f|=		(*(uint64_t *)(a+0x38)^*(uint64_t *)(b+0x38));
		if	nay	(f!=0)
		return		1;
	}

/* The compiler tracks what values e can not longer be */

	if			(e>=8)
	{	if	nay	(*(uint64_t *)(a)!=
				 *(uint64_t *)(b))	return	1;
	}
	if			(e>=0x10)
	{	if	nay	(*(uint64_t *)(a+8)!=
				 *(uint64_t *)(b+8))	return	1;
	}
	if			(e>=0x18)
	{	if	nay	(*(uint64_t *)(a+0x10)!=
				 *(uint64_t *)(b+0x10))	return	1;
	}
	if			(e>=0x20)
	{	if	nay	(*(uint64_t *)(a+0x18)!=
				 *(uint64_t *)(b+0x18))	return	1;
	}
	if			(e>=0x28)
	{	if	nay	(*(uint64_t *)(a+0x20)!=
				 *(uint64_t *)(b+0x20))	return	1;
	}
	if			(e>=0x30)
	{	if	nay	(*(uint64_t *)(a+0x28)!=
				 *(uint64_t *)(b+0x28))	return	1;
	}
	if			(e>=0x38)
	{	if	nay	(*(uint64_t *)(a+0x30)!=
				 *(uint64_t *)(b+0x30))	return	1;
	}

/*
With the e>=8 check
     the e>7 check
is   combined.
*/

	if		yay	(e>7)
	{	size_t	f=	e&~7;
		e&=		7;
		a+=		f;
		b+=		f;
	}

/*
8>e
the the e>=8 check only
is executed.
*/

	if			(e>=4)
	{	if	nay	(*(uint32_t *)(a)!=
				 *(uint32_t *)(b))	return	1;
		a+=		4;
		b+=		4;
		e-=		4;
	}
	if			(e>=2)
	{	if	nay	(*(uint16_t *)(a)!=
				 *(uint16_t *)(b))	return	1;
		a+=		2;
		b+=		2;
		e-=		2;
	}

	if			(e!=0)
	{	if	nay	(*(uint8_t *)(a)!=
				 *(uint8_t *)(b))	return	1;
	}
	return			0;
}


/* samebyte requires less opcode execution but is not faster than memcmp */

/* padding not required return 0 if same */
/* slower than memcmp */
__attribute__((unused))
__attribute__((always_inline))
static	inline	uint8_t	samebyte(void   const *a,
				 void   const *b,
				 size_t const c,
				 size_t const d)
{	if		nay	(c!=d)
	return			1;
	size_t		e=	c;

	if		nay	( e>=0x40)
	for			(;e>=0x40;e-=0x40,a+=0x40,b+=0x40)
	{	if	nay	(*(uint64_t *)(a)!=
				 *(uint64_t *)(b))	return	1;
		if	nay	(*(uint64_t *)(a+8)!=
				 *(uint64_t *)(b+8))	return	1;
		if	nay	(*(uint64_t *)(a+0x10)!=
				 *(uint64_t *)(b+0x10))	return	1;
		if	nay	(*(uint64_t *)(a+0x18)!=
				 *(uint64_t *)(b+0x18))	return	1;
		if	nay	(*(uint64_t *)(a+0x20)!=
				 *(uint64_t *)(b+0x20))	return	1;
		if	nay	(*(uint64_t *)(a+0x28)!=
				 *(uint64_t *)(b+0x28))	return	1;
		if	nay	(*(uint64_t *)(a+0x30)!=
				 *(uint64_t *)(b+0x30))	return	1;
		if	nay	(*(uint64_t *)(a+0x38)!=
				 *(uint64_t *)(b+0x38))	return	1;
	}

/* The compiler tracks what values e can not longer be */

	if			(e>=8)
	{	if	nay	(*(uint64_t *)(a)!=
				 *(uint64_t *)(b))	return	1;
	}
	if			(e>=0x10)
	{	if	nay	(*(uint64_t *)(a+8)!=
				 *(uint64_t *)(b+8))	return	1;
	}
	if			(e>=0x18)
	{	if	nay	(*(uint64_t *)(a+0x10)!=
				 *(uint64_t *)(b+0x10))	return	1;
	}
	if			(e>=0x20)
	{	if	nay	(*(uint64_t *)(a+0x18)!=
				 *(uint64_t *)(b+0x18))	return	1;
	}
	if			(e>=0x28)
	{	if	nay	(*(uint64_t *)(a+0x20)!=
				 *(uint64_t *)(b+0x20))	return	1;
	}
	if			(e>=0x30)
	{	if	nay	(*(uint64_t *)(a+0x28)!=
				 *(uint64_t *)(b+0x28))	return	1;
	}
	if			(e>=0x38)
	{	if	nay	(*(uint64_t *)(a+0x30)!=
				 *(uint64_t *)(b+0x30))	return	1;
	}

/*
With the e>=8 check
     the e>7 check
is   combined.
*/

	if		yay	(e>7)
	{	size_t	f=	e&~7;
		e&=		7;
		a+=		f;
		b+=		f;
	}

/*
8>e
the the e>=8 check only
is executed.
*/

	if			(e>=4)
	{	if	nay	(*(uint32_t *)(a)!=
				 *(uint32_t *)(b))	return	1;
		a+=		4;
		b+=		4;
		e-=		4;
	}
	if			(e>=2)
	{	if	nay	(*(uint16_t *)(a)!=
				 *(uint16_t *)(b))	return	1;
		a+=		2;
		b+=		2;
		e-=		2;
	}

	if			(e!=0)
	{	if	nay	(*(uint8_t *)(a)!=
				 *(uint8_t *)(b))	return	1;
	}
	return			0;
}
#endif
